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
#include "stm32f10x.h"
#include "platform_config.h"
#include "Global.h"
#include "CmdPrc.h"
#include "UsartCom.h"
#include "SPICom.h"
#include "Si4431Api.h"
#include "Si4431App.h"

#include "GloVar.h"
//------------------------------------------------------------------------------------//

//uint8_t SPI1_TxBuf[SPIBUFLEN] = "#NTA,0,12345\r\n";		//SPIy_Buffer_Tx
//uint8_t SPI2_TxBuf[SPIBUFLEN] = {0};		//SPIz_Buffer_Tx
//uint8_t SPI1_RxBuf[SPIBUFLEN] = {0};		//SPIy_Buffer_Rx
//uint8_t SPI2_RxBuf[SPIBUFLEN] = {0};		//SPIz_Buffer_Rx

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
//u8		SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����

//uint8_t	txLog[TXLOGLEN];
uint8_t	SPI1ByteNum;		 //��Э��0ʱ���ڰ����յ��������ֽ�����������һ������Ľ���
uint8_t	SPI2_ParseBuf[SPI2PARSEBUFLEN];//����1���ջ�����

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//����������
CMDSPI_BUF_TypeDef		CmdSpiTxBuf;										//����ͻ�����
CMDSPI_BUF_TypeDef	*	pCmdSpiTxBuf;								//ָ������ͻ�����
CMDSPI_BUF_TypeDef		CmdSpiRxBuf;										//������ջ�����
CMDSPI_BUF_TypeDef	*	pCmdSpiRxBuf;								//ָ��������ջ�����
CMDSPI_BODY_TypeDef  ReplyBuf;								//Ӧ�𻺳���
CMDSPI_BODY_TypeDef * pReplyBuf;								//Ӧ�𻺳���
//CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//����������
//CMD_BUF_TypeDef CmdBuf ;	//����������
/*
	u8		CmdListNum;													//��������������
	u8		CmdCurrentList;
	u8		CmdListFlag[CMD_LISTLMT];						//��¼�������ʹ�������0��ʾ��Ӧ�����գ�1��ʾ�������д����������
 	CMD_BODY_TypeDef * pCmd_Body_Current;							//ָ�����������������
	CMD_BODY_TypeDef	 Cmd_Body[CMD_LISTLMT];	//�������ռ�
	CMD_BODY_TypeDef * pReplyBuf;							//Ӧ�𻺳���	
*/
//CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

//union STT_DAT SttDat;
//union STT_DAT * pSttDat = &SttDat;
//union SUV_DAT	SuvDat;
//union SUV_DAT * pSuvDat = &SuvDat;
////union SYS_DAT	SysDat;
////union SYS_DAT * pSysDat = &SysDat;
//union CHN_DAT	ChnDat;
//union CHN_DAT * pChnDat = &ChnDat; 
//union FRQ_DAT	FrqDat;
//union FRQ_DAT * pFrqDat = &FrqDat; 
//union SEN_DAT	SenDat;
//union SEN_DAT * pSenDat = &SenDat;



//CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//����������
//CMD_BUF_TypeDef CmdBuf ;	//����������
//CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

//union STT_DAT SttDat;
//union STT_DAT * pSttDat = &SttDat;
//union SUV_DAT	SuvDat;
//union SUV_DAT * pSuvDat = &SuvDat;
////union SYS_DAT	SysDat;
////union SYS_DAT * pSysDat = &SysDat;
//union CHN_DAT	ChnDat;
//union CHN_DAT * pChnDat = &ChnDat; 
//union FRQ_DAT	FrqDat;
//union FRQ_DAT * pFrqDat = &FrqDat; 
//union SEN_DAT	SenDat;
//union SEN_DAT * pSenDat = &SenDat;


