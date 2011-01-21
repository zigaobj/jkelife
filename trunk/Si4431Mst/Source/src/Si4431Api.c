
#include "stm32f10x.h"
#include "platform_config.h"
#include "Si4431Api.h"




//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�Si4431��SPIдʱ��
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
	SPI1_CSN_L;			//NSS����		// CSN low, init SPI transaction                  
	status = SPI1_RW(Reg);      // select register
	SPI1_RW(Data);             // ..and write value to it..                  
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

static u8 SPI1_Read(u8 Reg)
{
	u8 Reg_val;
	SPI1_CSN_L;			//NSS����
	SPI1_RW(Reg);            // Select register to read from..
	Reg_val = SPI1_RW(0);    // ..then read registervalue
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI
	return(Reg_val);        // return register value
}

static u16 SPI1_RWWord(u16 Reg)
{
	u16 temp16;
	SPI1_CSN_L;			//NSS����	// Set CSN low, init SPI tranaction = 0;						
	temp16  = (u16) (SPI1_RW( (u8)((Reg & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (u16) (SPI1_RW( (u8)(Reg & 0x00FF) ));
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI	// Set CSN high again;
	return temp16;
}

/*++++++++++++++++++++++++++++++++++++++�ָ�SPI2+++++++++++++++++++++++++++++++++++++++++++++++*/

//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�Si4431��SPIдʱ��
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
	SPI2_CSN_L;			//NSS����		// CSN low, init SPI transaction                  
	status = SPI2_RW(Reg);      // select register
	SPI2_RW(Data);             // ..and write value to it..                  
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

static u8 SPI2_Read(u8 Reg)
{
	u8 Reg_val;
	SPI2_CSN_L;			//NSS����
	SPI2_RW(Reg);            // Select register to read from..
	Reg_val = SPI2_RW(0);    // ..then read registervalue
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI
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
	SPI2_CSN_L;			//NSS����	// Set CSN low, init SPI tranaction = 0;						
	temp16  = (u16) (SPI2_RW( (u8)((Reg & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (u16) (SPI2_RW( (u8)(Reg & 0x00FF) ));
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI	// Set CSN high again;
	return temp16;
}



//=============================================================================================
//˵��:Si4431����ģ���ʼ������
//����:void
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_Init(void)
{                   
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//�Ĵ�����λ
 	
	while ( GPIO_ReadOutputDataBit(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI1_Read(InterruptStatus1);	//���ж�
	SPI1_Read(InterruptStatus2);

	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//�ر������ж�

	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M����ĵ�г����Ϊ12.5P
//	SPI1_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);				//GPIO���2Mʱ��
	SPI1_RWReg((REG_WRITE | GPIO0Configuration), 0x12);									//GPIO_0 ����ģʽ
	SPI1_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 								//GPIO_1 ��������
	SPI1_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 								//GPIO_2 ����ģʽ	
	SPI1_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							  // gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI1_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//��ʹ������˹�ر��� û�а׻� 

//	SPI1_RWReg((REG_WRITE | IFFilterBandwidth), 0x1D); 								//(1Ch)BW=90kHZ
	SPI1_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x00);						//(1Dh)��ֹAFC

	SPI1_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);			//(20h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x20);								//(21h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x4e);								//(22h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset0), 0xa5);								//(23h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);				//(24h)
	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);				//(25h)0x0a
	  
	//case RATE_24K: // 2.4k 
//	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x13); 												//
//	SPI1_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	//TX��������9600BPS
	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x02); 												//(6EH)9600BPS
	SPI1_RWReg((REG_WRITE | TXDataRate0), 0x75);												//(6FH)

	SPI1_RWReg((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
	
	//Ƶ������													
	SPI1_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    						//(75H)�ߴ�ѡ�񣬵�Ƶ��240-479.9M 430Mhz
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x4b);  					//(76H)fc  ����433HZ
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);						//(77H)fc

	//��֪������
	SPI1_RWReg((REG_WRITE | FrequencyDeviation), 0x20);                 //(72h)Ƶ��ƫ��20k                            
	SPI1_RWReg((REG_WRITE | FrequencyOffset),0x00); 										//(73h)

	SPI1_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 						//(70H)
	SPI1_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 						//(71H)ֱ��ģʽ FSK����
	//���ݰ��ṹ
	SPI1_RWReg((REG_WRITE | HeaderControl1), 0x00);											//(32h)֡ͷ
	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x02); 										//(33h)no head; sync word 3 and 2
	SPI1_RWReg((REG_WRITE | PreambleLength), 0x04);   									//(34h)����ͷ2 byte
	SPI1_RWReg((REG_WRITE | PreambleDetectionControl), 0x10); 					//(35h)8bit
	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)ͬ��ͷ
	SPI1_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
	SPI1_RWReg((REG_WRITE | SyncWord1), 0x2d);													//(36h)
	SPI1_RWReg((REG_WRITE | SyncWord0), 0xa4);													//(37h)

	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x88); 									//(30h)enable TX handling	��ҪCRC
	
	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)readyģʽ��Xtal
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x02);										//ʹ�ܽ����ж�
	SPI1_RWReg((REG_WRITE | TXPower), 0x07);
        
	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);
}

