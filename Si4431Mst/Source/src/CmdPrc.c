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
u8	MsgReplyUNK[] = "$SEMUNK,013\r\n";	//Ó¦´ð²»ÊÇÄÏ·½µÚÈý°æ²âÉîÒÇµÄÃüÁî

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//ÃüÁîÊý¾ÝÌå



//CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//ÃüÁîÊý¾ÝÌå
//CMD_BUF_TypeDef CmdBuf ;	//ÃüÀí´¦Àí»º³åÇø
//CMD_BUF_TypeDef * pCmdBuf;	//Ö¸ÏòÃüÀí´¦Àí»º³åÇø

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
//ËµÃ÷£º½¨Á¢ÃüÁîË÷Òýº¯Êý£¬Ñ°ÕÒ¿ÕµÄË÷Òý¿Õ¼ä£¬°üÀ¨´®¿Ú,SPI,USBµÈÍ¨Ñ¶½Ó¿ÚµÄÊý¾ÝÃüÁî	
//²ÎÊý£ºport:Í¨Ñ¶½Ó¿ÚÀàÐÍ £»* cmddata:Êý¾Ý¿Õ¼äÊ×µØÖ·£»cmdlen:Êý¾Ý³¤¶È
//·µ»Ø£ºÃüÁî½¨Á¢Çé¿ö	
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
	
		while(1 == CmdBuf.CmdListFlag[loopi]){	//Ñ°ÕÒ¿ÕµÄ´ÓÄ£¿éµØÖ·¿Õ¼ä
			loopi++;
			if(CMD_RXLIST_LMT == loopi){
				loopi = 0;
			}
			else if(loopi == pCmdBuf->CmdCurrentList){
				return NULL;		//·µ»Ø¿ÕµØÖ·
			}
		}
		pCmdBuf->CmdCurrentList	=	loopi ;
		pCmdBuf->pCmd_Body_Current = & (pCmdBuf->Cmd_Body[loopi]);
		return (pCmdBuf);		//·µ»ØËù½¨Á¢µÄÃüÁîÊ×µØÖ·
	*/

	/*
	if(CmdProc.CMD_LIST.CmdNum<CMD_LMT) {
		// Ñ­»·ÁÐ±í Ñ°ÕÒ¿ÕBuffer CmdIndex×îÖÕÖ¸Ïò¿ÕµÄbuffer
		while(CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex]) {	//ken:ÕÒµ½ÓÐ¿ÕµÄË÷ÒýbufferÎªÖ¹
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
		pRxBuf = CmdProc.CMD_LIST.pCmdBuf+CmdProc.CMD_LIST.CmdIndex;	//ken:»ñµÃËù½¨Á¢µÄÃüÁîÊ×µØÖ·
		pRxBuf->part.CmdFlagPos = CmdProc.CMD_LIST.CmdIndex;			// ¼ÇÂ¼µ±Ç°ÃüÁî¶ÔÓ¦µÄFLAGÎ»ÖÃ ºÍpCmdPosÆäÊµÊÇÒ»ÑùµÄ
																		// pCmdPos		ÓÃÓÚÍâ²¿³ÌÐò
																		// CmdFlagPos 	ÈÃÃüÁî´®ËæÉíÐ¯´ø
		if(pCmdPos) {
			(*pCmdPos) = CmdProc.CMD_LIST.CmdIndex;						//ken:»ñµÃËù½¨Á¢µÄµ±Ç°´®¿Ú½ÓÊÕµÄÃüÁî¶ÔÓ¦µÄË÷ÒýºÅ
		}

		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] &= 0xff00;//ken:ÇåµÍ8Î»
		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] |= 'W';	//ken:±êÖ¾×Åµ±Ç°ÃüÁîÕýÔÚ½¨Á¢
//		CmdProc.CMD_LIST.CmdNum ++;		//ken:ÃüÁî¼ÆÊýÆ÷
	}
	*/
	
}



//---------------------------------------------------------------------------
//ËµÃ÷£º³É¹¦½ÓÊÕÍêÕûÒ»ÌõÃüÁîÊÕÎ²º¯Êý	
//²ÎÊý£ºvoid
//·µ»Ø£ºÃüÁî´¦ÀíÇøµØÖ·	
//---------------------------------------------------------------------------