//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*������void SPI1Rx_Parse(void)	
//*���ܣ�SPI1���մ�����
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //uint8_t i,j,k;
  uint8_t LoopStart,LoopEnd;
	if(0 != SPI1OkFlag ){								
		for(LoopStart = 0; LoopStart < SPI1index; LoopStart++){
			if(SPI1_ParseBuf[LoopStart]=='#'){		//�ҵ�����ͷ��	
				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//�ҽ�β
					if(SPI1_ParseBuf[LoopEnd]=='\n'){	//�ҵ������β
						SPI1OkFlag--;	//ÿ����һ�������������������Լ�
						SPI1Pindex = LoopEnd + 1;
						CmdSpiRxApply(&SPI1_ParseBuf[LoopStart] ,(LoopEnd-LoopStart+1));	//������������
						break;
					}
				}
			}
		}	
		//��ջ�����				
		for (LoopStart = 0; LoopStart < SPI1PARSEBUFLEN; LoopStart++){
			SPI1_ParseBuf[LoopStart] = 0;	
		}
		SPI1index   = 0;
		SPI1Pindex = 0;
		SPI1FullFlag = 0;				 
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
/*	//��ȡ InterruptStatus���Ƿŵ��ж�����ȥ

	SPI2Sta = SPI2_Read(InterruptStatus1);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	
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

	*/

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


                                
//---------------------------------------------------------------------------
//˵����SpiTx������������������Ѱ�ҿյ������ռ�
//������sta:TRUE��ʾ���������͵������Ҫ�ط����ƣ�FALSE��ʾ�ǻظ��������Ҫ�ط���* cmddata:���ݿռ��׵�ַ��cmdlen:���ݳ���
//���أ���������	
//---------------------------------------------------------------------------
u8 CmdSpiTxApply(bool sta ,u8 * cmddata ,u16 cmdlen)		
{
	u8	i = 0,j = 0;
										//������������������
			i = pCmdSpiTxBuf->CmdCurrentList ;			//��ô�ǰ��������λ��
			while(0 != CmdSpiTxBuf.CmdListFlag[i]){	//Ѱ�ҷ�����������
				i++;
				if(CMDSPI_TXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiTxBuf->CmdCurrentList){
					return 0;		//���������������ɹ�
				}
			}
			pCmdSpiTxBuf->CmdCurrentList	=	i ;	 //��ǰ��������λ��
			pCmdSpiTxBuf->pCmd_Body_Current = & (pCmdSpiTxBuf->Cmd_Body[i]);	//������������׵�ַ

			for(j = 0; j < cmdlen ; j++){
				pCmdSpiTxBuf->pCmd_Body_Current->all[j] = cmddata[j];
			}
			pCmdSpiTxBuf->pCmd_Body_Current->part.TotalLength = cmdlen;		//��¼�����
			pCmdSpiTxBuf->pCmd_Body_Current->part.HeaderHash	= Hash(pCmdSpiTxBuf->pCmd_Body_Current->part.Header , CMDSPI_HEADER_LEN);	//��������hashͷ			
			if(sta){
				pCmdSpiTxBuf->CmdListFlag[pCmdSpiTxBuf->CmdCurrentList]	= CMD_MAXRESEND_NUM;	//��ǰ����Ϊ�������������Ҫ�ط�		
			}
			else{
				pCmdSpiTxBuf->CmdListFlag[pCmdSpiTxBuf->CmdCurrentList]	= CMD_REPLYSEND_NUM;	//��ǰ����Ϊ�ظ������Ҫ�ط�		
			}
			pCmdSpiTxBuf->CmdListNum += 1;																//������������+1
			
	return 1;//�������������ɹ�
	
}
//---------------------------------------------------------------------------
//˵����SpiRx������������������Ѱ�ҿյ������ռ�
//������* cmddata:���ݿռ��׵�ַ��cmdlen:���ݳ���
//���أ���������	
//---------------------------------------------------------------------------
u8 CmdSpiRxApply(u8 * cmddata ,u16 cmdlen)		
{
	u8	i = 0,j = 0;
										//����������������
			i = pCmdSpiRxBuf->CmdCurrentList ;			//��ô�ǰ��������λ��
			while(1 == CmdSpiRxBuf.CmdListFlag[i]){	//Ѱ�ҿյĴ�ģ���ַ�ռ�
				i++;
				if(CMDSPI_RXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiRxBuf->CmdCurrentList){
					return 0;		//���������������ɹ�
				}
			}
			pCmdSpiRxBuf->CmdCurrentList	=	i ;	 //��ǰ��������λ��
			pCmdSpiRxBuf->pCmd_Body_Current = & (pCmdSpiRxBuf->Cmd_Body[i]);	//������������׵�ַ
			
			for(j = 0; j < cmdlen ; j++){
				pCmdSpiRxBuf->pCmd_Body_Current->all[j] = cmddata[j];
			}
			pCmdSpiRxBuf->pCmd_Body_Current->part.HeaderHash	= Hash(pCmdSpiRxBuf->pCmd_Body_Current->part.Header , CMDSPI_HEADER_LEN);	//��������hashͷ
			pCmdSpiRxBuf->pCmd_Body_Current->part.TotalLength = cmdlen;		//��¼�����
			pCmdSpiRxBuf->CmdListFlag[pCmdSpiRxBuf->CmdCurrentList]	= 1;	//��ǰ������ɹ�		
			pCmdSpiRxBuf->CmdListNum += 1;																//������������+1

	return 1;//�������������ɹ�
	
}

