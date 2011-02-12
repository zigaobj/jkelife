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
//#include "SPICom.h"	
//------------------------------------------------------------------------------------//

@near u8 SPI1_TxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Tx
//u8 SPI2_TxBuf[BufferSize] = {0};		//SPIz_Buffer_Tx
@near u8 SPI1_RxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Rx
//u8 SPI2_RxBuf[BufferSize] = {0};		//SPIz_Buffer_Rx

@near u8 SPI1OkFlag;           //Uart0�ɹ�������Ϣ��־
//u8 SPI2OkFlag;           //Uart1�ɹ�������Ϣ��־
@near u8 SPI1NewFlg;		//SPI1�յ�������
//u8 SPI2NewFlg;		//SPI2�յ�������

@near u8 SPI1FullFlag;        //���ջ���������־λ
@near u8 SPI1ProtocolFlag;	 //Э���־�����ִ���Э��
@near u8 SPI1index;		 //���ڽ��ջ����������
@near u8 SPI1Pindex;        //���ڴ���������
//u8 SPI2index;		 //���ڽ��ջ����������
//u8 SPI2Pindex;        //���ڴ���������
//u8 pdata txIndex;          //���ڷ��ͻ����������
@near u8 SPI1_ParseBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����
@near u8 SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����

//@near u8 txLog[TXLOGLEN];
@near u8 SPI1ByteNum;		 //��Э��0ʱ���ڰ����յ��������ֽ�����������һ������Ľ���
//u8 SPI2_ParseBuf[SPI2PARSEBUFLEN];//����1���ջ�����

//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*������void SPI1Rx_Parse(void)	
//*���ܣ�SPI1���մ�����
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //u8 i,j,k;
  u8 LoopStart,LoopEnd,Loopi;
  u16 comnum;
//  static u8 strCNT[]  = "CNT";             
//  static u8 LOG[] = "$log,ES";		   //  7
//  static u8 SET[] = "$set,ES";		   //  7

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
					case (RFCMD_NTA):	//NTA����������մ�ģ���ַ  "#NTA,00000\r\n";
				
						NetApply(SPI1_ParseBuf+LoopStart+5 );
					//	if(STA_NETCONNECT == WorkSta1){		//ֻ�е�ϵͳ������ģʽ��ִ��
							
							
						//	Uart1_SendString_End("NetApply\0");		//��ģ���ַ�ռ�����
							/*	else{
								SPI1OkFlag = 0;	//��SPI1OkFlag--
							}*/
					//	}
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//�������ӵĴ�ģ���ַ���浽�յĽ��յ�ַ�б�
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//���CNT����������ճɹ����������յ��ĵ�ַ������1��
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//ָ����һ���յĴ�ģ���ַ�ռ�
						*/
					break;
					
					case (RFCMD_SYN):	//�յ�ͬ������	"#SYN,00\r\n";	//16λTIM3->CNT��λ��ǰ
						if(STA_SYNCHRONIZE == WorkSta1){	//ֻ�е�ϵͳ��ͬ���׶β�ִ��							
							Synchronize(SPI1_ParseBuf + LoopStart);
						//	Uart1_SendString(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//ֱ������λ������												
						}
					break;					
					
					case (RFCMD_TMP):	//�¶Ȳɼ�	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta1){	//ֻ�е�ϵͳ�����ݽ��ս׶β�ִ��							
							SPI1_CMDTMP();
						//	CmdApply(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);		//������浽����������
						//	Uart1_SendString(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//ֱ������λ������												
						}

					break;
					
					default:
					//	Uart1_SendString_End(StrError);		//�������������޷�����
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




//======================================no  more==========================================//

