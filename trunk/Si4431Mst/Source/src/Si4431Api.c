
#include "stm32f10x.h"
#include "platform_config.h"
#include "Si4431Api.h"




//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：Si4431的SPI写时序
//****************************************************************************************************/

static u8 SPI1_RW(u8 Data)
{
	SPI_I2S_SendData(SPI1 , Data);
	// Wait for SPI1 data reception 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	Data = SPI_I2S_ReceiveData(SPI1);
	return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
static u8 SPI1_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI1_CSN_L;			//NSS拉低		// CSN low, init SPI transaction                  
	status = SPI1_RW(Reg);      // select register
	SPI1_RW(Data);             // ..and write value to it..                  
	SPI1_CSN_H;			//NSS拉高，关闭SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

static u8 SPI1_Read(u8 Reg)
{
	u8 Reg_val;
	SPI1_CSN_L;			//NSS拉低
	SPI1_RW(Reg);            // Select register to read from..
	Reg_val = SPI1_RW(0);    // ..then read registervalue
	SPI1_CSN_H;			//NSS拉高，关闭SPI
	return(Reg_val);        // return register value
}

static u16 SPI1_RWWord(u16 Reg)
{
	u16 temp16;
	SPI1_CSN_L;			//NSS拉低	// Set CSN low, init SPI tranaction = 0;						
	temp16  = (u16) (SPI1_RW( (u8)((Reg & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (u16) (SPI1_RW( (u8)(Reg & 0x00FF) ));
	SPI1_CSN_H;			//NSS拉高，关闭SPI	// Set CSN high again;
	return temp16;
}

/*++++++++++++++++++++++++++++++++++++++分割SPI2+++++++++++++++++++++++++++++++++++++++++++++++*/

//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：Si4431的SPI写时序
//****************************************************************************************************/

static u8 SPI2_RW(u8 Data)
{
	SPI_I2S_SendData(SPI2 , Data);
	// Wait for SPI1 data reception 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	Data = SPI_I2S_ReceiveData(SPI2);
	return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
static u8 SPI2_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI2_CSN_L;			//NSS拉低		// CSN low, init SPI transaction                  
	status = SPI2_RW(Reg);      // select register
	SPI2_RW(Data);             // ..and write value to it..                  
	SPI2_CSN_H;			//NSS拉高，关闭SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

static u8 SPI2_Read(u8 Reg)
{
	u8 Reg_val;
	SPI2_CSN_L;			//NSS拉低
	SPI2_RW(Reg);            // Select register to read from..
	Reg_val = SPI2_RW(0);    // ..then read registervalue
	SPI2_CSN_H;			//NSS拉高，关闭SPI
	return(Reg_val);        // return register value
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  unsigned short SpiReadWriteWord(unsigned short spi_in)
  +
  + DESCRIPTION:    sends and read 16 length data through the SPI port
  +
  +	INPUT:			data 
  +
  + RETURN:         received word
  +
  + NOTES:          it controls the nSEL pin
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static u16 SPI2_RWWord(u16 Reg)
{
	u16 temp16;
	SPI2_CSN_L;			//NSS拉低	// Set CSN low, init SPI tranaction = 0;						
	temp16  = (u16) (SPI2_RW( (u8)((Reg & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (u16) (SPI2_RW( (u8)(Reg & 0x00FF) ));
	SPI2_CSN_H;			//NSS拉高，关闭SPI	// Set CSN high again;
	return temp16;
}



//=============================================================================================
//说明:Si4431发射模块初始化函数
//输入:void
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_Init(void)
{                   
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//寄存器软复位
 	
	while ( GPIO_ReadOutputDataBit(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI1_Read(InterruptStatus1);	//清中断
	SPI1_Read(InterruptStatus2);

	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//关闭所有中断

	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M晶振的调谐电容为12.5P
//	SPI1_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);				//GPIO输出2M时钟
	SPI1_RWReg((REG_WRITE | GPIO0Configuration), 0x12);									//GPIO_0 发射模式
	SPI1_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 								//GPIO_1 接收数据
	SPI1_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 								//GPIO_2 接收模式	
	SPI1_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							  // gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI1_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//不使用曼彻斯特编码 没有白化 

//	SPI1_RWReg((REG_WRITE | IFFilterBandwidth), 0x1D); 								//(1Ch)BW=90kHZ
	SPI1_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x00);						//(1Dh)禁止AFC

	SPI1_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);			//(20h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x20);								//(21h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x4e);								//(22h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset0), 0xa5);								//(23h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);				//(24h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);				//(25h)0x0a
	  
	//case RATE_24K: // 2.4k 
//	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x13); 												//
//	SPI1_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	//TX发射速率9600BPS
	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x02); 												//(6EH)9600BPS
	SPI1_RWReg((REG_WRITE | TXDataRate0), 0x75);												//(6FH)

	SPI1_RWReg((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
	
	//频率设置													
	SPI1_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    						//(75H)边带选择，低频段240-479.9M 430Mhz
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x4b);  					//(76H)fc  正好433HZ
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);						//(77H)fc

	//不知道作用
	SPI1_RWReg((REG_WRITE | FrequencyDeviation), 0x20);                 //(72h)频率偏差20k                            
	SPI1_RWReg((REG_WRITE | FrequencyOffset),0x00); 										//(73h)

	SPI1_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 						//(70H)
	SPI1_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 						//(71H)直接模式 FSK调制
	//数据包结构
	SPI1_RWReg((REG_WRITE | HeaderControl1), 0x00);											//(32h)帧头
	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x02); 										//(33h)no head; sync word 3 and 2
	SPI1_RWReg((REG_WRITE | PreambleLength), 0x04);   									//(34h)引导头2 byte
	SPI1_RWReg((REG_WRITE | PreambleDetectionControl), 0x10); 					//(35h)8bit
	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)同步头
	SPI1_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
	SPI1_RWReg((REG_WRITE | SyncWord1), 0x2d);													//(36h)
	SPI1_RWReg((REG_WRITE | SyncWord0), 0xa4);													//(37h)

	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x88); 									//(30h)enable TX handling	不要CRC
	
	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)ready模式，Xtal
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x02);										//使能接收中断
	SPI1_RWReg((REG_WRITE | TXPower), 0x07);
        
	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);
}

//=============================================================================================
//说明:Si4431发射模块设置空闲模式
//输入:void
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_IdleMod(void)
{
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		// 
	//diasble all ITs
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x00);
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
  //releaze all IT flags
	SPI1_Read(InterruptStatus1);
	SPI1_Read(InterruptStatus2);
}

//=============================================================================================
//说明:Si4431发射模块设置发射模式
//输入:pTxHeader发射地址首地址；
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_TransmitMod(u8 * pTxHeader)
{
	u8 iLoop,TxHeaderAdr;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//发送帧头
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头，高位对齐	
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //中断使能包发送
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX人工接收模式，预备模式
}

//=============================================================================================
//说明:Si4431发射模块设置接收模式
//输入:pRxCheckHeader接收校对地址头	
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_ReceiveMod(u8 * pRxCheckHeader)
{	u8 iLoop,RxCheckHeaderAdr;
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//接收校对地址头
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //设置接收校对地址头	
		SPI1_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x02); 							 //中断使能接收到有效包
 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00); 

	SPI1_Read(InterruptStatus1);
	SPI1_Read(InterruptStatus2);
        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式

}

//=============================================================================================
//说明:Si4431发射模块设置发射模式检测信道是否繁忙
//输入:void
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
u8 Si4431TX_BusyCheck(void)
{
	unsigned char value;
	value =  (unsigned char)(SPI1_Read(ReceivedSignalStrengthIndicator)) ;//读信号强度寄存器
	if(value>40)
		return 0;
	else
		return 1;
}

//=============================================================================================
//说明:Si4431发射模块发送数据包
//输入:void
//输出:void
//调用:SPI1_RWReg();SPI1_Read();Si4431TX_IdleMod();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_TxPacket(unsigned char * packet, unsigned char length)
{
	u8 temp8;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	SPI1_RWReg((REG_WRITE | TransmitPacketLength), length);	 
  for(temp8=0;temp8<length;temp8++){	
		SPI1_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);		
	}
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);		
}

