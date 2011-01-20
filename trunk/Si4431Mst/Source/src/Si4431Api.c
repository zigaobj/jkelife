
#include "stm32f10x.h"
#include "platform_config.h"
#include "Si4431Api.h"



/***********************************************************end***********************************/
u8  receives[64];
unsigned char txdata[20];
unsigned char rxdata[20];
//unsigned char   recv_flag;
u8  rlength;
unsigned int ii;

u8  rdata;
u8  n;
u8 revframe;
unsigned char  recv1[2];
unsigned char  recvdat[10];
//unsigned char recv_flag;//接收从节点反回信息标志
unsigned char send_flag;//进入接收状态标志

void Si4431_Init()
{ //unsigned int ii;


//unsigned char  kk[0x90];
/*for(ii=0;ii<0x80;ii++)
  {
kk[ii] = SPI1_Read(ii);
}*/	
   SPI1_RWReg(0x87,0x80);	  
	for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
	for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
	for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
    SPI1_RWReg(0x87,0x00);	   
	SPI1_RWReg(0x85,0x00);
	SPI1_RWReg(0x86,0x02);	  
	SPI1_RWReg(0xD1,0x00);	  
	SPI1_RWReg(0xD0,0x00);	  
   /**********************************************总线初始化*******************************/
     SPI1_RWReg(0x87,0x01);	   
    SPI1_RWReg(0xf1,0x62);   
	SPI1_RWReg(0xf5,0x73);   
	SPI1_RWReg(0xf6,0x64);   
	SPI1_RWReg(0xf7,0x00);   
    SPI1_RWReg(0xb3,0x02);   
	SPI1_RWReg(0xb4,0x18);
	SPI1_RWReg(0x9f,0x03);
	SPI1_RWReg(0xb5,0x40);
	SPI1_RWReg(0x9d,0x40);
	SPI1_RWReg(0xb6,0x2d);   
	SPI1_RWReg(0xb7,0xd4);   
	SPI1_RWReg(0x88,0x00);   
	SPI1_RWReg(0x8b,0x1f);   
	SPI1_RWReg(0x8c,0x1f);   
	SPI1_RWReg(0x8d,0x1f);   

    


}
void send_init()
{ 		u8 num2 = 1;
 
        SPI1_RWReg(0xf0,0x20);	  
        SPI1_RWReg(0xb0,0x8d);   
        SPI1_RWReg(0xf1,0x62); 
        SPI1_RWReg(0x9c,baud[num2][0]);   // IF Filter Bandwidth                         
        SPI1_RWReg(0xa0,baud[num2][1]);   // Clock Recovery Oversampling Rate
        SPI1_RWReg(0xa1,baud[num2][2]);   // Clock Recovery Offset 2
        SPI1_RWReg(0xa2,baud[num2][3]);   // Clock Recovery Offset 1
        SPI1_RWReg(0xa3,baud[num2][4]);   // Clock Recovery Offset 0
        SPI1_RWReg(0xa4,baud[num2][5]);   // Clock Recovery Timing Loop Gain 1
        SPI1_RWReg(0xa5,baud[num2][6]);   // Clock Recovery Timing Loop Gain 0
	    SPI1_RWReg(0xee,baud[num2][7]);   // Block Enable Override 2
	    SPI1_RWReg(0xef,baud[num2][8]);   // Block Enable Override 2
	    SPI1_RWReg(0xf2,baud[num2][10]);   // Frequency Deviation Setting; Fd=625Hz*fd[7:0]  
/* for(ii=0;ii<0x80;ii++)
  {
kk[ii] = SPI1_Read(ii);
}*/	

}
void send_data(unsigned char *seddat,unsigned char leng)
//void send()
{
unsigned int ii,i,ii1;
unsigned char men,s1;



    for(ii=0;ii<200;ii++);
    for(ii=0;ii<200;ii++);
	for(ii1=0;ii1<10000;ii1++);
    SPI1_RWReg(0x87,0x01);
	SPI1_RWReg(0x88,0x01);

	SPI1_RWReg(0x88,0x00);
	SPI1_RWReg(0xb3,0x02);
	SPI1_RWReg(0xbe,leng);
	for(i=0;i<leng;i++)
	{
	  men= *(seddat+i);
     
	    SPI1_RWReg(0xff,men);
	   
	 }
   
		SPI1_RWReg(0x87,0x09);//transimission starts turn on 置发射位
	 	send_flag=1;
		s1 = SPI1_Read( 0x03 );
		   s1 &= 0x04;
		   while(s1!=0x04)
		   {
		   s1 = SPI1_Read( 0x03 );
		   s1 &= 0x04;
		   }
	
// for(i=0;i<60000;i++);

 
 SPI1_CSN_H;

}


