/***********************************************
*Copyright 2010,South Marine R&D Dpt.
*All rights reserved.
*
*File Name: CmdPrc.c
*ID       : 
*Abstract : Command Process application
*
*Version NO.:1.0
*Writer     :Ken
*Date       :2010-10-26
**************************************************/

#include "stm32f10x.h"
//#include "system.h"
#include "Global.h"
#include "CmdPrc.h"
#include "GloVar.h"

/* Global variables ---------------------------------------------------------*/ 
uint8_t TestStr[] = "USART1TEST\r\n";
uint8_t TxNoReply[] = "TxNoReply\r\n";
uint8_t RxNotMatch[] = "RxNotMatch\r\n";
uint8_t RxMatch[] = "RxMatch\r\n";

uint8_t TestWord[] = "A";

uint8_t StrError[] = "Error!";

uint8_t MSGRP_OK[] = "OK\0";
uint8_t MSGRP_ERR[] = "ERR\0";
u8	MsgReplyUNK[] = "$SEMUNK,013\r\n";	//Ӧ�����Ϸ�����������ǵ�����

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//����������



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

                                
//---------------------------------------------------------------------------
//˵����������������������Ѱ�ҿյ������ռ䣬��������,SPI,USB��ͨѶ�ӿڵ���������	
//������port:ͨѶ�ӿ����� ��* cmddata:���ݿռ��׵�ַ��cmdlen:���ݳ���
//���أ���������	
//---------------------------------------------------------------------------
u8 CmdApply(CMD_PORT_TPYE port ,u8 * cmddata ,u16 cmdlen)		
{
	u8	loopi;
//	CMD_BUF_TypeDef * pCmdBufApp = NULL;
	switch(port){
		case (Spi1_Cmd_TxPort):
		
		break;
		case (Spi1_Cmd_RxPort):
		
		break;
		default 
		break;
	}
	/*
		loopi = pCmdBuf->CmdCurrentList ;
	
		while(1 == CmdBuf.CmdListFlag[loopi]){	//Ѱ�ҿյĴ�ģ���ַ�ռ�
			loopi++;
			if(CMD_RXLIST_LMT == loopi){
				loopi = 0;
			}
			else if(loopi == pCmdBuf->CmdCurrentList){
				return NULL;		//���ؿյ�ַ
			}
		}
		pCmdBuf->CmdCurrentList	=	loopi ;
		pCmdBuf->pCmd_Body_Current = & (pCmdBuf->Cmd_Body[loopi]);
		return (pCmdBuf);		//�����������������׵�ַ
	*/

	/*
	if(CmdProc.CMD_LIST.CmdNum<CMD_LMT) {
		// ѭ���б� Ѱ�ҿ�Buffer CmdIndex����ָ��յ�buffer
		while(CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex]) {	//ken:�ҵ��пյ�����bufferΪֹ
			CmdProc.CMD_LIST.CmdIndex++;
			if(CmdProc.CMD_LIST.CmdIndex>=CMD_LMT) {
				CmdProc.CMD_LIST.CmdIndex = 0;
			}

			LoopCnt++;
			if(LoopCnt>CMD_LMT) {
				return NULL;
			}
		}

		// 
		pRxBuf = CmdProc.CMD_LIST.pCmdBuf+CmdProc.CMD_LIST.CmdIndex;	//ken:����������������׵�ַ
		pRxBuf->part.CmdFlagPos = CmdProc.CMD_LIST.CmdIndex;			// ��¼��ǰ�����Ӧ��FLAGλ�� ��pCmdPos��ʵ��һ����
																		// pCmdPos		�����ⲿ����
																		// CmdFlagPos 	���������Я��
		if(pCmdPos) {
			(*pCmdPos) = CmdProc.CMD_LIST.CmdIndex;						//ken:����������ĵ�ǰ���ڽ��յ������Ӧ��������
		}

		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] &= 0xff00;//ken:���8λ
		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] |= 'W';	//ken:��־�ŵ�ǰ�������ڽ���
//		CmdProc.CMD_LIST.CmdNum ++;		//ken:���������
	}
	*/
	
}