/********************************Si4431RX分割线****************************************/

//=============================================================================================
//说明:Si4431接收模块初始化函数
//输入:void
//输出:void
//调用:SPI2_RWReg();SPI2_Read();
//修改:2011-01-20			KEN			初定
//=============================================================================================
void Si4431RX_Init(void)
{                   
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//寄存器软复位
 	
	while ( GPIO_ReadOutputDataBit(SPI2_CTL_GPIO, SPI2_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI2_Read(InterruptStatus1);	//清中断
	SPI2_Read(InterruptStatus2);

	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//关闭所有中断

	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M晶振的调谐电容为12.5P
//	SPI2_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);				//GPIO输出2M时钟
	SPI2_RWReg((REG_WRITE | GPIO0Configuration), 0x12);									//GPIO_0 发射模式
	SPI2_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 								//GPIO_1 接收数据
	SPI2_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 								//GPIO_2 接收模式	
	SPI2_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							  // gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI2_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//不使用曼彻斯特编码 没有白化 

//	SPI2_RWReg((REG_WRITE | IFFilterBandwidth), 0x1D); 								//(1Ch)BW=90kHZ
	SPI2_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x00);						//(1Dh)禁止AFC

	SPI2_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);			//(20h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x20);								//(21h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x4e);								//(22h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset0), 0xa5);								//(23h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);				//(24h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);				//(25h)0x0a
	  
	//case RATE_24K: // 2.4k 
//	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x13); 												//
//	SPI2_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	//TX发射速率9600BPS
	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x02); 												//(6EH)9600BPS
	SPI2_RWReg((REG_WRITE | TXDataRate0), 0x75);												//(6FH)

	SPI2_RWReg((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
	
	//频率设置													
	SPI2_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    						//(75H)边带选择，低频段240-479.9M 430Mhz
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x4b);  					//(76H)fc  正好433HZ
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);						//(77H)fc

	//不知道作用
	SPI2_RWReg((REG_WRITE | FrequencyDeviation), 0x20);                 //(72h)频率偏差20k                            
	SPI2_RWReg((REG_WRITE | FrequencyOffset),0x00); 										//(73h)

	SPI2_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 						//(70H)
	SPI2_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 						//(71H)直接模式 FSK调制
	//数据包结构
	SPI2_RWReg((REG_WRITE | HeaderControl1), 0x00);											//(32h)帧头
	SPI2_RWReg((REG_WRITE | HeaderControl2), 0x02); 										//(33h)no head; sync word 3 and 2
	SPI2_RWReg((REG_WRITE | PreambleLength), 0x04);   									//(34h)引导头2 byte
	SPI2_RWReg((REG_WRITE | PreambleDetectionControl), 0x10); 					//(35h)8bit
	SPI2_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)同步头
	SPI2_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
	SPI2_RWReg((REG_WRITE | SyncWord1), 0x2d);													//(36h)
	SPI2_RWReg((REG_WRITE | SyncWord0), 0xa4);													//(37h)

	SPI2_RWReg((REG_WRITE | DataAccessControl), 0x88); 									//(30h)enable TX handling	不要CRC
	
	SPI2_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)ready模式，Xtal
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x02);										//使能接收中断
	SPI2_RWReg((REG_WRITE | TXPower), 0x07);
        
	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);
}

