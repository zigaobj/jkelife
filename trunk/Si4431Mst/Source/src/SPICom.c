/***********************************************
*Copyright 2010,JK Ltd.
*All rights reserved.
*
*File Name: communication.c
*ID       : 
*Abstract : communication of SPI or USART
*		  : 
*Version NO.:1.0
*Writer     :Ken
*Date       :2010-08-27
**************************************************/
#include "Global.h"
#include "SPICom.h"	
//------------------------------------------------------------------------------------//

uint8_t SPI1_TxBuf[BufferSize] = "#NTA,0,12345\r\n";		//SPIy_Buffer_Tx
uint8_t SPI2_TxBuf[BufferSize] = {0};		//SPIz_Buffer_Tx
uint8_t SPI1_RxBuf[BufferSize] = {0};		//SPIy_Buffer_Rx
uint8_t SPI2_RxBuf[BufferSize] = {0};		//SPIz_Buffer_Rx

uint8_t	SPI1OkFlag;           //Uart0�ɹ�������Ϣ��־
uint8_t	SPI2OkFlag;           //Uart1�ɹ�������Ϣ��־
uint8_t	SPI1NewFlg;		//SPI1�յ�������
uint8_t	SPI2NewFlg;		//SPI2�յ�������

uint8_t	SPI1FullFlag;        //���ջ���������־λ
u8 			SPI2FullFlag;        //���ջ���������־λ
uint8_t	SPI1ProtocolFlag;	 //Э���־�����ִ���Э��
uint8_t	SPI1index;		 //���ڽ��ջ����������
uint8_t	SPI1Pindex;        //���ڴ���������
uint8_t	SPI2index;		 //���ڽ��ջ����������
uint8_t	SPI2Pindex;        //���ڴ���������
//uint8_t pdata txIndex;          //���ڷ��ͻ����������
uint8_t	SPI1_ParseBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����
u8		SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����

uint8_t	txLog[TXLOGLEN];
uint8_t	SPI1ByteNum;		 //��Э��0ʱ���ڰ����յ��������ֽ�����������һ������Ľ���
uint8_t	SPI2_ParseBuf[SPI2PARSEBUFLEN];//����1���ջ�����

//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*������void SPI1Rx_Parse(void)	
//*���ܣ�SPI1���մ�����
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //uint8_t i,j,k;
  uint8_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;
//  static uint8_t strCNT[]  = "CNT";             
//  static uint8_t LOG[] = "$log,ES";		   //  7
//  static uint8_t SET[] = "$set,ES";		   //  7