//---------------------------------------------------------------------------
//˵�����ɹ���������һ��������β����	
//������void
//���أ����������ַ	
//---------------------------------------------------------------------------

CMD_BUF_TypeDef * CmdOver(u8 CmdFg)		//ken:����������������
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//��ǰ������ɹ�		
		pCmdBuf->CmdListNum += 1;														//������������+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//���������
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//��յ�ǰ����������������ָ��
	
	if(CMD_RXLIST_LMT == pCmdBuf->CmdListNum){		//���������ռ�������EP����RXNAK�ȴ�״̬����������֮ǰ��������ʹ�ܽ���
			
	}
	return pCmdBuf;		//���ؿյ�ַ
}

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

void CmdExecute(void)		//ִ��ɢת����
{	u16	HeadHash,loopi;
//	timems_t CmdExecutePassTime;
//	void ( *pExeFunc)(CMD_BODY_TypeDef *); 
//	u16 StrLen,StrIndex;		//StrCnt,,EP2StrLen

/*	
	if(EP2index != 0){	
		//SetEPRxStatus(ENDP2, EP_RX_NAK);		//�ȴ�����EP2RxBuf�е�����
		for(EP2Pindex = 0; EP2Pindex < EP2index ; EP2Pindex++){
			if(EP2RxBuf[EP2Pindex] == '$'){	//�յ�����ͷ'$'
				if(CmdApply()){				//Ѱ�ҿյ�����������ռ��ַ
					EP2RxOkFg	=	1;								//EP2�յ�����
					StrIndex = 0;							
				}				
			}
			if(EP2RxOkFg) {									//�ҵ��յ������ռ�	
				if(StrIndex <= CMD_BUF_LEN){	//��������												
					pCmdBuf->pCmd_Body_Current->all[StrIndex++] = EP2RxBuf[EP2Pindex];
					
					if(StrIndex == CMD_LEN_CNT){	//��������
						StrLen = MyStrToNum(pCmdBuf->pCmd_Body_Current->part.CmdTotalLen , CMD_TOTAL_LEN);	//��������			
						if(0 == StrLen){			//���Ȳ���
							CmdOver(FALSE);			//�������ʧ��
							EP2RxOkFg = 0;			
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
						}
					}
					if((StrLen != 0)&&(StrLen == StrIndex)){
						
						if('\n' == EP2RxBuf[EP2Pindex]){
							CmdOver(TRUE);			//������ճɹ�
							EP2RxOkFg = 0;			//���ճɹ�������������һ������
							StrIndex = 0;	
						}
						else{
							CmdOver(FALSE);			//�������ʧ��
							EP2RxOkFg = 0;	//���ճɹ�������������һ������
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
						}
					}	
//					else{//������0x0D 0x0A��ƥ��
//						EP2RxOkFg = 0;	
//						EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK						
//					}	
				}		
				else{		//����������������������С
					CmdOver(FALSE);			//�������ʧ��
					EP2RxOkFg = 0;			//���Ȳ���
					StrIndex = 0;					
					//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
				}
			}		
		}
		EP2Pindex = 0;
		EP2index = 0;

	}
*/	
	if(0 != pCmdBuf->CmdListNum){			
//		StartTimeMs2 = ReadRunTime();
		loopi = pCmdBuf->CmdPrcList ;
		
			while(0 == pCmdBuf->CmdListFlag[loopi]){	//Ѱ�Ҵ���������ռ�
				loopi++;
				if(CMD_RXLIST_LMT == loopi){
					loopi = 0;
				}
				else if(loopi == pCmdBuf->CmdPrcList){
					return;	//û����Ҫ���������		
				}
			}
		pCmdBuf->CmdPrcList = loopi;
		pCmdBuf->pCmd_Prc_Current = & (pCmdBuf->Cmd_Body[loopi]);									//ָ��ǰ����������
	
	
		HeadHash = Hash(pCmdBuf->pCmd_Prc_Current->part.Header , CMD_HEADER_LEN);	//��������hashͷ
		//�������У��λ
		
			
		switch(HeadHash){		// ��ȡ�ͷ����ֵ���ж�
		//	case CMD_HASH_JMP:	CmdFuncJMP(pCmdBuf->pCmd_Prc_Current);	break;	//ken:JMP����
			case CMD_HASH_STT:	CmdFuncSTT(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_RST:	CmdFuncRST(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_SUV:	CmdFuncSUV(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_SYS:	CmdFuncSYS(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_RNG:	CmdFuncRNG(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_UPD:	CmdFuncUPD(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_CHN:	CmdFuncCHN(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_FRQ:	CmdFuncFRQ(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_TXW:	CmdFuncTXW(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_GAN:	CmdFuncGAN(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_PWR:	CmdFuncPWR(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_SEN:	CmdFuncSEN(pCmdBuf->pCmd_Prc_Current);			break;
			case CMD_HASH_REG:	CmdFuncREG(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_TVG:	CmdFuncTVG(pCmdBuf->pCmd_Prc_Current);			break;
//			case CMD_HASH_TRK:	CmdFuncTRK(pCmdBuf->pCmd_Prc_Current);			break;


			default:
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//��˵�2����MsgReplyUNK
			break;		
			
		}
		if(pCmdBuf->CmdListNum == CMD_RXLIST_LMT){	//����ִ���������
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//����ʹ��EP2����
		}
		pCmdBuf->CmdListNum -= 1;
		pCmdBuf->CmdListFlag[loopi] = 0;	
		for(loopi = 0;loopi < CMD_BUF_LEN;loopi++){		//������������
			pCmdBuf->pCmd_Prc_Current->all[loopi] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
			
}

/*
//---------------------------------------------------------------------------
//˵����STT��������������ִ�г���	
//������pCmdJMPBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncSTT(CMD_BODY_TypeDef * pCmdSTTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSTTBody;
 
 	if(CmdCheck(pCmdSTTBody)){	//���鳤��	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//���鳤�ȼ����λ��ȷ
		if('L' == pCmdSTTBody->part.CmdFuncType){
			goto ERROR;			
		}
		else if('S' == pCmdSTTBody->part.CmdFuncType){
			//�ּ������岿�֡�
			MsgCopy(pSttDat->all, pCmdSTTBody->part.Others, sizeof(pSttDat->all));
			SounderState.SwitchRefresh = 1;
			//	if('1' == pCmdBuf->pReplyBuf->part.Others[0] ){	//��������
			if('1' == pSttDat->bit.State ){	//��������	
				SounderState.OnOff         = ON;
			} 
			else{	//�رղ���
				SounderState.OnOff         = OFF;
			}
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}	
	}
  else{	//���鳤�ȼ����λ����
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//˵����RST��λ����ִ�г���	
//������pCmdRSTBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncRST(CMD_BODY_TypeDef * pCmdRSTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdRSTBody;
	if(CmdCheck(pCmdRSTBody)){
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
	 	//���鳤�ȼ����λ��ȷ	
		if('L' == pCmdRSTBody->part.CmdFuncType){	
		//	pCmdBuf->pReplyBuf = NULL;
		//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			goto ERROR;
		}
		else if('S' == pCmdRSTBody->part.CmdFuncType){
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
			RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
			EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����					
			pCmdBuf->pReplyBuf = NULL;
			RSTFg = 1; 
			DelayCom(300);
			//������ת��boot��
			JumpToBoot();
		}
	}
  else{	//���鳤�ȼ����λ����
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//˵����REGע������ִ�г���	
//������pCmdREGBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncREG(CMD_BODY_TypeDef * pCmdREGBody)
{	u16 RpStrLen ,iLoop;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	u32 RegData = 0x00;
	pCmdBuf->pReplyBuf = pCmdREGBody;
 	
	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//���鳤�ȼ����λ��ȷ	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			goto ERROR;
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			for(iLoop = 0; iLoop < 16;iLoop++){
				RegNum[iLoop] = pCmdREGBody->part.Others[iLoop];	//����ע����
			}						
				if(Decrypt())
				{			 					

				  FLASH_Unlock();

					FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);					
					
					RegData 	= RegNum[19];		//��8λ�ַ��ϳ�32λ����	�ؼ�����ζ�����
					RegData += RegNum[18] << 8;
					RegData += RegNum[17] << 16;
					RegData += RegNum[16] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//д��ע��ʱ�䣿
				 	FLASHStatus = FLASH_ProgramWord( (u32)REG_TIME_ADRESS, RegData);	//һ��дһ�����֣�32λ��
				
					RegData 	= RegNum[23];		//��8λ�ַ��ϳ�32λ����	�ؼ�����ζ�����
					RegData += RegNum[22] << 8;
					RegData += RegNum[21] << 16;
					RegData += RegNum[20] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//д��ע��ʱ�䣿
				 	FLASHStatus = FLASH_ProgramWord( (u32)(REG_TIME_ADRESS + 4), RegData);	//һ��дһ�����֣�32λ��
					
					//  FLASH_LockBank1();
		  		FLASH_Lock();				
				//	Write_Flash_Byte(RegNum+16,dUseTime,8);	//ken:ֻ��ʹ��ʱ�䣬ע��ʱ��д��flash���棬ע����ûд��ȥ
				//	Uart0_Tx(ESOK,7);								
					
//					MsgInsrt(pCmdBuf->pReplyBuf->all, &RegNum[20], 4 ,TRUE);
					MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
				}
				else{	//ע���벻��ȷ
					goto ERROR;	
				}
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����SYSע������ִ�г���	
//������pCmdSYSBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncSYS(CMD_BODY_TypeDef * pCmdSYSBody)
{	u16 RpStrLen,iLoop,errFlag = 0;
	u8	Tmp[6];
	pCmdBuf->pReplyBuf = pCmdSYSBody;
 	
	if(CmdCheck(pCmdSYSBody)){	//���鳤��	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//���鳤�ȼ����λ��ȷ
		if('L' == pCmdSYSBody->part.CmdFuncType){
			for(iLoop=0; iLoop<10; iLoop++)	//ken:������ֻ�ܳ���0-9 
			{
				if((pCmdBuf->pReplyBuf->part.Others[iLoop] < 0x30) || (pCmdBuf->pReplyBuf->part.Others[iLoop] > 0x39))	
				{
				 	errFlag = 1;
				}	
			}
			if(errFlag) 
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = 0x30;	//ken:����Ĺ���
			}
			else
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = pCmdBuf->pReplyBuf->part.Others[iLoop];	//ken:��ȡ��ȷ�Ĺ���	
			
			}
			if(Dog_Key(dogID)==1){	//ken:����10λ���빷��
			//	sprintf(pCmdBuf->pReplyBuf->part.Others,"%s,%s,%ld,%ld,0%,%s,%2.1f,SDE-28M\r\n",Firmware,Serial,regTime/6,useTime/6,dogID,batVol);	
			//	MyNumToStr(pSysDat->bit.FirmWare , Firmware , 6);
				MsgInsrt(pCmdBuf->pReplyBuf->all, FirmWare, sizeof(FirmWare) ,TRUE);
				MsgInsrt(pCmdBuf->pReplyBuf->all, HardWare, sizeof(HardWare) ,TRUE);
				MsgInsrt(pCmdBuf->pReplyBuf->all, Serial, sizeof(Serial) ,TRUE);
				MsgInsrt(pCmdBuf->pReplyBuf->all, dogID, sizeof(dogID) ,TRUE);
				MsgInsrt(pCmdBuf->pReplyBuf->all, "SDE28S", 6 ,TRUE);
				MyNumToStr(Tmp ,(regTime/6), 6);
				MsgInsrt(pCmdBuf->pReplyBuf->all, Tmp, 6 ,TRUE);
				MyNumToStr(Tmp ,(useTime/6), 6);
				MsgInsrt(pCmdBuf->pReplyBuf->all, Tmp, 6 ,TRUE);
				MyNumToStr(Tmp ,(batVol * 10), 3);
				MsgInsrt(pCmdBuf->pReplyBuf->all, Tmp, 3 ,TRUE);
			}
			else{	//���Ų���
			//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	
				goto ERROR;
			}
	
		}
		else if('S' == pCmdSYSBody->part.CmdFuncType){
			goto ERROR;
		}
	}
  else{	//���鳤�ȼ����λ����
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;
				


	
}


//---------------------------------------------------------------------------
//˵����RNG���ò�����λ����ִ�г���	
//������pCmdRNGBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncRNG(CMD_BODY_TypeDef * pCmdRNGBody)
{	u16 RpStrLen;
	u16	TmpRange;
 	pCmdBuf->pReplyBuf = pCmdRNGBody;
		
 if(CmdCheck(pCmdRNGBody)){	
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 	//���鳤�ȼ����λ��ȷ	
	if('L' == pCmdRNGBody->part.CmdFuncType){
		goto ERROR;
	}
	else if('S' == pCmdRNGBody->part.CmdFuncType){
		if('1' == pCmdRNGBody->part.Others[0] ){	//�Զ�����

		} 
		else{	//�ֶ�����
			
		//ken:���Ե�λ������ʱ�䣬��ȻӰ��ˮ�����	
			TmpRange = 	(pCmdBuf->pReplyBuf->part.Others[2]) - '0';
		//	TmpRange = MyStrToNum( &(pCmdBuf->pReplyBuf->part.Others[2]) , 2);				 
			if(0< TmpRange < 8){	//����28M�ĵ�λ1-7��
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;
//				
//				switch(TmpRange)
//				{
//					case 1:
//					TmpRange = TIMERBASE;	//��Ӧ15�׵���40hz(��Ϊ�Ƕ�ͨ�����8��ͨ��ȫ���򵥶�һ��ֻ��5Hz)����ʱ25ms��PLCK1��72Mhz(65535/72*10^6 = 0.9102*10^-3 ,0.9102*10^-3 * 28 = 0.0255)
//					break;
//					case 2:
//					TmpRange = TIMERBASE * 2^(grad -1);	//��Ӧ30�׵���20hz����ʱ50ms��
//					break;
//					case 3:
//					TmpRange = 110;	//��Ӧ120�׵���10hz����ʱ100ms��
//					break;
//					case 4:
//					TmpRange = 220;	//��Ӧ240�׵���5hz����ʱ200ms��
//					break;
//					case 5:
//					TmpRange = 440;	//��Ӧ480�׵���2.5hz����ʱ400ms��
//					break;
//					case 6:
//					TmpRange = 880;	//��Ӧ960�׵���1.25hz����ʱ800ms��
//					break;
//
//					default:
//					TmpRange = 28;	//��Ӧ30�׵���20hz����ʱ50ms��
//					break;	
//				}				
				
				SounderState.GradRefresh = 1;			//��λ���±�־λ
				FiltProFlag=1;								
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);					
			}
			else if(0 == TmpRange){	
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;								
			}
			else{	//��λ��������ȷ
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			}	
		}		
	}
	else{
		goto ERROR;
	}
 }
 else{	//���鳤�ȼ����λ����
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 }	
	
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
 	
}

//---------------------------------------------------------------------------
//˵����SUV���ò�����λ����ִ�г���	
//������pCmdSUVBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncSUV(CMD_BODY_TypeDef * pCmdSUVBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSUVBody;

 	if(CmdCheck(pCmdSUVBody)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//���鳤�ȼ����λ��ȷ	
		if('L' == pCmdSUVBody->part.CmdFuncType){

			MyNumToStr(pSuvDat->bit.Velocity ,SurvPara.Velocity, 6);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.Velocity, sizeof(pSuvDat->bit.Velocity) ,TRUE);
			MyNumToStr(pSuvDat->bit.LowLmt ,SurvPara.LowLmt, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.LowLmt, sizeof(pSuvDat->bit.LowLmt) ,TRUE);
			MyNumToStr(pSuvDat->bit.DeepLmt ,SurvPara.DeepLmt, 5);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.DeepLmt, sizeof(pSuvDat->bit.DeepLmt) ,TRUE);
			pSuvDat->bit.AlarmSw = MyNumToChar(SurvPara.AlarmSw);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSuvDat->bit.AlarmSw), sizeof(pSuvDat->bit.AlarmSw) ,TRUE);
			MyNumToStr(pSuvDat->bit.RefChn ,SurvPara.RefChn, 2);		// ����û�в���','��		
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.RefChn, sizeof(pSuvDat->bit.RefChn) ,TRUE);		
			//����ظ������岿�֡�
	//		MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->all, sizeof(pSuvDat->all) ,TRUE);		
		}
		else if('S' == pCmdSUVBody->part.CmdFuncType){
			//�ּ������岿�֡�
			MsgCopy(pSuvDat->all, pCmdSUVBody->part.Others, sizeof(pSuvDat->all));
			
			SurvPara.Velocity = MyStrToNum(pSuvDat->bit.Velocity , 6);
			SurvPara.LowLmt = MyStrToNum(pSuvDat->bit.LowLmt , 4);
			SurvPara.DeepLmt = MyStrToNum(pSuvDat->bit.DeepLmt , 5);
			SurvPara.AlarmSw = MyCharToNum(pSuvDat->bit.AlarmSw);
			SurvPara.RefChn = MyStrToNum(pSuvDat->bit.RefChn , 2);						 
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//˵����CHN���ò�����λ����ִ�г���	
//������pCmdCHNBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncCHN(CMD_BODY_TypeDef * pCmdCHNBody)
{	u16 RpStrLen;
	u8 Chn_Cnt,iLoop;
	pCmdBuf->pReplyBuf = pCmdCHNBody;

 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//���鳤�ȼ����λ��ȷ	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){				
			MyNumToStr(pChnDat->bit.ChnNum,ChanPara.Chn_Num, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnNum, sizeof(pChnDat->bit.ChnNum) ,TRUE);
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				pChnDat->bit.ChnName[iLoop]	= ChanPara.Chn_Name[iLoop] + 0x30;			
			}			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnName, sizeof(pChnDat->bit.ChnName) ,TRUE);				
			//����ظ������岿�֡�		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){						 
			//�ּ������岿�֡�
			MsgCopy(pChnDat->all, pCmdCHNBody->part.Others, sizeof(pChnDat->all));			
			
			ChanPara.Chn_Num = MyStrToNum(pChnDat->bit.ChnNum, 2);
			if(ChanPara.Chn_Num > MAXCHNUM){	//ͨ�������ô���		
				ChanPara.Chn_Num = 0;
				goto ERROR;			
			}
			
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				if(0x30 == pChnDat->bit.ChnName[iLoop]){	//ken:��þ���ͨ����
					ChanPara.Chn_Name[iLoop] = 0;	
				}
				else if(0x31 == pChnDat->bit.ChnName[iLoop]){	
					ChanPara.Chn_Name[iLoop] = 1;
				}
				else{
					goto ERROR;
				}
			
			}	
			for(Chn_Cnt = 0;Chn_Cnt < MAXCHNUM ;Chn_Cnt++){
			  if(0 == ChanPara.Chn_Name[Chn_Cnt]){	//���ûѡ�е�ͨ���ز���¼����
				for(iLoop=0; iLoop<AVEDEPTHLEN+1; iLoop++){
				     aveDepth[Chn_Cnt][iLoop] = 0; //�����ͨ��ǰ50�θ�10�ε�ƽ��ֵ����0��Ԫ����ָ��ֵ
					 echoTrend[Chn_Cnt][iLoop]= 0; //ˮ������
					 AveEchoWidth[Chn_Cnt][iLoop]= 0; //�ز����ƽ������s
				}
				for(iLoop=0; iLoop<PREDEPTHLEN+1; iLoop++){
				     preDepth[Chn_Cnt][iLoop]    = 0; //����ǰ10��ˮ������ ����0��Ԫ����ָ��ֵ
					 echoStrenth[Chn_Cnt][iLoop] = 0; //����ÿ�λز���ƽ��ǿ�ȣ���0��Ԫ����ָ��ֵ
					 echoWidth[Chn_Cnt][iLoop] = 0; 	//����ÿ�λز��Ŀ�ȣ���0��Ԫ����ָ��ֵ
					 TxPlusWidth[Chn_Cnt][iLoop] = 0;
				}		
		                                     
					//ken:��ʼ����ͨ���ز���Ϣ����
				RecInfo[Chn_Cnt].DepthTrend = 0;//0:ƽ���� 1:��ǳ��2:����
				RecInfo[Chn_Cnt].Depth = 0;
				RecInfo[Chn_Cnt].MaxEchoTime = GATEB;
				RecInfo[Chn_Cnt].MinEchoTime = GATEF;
				RecInfo[Chn_Cnt].EchoQuality = 0x00;
				RecInfo[Chn_Cnt].EchoCnt     = 0;
				RecInfo[Chn_Cnt].EchoNum     = 0;
				RecInfo[Chn_Cnt].NoechoCnt   = 0;
				RecInfo[Chn_Cnt].NoechoNum   = 0;
				RecInfo[Chn_Cnt].AutoLevel   = 0;//0���Զ�ģʽ�¼�����1���Զ�ģʽ�²�����2���Զ�ģʽ�¼ӵ�
				RecInfo[Chn_Cnt].CopyUnworkCnt   = 0;
				RecInfo[Chn_Cnt].GainDepthConnect   = 1;	//Ĭ���Զ����Ƶ�λʱ�����漰ˮ���ǹ����ġ�
				RecInfo[Chn_Cnt].GainDepthUWCnt = 0;				
			  }
			}
			SounderState.ChanRefresh = 1;	//ken:����ͨ����־�

			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//˵����FRQ̽ͷƵ����������ִ�г���	
//������pCmdFRQBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncFRQ(CMD_BODY_TypeDef * pCmdFRQBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	pCmdBuf->pReplyBuf = pCmdFRQBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:ͨ���Ÿ�Ϊ1-8 							
				}
			}
			MyNumToStr(pFrqDat->bit.Frequency,RevPara[ChnName].Frequency, 3);			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Frequency, sizeof(pFrqDat->bit.Frequency) ,TRUE);				
			MyNumToStr(pFrqDat->bit.Draft,RevPara[ChnName].Draft, 3);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Draft, sizeof(pFrqDat->bit.Draft) ,TRUE);
			//����ظ������岿�֡�

		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//�ּ������岿�֡�
			MsgCopy(pFrqDat->all, pCmdFRQBody->part.Others, sizeof(pFrqDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:ͨ���Ÿ�Ϊ1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				RevPara[ChnIndex].Draft   = MyStrToNum(pFrqDat->bit.Draft , 3);
				RevPara[ChnIndex].Frequency = MyStrToNum(pFrqDat->bit.Frequency , 3);
			}			
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);			
			 
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����TXW������������ִ�г���	
//������pCmdTXWBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncTXW(CMD_BODY_TypeDef * pCmdTXWBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrTranWidth[4];
	pCmdBuf->pReplyBuf = pCmdTXWBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:ͨ���Ÿ�Ϊ1-8 							
				}
			}
			MyNumToStr(StrTranWidth,TranPara[ChnName].TrnWdth, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrTranWidth, sizeof(StrTranWidth) ,TRUE);				
			//����ظ������岿�֡�		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:ͨ���Ÿ�Ϊ1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].TrnWdth   = MyStrToNum(pCmdTXWBody->part.Others , 4);	//ת����������λ΢��				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����GAN������������ִ�г���	
//������pCmdGANBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncGAN(CMD_BODY_TypeDef * pCmdGANBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrGain[2];
	pCmdBuf->pReplyBuf = pCmdGANBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:ͨ���Ÿ�Ϊ1-8 							
				}
			}
			MyNumToStr(StrGain,RevPara[ChnName].Gain, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrGain, sizeof(StrGain) ,TRUE);				
			//����ظ������岿�֡�	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:ͨ���Ÿ�Ϊ1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				RevPara[ChnIndex].Gain   = MyStrToNum(pCmdGANBody->part.Others , 2);	//ת������
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����PWR���书������ִ�г���	
//������pCmdPWRBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncPWR(CMD_BODY_TypeDef * pCmdPWRBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrPwr;
	pCmdBuf->pReplyBuf = pCmdPWRBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//��ѯȫ��ͨ��
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:ͨ���Ÿ�Ϊ1-8 							
				}
			}
			StrPwr = TranPara[ChnName].Pwr + 0x30 ;
			MsgInsrt(pCmdBuf->pReplyBuf->all, & StrPwr, 1 ,TRUE);				
			//����ظ������岿�֡�	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:ͨ���Ÿ�Ϊ1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Pwr   = MyStrToNum(pCmdPWRBody->part.Others , 1);	//ת������				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����SEN�����������ʡ��ز���ֵ����ִ�г���	
//������pCmdSENBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncSEN(CMD_BODY_TypeDef * pCmdSENBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	float TmpBlank;
	pCmdBuf->pReplyBuf = pCmdSENBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//��ѯȫ��ͨ��
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:ͨ���Ÿ�Ϊ1-8 							
				}
			}
			TmpBlank = (float)((float)TranPara[ChnName].ClrWdth / 1000) * ((float)SurvPara.Velocity / 1000);
			TranPara[ChnName].Blank = TmpBlank;	//��������תΪ����ˮ��
			MyNumToStr(pSenDat->bit.Blank ,TranPara[ChnName].Blank, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Blank, sizeof(pSenDat->bit.Blank) ,TRUE);
			MyNumToStr(pSenDat->bit.Threshold ,RevPara[ChnName].Shold, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Threshold, sizeof(pSenDat->bit.Threshold) ,TRUE);
			pSenDat->bit.Filter = MyNumToChar(RevPara[ChnName].Filt);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSenDat->bit.Filter), sizeof(pSenDat->bit.Filter) ,TRUE);			
			//����ظ������岿�֡�	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//�ּ������岿�֡�
			MsgCopy(pSenDat->all, pCmdSENBody->part.Others, sizeof(pSenDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//����ȫ��ͨ��
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:���ͨ����	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:����ͨ����
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:ͨ���Ÿ�Ϊ1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Blank	= MyStrToNum(pSenDat->bit.Blank , 4);
				TmpBlank = (float)((float)TranPara[ChnIndex].Blank * 1000000) / ((float)SurvPara.Velocity);				
				TranPara[ChnIndex].ClrWdth = TmpBlank;	//����ˮ��תΪ��������
				RevPara[ChnIndex].Shold   = MyStrToNum(pSenDat->bit.Threshold , 2);
				RevPara[ChnIndex].Filt 		= MyCharToNum(pSenDat->bit.Filter);
				SounderState.TranRefresh[ChnIndex] = 1;		//��Ҫ����
				SounderState.SensRefresh[ChnIndex] = 1;
//				SounderState.FiltRefresh[ChnIndex] = 1;
			}						
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);				
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����TVG����ִ�г���	
//������pCmdTVGBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncTVG(CMD_BODY_TypeDef * pCmdTVGBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdTVGBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
	
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����TRKˮ�׸�������ִ�г���	
//������pCmdTRKBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncTRK(CMD_BODY_TypeDef * pCmdTRKBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdTRKBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
	
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//˵����UPD��������ִ�г���ÿ�η���128�ֽڳ��򣬴��е�ַ	
//������pCmdUPDBody ��������
//���أ�	
//---------------------------------------------------------------------------
void CmdFuncUPD(CMD_BODY_TypeDef * pCmdUPDBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdUPDBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
		}
		else{
			goto ERROR;
		}
	}
	else{	//���鳤�ȼ����λ����
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//��˵�2���ͻظ�����	
	pCmdBuf->pReplyBuf = NULL;			
}

*/