//=============================================================================================
//˵��:Si4431����ģ�����ÿ���ģʽ
//����:void
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
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
//˵��:Si4431����ģ�����÷���ģʽ
//����:pTxHeader�����ַ�׵�ַ��
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_TransmitMod(u8 * pTxHeader)
{
	u8 iLoop,TxHeaderAdr;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //�巢��FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//����֡ͷ
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//���÷��͵�ַͷ����λ����	
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //�ж�ʹ�ܰ�����
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX�˹�����ģʽ��Ԥ��ģʽ
}

//=============================================================================================
//˵��:Si4431����ģ�����ý���ģʽ
//����:pRxCheckHeader����У�Ե�ַͷ	
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_ReceiveMod(u8 * pRxCheckHeader)
{	u8 iLoop,RxCheckHeaderAdr;
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //�����FIFO
 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//����У�Ե�ַͷ
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //���ý���У�Ե�ַͷ	
		SPI1_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x02); 							 //�ж�ʹ�ܽ��յ���Ч��
 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00); 

	SPI1_Read(InterruptStatus1);
	SPI1_Read(InterruptStatus2);
        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX�˹�����ģʽ��Ԥ��ģʽ

}

//=============================================================================================
//˵��:Si4431����ģ�����÷���ģʽ����ŵ��Ƿ�æ
//����:void
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
u8 Si4431TX_BusyCheck(void)
{
	unsigned char value;
	value =  (unsigned char)(SPI1_Read(ReceivedSignalStrengthIndicator)) ;//���ź�ǿ�ȼĴ���
	if(value>40)
		return 0;
	else
		return 1;
}

//=============================================================================================
//˵��:Si4431����ģ�鷢�����ݰ�
//����:void
//���:void
//����:SPI1_RWReg();SPI1_Read();Si4431TX_IdleMod();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_TxPacket(unsigned char * packet, unsigned char length)
{
	u8 temp8;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //�巢��FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	SPI1_RWReg((REG_WRITE | TransmitPacketLength), length);	 
  for(temp8=0;temp8<length;temp8++){	
		SPI1_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);		
	}
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);		
}

/********************************Si4431RX�ָ���****************************************/

//=============================================================================================
//˵��:Si4431����ģ���ʼ������
//����:void
//���:void
//����:SPI2_RWReg();SPI2_Read();
//�޸�:2011-01-20			KEN			����
//=============================================================================================
void Si4431RX_Init(void)
{                   
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//�Ĵ�����λ
 	
	while ( GPIO_ReadOutputDataBit(SPI2_CTL_GPIO, SPI2_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI2_Read(InterruptStatus1);	//���ж�
	SPI2_Read(InterruptStatus2);

	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//�ر������ж�

	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M����ĵ�г����Ϊ12.5P
//	SPI2_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);				//GPIO���2Mʱ��
	SPI2_RWReg((REG_WRITE | GPIO0Configuration), 0x12);									//GPIO_0 ����ģʽ
	SPI2_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 								//GPIO_1 ��������
	SPI2_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 								//GPIO_2 ����ģʽ	
	SPI2_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							  // gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI2_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//��ʹ������˹�ر��� û�а׻� 

//	SPI2_RWReg((REG_WRITE | IFFilterBandwidth), 0x1D); 								//(1Ch)BW=90kHZ
	SPI2_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x00);						//(1Dh)��ֹAFC

	SPI2_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);			//(20h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x20);								//(21h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x4e);								//(22h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset0), 0xa5);								//(23h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);				//(24h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);				//(25h)0x0a
	  
	//case RATE_24K: // 2.4k 
//	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x13); 												//
//	SPI2_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	//TX��������9600BPS
	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x02); 												//(6EH)9600BPS
	SPI2_RWReg((REG_WRITE | TXDataRate0), 0x75);												//(6FH)

	SPI2_RWReg((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
	
	//Ƶ������													
	SPI2_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    						//(75H)�ߴ�ѡ�񣬵�Ƶ��240-479.9M 430Mhz
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x4b);  					//(76H)fc  ����433HZ
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);						//(77H)fc

	//��֪������
	SPI2_RWReg((REG_WRITE | FrequencyDeviation), 0x20);                 //(72h)Ƶ��ƫ��20k                            
	SPI2_RWReg((REG_WRITE | FrequencyOffset),0x00); 										//(73h)

	SPI2_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 						//(70H)
	SPI2_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 						//(71H)ֱ��ģʽ FSK����
	//���ݰ��ṹ
	SPI2_RWReg((REG_WRITE | HeaderControl1), 0x00);											//(32h)֡ͷ
	SPI2_RWReg((REG_WRITE | HeaderControl2), 0x02); 										//(33h)no head; sync word 3 and 2
	SPI2_RWReg((REG_WRITE | PreambleLength), 0x04);   									//(34h)����ͷ2 byte
	SPI2_RWReg((REG_WRITE | PreambleDetectionControl), 0x10); 					//(35h)8bit
	SPI2_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)ͬ��ͷ
	SPI2_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
	SPI2_RWReg((REG_WRITE | SyncWord1), 0x2d);													//(36h)
	SPI2_RWReg((REG_WRITE | SyncWord0), 0xa4);													//(37h)

	SPI2_RWReg((REG_WRITE | DataAccessControl), 0x88); 									//(30h)enable TX handling	��ҪCRC
	
	SPI2_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)readyģʽ��Xtal
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x02);										//ʹ�ܽ����ж�
	SPI2_RWReg((REG_WRITE | TXPower), 0x07);
        
	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);
}