//--------------------------------------------------------------------------- 	
// �ظ�������Ϻ���
// ken:����������ַ�������	
u16 CmdSpiReplyAppend(CMDSPI_BODY_TypeDef *pRplyStr)
{	u16	nRplyStrLen = 0;

	while(pRplyStr->all[nRplyStrLen] != '\0'){nRplyStrLen++;}	//Ѱ�ҽ�β
	//���볤��					
	pRplyStr->all[nRplyStrLen++] = '\r';
	pRplyStr->all[nRplyStrLen++] = '\n';	
	return nRplyStrLen;
}


//---------------------------------------------------------------------------
//˵�����ɹ���������һ��������β����	
//������void
//���أ����������ַ	
//---------------------------------------------------------------------------
/*
u8 CmdOver(u8 CmdFg)		//ken:����������������
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//��ǰ������ɹ�		
		pCmdBuf->CmdListNum += 1;														//������������+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//���������
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//��յ�ǰ����������������ָ��
	
	if(CMDSPI_RXLIST_LMT == pCmdBuf->CmdListNum){		//���������ռ�������EP����RXNAK�ȴ�״̬����������֮ǰ��������ʹ�ܽ���
			
	}
	return pCmdBuf;		//���ؿյ�ַ
}
*/
//---------------------------------------------------------------------------
//˵����USB����ּ����	
//������void
//���أ�������������ռ��ַ	
//---------------------------------------------------------------------------
/*
CMD_BODY_TypeDef * CmdPrase(u8 ListNum)		//ken:����������������
{	u16 StrIndex ,Strcnt;
	
	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;

	Strcnt = EP2Pindex;
		for(; Strcnt < EP2index ; Strcnt++){
			if(EP2ParseBuf[Strcnt] == '$'){	//�յ�����ͷ'$'
				pCmdBodyBuf = CmdApply();			//Ѱ�ҿյ�����������ռ��ַ				
			}
			if(pCmdBodyBuf) {								//������ɹ�����	
				if(StrIndex <= CMD_BUF_LEN){	//��������												
					pCmdBodyBuf->all[StrIndex++] = EP2RxBuf[Strcnt];
				
				}
			}		
		}
			if(NULL == pCmdBodyBuf){
				USB_SIL_Write(EP2_IN, MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
				
			}
	//��EP2ParseBuf�������������ݴ�����ϡ�
	SetEPRxStatus(ENDP2, EP_RX_NAK);		//EP2RX�ȴ���������λ
	EP2index = 0;
	SetEPRxStatus(ENDP2, EP_RX_VALID);	//����ʹ�ܽ���				
}
*/
                               
//---------------------------------------------------------------------------
//˵����USB����ִ�г���	
//������void
//���أ�������������ռ��ַ	
//---------------------------------------------------------------------------