//=============================================================================================
//说明:Si4431接收模块设置空闲模式
//输入:void
//输出:void
//调用:SPI2_RWReg();SPI2_Read();
//修改:2011-01-20			KEN			初定
//=============================================================================================
void Si4431RX_IdleMod(void)
{
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		// 
	//diasble all ITs
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x00);
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);
  //releaze all IT flags
	SPI2_Read(InterruptStatus1);
	SPI2_Read(InterruptStatus2);
}

//=============================================================================================
//说明:Si4431接收模块设置发射模式
//输入:pTxHeader发射地址首地址；HeaderLen地址长度，，高位对齐
//输出:void
//调用:SPI2_RWReg();SPI2_Read();
//修改:2011-01-20			KEN			初定
//=============================================================================================
void Si4431RX_TransmitMod(u8 * pTxHeader)
{
	u8 iLoop,TxHeaderAdr;	
	Si4431RX_IdleMod();        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//发送帧头
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头	
		SPI2_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //中断使能包发送
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX人工接收模式，预备模式
}

//=============================================================================================
//说明:Si4431接收模块设置接收模式
//输入:pRxCheckHeader接收校对地址头	
//输出:void
//调用:SPI2_RWReg();SPI2_Read();
//修改:2011-01-21			KEN			初定
//=============================================================================================
void Si4431RX_ReceiveMod(u8 * pRxCheckHeader)
{	u8 iLoop,RxCheckHeaderAdr;
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//接收校对地址头
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //设置接收校对地址头	
		SPI2_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x02); 							 //中断使能接收到有效包
 	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00); 

	SPI2_Read(InterruptStatus1);
	SPI2_Read(InterruptStatus2);
        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式

}

//=============================================================================================
//说明:Si4431接收模块设置发射模式检测信道是否繁忙
//输入:void
//输出:void
//调用:SPI2_RWReg();SPI2_Read();
//修改:2011-01-20			KEN			初定
//=============================================================================================
u8 Si4431RX_BusyCheck(void)
{
	unsigned char value;
	value =  (unsigned char)(SPI2_Read(ReceivedSignalStrengthIndicator)) ;//读信号强度寄存器
	if(value>40)
		return 0;
	else
		return 1;
}

//=============================================================================================
//说明:Si4431接收模块发送数据包
//输入:void
//输出:void
//调用:SPI2_RWReg();SPI2_Read();Si4431RX_IdleMod();
//修改:2011-01-20			KEN			初定
//=============================================================================================
void Si4431RX_TxPacket(unsigned char * packet, unsigned char length)
{
	u8 temp8;	
	Si4431RX_IdleMod();        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	SPI2_RWReg((REG_WRITE | TransmitPacketLength), length);	 
  for(temp8=0;temp8<length;temp8++){	
		SPI2_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);		
	}
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x04);
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);		
}


