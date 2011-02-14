
#include "stm32f10x.h"
#include "platform_config.h"
#include "Si4431Api.h"
#include "Global.h"



//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�Si4431��SPIдʱ��
//****************************************************************************************************/

u8 SPI1_RW(u8 Data)
{
	SPI_I2S_SendData(SPI1 , Data);
	DelayUs_Soft(100);
	// Wait for SPI1 data reception 
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	
	Data = SPI_I2S_ReceiveData(SPI1);
	return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
u8 SPI1_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI1_CSN_L;			//NSS����		// CSN low, init SPI transaction                  
	status = SPI1_RW(Reg);      // select register
	SPI1_RW(Data);             // ..and write value to it..                  
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

u8 SPI1_Read(u8 Reg)
{
	u8 Reg_val;
	SPI1_CSN_L;			//NSS����
	SPI1_RW(Reg);            // Select register to read from..
	Reg_val = SPI1_RW(0);    // ..then read registervalue
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI
	return(Reg_val);        // return register value
}

u16 SPI1_RWWord(u16 Reg)
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

u8 SPI2_RW(u8 Data)
{
	SPI_I2S_SendData(SPI2 , Data);
	DelayUs_Soft(100);
	
	// Wait for SPI1 data reception 
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	Data = SPI_I2S_ReceiveData(SPI2);
	return(Data);           		  // return read uchar
}

//u8 SpiRfWriteAddressData(u8 address, u8 data)
u8 SPI2_RWReg(u8 Reg, u8 Data)
{
	u8 status;
	SPI2_CSN_L;			//NSS����		// CSN low, init SPI transaction                  
	status = SPI2_RW(Reg);      // select register
	SPI2_RW(Data);             // ..and write value to it..                  
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI	 // CSN high again
	return(status);            // return nRF24L01 status uchar
}

u8 SPI2_Read(u8 Reg)
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
u16 SPI2_RWWord(u16 Reg)
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
{ u8 TmpRegVal;                  
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//(07h)�Ĵ�������λ
 	
	while ( GPIO_ReadOutputDataBit(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI1_Read(InterruptStatus1);	//(03h)���ж�
	SPI1_Read(InterruptStatus2);	//(04h)

	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);			//(06h)�ر������ж�
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), RF22_PWRSTATE_READY);	//(07h)����ģʽ

	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//(09h)30M����ĵ�г����Ϊ12.5P
	TmpRegVal = SPI1_Read(CrystalOscillatorLoadCapacitance);						//���Ĵ���������Ƿ�������ȷ

	SPI1_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);						//(0Ah)GPIO���2Mʱ��
	SPI1_RWReg((REG_WRITE | GPIO0Configuration), 0x12);								//(0Bh)GPIO_0 ����ģʽ
	SPI1_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 							//(0Ch)GPIO_1 ��������
	SPI1_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 							//(0Dh)GPIO_2 ����ģʽ	
	SPI1_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							//(0Eh)gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI1_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//(70h)��ʹ������˹�ر��� û�а׻� 

	SPI1_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x40);						//(1Dh)ʹ��AFC

	//TX��������9600BPS
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
	
	//���ݰ��ṹ
	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x8D); 					//(30h)enable packet handlerʹ�ܰ�����, msb first, enable crc,
	SPI1_RWReg((REG_WRITE | HeaderControl1), 0xFF);						//(32h)У��checkhead3-0 4λ���յ�ַaddress enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3
	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x42); 					//(33h)header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
	
	SPI1_RWReg((REG_WRITE | PreambleLength), 64);   					//(34h)����ͷ���� // 64 nibble = 32byte preamble
	SPI1_RWReg((REG_WRITE | PreambleDetectionControl), 0x20); 			//(35h)need to detect 20bit preamble
	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);							//(36h)// synchronize word						//(36h)ͬ��ͷ
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

	SPI1_RWReg((REG_WRITE | TXPower), 0x03);				//(6Dh)1db����
	SPI1_RWReg((REG_WRITE | FrequencyHoppingChannelSelect), 0x00);  	//(79h)no hopping
	SPI1_RWReg((REG_WRITE | FrequencyHoppingStepSize), 0x00);  		//(7Ah)no hopping
	//Ƶ������
	                           

//	SPI1_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 			//(70H)
	SPI1_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 			//(71H)// Gfsk, fd[8] =0, no invert for Tx/Rx data, fifo mode, txclk -->gpio
	SPI1_RWReg((REG_WRITE | FrequencyDeviation), 0x48);           //(72h)// frequency deviation setting to 45k = 72*625 													
	SPI1_RWReg((REG_WRITE | FrequencyOffset),0x00); 							//(73h)
	SPI1_RWReg((REG_WRITE | FrequencyChannelControl),0x00);				//(74h)no offset

	SPI1_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    			//(75H)�ߴ�ѡ�񣬵�Ƶ��240-479.9M 430Mhz
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x64);  		//(76H)fc  ����434HZ
	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);			//(77H)fc


	/*		
	SPI1_RWReg((REG_WRITE | TXRampControl), 0x7F); 											//(52h)Add by T.L.Steve	
	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)readyģʽ��Xtal
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x60);										//(50h)ʹ�ܷ���FIFO���������������ж�
	        
	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);		*/
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
  //releaze all IT flags
	SPI1_Read(InterruptStatus1);		//(03h)
	SPI1_Read(InterruptStatus2);		//(04h)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		//(07h) 
}

