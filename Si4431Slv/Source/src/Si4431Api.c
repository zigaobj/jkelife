
//#include "stm32f10x.h"
#include "Global.h"
#include "Si4431Api.h"
//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�Si4431��SPIдʱ��
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




//=============================================================================================
//˵��:Si4431����ģ���ʼ������
//����:void
//���:void
//����:SPI1_RWReg();SPI1_Read();
//�޸�:2011-01-15			KEN			����
//=============================================================================================
void Si4431TX_Init(void)
{ u8 TmpRegVal;                  
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//�Ĵ�����λ
 	
	while ( GPIO_ReadInputPin(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
//	DelayCom(2);
	SPI1_Read(InterruptStatus1);	//���ж�
	SPI1_Read(InterruptStatus2);

	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//�ر������ж�

	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M����ĵ�г����Ϊ12.5P
	TmpRegVal = SPI1_Read(CrystalOscillatorLoadCapacitance);						//���Ĵ���������Ƿ�������ȷ

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
//	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x13); 											//
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
	SPI1_RWReg((REG_WRITE | HeaderControl1), 0x0F);											//(32h)У��checkhead3-0 4λ���յ�ַ
	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x42); 										//(33h)no head; sync word 3 and 2
	SPI1_RWReg((REG_WRITE | PreambleLength), 0x08);   									//(34h)����ͷ���� 32 byte
//	SPI1_RWReg((REG_WRITE | PreambleDetectionControl), 0x10); 				//(35h)8bit
	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)ͬ��ͷ
	SPI1_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
//	SPI1_RWReg((REG_WRITE | SyncWord1), 0x2d);												//(36h)
//	SPI1_RWReg((REG_WRITE | SyncWord0), 0xa4);												//(37h)

	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x8D); 									//(30h)enable TX handling	CRC16
	
	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)

	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)readyģʽ��Xtal
	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x60);										//(50h)ʹ�ܷ���FIFO���������������ж�
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
	u8 iLoop,TxHeaderAdr,TmpVal;	
	Si4431TX_IdleMod();        
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //�巢��FIFO
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
	TxHeaderAdr = TransmitHeader3;			//����֡ͷ
  
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//���÷��͵�ַͷ����λ����	
		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
	}

  TmpVal = SPI1_Read(TransmitHeader3);
	TmpVal = SPI1_Read(TransmitHeader0);

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
{	u8 iLoop,RxCheckHeaderAdr,TmpVal;
	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //�����FIFO
 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
	RxCheckHeaderAdr = CheckHeader3;			//����У�Ե�ַͷ
	
	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //���ý���У�Ե�ַͷ	
		SPI1_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
	}
  TmpVal = SPI1_Read(CheckHeader3);
	TmpVal = SPI1_Read(CheckHeader0);

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