CMD_BUF_TypeDef * CmdOver(u8 CmdFg)		//ken:½¨Á¢ÃüÁîË÷Òýº¯Êý
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//µ±Ç°ÃüÁî½¨Á¢³É¹¦		
		pCmdBuf->CmdListNum += 1;														//´ý´¦ÀíÃüÁîÊý+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//¼ÆËãÃüÁî³¤¶È
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//Çå¿Õµ±Ç°´ý´¦ÀíµÄÃüÁî´¦Àí»º³åÇøÖ¸Õë
	
	if(CMD_RXLIST_LMT == pCmdBuf->CmdListNum){		//ÃüÁî´ý´¦Àí¿Õ¼äÂú£¬ÈÃEP½øÈëRXNAKµÈ´ý×´Ì¬£¬´ý´¦ÀíÍêÖ®Ç°µÄÃüÁîÔÚÊ¹ÄÜ½ÓÊÕ
			
	}
	return pCmdBuf;		//·µ»Ø¿ÕµØÖ·
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºUSBÃüÁî·Ö¼ð³ÌÐò	
//²ÎÊý£ºvoid
//·µ»Ø£ºÃüÁî´ý´¦ÀíÇø¿Õ¼äµØÖ·	
//---------------------------------------------------------------------------
/*
CMD_BODY_TypeDef * CmdPrase(u8 ListNum)		//ken:½¨Á¢ÃüÁîË÷Òýº¯Êý
{	u16 StrIndex ,Strcnt;
	
	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;

	Strcnt = EP2Pindex;
		for(; Strcnt < EP2index ; Strcnt++){
			if(EP2ParseBuf[Strcnt] == '$'){	//ÊÕµ½ÃüÁîÍ·'$'
				pCmdBodyBuf = CmdApply();			//Ñ°ÕÒ¿ÕµÄÃüÁî´¦ÀíË÷Òý¿Õ¼äµØÖ·				
			}
			if(pCmdBodyBuf) {								//ÃüÁî½¨Á¢³É¹¦½øÈë	
				if(StrIndex <= CMD_BUF_LEN){	//ÃüÁîÄÚÈÝ												
					pCmdBodyBuf->all[StrIndex++] = EP2RxBuf[Strcnt];
				
				}
			}		
		}
			if(NULL == pCmdBodyBuf){
				USB_SIL_Write(EP2_IN, MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK
				
			}
	//ÔÚEP2ParseBuf»º³åÇøµÄÖÐÊý¾Ý´¦ÀíÍê±Ï¡£
	SetEPRxStatus(ENDP2, EP_RX_NAK);		//EP2RXµÈ´ý»º³åÇø¸´Î»
	EP2index = 0;
	SetEPRxStatus(ENDP2, EP_RX_VALID);	//ÖØÐÂÊ¹ÄÜ½ÓÊÕ				
}
*/
//---------------------------------------------------------------------------
//ËµÃ÷£ºUSBÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºvoid
//·µ»Ø£ºÃüÁî´ý´¦ÀíÇø¿Õ¼äµØÖ·	
//---------------------------------------------------------------------------