//=============================================================================================
//˵��:Si4431����ģ�����÷���ģʽ
//����:pTxHeader�����ַ�׵�ַ��
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_TransmitMod(u8 * pTxHeader)
{	u8 iLoop,TxHeaderAdr;
		
	Si4431TX_IdleMod();        	//���ÿ���״̬

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //(08h)�巢��FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	
	TxHeaderAdr = TransmitHeader3;			//����֡ͷ
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		//(3Ah-3Dh)���÷��͵�ַͷ����λ����	
	}

	SPI1_RWReg((REG_WRITE | TXFIFOControl2), 32);  //(7Dh)tx almost empty ����

//  TmpVal = SPI1_Read(TransmitHeader3);
//	TmpVal = SPI1_Read(TransmitHeader0);

//	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //(05h)�ж�ʹ�ܰ�����
//	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
//	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//(07h)TX�˹�����ģʽ��Ԥ��ģʽ
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
//  TmpVal = SPI1_Read(CheckHeader3);
//	TmpVal = SPI1_Read(CheckHeader0);

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
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //(08h)�巢��FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	SPI1_RWReg((REG_WRITE | TransmitPacketLength), length);	 				//(3Eh)���������
  for(temp8=0;temp8<length;temp8++){	
		SPI1_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);						//(7Fh)
	}
	
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x44);							  //(05h)�ж�ʹ�ܰ�����
	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);

	SPI1_Read(InterruptStatus1);
	SPI1_Read(InterruptStatus2);

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//(07h)TX�˹�����ģʽ��Ԥ��ģʽ
				
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
{u8 TmpRegVal;                  
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//(07h)�Ĵ�������λ
 	
	while ( GPIO_ReadOutputDataBit(SPI2_CTL_GPIO, SPI2_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI2_Read(InterruptStatus1);	//(03h)���ж�
	SPI2_Read(InterruptStatus2);	//(04h)

	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);			//(06h)�ر������ж�
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), RF22_PWRSTATE_READY);	//(07h)����ģʽ

	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//(09h)30M����ĵ�г����Ϊ12.5P

	SPI2_RWReg((REG_WRITE | MicrocontrollerOutputClock), 0x05);						//(0Ah)GPIO���2Mʱ��
	SPI2_RWReg((REG_WRITE | GPIO0Configuration), 0x12);								//(0Bh)GPIO_0 ����ģʽ
	SPI2_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 							//(0Ch)GPIO_1 ��������
	SPI2_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 							//(0Dh)GPIO_2 ����ģʽ	
	SPI2_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							//(0Eh)gpio    0, 1,2 NO OTHER FUNCTION. 
	SPI2_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//(70h)��ʹ������˹�ر��� û�а׻� 

	SPI2_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x40);						//(1Dh)ʹ��AFC
	TmpRegVal = SPI2_Read(AFCLoopGearshiftOverride);						//���Ĵ���������Ƿ�������ȷ

	//TX��������9600BPS
	SPI2_RWReg((REG_WRITE | IFFilterBandwidth), 0x1e); 						//(1Ch)BW=90kHZ
	SPI2_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xd0);			//(20h)calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x00);					//(21h)rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x9d);					//(22h)ncoff =5033 = 0x13a9
	SPI2_RWReg((REG_WRITE | ClockRecoveryOffset0), 0x49);					//(23h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);			//(24h)
	SPI2_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x45);			//(25h)0x0a
	SPI2_RWReg((REG_WRITE | 0x2a), 0x20);
	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x4e); 	//(6Eh)											//(6EH)9600BPS
	SPI2_RWReg((REG_WRITE | TXDataRate0), 0xa5);	//(6Fh)	  
	//case RATE_24K: // 2.4k 
