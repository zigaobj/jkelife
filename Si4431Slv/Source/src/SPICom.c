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
#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"
#include "SPICom.h"	
#include "Si4431App.h"

//------------------------------------------------------------------------------------//

//@near u8 SPI1_TxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Tx
//u8 SPI2_TxBuf[BufferSize] = {0};		//SPIz_Buffer_Tx
//@near u8 SPI1_RxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Rx
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
//@near u8 SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1���ջ�����

//@near u8 txLog[TXLOGLEN];
@near u8 SPI1ByteNum;		 //��Э��0ʱ���ڰ����յ��������ֽ�����������һ������Ľ���
//u8 SPI2_ParseBuf[SPI2PARSEBUFLEN];//����1���ջ�����

CMDSPI_BUF_TypeDef		CmdSpiTxBuf;										//����ͻ�����
CMDSPI_BUF_TypeDef	*	pCmdSpiTxBuf;								//ָ������ͻ�����
CMDSPI_BUF_TypeDef		CmdSpiRxBuf;										//������ջ�����
CMDSPI_BUF_TypeDef	*	pCmdSpiRxBuf;								//ָ��������ջ�����
CMDSPI_BODY_TypeDef  ReplyBuf;								//Ӧ�𻺳���
CMDSPI_BODY_TypeDef * pReplyBuf;								//Ӧ�𻺳���
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
			case CMDSPI_HASH_NETCNT:	CmdFuncNETCNT(pCmdSpiRxBuf->pCmd_Prc_Current);	break;	

			default:
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
					nop();
			
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
	u8 loopi,loopj,NetFlag = 0;//TmpSta;
	//����ɾ�����ٷ�������NETCNT����
	GPIO_WriteReverse(LEDS_PORT, Q1_PIN);		
	
	return 1;	//�Ѽ�¼������ģ���ַ
}

//========================================================================================//




//======================================no  more==========================================//