void CmdExecute(void)		//Ö´ÐÐÉ¢×ªº¯Êý
{	u16	HeadHash,loopi;
//	timems_t CmdExecutePassTime;
//	void ( *pExeFunc)(CMD_BODY_TypeDef *); 
//	u16 StrLen,StrIndex;		//StrCnt,,EP2StrLen

/*	
	if(EP2index != 0){	
		//SetEPRxStatus(ENDP2, EP_RX_NAK);		//µÈ´ý´¦ÀíEP2RxBufÖÐµÄÃüÁî
		for(EP2Pindex = 0; EP2Pindex < EP2index ; EP2Pindex++){
			if(EP2RxBuf[EP2Pindex] == '$'){	//ÊÕµ½ÃüÁîÍ·'$'
				if(CmdApply()){				//Ñ°ÕÒ¿ÕµÄÃüÁî´¦ÀíË÷Òý¿Õ¼äµØÖ·
					EP2RxOkFg	=	1;								//EP2ÊÕµ½Êý¾Ý
					StrIndex = 0;							
				}				
			}
			if(EP2RxOkFg) {									//ÕÒµ½¿ÕµÄÃüÁî´¦Àí¿Õ¼ä	
				if(StrIndex <= CMD_BUF_LEN){	//ÃüÁîÄÚÈÝ												
					pCmdBuf->pCmd_Body_Current->all[StrIndex++] = EP2RxBuf[EP2Pindex];
					
					if(StrIndex == CMD_LEN_CNT){	//»ñµÃÃüÁî³¤¶È
						StrLen = MyStrToNum(pCmdBuf->pCmd_Body_Current->part.CmdTotalLen , CMD_TOTAL_LEN);	//»ñµÃÃüÁî³¤¶È			
						if(0 == StrLen){			//³¤¶È²»¶Ô
							CmdOver(FALSE);			//ÃüÁî½ÓÊÕÊ§°Ü
							EP2RxOkFg = 0;			
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK
						}
					}
					if((StrLen != 0)&&(StrLen == StrIndex)){
						
						if('\n' == EP2RxBuf[EP2Pindex]){
							CmdOver(TRUE);			//ÃüÁî½ÓÊÕ³É¹¦
							EP2RxOkFg = 0;			//½ÓÊÕ³É¹¦£¬¼ÌÐø½âÎöÏÂÒ»ÌõÃüÁî
							StrIndex = 0;	
						}
						else{
							CmdOver(FALSE);			//ÃüÁî½ÓÊÕÊ§°Ü
							EP2RxOkFg = 0;	//½ÓÊÕ³É¹¦£¬¼ÌÐø½âÎöÏÂÒ»ÌõÃüÁî
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK
						}
					}	
//					else{//³¤¶ÈÓë0x0D 0x0A²»Æ¥Åä
//						EP2RxOkFg = 0;	
//						EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK						
//					}	
				}		
				else{		//³¬¹ý´æ·ÅÃüÁî´ý´¦Àí»º³åÇø´óÐ¡
					CmdOver(FALSE);			//ÃüÁî½ÓÊÕÊ§°Ü
					EP2RxOkFg = 0;			//³¤¶È²»¶Ô
					StrIndex = 0;					
					//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK
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
		
			while(0 == pCmdBuf->CmdListFlag[loopi]){	//Ñ°ÕÒ´ý´¦ÀíÃüÁî¿Õ¼ä
				loopi++;
				if(CMD_RXLIST_LMT == loopi){
					loopi = 0;
				}
				else if(loopi == pCmdBuf->CmdPrcList){
					return;	//Ã»ÓÐÐèÒª´¦ÀíµÄÃüÁî		
				}
			}
		pCmdBuf->CmdPrcList = loopi;
		pCmdBuf->pCmd_Prc_Current = & (pCmdBuf->Cmd_Body[loopi]);									//Ö¸Ïòµ±Ç°´ý´¦ÀíÃüÁî
	
	
		HeadHash = Hash(pCmdBuf->pCmd_Prc_Current->part.Header , CMD_HEADER_LEN);	//¼ÆËãÃüÁîhashÍ·
		//¼ìÑéÒì»òÐ£ÑéÎ»
		
			
		switch(HeadHash){		// ÌáÈ¡Áî´®Í·ÌØÕ÷Öµ²¢ÅÐ¶Ï
		//	case CMD_HASH_JMP:	CmdFuncJMP(pCmdBuf->pCmd_Prc_Current);	break;	//ken:JMPÃüÁî
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
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//Ïò¶Ëµã2·¢ËÍMsgReplyUNK
			break;		
			
		}
		if(pCmdBuf->CmdListNum == CMD_RXLIST_LMT){	//µ±´øÖ´ÐÐÃüÁî´¦ÀíÍê
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//ÖØÐÂÊ¹ÄÜEP2½ÓÊÕ
		}
		pCmdBuf->CmdListNum -= 1;
		pCmdBuf->CmdListFlag[loopi] = 0;	
		for(loopi = 0;loopi < CMD_BUF_LEN;loopi++){		//Çå¿ÕÃüÁî´¦Àí»º³åÇø
			pCmdBuf->pCmd_Prc_Current->all[loopi] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
			
}

/*
//---------------------------------------------------------------------------
//ËµÃ÷£ºSTTÆô¶¯²âÉîÒÇÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdJMPBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncSTT(CMD_BODY_TypeDef * pCmdSTTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSTTBody;
 
 	if(CmdCheck(pCmdSTTBody)){	//¼ìÑé³¤¶È	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·
		if('L' == pCmdSTTBody->part.CmdFuncType){
			goto ERROR;			
		}
		else if('S' == pCmdSTTBody->part.CmdFuncType){
			//·Ö¼ðÃüÁîÌå²¿·Ö¡£
			MsgCopy(pSttDat->all, pCmdSTTBody->part.Others, sizeof(pSttDat->all));
			SounderState.SwitchRefresh = 1;
			//	if('1' == pCmdBuf->pReplyBuf->part.Others[0] ){	//¿ªÆô²âÁ¿
			if('1' == pSttDat->bit.State ){	//¿ªÆô²âÁ¿	
				SounderState.OnOff         = ON;
			} 
			else{	//¹Ø±Õ²âÁ¿
				SounderState.OnOff         = OFF;
			}
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}	
	}
  else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºRST¸´Î»ÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdRSTBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncRST(CMD_BODY_TypeDef * pCmdRSTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdRSTBody;
	if(CmdCheck(pCmdRSTBody)){
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
	 	//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·	
		if('L' == pCmdRSTBody->part.CmdFuncType){	
		//	pCmdBuf->pReplyBuf = NULL;
		//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			goto ERROR;
		}
		else if('S' == pCmdRSTBody->part.CmdFuncType){
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
			RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
			EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî					
			pCmdBuf->pReplyBuf = NULL;
			RSTFg = 1; 
			DelayCom(300);
			//³ÌÐòÌø×ªµ½bootÇø
			JumpToBoot();
		}
	}
  else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºREG×¢²áÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdREGBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncREG(CMD_BODY_TypeDef * pCmdREGBody)
{	u16 RpStrLen ,iLoop;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	u32 RegData = 0x00;
	pCmdBuf->pReplyBuf = pCmdREGBody;
 	
	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			goto ERROR;
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			for(iLoop = 0; iLoop < 16;iLoop++){
				RegNum[iLoop] = pCmdREGBody->part.Others[iLoop];	//¸´ÖÆ×¢²áÂë
			}						
				if(Decrypt())
				{			 					

				  FLASH_Unlock();

					FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);					
					
					RegData 	= RegNum[19];		//½«8Î»×Ö·ûºÏ³É32Î»Õû×Ö	¹Ø¼üÊÇÈçºÎ¶Á³öÀ´
					RegData += RegNum[18] << 8;
					RegData += RegNum[17] << 16;
					RegData += RegNum[16] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//Ð´Èë×¢²áÊ±¼ä£¿
				 	FLASHStatus = FLASH_ProgramWord( (u32)REG_TIME_ADRESS, RegData);	//Ò»´ÎÐ´Ò»¸öÕû×Ö£¬32Î»³¤
				
					RegData 	= RegNum[23];		//½«8Î»×Ö·ûºÏ³É32Î»Õû×Ö	¹Ø¼üÊÇÈçºÎ¶Á³öÀ´
					RegData += RegNum[22] << 8;
					RegData += RegNum[21] << 16;
					RegData += RegNum[20] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//Ð´Èë×¢²áÊ±¼ä£¿
				 	FLASHStatus = FLASH_ProgramWord( (u32)(REG_TIME_ADRESS + 4), RegData);	//Ò»´ÎÐ´Ò»¸öÕû×Ö£¬32Î»³¤
					
					//  FLASH_LockBank1();
		  		FLASH_Lock();				
				//	Write_Flash_Byte(RegNum+16,dUseTime,8);	//ken:Ö»°ÑÊ¹ÓÃÊ±¼ä£¬×¢²áÊ±¼äÐ´µ½flashÀïÃæ£¬×¢²áÂëÃ»Ð´½øÈ¥
				//	Uart0_Tx(ESOK,7);								
					
//					MsgInsrt(pCmdBuf->pReplyBuf->all, &RegNum[20], 4 ,TRUE);
					MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
				}
				else{	//×¢²áÂë²»ÕýÈ·
					goto ERROR;	
				}
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºSYS×¢²áÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdSYSBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncSYS(CMD_BODY_TypeDef * pCmdSYSBody)
{	u16 RpStrLen,iLoop,errFlag = 0;
	u8	Tmp[6];
	pCmdBuf->pReplyBuf = pCmdSYSBody;
 	
	if(CmdCheck(pCmdSYSBody)){	//¼ìÑé³¤¶È	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·
		if('L' == pCmdSYSBody->part.CmdFuncType){
			for(iLoop=0; iLoop<10; iLoop++)	//ken:¹·ºÅÖÐÖ»ÄÜ³öÏÖ0-9 
			{
				if((pCmdBuf->pReplyBuf->part.Others[iLoop] < 0x30) || (pCmdBuf->pReplyBuf->part.Others[iLoop] > 0x39))	
				{
				 	errFlag = 1;
				}	
			}
			if(errFlag) 
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = 0x30;	//ken:´íÎóµÄ¹·ºÅ
			}
			else
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = pCmdBuf->pReplyBuf->part.Others[iLoop];	//ken:¶ÁÈ¡ÕýÈ·µÄ¹·ºÅ	
			
			}
			if(Dog_Key(dogID)==1){	//ken:¼ÆËã10Î»°µÂë¹·ºÅ
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
			else{	//¹·ºÅ²»¶Ô
			//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	
				goto ERROR;
			}
	
		}
		else if('S' == pCmdSYSBody->part.CmdFuncType){
			goto ERROR;
		}
	}
  else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;
				


	
}


//---------------------------------------------------------------------------
//ËµÃ÷£ºRNGÉèÖÃ²âÁ¿µµÎ»ÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdRNGBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncRNG(CMD_BODY_TypeDef * pCmdRNGBody)
{	u16 RpStrLen;
	u16	TmpRange;
 	pCmdBuf->pReplyBuf = pCmdRNGBody;
		
 if(CmdCheck(pCmdRNGBody)){	
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 	//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·	
	if('L' == pCmdRNGBody->part.CmdFuncType){
		goto ERROR;
	}
	else if('S' == pCmdRNGBody->part.CmdFuncType){
		if('1' == pCmdRNGBody->part.Others[0] ){	//×Ô¶¯»»µµ

		} 
		else{	//ÊÖ¶¯»»µµ
			
		//ken:²âÊÔµµÎ»²»ÄÜËæÊ±±ä£¬²»È»Ó°ÏìË®Éî¼ÆËã	
			TmpRange = 	(pCmdBuf->pReplyBuf->part.Others[2]) - '0';
		//	TmpRange = MyStrToNum( &(pCmdBuf->pReplyBuf->part.Others[2]) , 2);				 
			if(0< TmpRange < 8){	//Õý³£28MµÄµµÎ»1-7µµ
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;
//				
//				switch(TmpRange)
//				{
//					case 1:
//					TmpRange = TIMERBASE;	//¶ÔÓ¦15Ã×µµ£¬40hz(ÒòÎªÊÇ¶àÍ¨µÀÈç¹û8¸öÍ¨µÀÈ«¿ªÔòµ¥¶ÀÒ»¸öÖ»ÓÐ5Hz)£¬ÓÃÊ±25ms£¬PLCK1ÊÇ72Mhz(65535/72*10^6 = 0.9102*10^-3 ,0.9102*10^-3 * 28 = 0.0255)
//					break;
//					case 2:
//					TmpRange = TIMERBASE * 2^(grad -1);	//¶ÔÓ¦30Ã×µµ£¬20hz£¬ÓÃÊ±50ms£¬
//					break;
//					case 3:
//					TmpRange = 110;	//¶ÔÓ¦120Ã×µµ£¬10hz£¬ÓÃÊ±100ms£¬
//					break;
//					case 4:
//					TmpRange = 220;	//¶ÔÓ¦240Ã×µµ£¬5hz£¬ÓÃÊ±200ms£¬
//					break;
//					case 5:
//					TmpRange = 440;	//¶ÔÓ¦480Ã×µµ£¬2.5hz£¬ÓÃÊ±400ms£¬
//					break;
//					case 6:
//					TmpRange = 880;	//¶ÔÓ¦960Ã×µµ£¬1.25hz£¬ÓÃÊ±800ms£¬
//					break;
//
//					default:
//					TmpRange = 28;	//¶ÔÓ¦30Ã×µµ£¬20hz£¬ÓÃÊ±50ms£¬
//					break;	
//				}				
				
				SounderState.GradRefresh = 1;			//µµÎ»¸üÐÂ±êÖ¾Î»
				FiltProFlag=1;								
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);					
			}
			else if(0 == TmpRange){	
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;								
			}
			else{	//µµÎ»²ÎÊý²»ÕýÈ·
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			}	
		}		
	}
	else{
		goto ERROR;
	}
 }
 else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 }	
	
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
 	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºSUVÉèÖÃ²âÁ¿µµÎ»ÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdSUVBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncSUV(CMD_BODY_TypeDef * pCmdSUVBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSUVBody;

 	if(CmdCheck(pCmdSUVBody)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·	
		if('L' == pCmdSUVBody->part.CmdFuncType){

			MyNumToStr(pSuvDat->bit.Velocity ,SurvPara.Velocity, 6);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.Velocity, sizeof(pSuvDat->bit.Velocity) ,TRUE);
			MyNumToStr(pSuvDat->bit.LowLmt ,SurvPara.LowLmt, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.LowLmt, sizeof(pSuvDat->bit.LowLmt) ,TRUE);
			MyNumToStr(pSuvDat->bit.DeepLmt ,SurvPara.DeepLmt, 5);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.DeepLmt, sizeof(pSuvDat->bit.DeepLmt) ,TRUE);
			pSuvDat->bit.AlarmSw = MyNumToChar(SurvPara.AlarmSw);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSuvDat->bit.AlarmSw), sizeof(pSuvDat->bit.AlarmSw) ,TRUE);
			MyNumToStr(pSuvDat->bit.RefChn ,SurvPara.RefChn, 2);		// ÒÔÉÏÃ»ÓÐ²åÈë','ºÅ		
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.RefChn, sizeof(pSuvDat->bit.RefChn) ,TRUE);		
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£
	//		MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->all, sizeof(pSuvDat->all) ,TRUE);		
		}
		else if('S' == pCmdSUVBody->part.CmdFuncType){
			//·Ö¼ðÃüÁîÌå²¿·Ö¡£
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
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºCHNÉèÖÃ²âÁ¿µµÎ»ÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdCHNBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncCHN(CMD_BODY_TypeDef * pCmdCHNBody)
{	u16 RpStrLen;
	u8 Chn_Cnt,iLoop;
	pCmdBuf->pReplyBuf = pCmdCHNBody;

 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//¼ìÑé³¤¶È¼°Òì»òÎ»ÕýÈ·	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){				
			MyNumToStr(pChnDat->bit.ChnNum,ChanPara.Chn_Num, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnNum, sizeof(pChnDat->bit.ChnNum) ,TRUE);
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				pChnDat->bit.ChnName[iLoop]	= ChanPara.Chn_Name[iLoop] + 0x30;			
			}			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnName, sizeof(pChnDat->bit.ChnName) ,TRUE);				
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){						 
			//·Ö¼ðÃüÁîÌå²¿·Ö¡£
			MsgCopy(pChnDat->all, pCmdCHNBody->part.Others, sizeof(pChnDat->all));			
			
			ChanPara.Chn_Num = MyStrToNum(pChnDat->bit.ChnNum, 2);
			if(ChanPara.Chn_Num > MAXCHNUM){	//Í¨µÀºÅÉèÖÃ´íÎó		
				ChanPara.Chn_Num = 0;
				goto ERROR;			
			}
			
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				if(0x30 == pChnDat->bit.ChnName[iLoop]){	//ken:»ñµÃ¾ßÌåÍ¨µÀºÅ
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
			  if(0 == ChanPara.Chn_Name[Chn_Cnt]){	//Çå¿ÕÃ»Ñ¡ÖÐµÄÍ¨µÀ»Ø²¨¼ÇÂ¼Êý¾Ý
				for(iLoop=0; iLoop<AVEDEPTHLEN+1; iLoop++){
				     aveDepth[Chn_Cnt][iLoop] = 0; //±£´æ¸÷Í¨µÀÇ°50´Î¸÷10´ÎµÄÆ½¾ùÖµ£¬µÚ0µ¥Ôª±£´æÖ¸ÏòÖµ
					 echoTrend[Chn_Cnt][iLoop]= 0; //Ë®ÉîÇ÷ÊÆ
					 AveEchoWidth[Chn_Cnt][iLoop]= 0; //»Ø²¨¿í¶ÈÆ½¾ùÇ÷ÊÆs
				}
				for(iLoop=0; iLoop<PREDEPTHLEN+1; iLoop++){
				     preDepth[Chn_Cnt][iLoop]    = 0; //±£´æÇ°10´ÎË®ÉîÊý¾Ý £¬µÚ0µ¥Ôª±£´æÖ¸ÏòÖµ
					 echoStrenth[Chn_Cnt][iLoop] = 0; //±£´æÃ¿´Î»Ø²¨µÄÆ½¾ùÇ¿¶È£¬µÚ0µ¥Ôª±£´æÖ¸ÏòÖµ
					 echoWidth[Chn_Cnt][iLoop] = 0; 	//±£´æÃ¿´Î»Ø²¨µÄ¿í¶È£¬µÚ0µ¥Ôª±£´æÖ¸ÏòÖµ
					 TxPlusWidth[Chn_Cnt][iLoop] = 0;
				}		
		                                     
					//ken:³õÊ¼»¯¸÷Í¨µÀ»Ø²¨ÐÅÏ¢±äÁ¿
				RecInfo[Chn_Cnt].DepthTrend = 0;//0:Æ½»º£» 1:±äÇ³£»2:±äÉî
				RecInfo[Chn_Cnt].Depth = 0;
				RecInfo[Chn_Cnt].MaxEchoTime = GATEB;
				RecInfo[Chn_Cnt].MinEchoTime = GATEF;
				RecInfo[Chn_Cnt].EchoQuality = 0x00;
				RecInfo[Chn_Cnt].EchoCnt     = 0;
				RecInfo[Chn_Cnt].EchoNum     = 0;
				RecInfo[Chn_Cnt].NoechoCnt   = 0;
				RecInfo[Chn_Cnt].NoechoNum   = 0;
				RecInfo[Chn_Cnt].AutoLevel   = 0;//0£º×Ô¶¯Ä£Ê½ÏÂ¼õµµ£»1£º×Ô¶¯Ä£Ê½ÏÂ²»¶¨£»2£º×Ô¶¯Ä£Ê½ÏÂ¼Óµµ
				RecInfo[Chn_Cnt].CopyUnworkCnt   = 0;
				RecInfo[Chn_Cnt].GainDepthConnect   = 1;	//Ä¬ÈÏ×Ô¶¯¿ØÖÆµµÎ»Ê±£¬ÔöÒæ¼°Ë®ÉîÊÇ¹ØÁªµÄ¡£
				RecInfo[Chn_Cnt].GainDepthUWCnt = 0;				
			  }
			}
			SounderState.ChanRefresh = 1;	//ken:¸üÐÂÍ¨µÀ±êÖ¾»

			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºFRQÌ½Í·ÆµÂÊÉèÖÃÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdFRQBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncFRQ(CMD_BODY_TypeDef * pCmdFRQBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	pCmdBuf->pReplyBuf = pCmdFRQBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 							
				}
			}
			MyNumToStr(pFrqDat->bit.Frequency,RevPara[ChnName].Frequency, 3);			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Frequency, sizeof(pFrqDat->bit.Frequency) ,TRUE);				
			MyNumToStr(pFrqDat->bit.Draft,RevPara[ChnName].Draft, 3);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Draft, sizeof(pFrqDat->bit.Draft) ,TRUE);
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£

		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//·Ö¼ðÃüÁîÌå²¿·Ö¡£
			MsgCopy(pFrqDat->all, pCmdFRQBody->part.Others, sizeof(pFrqDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 
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
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºTXW·¢ÉäÂö¿íÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdTXWBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncTXW(CMD_BODY_TypeDef * pCmdTXWBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrTranWidth[4];
	pCmdBuf->pReplyBuf = pCmdTXWBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 							
				}
			}
			MyNumToStr(StrTranWidth,TranPara[ChnName].TrnWdth, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrTranWidth, sizeof(StrTranWidth) ,TRUE);				
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].TrnWdth   = MyStrToNum(pCmdTXWBody->part.Others , 4);	//×ª»»·¢ÉäÂö¿íµ¥Î»Î¢Ãë				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
		}
		else{
			goto ERROR;
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºGAN½ÓÊÕÔöÒæÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdGANBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncGAN(CMD_BODY_TypeDef * pCmdGANBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrGain[2];
	pCmdBuf->pReplyBuf = pCmdGANBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 							
				}
			}
			MyNumToStr(StrGain,RevPara[ChnName].Gain, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrGain, sizeof(StrGain) ,TRUE);				
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				RevPara[ChnIndex].Gain   = MyStrToNum(pCmdGANBody->part.Others , 2);	//×ª»»ÔöÒæ
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºPWR·¢Éä¹¦ÂÊÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdPWRBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncPWR(CMD_BODY_TypeDef * pCmdPWRBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrPwr;
	pCmdBuf->pReplyBuf = pCmdPWRBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//²éÑ¯È«²¿Í¨µÀ
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 							
				}
			}
			StrPwr = TranPara[ChnName].Pwr + 0x30 ;
			MsgInsrt(pCmdBuf->pReplyBuf->all, & StrPwr, 1 ,TRUE);				
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Pwr   = MyStrToNum(pCmdPWRBody->part.Others , 1);	//×ª»»¹¦ÂÊ				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºSENÒÖÖÆÂö¿í¡¢¹¦ÂÊ¡¢»Ø²¨ãÐÖµÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdSENBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
//---------------------------------------------------------------------------
void CmdFuncSEN(CMD_BODY_TypeDef * pCmdSENBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	float TmpBlank;
	pCmdBuf->pReplyBuf = pCmdSENBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//²éÑ¯È«²¿Í¨µÀ
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 							
				}
			}
			TmpBlank = (float)((float)TranPara[ChnName].ClrWdth / 1000) * ((float)SurvPara.Velocity / 1000);
			TranPara[ChnName].Blank = TmpBlank;	//ÒÖÖÆÂö¿í×ªÎªÒÖÖÆË®Éî
			MyNumToStr(pSenDat->bit.Blank ,TranPara[ChnName].Blank, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Blank, sizeof(pSenDat->bit.Blank) ,TRUE);
			MyNumToStr(pSenDat->bit.Threshold ,RevPara[ChnName].Shold, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Threshold, sizeof(pSenDat->bit.Threshold) ,TRUE);
			pSenDat->bit.Filter = MyNumToChar(RevPara[ChnName].Filt);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSenDat->bit.Filter), sizeof(pSenDat->bit.Filter) ,TRUE);			
			//²åÈë»Ø¸´ÃüÁîÌå²¿·Ö¡£	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//·Ö¼ðÃüÁîÌå²¿·Ö¡£
			MsgCopy(pSenDat->all, pCmdSENBody->part.Others, sizeof(pSenDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//ÉèÖÃÈ«²¿Í¨µÀ
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:»ñµÃÍ¨µÀºÅ	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:ÏÞÖÆÍ¨µÀºÅ
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:Í¨µÀºÅ¸ÄÎª1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Blank	= MyStrToNum(pSenDat->bit.Blank , 4);
				TmpBlank = (float)((float)TranPara[ChnIndex].Blank * 1000000) / ((float)SurvPara.Velocity);				
				TranPara[ChnIndex].ClrWdth = TmpBlank;	//ÒÖÖÆË®Éî×ªÎªÒÖÖÆÂö¿í
				RevPara[ChnIndex].Shold   = MyStrToNum(pSenDat->bit.Threshold , 2);
				RevPara[ChnIndex].Filt 		= MyCharToNum(pSenDat->bit.Filter);
				SounderState.TranRefresh[ChnIndex] = 1;		//ÐèÒªÕûºÏ
				SounderState.SensRefresh[ChnIndex] = 1;
//				SounderState.FiltRefresh[ChnIndex] = 1;
			}						
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);				
		}
		else{
			goto ERROR;
		}
	}
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºTVGÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdTVGBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
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
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºTRKË®µ×¸ú×ÙÃüÁîÖ´ÐÐ³ÌÐò	
//²ÎÊý£ºpCmdTRKBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
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
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//ËµÃ÷£ºUPDÉý¼¶ÃüÁîÖ´ÐÐ³ÌÐò£¬Ã¿´Î·¢ËÍ128×Ö½Ú³ÌÐò£¬´øÓÐµØÖ·	
//²ÎÊý£ºpCmdUPDBody ÃüÁîÄÚÈÝ
//·µ»Ø£º	
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
	else{	//¼ìÑé³¤¶È¼°Òì»òÎ»´íÎó
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//Ïò¶Ëµã2·¢ËÍ»Ø¸´ÃüÁî	
	pCmdBuf->pReplyBuf = NULL;			
}

*/