//	SPI2_RWReg((REG_WRITE | TXDataRate1), 0x13); 											//
//	SPI2_RWReg((REG_WRITE | TXDataRate0), 0xa9); 
	
	//���ݰ��ṹ
	SPI2_RWReg((REG_WRITE | DataAccessControl), 0x8D); 					//(30h)enable packet handlerʹ�ܰ�����, msb first, enable crc,
	SPI2_RWReg((REG_WRITE | HeaderControl1), 0xFF);						//(32h)У��checkhead3-0 4λ���յ�ַaddress enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3
	SPI2_RWReg((REG_WRITE | HeaderControl2), 0x42); 					//(33h)header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
	
	SPI2_RWReg((REG_WRITE | PreambleLength), 64);   					//(34h)����ͷ���� // 64 nibble = 32byte preamble
	SPI2_RWReg((REG_WRITE | PreambleDetectionControl), 0x20); 			//(35h)need to detect 20bit preamble
	SPI2_RWReg((REG_WRITE | SyncWord3), 0x2d);							//(36h)// synchronize word						//(36h)ͬ��ͷ
	SPI2_RWReg((REG_WRITE | SyncWord2), 0xa4);							//(37h)						
	SPI2_RWReg((REG_WRITE | SyncWord1), 0x00);							//(38h)
	SPI2_RWReg((REG_WRITE | SyncWord0), 0x00);							//(39h)

	SPI2_RWReg((REG_WRITE | 0x3a), 's');  // tx header
	SPI2_RWReg((REG_WRITE | 0x3b), 'o');
	SPI2_RWReg((REG_WRITE | 0x3c), 'n');
	SPI2_RWReg((REG_WRITE | 0x3d), 'g');
	SPI2_RWReg((REG_WRITE | 0x3e), 17);  // total tx 17 byte
	SPI2_RWReg((REG_WRITE | 0x3f), 's'); // check hearder
	SPI2_RWReg((REG_WRITE | 0x40), 'o');
	SPI2_RWReg((REG_WRITE | 0x41), 'n');
	SPI2_RWReg((REG_WRITE | 0x42), 'g');
	SPI2_RWReg((REG_WRITE | 0x43), 0xff);  // all the bit to be checked
	SPI2_RWReg((REG_WRITE | 0x44), 0xff);  // all the bit to be checked
	SPI2_RWReg((REG_WRITE | 0x45), 0xff);  // all the bit to be checked
	SPI2_RWReg((REG_WRITE | 0x46), 0xff);  // all the bit to be checked

	SPI2_RWReg((REG_WRITE | TXPower), 0x03);				//(6Dh)1db����
	SPI2_RWReg((FrequencyHoppingChannelSelect), 0x00);  	//(79h)no hopping
	SPI2_RWReg((FrequencyHoppingStepSize), 0x00);  		//(7Ah)no hopping
	//Ƶ������
	                           

//	SPI2_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 			//(70H)
	SPI2_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 			//(71H)// Gfsk, fd[8] =0, no invert for Tx/Rx data, fifo mode, txclk -->gpio
	SPI2_RWReg((REG_WRITE | FrequencyDeviation), 0x48);           //(72h)// frequency deviation setting to 45k = 72*625 													
	SPI2_RWReg((REG_WRITE | FrequencyOffset),0x00); 							//(73h)
	SPI2_RWReg((REG_WRITE | FrequencyChannelControl),0x00);				//(74h)no offset

	SPI2_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    			//(75H)�ߴ�ѡ�񣬵�Ƶ��240-479.9M 430Mhz
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x64);  		//(76H)fc  ����434HZ
	SPI2_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);			//(77H)fc


	/*		
	SPI2_RWReg((REG_WRITE | TXRampControl), 0x7F); 											//(52h)Add by T.L.Steve	
	SPI2_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)readyģʽ��Xtal
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x60);										//(50h)ʹ�ܷ���FIFO���������������ж�
	        
	SPI2_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);		*/
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
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		//(07h) 
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
	Si4431RX_IdleMod();        										//(07h)0x01
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x02);       //(08h)�����FIFO
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//����֡ͷ
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//���÷��͵�ַͷ	
		SPI2_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}
	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//(07h)TX�˹�����ģʽ��Ԥ��ģʽ
	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x12);					//(05h)�ж�ʹ�ܰ����ռ�FIFO�������ж�
	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00);

  //releaze all IT flags
	SPI2_Read(InterruptStatus1);
	SPI2_Read(InterruptStatus2);	
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
	Si4431RX_IdleMod();
	SPI2_RWReg((REG_WRITE | RXFIFOControl), 5);							 //(7Eh)threshold for rx almost full, interrupt when 1 byte received

	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //(08h)�����FIFO
 	SPI2_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//����У�Ե�ַͷ
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //���ý���У�Ե�ַͷ	
		SPI2_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  	SPI2_RWReg((REG_WRITE | OperatingFunctionControl1), 5);			 //(07h)RX�˹�����ģʽ��Ԥ��ģʽ

	SPI2_RWReg((REG_WRITE | InterruptEnable1), 0x10);				 //(50h)ʹ�ܽ���FIFO�������ж�
 	SPI2_RWReg((REG_WRITE | InterruptEnable2), 0x00); 

	SPI2_Read(InterruptStatus1);
	SPI2_Read(InterruptStatus2);
        
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