void recv_init()
{
	u8 num2 = 2;
    SPI1_RWReg(0xf0,0x20);	  
    SPI1_RWReg(0xb0,0x8d);   
    SPI1_RWReg(0xf1,0x62); 



	    SPI1_RWReg(0x9c,baud[num2][0]);   // IF Filter Bandwidth                         
        SPI1_RWReg(0xa0,baud[num2][1]);   // Clock Recovery Oversampling Rate
        SPI1_RWReg(0xa1,baud[num2][2]);   // Clock Recovery Offset 2
        SPI1_RWReg(0xa2,baud[num2][3]);   // Clock Recovery Offset 1
        SPI1_RWReg(0xa3,baud[num2][4]);   // Clock Recovery Offset 0
        SPI1_RWReg(0xa4,baud[num2][5]);   // Clock Recovery Timing Loop Gain 1
        SPI1_RWReg(0xa5,baud[num2][6]);   // Clock Recovery Timing Loop Gain 0
	    SPI1_RWReg(0xee,baud[num2][7]);   // Block Enable Override 2
	    SPI1_RWReg(0xef,baud[num2][8]);   // Block Enable Override 2
	    SPI1_RWReg(0xf2,baud[num2][10]);   // Frequency Deviation Setting; Fd=625Hz*fd[7:0]  

	SPI1_RWReg(0x88,0x02);   
	SPI1_RWReg(0x88,0x00);   
    SPI1_RWReg(0xb2,0x00);	  
	SPI1_RWReg(0xb3,0x02);	  
	SPI1_RWReg(0x87,0x05);	  	
	SPI1_RWReg(0x85,0x02);	  
    SPI1_RWReg(0x86,0xc0);	 

}

void recv_data()
{
	 u8  i;
	 u8  s1,s2;
	 u8  ch;
     revframe = 0;
     rlength = 0;
     ch = 0;
	 s1 = SPI1_Read( 0x03 ); // Interrupt status 1
	 s2 = SPI1_Read( 0x04 ); // Interrupt status 2

 	 if( (s1 & 0x02) == 0x02 )       // Check if the receive packet is valid.
	 {
	      revframe = 1;

	      SPI1_RWReg(0x87,0x01);  // Set si4432 in the READY mode
	      ch = SPI1_Read( 0x4b );    // Receive the packet length 
		  rlength = ch;

		  if(rlength == 0xff)
		  {
		      rlength = 0;
          }

	      i = 0;
          for(i=0;i<rlength;i++)
          {
               rdata=SPI1_Read( 0x7f );  // Read a byte from the fifo, 
               rxdata[i] = rdata;
           }
		   send_flag=0;   //清接收标志位
//           send_uart(rxdata,rlength);
           SPI1_CSN_H;
           SPI1_RWReg(0x88,0x02);     // Clear the RX fifo
	       SPI1_RWReg(0x88,0x00);     // The si4432 out of automatically TX state;
           SPI1_RWReg(0xb2,0x00);	 // Not broadcast address enable and No Received Header check
	       SPI1_RWReg(0xb3,0x02);	 // No TX/RX header and Synchronization Word 3 and 2;
	       SPI1_RWReg(0x87,0x05);	 // Enable RX in the receive mode
	       SPI1_RWReg(0x85,0x02);	 // When the receive packet is valid,the interrupt will be enable;
	       SPI1_RWReg(0x86,0xc0);	 // Enable Sync Word Detected and Enable Valid Preamble Detected.

	 } 
   	 

}




//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：Si4431的SPI写时序
//****************************************************************************************************/

u8 SPI1_RW(u8 Data)
{
	SPI_I2S_SendData(SPI1 , Data);
	// Wait for SPI1 data reception 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	Data = SPI_I2S_ReceiveData(SPI1);
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

/*++++++++++++++++++++++++++++++++++++++分割SPI2+++++++++++++++++++++++++++++++++++++++++++++++*/

//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：Si4431的SPI写时序
//****************************************************************************************************/

u8 SPI2_RW(u8 Data)
{
	SPI_I2S_SendData(SPI2 , Data);
	// Wait for SPI1 data reception 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	Data = SPI_I2S_ReceiveData(SPI2);
	return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
u8 SPI2_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI2_CSN_L;			//NSS拉低		// CSN low, init SPI transaction                  
	status = SPI2_RW(Reg);      // select register
	SPI2_RW(Data);             // ..and write value to it..                  
	SPI2_CSN_H;			//NSS拉高，关闭SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

u8 SPI2_Read(u8 Reg)
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
u16 SPI2_RWWord(u16 Reg)
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
//输入:pTxHeader发射地址首地址；HeaderLen地址长度，，高位对齐
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_TransmitMod(u8 * pTxHeader)
{
	u8 iLoop,lLoop,reg,TxHeaderAdr;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//发送帧头
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头	
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //中断使能包发送
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX人工接收模式，预备模式
}

//=============================================================================================
//说明:Si4431发射模块设置接收模式
//输入:void
//输出:void
//调用:SPI1_RWReg();SPI1_Read();
//修改:2011-01-15			KEN			初定
//=============================================================================================
void Si4431TX_ReceiveMod(void)
{
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
  
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
	u8 temp8,reg;	
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