/*	if(1 == SPI1NewFlg){	//SPI1�յ�������
		for(i=0;i<TX_PLOAD_WIDTH_24L01;i++){
			SPI1_ParseBuf[SPI1index] = SPI1_RxBuf[i];
			if(0x0A == SPI1_ParseBuf[SPI1index] ){		
				if(0x0D == SPI1_ParseBuf[SPI1index-1] ){
					SPI1OkFlag ++;		//�յ�0x0D 0x0A��Ϊ��һ������������		
				}
			}
			SPI1index++;
		}
		SPI1NewFlg = 0;	
	}	*/
	if(0 != SPI1OkFlag ){								
		for(LoopStart = SPI1Pindex; LoopStart < SPI1index; LoopStart++){
			if(SPI1_ParseBuf[LoopStart]=='#'){//�ҵ�����ͷ��	
				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//�ҽ�β
					if(SPI1_ParseBuf[LoopEnd]=='\n'){//�ҵ�����ͷ��
						SPI1OkFlag--;	//ÿ����һ�������������������Լ�
						SPI1Pindex = LoopEnd + 1;
						break;
					}
				}
				comnum = Hash(SPI1_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//��������Hashͷ
				switch (comnum){	//����ɢת
			/*		case (RFCMD_CNT):	//CNT����������մ�ģ���ַ  "#CNT,00000\r\n";
						if(STA_NETCONNECT == WorkSta1){		//ֻ�е�ϵͳ������ģʽ��ִ��
							if(! NewConnect(SPI1_ParseBuf+LoopStart+5 )){
								Usart_SendString_End(USART1 ,StrError);		//��ģ���ַ�ռ�����
							}
						}	
					break;*/

						/*	else{
								SPI1OkFlag = 0;	//��SPI1OkFlag--
							}*/

						
						
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//�������ӵĴ�ģ���ַ���浽�յĽ��յ�ַ�б�
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//���CNT����������ճɹ����������յ��ĵ�ַ������1��
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//ָ����һ���յĴ�ģ���ַ�ռ�
						*/
					
					case (RFCMD_HRB):	//������	"#HRB,00000\r\n";
						if(STA_DATA == WorkSta2){	//ֻ�е�ϵͳ�����ݽ��ս׶β�ִ��							
							if(! HeartBeat(SPI1_ParseBuf+LoopStart+5 )){	//���������������Ĵ�ģ���ַ
							//	Usart_SendString_End(USART1 ,StrError);		//��ģ���ַ�ռ�����
							}
						//	else{
						//		SPI1OkFlag = 0;	//��SPI1OkFlag--
						//	}													
						}

					break;
					case (RFCMD_TMP):	//�¶Ȳɼ�	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta2){	//ֻ�е�ϵͳ�����ݽ��ս׶β�ִ��							
							Usart_SendString(USART1 ,SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//ֱ������λ������												
						}

					break;
					

					default:
						Usart_SendString_End(USART1 ,StrError);		//�������������޷�����
					break;
							
				}
				
			//��ջ�����
			if((0 == SPI1OkFlag)||(SPI1index >= SPI1PARSEBUFLEN))
			for (Loopi = 0; Loopi < SPI1PARSEBUFLEN; Loopi++){
	 			SPI1_ParseBuf[Loopi] = 0;	
			}
	  		SPI1index   = 0;
			SPI1Pindex = 0;
			SPI1FullFlag = 0;
		//	U0Pindex  = 0;
	  				   			
				
							
			}
		} 
	//	if(0 != SPI1OkFlag){	
	//		SPI1OkFlag--;	
	//	}
	}
				

}