//=============================================================================================
//˵��:Si4431����ģ�����ÿ���ģʽ
//����:void
//���:void
//����:SPI2_RWReg();SPI2_Read();
//�޸�:2011-01-20			KEN			����
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
//˵��:Si4431����ģ�����÷���ģʽ
//����:pTxHeader�����ַ�׵�ַ��HeaderLen��ַ���ȣ�����λ����
//���:void
//����:SPI2_RWReg();SPI2_Read();
//�޸�:2011-01-20			KEN			����
//=============================================================================================
void Si4431RX_TransmitMod(u8 * pTxHeader)
{
	u8 iLoop,TxHeaderAdr;	
	Si4431RX_IdleMod();        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //�巢��FIFO
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//����֡ͷ
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//���÷��͵�ַͷ	
		SPI2_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //�ж�ʹ�ܰ�����
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX�˹�����ģʽ��Ԥ��ģʽ
}

//=============================================================================================
//˵��:Si4431����ģ�����ý���ģʽ
//����:pRxCheckHeader����У�Ե�ַͷ	
//���:void
//����:SPI2_RWReg();SPI2_Read();
//�޸�:2011-01-21			KEN			����
//=============================================================================================
void Si4431RX_ReceiveMod(u8 * pRxCheckHeader)
{	u8 iLoop,RxCheckHeaderAdr;
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //�����FIFO
 	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//����У�Ե�ַͷ
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //���ý���У�Ե�ַͷ	
		SPI2_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x02); 							 //�ж�ʹ�ܽ��յ���Ч��
 	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00); 

	SPI2_Read(InterruptStatus1);
	SPI2_Read(InterruptStatus2);
        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX�˹�����ģʽ��Ԥ��ģʽ

}

//=============================================================================================
//˵��:Si4431����ģ�����÷���ģʽ����ŵ��Ƿ�æ
//����:void
//���:void
//����:SPI2_RWReg();SPI2_Read();
//�޸�:2011-01-20			KEN			����
//=============================================================================================
u8 Si4431RX_BusyCheck(void)
{
	unsigned char value;
	value =  (unsigned char)(SPI2_Read(ReceivedSignalStrengthIndicator)) ;//���ź�ǿ�ȼĴ���
	if(value>40)
		return 0;
	else
		return 1;
}

//=============================================================================================
//˵��:Si4431����ģ�鷢�����ݰ�
//����:void
//���:void
//����:SPI2_RWReg();SPI2_Read();Si4431RX_IdleMod();
//�޸�:2011-01-20			KEN			����
//=============================================================================================
void Si4431RX_TxPacket(unsigned char * packet, unsigned char length)
{
	u8 temp8;	
	Si4431RX_IdleMod();        
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //�巢��FIFO
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	SPI2_RWReg((REG_WRITE | TransmitPacketLength), length);	 
  for(temp8=0;temp8<length;temp8++){	
		SPI2_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);		
	}
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x04);
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);		
}