void CmdSpiExecute(void)		//ִ��ɢת����
{	u16	HeadHash,i,j;	
	if(0 != pCmdSpiRxBuf->CmdListNum){			
//		StartTimeMs2 = ReadRunTime();
	 for(j = 0;j < pCmdSpiRxBuf->CmdListNum; j++){	//��������
		i = pCmdSpiRxBuf->CmdPrcList ;
		
			while(0 == pCmdSpiRxBuf->CmdListFlag[i]){	//Ѱ�Ҵ���������ռ�
				i++;
				if(CMDSPI_RXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiRxBuf->CmdPrcList){
					return;	//û����Ҫ���������		
				}
			}
		pCmdSpiRxBuf->CmdPrcList = i;
		pCmdSpiRxBuf->pCmd_Prc_Current = & (pCmdSpiRxBuf->Cmd_Body[i]);									//ָ��ǰ����������
	
		HeadHash = pCmdSpiRxBuf->pCmd_Prc_Current->part.HeaderHash;	//���Hashͷ
//		HeadHash = Hash(pCmdSpiRxBuf->pCmd_Prc_Current->part.Header , CMDSPI_HEADER_LEN);	//��������hashͷ
		//�������У��λ
							
		switch(HeadHash){		// ��ȡ�ͷ����ֵ���ж�
			case CMDSPI_HASH_NETCNT:	CmdFuncNETCNT(pCmdSpiRxBuf->pCmd_Prc_Current);	break;	//ken:JMP����
//			case CMD_HASH_STT:	CmdFuncSTT(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_RST:	CmdFuncRST(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_SUV:	CmdFuncSUV(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_SYS:	CmdFuncSYS(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_RNG:	CmdFuncRNG(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_UPD:	CmdFuncUPD(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_CHN:	CmdFuncCHN(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_FRQ:	CmdFuncFRQ(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_TXW:	CmdFuncTXW(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_GAN:	CmdFuncGAN(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_PWR:	CmdFuncPWR(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_SEN:	CmdFuncSEN(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_REG:	CmdFuncREG(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_TVG:	CmdFuncTVG(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_TRK:	CmdFuncTRK(pCmdBuf->pCmd_Prc_Current);			break;


			default:
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
					__NOP();
			
			break;		
			
		}
		if(pCmdSpiRxBuf->CmdListNum == CMDSPI_RXLIST_LMT){	//����ִ���������
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//����ʹ��EP2����
		}
		pCmdSpiRxBuf->CmdListNum -= 1;
		pCmdSpiRxBuf->CmdListFlag[i] = 0;	
		for(i = 0;i < CMDSPI_BUF_LEN;i++){		//������������
			pCmdSpiRxBuf->pCmd_Prc_Current->all[j] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
 }			
}

//=============================================================================================
//˵��:������������ģ���ַ��������ʽ���棬�ȸ�����������ַ�Ƚϣ���ͬ��������ÿ������һ�α����ַ�ռ�����
//����:pNewAdrָ����������ַ��AdrLen��ַ���ȣ��ɹ������ַ����������1�����򷵻�0��ʾ��ַ�ռ�������
//=============================================================================================
u8 CmdFuncNETCNT(CMDSPI_BODY_TypeDef * pCmdData)
{	si4431adrtype	NewAdr;	 //	u16 RpStrLen;	 
	uint8_t loopi,loopj,NetFlag = 0;//TmpSta;
	pReplyBuf = pCmdData;
	pReplyBuf->part.Dot0 = '\0';
		
	NewAdr.HexAdr.All32 = MyStrToHex(pCmdData->part.SourceAdr, CMDSPI_ADR_WIDTH);	//�������ģ���ַ	
	MyHexToStr(NewAdr.StrAdr ,NewAdr.HexAdr.All32 , CMDSPI_ADR_WIDTH)	;			
	
	for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){		//��������������ַ�Ƚ�
		if(1 == pJKNetAdr_Tab->TabFlag[loopi]){	
		 	if(pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 == NewAdr.HexAdr.All32){				
				NetFlag = 1;																					//��ģ��������
				pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//��������������				
				break;
			}
		}			
	}  
	if(0 == NetFlag){		//��ģ��δ����
		if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){		//������ģ���ַ����ռ���
	  //	Usart_SendString_End(USART1 , "JKNetAdrTab is Full!\r\n");
	  	return 0;	//û��ַ�ռ�������
		}
	  else{		//����ģ������
			for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){	//Ѱ�ҿյĴ�ģ���ַ�ռ�
				if(0 == pJKNetAdr_Tab->TabFlag[loopi]){
				 	pJKNetAdr_Tab->TabFlag[loopi] = 0x01;	//�ҵ��մ�ģ���ַ�ռ�
					pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//��ʼ������������
					pJKNetAdr_Tab->JKNetAdrTabCnt++;	//��ģ���ַ��������1
					break;
				}			
			}
		//	pJKNetAdr_Tab->JKNetNumTab[loopi] = NewAdr.All32;	//��¼��������ַ
			pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 = NewAdr.HexAdr.All32;	//��¼��������ַ
			MyHexToStr(pJKNetAdr_Tab->JKNetAdrTab[loopi].StrAdr ,pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 , CMDSPI_ADR_WIDTH)	;			
		}
	}
	MsgInsrt(pReplyBuf->all , RX_ADDRESS_Si4431.StrAdr , CMDSPI_ADR_WIDTH , TRUE);	//����Դ��ַ
	MsgInsrt(pReplyBuf->all , NewAdr.StrAdr , CMDSPI_ADR_WIDTH , TRUE);	//����Ŀ���ַ
	MsgInsrt(pReplyBuf->all , MSGRP_OK , MyStrLen(MSGRP_OK) , TRUE);	//����OK

	CmdSpiReplyAppend(pReplyBuf);	//�ظ������β
	
	NET_LED_TURN();							//��ģ�������ɹ�
	CmdSpiTxApply(FALSE ,pReplyBuf->all ,MyStrLen(pReplyBuf->all));				//������浽����������
	return 1;	//�Ѽ�¼������ģ���ַ
}


//======================================no  more==========================================//