//========================================================================================//
//****************************************************************************************************
//*������void SPI1Rx_Parse(void)	
//*���ܣ�SPI1���մ�����
//****************************************************************************************************/
void SPI2Rx_Parse(void)
{ //uint8_t i,j,k;
  uint16_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;

	DelayCom(2000);

	SPI2Sta = SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	//	IRDA_LED_ON();
	if(SPI2Sta & RX_DR){				// �ж��Ƿ���յ�����
		DelayCom(1000);		    
			SPI2NewFlg = 1;
			SPI2RxCnt++;  //�������RX�жϴ���
		SPI2_CE_L;	//StandBy Iģʽ
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,SPI2_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
//	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
//	SPI2_RW(FLUSH_RX_24L01);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����
	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
	SPI2_Read(FIFO_STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	
//	SPI2_CSN_H;			//NSS���ߣ��ر�SPI

	SPI2_CE_H;	//�ø�CE�����ֽ���ģʽ
	  	//����֪����������ͨ����RX_P_NO
//	  	TmpVal = ((SPI2Sta & MASK_RX_P_NO)>>1);	//��ȡ��������ͨ����RX_P_NO 
	  if(!SPI2FullFlag){
		for(Loopi=0 ; Loopi<RX_PLOAD_WIDTH_24L01 ; Loopi++){
			SPI2_ParseBuf[SPI2index] = SPI2_RxBuf[Loopi];	//�����ջ�����SPI1_RxBuf����ת�Ƶ��������ݻ�����SPI1_ParseBuf
			if(0x0A == SPI2_ParseBuf[SPI2index] ){		
				if(0x0D == SPI2_ParseBuf[SPI2index-1] ){
					SPI2OkFlag ++;		//�յ�0x0D 0x0A��Ϊ��һ������������		
				}
			}
			SPI2index++;
			if(SPI2index >= SPI2PARSEBUFLEN){
				SPI2FullFlag = 1;	//���ջ���������δ���ü���������
			}
		}
	  }
		SPI2NewFlg = 0;



//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	
//	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
//	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
//	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
//	SPI2_CSN_H;			//NSS���ߣ��ر�SPI
//	SPI2Sta = SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	}

//	Init_NRF24L01_SPI2();
//	NetConnect(TRUE);				//����Ϊ����ģʽ

	if(0 != SPI2OkFlag ){								
		for(LoopStart = SPI2Pindex; LoopStart < SPI2index; LoopStart++){
			if(SPI2_ParseBuf[LoopStart]=='#'){//�ҵ�����ͷ��	
				for(LoopEnd = LoopStart; LoopEnd < SPI2index; LoopEnd++){	//�ҽ�β
					if(SPI2_ParseBuf[LoopEnd]=='\n'){//�ҵ�����ͷ��
						SPI2OkFlag--;	//ÿ����һ�������������������Լ�
						SPI2Pindex = LoopEnd + 1;
						break;
					}
				}
				comnum = Hash(SPI2_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//��������Hashͷ
				switch (comnum){	//����ɢת
					case (RFCMD_CNT):	//CNT����������մ�ģ���ַ  "#CNT,00000\r\n";
					//	if(STA_NETCONNECT == WorkSta1){		//ֻ�е�ϵͳ������ģʽ��ִ��
							
							if(! NewConnect(SPI2_ParseBuf+LoopStart+5 )){
							//	Usart_SendString_End(USART1 ,StrError);		//��ģ���ַ�ռ�����
							}	

						/*	else{
								SPI1OkFlag = 0;	//��SPI1OkFlag--
							}*/

						
				//		}
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//�������ӵĴ�ģ���ַ���浽�յĽ��յ�ַ�б�
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//���CNT����������ճɹ����������յ��ĵ�ַ������1��
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//ָ����һ���յĴ�ģ���ַ�ռ�
						*/
					break;
					case (RFCMD_CNS):	//���԰�	"#CNS,00000\r\n";
					__NOP();
					
					break;
					case (RFCMD_HRB):	//������	"#HRB,00000\r\n";
					//	if(STA_DATA == WorkSta2){	//ֻ�е�ϵͳ�����ݽ��ս׶β�ִ��							
							if(! HeartBeat(SPI2_ParseBuf+LoopStart+5 )){	//���������������Ĵ�ģ���ַ
							//	Usart_SendString_End(USART1 ,StrError);		//��ģ���ַ�ռ�����
							}
						/*	else{
								SPI1OkFlag = 0;	//��SPI1OkFlag--
							}	*/												
					//	}

					break;
					case (RFCMD_TMP):	//�¶Ȳɼ�	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta2){	//ֻ�е�ϵͳ�����ݽ��ս׶β�ִ��							
					//		Usart_SendString(USART1 ,SPI2_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//ֱ������λ������												
						}

					break;
					

					default:
						__NOP();
					//	Usart_SendString_End(USART1 ,StrError);		//�������������޷�����
					break;
							
				}
				
			//��ջ�����
			if((0 == SPI2OkFlag)||(SPI2index >= SPI2PARSEBUFLEN))
			for (Loopi = 0; Loopi < SPI2PARSEBUFLEN; Loopi++){
	 			SPI2_ParseBuf[Loopi] = 0;	
			}
	  		SPI2index   = 0;
			SPI2Pindex = 0;
			SPI2FullFlag = 0;
		//	U0Pindex  = 0;
	  				   			
				
							
			}
		} 
	//	if(0 != SPI1OkFlag){	
	//		SPI1OkFlag--;	
	//	}
	}
				

}



//======================================no  more==========================================//

