
#include "stm8s_conf.h"
#include "Global.h"
#include "Si4431Api.h"

//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：Si4431的SPI写时序
//****************************************************************************************************/
u8 SPI1_RW(u8 Data)
{
	SPI_SendData(Data);
	while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	Data = SPI_ReceiveData();
  return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
u8 SPI1_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI1_CSN_L;			//NSS拉低		// CSN low, init SPI transaction                  
	status = SPI1_RW(Reg);      // select register
	SPI1_RW(Data);             // ..and write value to it..                  
	SPI1_CSN_H;			//NSS拉高，关闭SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

u8 SPI1_Read(u8 Reg)
{
	u8 Reg_val;
	SPI1_CSN_L;			//NSS拉低
	SPI1_RW(Reg);            // Select register to read from..
	Reg_val = SPI1_RW(0);    // ..then read registervalue
	SPI1_CSN_H;			//NSS拉高，关闭SPI
	return(Reg_val);        // return register value
}

u16 SPI1_RWWord(u16 Reg)
{
	u16 temp16;
	SPI1_CSN_L;			//NSS拉低	// Set CSN low, init SPI tranaction = 0;						
	temp16  = (u16) (SPI1_RW( (u8)((Reg & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (u16) (SPI1_RW( (u8)(Reg & 0x00FF) ));
	SPI1_CSN_H;			//NSS拉高，关闭SPI	// Set CSN high again;
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
{ u8 TmpRegVal;                  
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//(07h)寄存器软复位
 	
	while ( GPIO_ReadInputPin(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI1_Read(InterruptStatus1);	//(03h)清中断
	SPI1_Read(InterruptStatus2);	//(04h)

	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);			//(06h)关闭所有中断
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), RF22_PWRSTATE_READY);	//(07h)空闲模式

	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//(09h)30M晶振的调谐电容为12.5P
	TmpRegVal = SPI1_Read(CrystalOscillatorLoadCapacitance);						//读寄存器，检查是否设置正确

	SPI1_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);						//(0Ah)GPIO输出2M时钟
	SPI1_RWReg((REG_WRITE | GPIO0Configuration), 0x12);								//(0Bh)GPIO_0 发射模式
	SPI1_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 							//(0Ch)GPIO_1 接收数据
	SPI1_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 							//(0Dh)GPIO_2 接收模式	
	SPI1_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							//(0Eh)gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI1_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//(70h)不使用曼彻斯特编码 没有白化 

	SPI1_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x40);						//(1Dh)使能AFC

	//TX发射速率9600BPS
	SPI1_RWReg((REG_WRITE | IFFilterBandwidth), 0x1e); 						//(1Ch)BW=90kHZ
	SPI1_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xd0);			//(20h)calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x00);					//(21h)rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x9d);					//(22h)ncoff =5033 = 0x13a9
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset0), 0x49);					//(23h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);			//(24h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x45);			//(25h)0x0a
	SPI1_RWReg((REG_WRITE | 0x2a), 0x20);
	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x4e); 	//(6Eh)											//(6EH)9600BPS
	SPI1_RWReg((REG_WRITE | TXDataRate0), 0xa5);	//(6Fh)	  
	//case RATE_24K: // 2.4k 
//	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x13); 											//
//	SPI1_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	
	//数据包结构
	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x8D); 					//(30h)enable packet handler使能包处理, msb first, enable crc,
	SPI1_RWReg((REG_WRITE | HeaderControl1), 0xFF);						//(32h)校验checkhead3-0 4位接收地址address enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3
	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x42); 					//(33h)header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
	
	SPI1_RWReg((REG_WRITE | PreambleLength), 64);   					//(34h)引导头长度 // 64 nibble = 32byte preamble
	SPI1_RWReg((REG_WRITE | PreambleDetectionControl), 0x20); 			//(35h)need to detect 20bit preamble
	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);							//(36h)// synchronize word						//(36h)同步头
	SPI1_RWReg((REG_WRITE | SyncWord2), 0xa4);							//(37h)						
	SPI1_RWReg((REG_WRITE | SyncWord1), 0x00);							//(38h)
	SPI1_RWReg((REG_WRITE | SyncWord0), 0x00);							//(39h)

	SPI1_RWReg((REG_WRITE | 0x3a), 's');  // tx header
	SPI1_RWReg((REG_WRITE | 0x3b), 'o');
	SPI1_RWReg((REG_WRITE | 0x3c), 'n');
	SPI1_RWReg((REG_WRITE | 0x3d), 'g');
	SPI1_RWReg((REG_WRITE | 0x3e), 17);  // total tx 17 byte
	SPI1_RWReg((REG_WRITE | 0x3f), 's'); // check hearder
	SPI1_RWReg((REG_WRITE | 0x40), 'o');
	SPI1_RWReg((REG_WRITE | 0x41), 'n');
	SPI1_RWReg((REG_WRITE | 0x42), 'g');
	SPI1_RWReg((REG_WRITE | 0x43), 0xff);  // all the bit to be checked
	SPI1_RWReg((REG_WRITE | 0x44), 0xff);  // all the bit to be checked
	SPI1_RWReg((REG_WRITE | 0x45), 0xff);  // all the bit to be checked
	SPI1_RWReg((REG_WRITE | 0x46), 0xff);  // all the bit to be checked

	SPI1_RWReg((REG_WRITE | TXPower), 0x03);				//(6Dh)1db发射
	SPI1_RWReg((REG_WRITE | FrequencyHoppingChannelSelect), 0x00);  	//(79h)no hopping
	SPI1_RWReg((REG_WRITE | FrequencyHoppingStepSize), 0x00);  		//(7Ah)no hopping
	//频率设置
	                           

//	SPI1_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 			//(70H)
	SPI1_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 			//(71H)// Gfsk, fd[8] =0, no invert for Tx/Rx data, fifo mode, txclk -->gpio
	SPI1_RWReg((REG_WRITE | FrequencyDeviation), 0x48);           //(72h)// frequency deviation setting to 45k = 72*625 													
	SPI1_RWReg((REG_WRITE | FrequencyOffset),0x00); 							//(73h)
	SPI1_RWReg((REG_WRITE | FrequencyChannelControl),0x00);				//(74h)no offset

	SPI1_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    			//(75H)边带选择，低频段240-479.9M 430Mhz
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x64);  		//(76H)fc  正好434HZ
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);			//(77H)fc


	/*		
	SPI1_RWReg((REG_WRITE | TXRampControl), 0x7F); 											//(52h)Add by T.L.Steve	
	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)ready模式，Xtal
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x60);										//(50h)使能发射FIFO几乎满，几乎空中断
	        
	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);		*/
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
	u8 iLoop,TxHeaderAdr,TmpVal;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//发送帧头
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头，高位对齐	
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

  TmpVal = SPI1_Read(TransmitHeader3);
	TmpVal = SPI1_Read(TransmitHeader0);

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
{	u8 iLoop,RxCheckHeaderAdr,TmpVal;
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//接收校对地址头
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //设置接收校对地址头	
		SPI1_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  TmpVal = SPI1_Read(CheckHeader3);
	TmpVal = SPI1_Read(CheckHeader0);

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

