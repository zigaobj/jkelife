<<<<<<< .mine
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
u8	MsgReplyUNK[] = "$SEMUNK,013\r\n";	//应答不是南方第三版测深仪的命令

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体



//CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//命令数据体
//CMD_BUF_TypeDef CmdBuf ;	//命理处理缓冲区
/*
	u8		CmdListNum;													//待处理的命令个数
	u8		CmdCurrentList;
	u8		CmdListFlag[CMD_LISTLMT];						//记录命令处理缓冲使用情况，0表示对应索引空，1表示索引内有待处理的命令
 	CMD_BODY_TypeDef * pCmd_Body_Current;							//指向待处理的命令处理缓冲区
	CMD_BODY_TypeDef	 Cmd_Body[CMD_LISTLMT];	//命令处理缓冲空间
	CMD_BODY_TypeDef * pReplyBuf;							//应答缓冲区	
*/
//CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

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
//说明：建立命令索引函数，寻找空的索引空间，包括串口,SPI,USB等通讯接口的数据命令	
//参数：port:通讯接口类型 ；* cmddata:数据空间首地址；cmdlen:数据长度
//返回：命令建立情况	
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
	
		while(1 == CmdBuf.CmdListFlag[loopi]){	//寻找空的从模块地址空间
			loopi++;
			if(CMD_RXLIST_LMT == loopi){
				loopi = 0;
			}
			else if(loopi == pCmdBuf->CmdCurrentList){
				return NULL;		//返回空地址
			}
		}
		pCmdBuf->CmdCurrentList	=	loopi ;
		pCmdBuf->pCmd_Body_Current = & (pCmdBuf->Cmd_Body[loopi]);
		return (pCmdBuf);		//返回所建立的命令首地址
	*/

	/*
	if(CmdProc.CMD_LIST.CmdNum<CMD_LMT) {
		// 循环列表 寻找空Buffer CmdIndex最终指向空的buffer
		while(CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex]) {	//ken:找到有空的索引buffer为止
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
		pRxBuf = CmdProc.CMD_LIST.pCmdBuf+CmdProc.CMD_LIST.CmdIndex;	//ken:获得所建立的命令首地址
		pRxBuf->part.CmdFlagPos = CmdProc.CMD_LIST.CmdIndex;			// 记录当前命令对应的FLAG位置 和pCmdPos其实是一样的
																		// pCmdPos		用于外部程序
																		// CmdFlagPos 	让命令串随身携带
		if(pCmdPos) {
			(*pCmdPos) = CmdProc.CMD_LIST.CmdIndex;						//ken:获得所建立的当前串口接收的命令对应的索引号
		}

		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] &= 0xff00;//ken:清低8位
		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] |= 'W';	//ken:标志着当前命令正在建立
//		CmdProc.CMD_LIST.CmdNum ++;		//ken:命令计数器
	}
	*/
	
}



//---------------------------------------------------------------------------
//说明：成功接收完整一条命令收尾函数	
//参数：void
//返回：命令处理区地址	
//---------------------------------------------------------------------------

CMD_BUF_TypeDef * CmdOver(u8 CmdFg)		//ken:建立命令索引函数
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
		pCmdBuf->CmdListNum += 1;														//待处理命令数+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//计算命令长度
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//清空当前待处理的命令处理缓冲区指针
	
	if(CMD_RXLIST_LMT == pCmdBuf->CmdListNum){		//命令待处理空间满，让EP进入RXNAK等待状态，待处理完之前的命令在使能接收
			
	}
	return pCmdBuf;		//返回空地址
}

//---------------------------------------------------------------------------
//说明：USB命令分拣程序	
//参数：void
//返回：命令待处理区空间地址	
//---------------------------------------------------------------------------
/*
CMD_BODY_TypeDef * CmdPrase(u8 ListNum)		//ken:建立命令索引函数
{	u16 StrIndex ,Strcnt;
	
	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;

	Strcnt = EP2Pindex;
		for(; Strcnt < EP2index ; Strcnt++){
			if(EP2ParseBuf[Strcnt] == '$'){	//收到命令头'$'
				pCmdBodyBuf = CmdApply();			//寻找空的命令处理索引空间地址				
			}
			if(pCmdBodyBuf) {								//命令建立成功进入	
				if(StrIndex <= CMD_BUF_LEN){	//命令内容												
					pCmdBodyBuf->all[StrIndex++] = EP2RxBuf[Strcnt];
				
				}
			}		
		}
			if(NULL == pCmdBodyBuf){
				USB_SIL_Write(EP2_IN, MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
				
			}
	//在EP2ParseBuf缓冲区的中数据处理完毕。
	SetEPRxStatus(ENDP2, EP_RX_NAK);		//EP2RX等待缓冲区复位
	EP2index = 0;
	SetEPRxStatus(ENDP2, EP_RX_VALID);	//重新使能接收				
}
*/
//---------------------------------------------------------------------------
//说明：USB命令执行程序	
//参数：void
//返回：命令待处理区空间地址	
//---------------------------------------------------------------------------

void CmdExecute(void)		//执行散转函数
{	u16	HeadHash,loopi;
//	timems_t CmdExecutePassTime;
//	void ( *pExeFunc)(CMD_BODY_TypeDef *); 
//	u16 StrLen,StrIndex;		//StrCnt,,EP2StrLen

/*	
	if(EP2index != 0){	
		//SetEPRxStatus(ENDP2, EP_RX_NAK);		//等待处理EP2RxBuf中的命令
		for(EP2Pindex = 0; EP2Pindex < EP2index ; EP2Pindex++){
			if(EP2RxBuf[EP2Pindex] == '$'){	//收到命令头'$'
				if(CmdApply()){				//寻找空的命令处理索引空间地址
					EP2RxOkFg	=	1;								//EP2收到数据
					StrIndex = 0;							
				}				
			}
			if(EP2RxOkFg) {									//找到空的命令处理空间	
				if(StrIndex <= CMD_BUF_LEN){	//命令内容												
					pCmdBuf->pCmd_Body_Current->all[StrIndex++] = EP2RxBuf[EP2Pindex];
					
					if(StrIndex == CMD_LEN_CNT){	//获得命令长度
						StrLen = MyStrToNum(pCmdBuf->pCmd_Body_Current->part.CmdTotalLen , CMD_TOTAL_LEN);	//获得命令长度			
						if(0 == StrLen){			//长度不对
							CmdOver(FALSE);			//命令接收失败
							EP2RxOkFg = 0;			
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
						}
					}
					if((StrLen != 0)&&(StrLen == StrIndex)){
						
						if('\n' == EP2RxBuf[EP2Pindex]){
							CmdOver(TRUE);			//命令接收成功
							EP2RxOkFg = 0;			//接收成功，继续解析下一条命令
							StrIndex = 0;	
						}
						else{
							CmdOver(FALSE);			//命令接收失败
							EP2RxOkFg = 0;	//接收成功，继续解析下一条命令
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
						}
					}	
//					else{//长度与0x0D 0x0A不匹配
//						EP2RxOkFg = 0;	
//						EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK						
//					}	
				}		
				else{		//超过存放命令待处理缓冲区大小
					CmdOver(FALSE);			//命令接收失败
					EP2RxOkFg = 0;			//长度不对
					StrIndex = 0;					
					//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
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
		
			while(0 == pCmdBuf->CmdListFlag[loopi]){	//寻找待处理命令空间
				loopi++;
				if(CMD_RXLIST_LMT == loopi){
					loopi = 0;
				}
				else if(loopi == pCmdBuf->CmdPrcList){
					return;	//没有需要处理的命令		
				}
			}
		pCmdBuf->CmdPrcList = loopi;
		pCmdBuf->pCmd_Prc_Current = & (pCmdBuf->Cmd_Body[loopi]);									//指向当前待处理命令
	
	
		HeadHash = Hash(pCmdBuf->pCmd_Prc_Current->part.Header , CMD_HEADER_LEN);	//计算命令hash头
		//检验异或校验位
		
			
		switch(HeadHash){		// 提取令串头特征值并判断
		//	case CMD_HASH_JMP:	CmdFuncJMP(pCmdBuf->pCmd_Prc_Current);	break;	//ken:JMP命令
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
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
			break;		
			
		}
		if(pCmdBuf->CmdListNum == CMD_RXLIST_LMT){	//当带执行命令处理完
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//重新使能EP2接收
		}
		pCmdBuf->CmdListNum -= 1;
		pCmdBuf->CmdListFlag[loopi] = 0;	
		for(loopi = 0;loopi < CMD_BUF_LEN;loopi++){		//清空命令处理缓冲区
			pCmdBuf->pCmd_Prc_Current->all[loopi] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
			
}

/*
//---------------------------------------------------------------------------
//说明：STT启动测深仪命令执行程序	
//参数：pCmdJMPBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSTT(CMD_BODY_TypeDef * pCmdSTTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSTTBody;
 
 	if(CmdCheck(pCmdSTTBody)){	//检验长度	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//检验长度及异或位正确
		if('L' == pCmdSTTBody->part.CmdFuncType){
			goto ERROR;			
		}
		else if('S' == pCmdSTTBody->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pSttDat->all, pCmdSTTBody->part.Others, sizeof(pSttDat->all));
			SounderState.SwitchRefresh = 1;
			//	if('1' == pCmdBuf->pReplyBuf->part.Others[0] ){	//开启测量
			if('1' == pSttDat->bit.State ){	//开启测量	
				SounderState.OnOff         = ON;
			} 
			else{	//关闭测量
				SounderState.OnOff         = OFF;
			}
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}	
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//说明：RST复位命令执行程序	
//参数：pCmdRSTBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncRST(CMD_BODY_TypeDef * pCmdRSTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdRSTBody;
	if(CmdCheck(pCmdRSTBody)){
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
	 	//检验长度及异或位正确	
		if('L' == pCmdRSTBody->part.CmdFuncType){	
		//	pCmdBuf->pReplyBuf = NULL;
		//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			goto ERROR;
		}
		else if('S' == pCmdRSTBody->part.CmdFuncType){
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
			RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
			EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令					
			pCmdBuf->pReplyBuf = NULL;
			RSTFg = 1; 
			DelayCom(300);
			//程序跳转到boot区
			JumpToBoot();
		}
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//说明：REG注册命令执行程序	
//参数：pCmdREGBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncREG(CMD_BODY_TypeDef * pCmdREGBody)
{	u16 RpStrLen ,iLoop;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	u32 RegData = 0x00;
	pCmdBuf->pReplyBuf = pCmdREGBody;
 	
	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			goto ERROR;
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			for(iLoop = 0; iLoop < 16;iLoop++){
				RegNum[iLoop] = pCmdREGBody->part.Others[iLoop];	//复制注册码
			}						
				if(Decrypt())
				{			 					

				  FLASH_Unlock();

					FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);					
					
					RegData 	= RegNum[19];		//将8位字符合成32位整字	关键是如何读出来
					RegData += RegNum[18] << 8;
					RegData += RegNum[17] << 16;
					RegData += RegNum[16] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//写入注册时间？
				 	FLASHStatus = FLASH_ProgramWord( (u32)REG_TIME_ADRESS, RegData);	//一次写一个整字，32位长
				
					RegData 	= RegNum[23];		//将8位字符合成32位整字	关键是如何读出来
					RegData += RegNum[22] << 8;
					RegData += RegNum[21] << 16;
					RegData += RegNum[20] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//写入注册时间？
				 	FLASHStatus = FLASH_ProgramWord( (u32)(REG_TIME_ADRESS + 4), RegData);	//一次写一个整字，32位长
					
					//  FLASH_LockBank1();
		  		FLASH_Lock();				
				//	Write_Flash_Byte(RegNum+16,dUseTime,8);	//ken:只把使用时间，注册时间写到flash里面，注册码没写进去
				//	Uart0_Tx(ESOK,7);								
					
//					MsgInsrt(pCmdBuf->pReplyBuf->all, &RegNum[20], 4 ,TRUE);
					MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
				}
				else{	//注册码不正确
					goto ERROR;	
				}
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：SYS注册命令执行程序	
//参数：pCmdSYSBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSYS(CMD_BODY_TypeDef * pCmdSYSBody)
{	u16 RpStrLen,iLoop,errFlag = 0;
	u8	Tmp[6];
	pCmdBuf->pReplyBuf = pCmdSYSBody;
 	
	if(CmdCheck(pCmdSYSBody)){	//检验长度	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//检验长度及异或位正确
		if('L' == pCmdSYSBody->part.CmdFuncType){
			for(iLoop=0; iLoop<10; iLoop++)	//ken:狗号中只能出现0-9 
			{
				if((pCmdBuf->pReplyBuf->part.Others[iLoop] < 0x30) || (pCmdBuf->pReplyBuf->part.Others[iLoop] > 0x39))	
				{
				 	errFlag = 1;
				}	
			}
			if(errFlag) 
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = 0x30;	//ken:错误的狗号
			}
			else
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = pCmdBuf->pReplyBuf->part.Others[iLoop];	//ken:读取正确的狗号	
			
			}
			if(Dog_Key(dogID)==1){	//ken:计算10位暗码狗号
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
			else{	//狗号不对
			//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	
				goto ERROR;
			}
	
		}
		else if('S' == pCmdSYSBody->part.CmdFuncType){
			goto ERROR;
		}
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;
				


	
}


//---------------------------------------------------------------------------
//说明：RNG设置测量档位命令执行程序	
//参数：pCmdRNGBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncRNG(CMD_BODY_TypeDef * pCmdRNGBody)
{	u16 RpStrLen;
	u16	TmpRange;
 	pCmdBuf->pReplyBuf = pCmdRNGBody;
		
 if(CmdCheck(pCmdRNGBody)){	
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 	//检验长度及异或位正确	
	if('L' == pCmdRNGBody->part.CmdFuncType){
		goto ERROR;
	}
	else if('S' == pCmdRNGBody->part.CmdFuncType){
		if('1' == pCmdRNGBody->part.Others[0] ){	//自动换档

		} 
		else{	//手动换档
			
		//ken:测试档位不能随时变，不然影响水深计算	
			TmpRange = 	(pCmdBuf->pReplyBuf->part.Others[2]) - '0';
		//	TmpRange = MyStrToNum( &(pCmdBuf->pReplyBuf->part.Others[2]) , 2);				 
			if(0< TmpRange < 8){	//正常28M的档位1-7档
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;
//				
//				switch(TmpRange)
//				{
//					case 1:
//					TmpRange = TIMERBASE;	//对应15米档，40hz(因为是多通道如果8个通道全开则单独一个只有5Hz)，用时25ms，PLCK1是72Mhz(65535/72*10^6 = 0.9102*10^-3 ,0.9102*10^-3 * 28 = 0.0255)
//					break;
//					case 2:
//					TmpRange = TIMERBASE * 2^(grad -1);	//对应30米档，20hz，用时50ms，
//					break;
//					case 3:
//					TmpRange = 110;	//对应120米档，10hz，用时100ms，
//					break;
//					case 4:
//					TmpRange = 220;	//对应240米档，5hz，用时200ms，
//					break;
//					case 5:
//					TmpRange = 440;	//对应480米档，2.5hz，用时400ms，
//					break;
//					case 6:
//					TmpRange = 880;	//对应960米档，1.25hz，用时800ms，
//					break;
//
//					default:
//					TmpRange = 28;	//对应30米档，20hz，用时50ms，
//					break;	
//				}				
				
				SounderState.GradRefresh = 1;			//档位更新标志位
				FiltProFlag=1;								
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);					
			}
			else if(0 == TmpRange){	
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;								
			}
			else{	//档位参数不正确
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			}	
		}		
	}
	else{
		goto ERROR;
	}
 }
 else{	//检验长度及异或位错误
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 }	
	
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
 	
}

//---------------------------------------------------------------------------
//说明：SUV设置测量档位命令执行程序	
//参数：pCmdSUVBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSUV(CMD_BODY_TypeDef * pCmdSUVBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSUVBody;

 	if(CmdCheck(pCmdSUVBody)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdSUVBody->part.CmdFuncType){

			MyNumToStr(pSuvDat->bit.Velocity ,SurvPara.Velocity, 6);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.Velocity, sizeof(pSuvDat->bit.Velocity) ,TRUE);
			MyNumToStr(pSuvDat->bit.LowLmt ,SurvPara.LowLmt, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.LowLmt, sizeof(pSuvDat->bit.LowLmt) ,TRUE);
			MyNumToStr(pSuvDat->bit.DeepLmt ,SurvPara.DeepLmt, 5);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.DeepLmt, sizeof(pSuvDat->bit.DeepLmt) ,TRUE);
			pSuvDat->bit.AlarmSw = MyNumToChar(SurvPara.AlarmSw);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSuvDat->bit.AlarmSw), sizeof(pSuvDat->bit.AlarmSw) ,TRUE);
			MyNumToStr(pSuvDat->bit.RefChn ,SurvPara.RefChn, 2);		// 以上没有插入','号		
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.RefChn, sizeof(pSuvDat->bit.RefChn) ,TRUE);		
			//插入回复命令体部分。
	//		MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->all, sizeof(pSuvDat->all) ,TRUE);		
		}
		else if('S' == pCmdSUVBody->part.CmdFuncType){
			//分拣命令体部分。
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//说明：CHN设置测量档位命令执行程序	
//参数：pCmdCHNBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncCHN(CMD_BODY_TypeDef * pCmdCHNBody)
{	u16 RpStrLen;
	u8 Chn_Cnt,iLoop;
	pCmdBuf->pReplyBuf = pCmdCHNBody;

 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){				
			MyNumToStr(pChnDat->bit.ChnNum,ChanPara.Chn_Num, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnNum, sizeof(pChnDat->bit.ChnNum) ,TRUE);
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				pChnDat->bit.ChnName[iLoop]	= ChanPara.Chn_Name[iLoop] + 0x30;			
			}			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnName, sizeof(pChnDat->bit.ChnName) ,TRUE);				
			//插入回复命令体部分。		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){						 
			//分拣命令体部分。
			MsgCopy(pChnDat->all, pCmdCHNBody->part.Others, sizeof(pChnDat->all));			
			
			ChanPara.Chn_Num = MyStrToNum(pChnDat->bit.ChnNum, 2);
			if(ChanPara.Chn_Num > MAXCHNUM){	//通道号设置错误		
				ChanPara.Chn_Num = 0;
				goto ERROR;			
			}
			
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				if(0x30 == pChnDat->bit.ChnName[iLoop]){	//ken:获得具体通道号
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
			  if(0 == ChanPara.Chn_Name[Chn_Cnt]){	//清空没选中的通道回波记录数据
				for(iLoop=0; iLoop<AVEDEPTHLEN+1; iLoop++){
				     aveDepth[Chn_Cnt][iLoop] = 0; //保存各通道前50次各10次的平均值，第0单元保存指向值
					 echoTrend[Chn_Cnt][iLoop]= 0; //水深趋势
					 AveEchoWidth[Chn_Cnt][iLoop]= 0; //回波宽度平均趋势s
				}
				for(iLoop=0; iLoop<PREDEPTHLEN+1; iLoop++){
				     preDepth[Chn_Cnt][iLoop]    = 0; //保存前10次水深数据 ，第0单元保存指向值
					 echoStrenth[Chn_Cnt][iLoop] = 0; //保存每次回波的平均强度，第0单元保存指向值
					 echoWidth[Chn_Cnt][iLoop] = 0; 	//保存每次回波的宽度，第0单元保存指向值
					 TxPlusWidth[Chn_Cnt][iLoop] = 0;
				}		
		                                     
					//ken:初始化各通道回波信息变量
				RecInfo[Chn_Cnt].DepthTrend = 0;//0:平缓； 1:变浅；2:变深
				RecInfo[Chn_Cnt].Depth = 0;
				RecInfo[Chn_Cnt].MaxEchoTime = GATEB;
				RecInfo[Chn_Cnt].MinEchoTime = GATEF;
				RecInfo[Chn_Cnt].EchoQuality = 0x00;
				RecInfo[Chn_Cnt].EchoCnt     = 0;
				RecInfo[Chn_Cnt].EchoNum     = 0;
				RecInfo[Chn_Cnt].NoechoCnt   = 0;
				RecInfo[Chn_Cnt].NoechoNum   = 0;
				RecInfo[Chn_Cnt].AutoLevel   = 0;//0：自动模式下减档；1：自动模式下不定；2：自动模式下加档
				RecInfo[Chn_Cnt].CopyUnworkCnt   = 0;
				RecInfo[Chn_Cnt].GainDepthConnect   = 1;	//默认自动控制档位时，增益及水深是关联的。
				RecInfo[Chn_Cnt].GainDepthUWCnt = 0;				
			  }
			}
			SounderState.ChanRefresh = 1;	//ken:更新通道标志�

			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//说明：FRQ探头频率设置命令执行程序	
//参数：pCmdFRQBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncFRQ(CMD_BODY_TypeDef * pCmdFRQBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	pCmdBuf->pReplyBuf = pCmdFRQBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(pFrqDat->bit.Frequency,RevPara[ChnName].Frequency, 3);			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Frequency, sizeof(pFrqDat->bit.Frequency) ,TRUE);				
			MyNumToStr(pFrqDat->bit.Draft,RevPara[ChnName].Draft, 3);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Draft, sizeof(pFrqDat->bit.Draft) ,TRUE);
			//插入回复命令体部分。

		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pFrqDat->all, pCmdFRQBody->part.Others, sizeof(pFrqDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TXW发射脉宽命令执行程序	
//参数：pCmdTXWBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncTXW(CMD_BODY_TypeDef * pCmdTXWBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrTranWidth[4];
	pCmdBuf->pReplyBuf = pCmdTXWBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(StrTranWidth,TranPara[ChnName].TrnWdth, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrTranWidth, sizeof(StrTranWidth) ,TRUE);				
			//插入回复命令体部分。		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].TrnWdth   = MyStrToNum(pCmdTXWBody->part.Others , 4);	//转换发射脉宽单位微秒				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：GAN接收增益命令执行程序	
//参数：pCmdGANBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncGAN(CMD_BODY_TypeDef * pCmdGANBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrGain[2];
	pCmdBuf->pReplyBuf = pCmdGANBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(StrGain,RevPara[ChnName].Gain, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrGain, sizeof(StrGain) ,TRUE);				
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				RevPara[ChnIndex].Gain   = MyStrToNum(pCmdGANBody->part.Others , 2);	//转换增益
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：PWR发射功率命令执行程序	
//参数：pCmdPWRBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncPWR(CMD_BODY_TypeDef * pCmdPWRBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrPwr;
	pCmdBuf->pReplyBuf = pCmdPWRBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//查询全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			StrPwr = TranPara[ChnName].Pwr + 0x30 ;
			MsgInsrt(pCmdBuf->pReplyBuf->all, & StrPwr, 1 ,TRUE);				
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Pwr   = MyStrToNum(pCmdPWRBody->part.Others , 1);	//转换功率				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：SEN抑制脉宽、功率、回波阈值命令执行程序	
//参数：pCmdSENBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSEN(CMD_BODY_TypeDef * pCmdSENBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	float TmpBlank;
	pCmdBuf->pReplyBuf = pCmdSENBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//查询全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			TmpBlank = (float)((float)TranPara[ChnName].ClrWdth / 1000) * ((float)SurvPara.Velocity / 1000);
			TranPara[ChnName].Blank = TmpBlank;	//抑制脉宽转为抑制水深
			MyNumToStr(pSenDat->bit.Blank ,TranPara[ChnName].Blank, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Blank, sizeof(pSenDat->bit.Blank) ,TRUE);
			MyNumToStr(pSenDat->bit.Threshold ,RevPara[ChnName].Shold, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Threshold, sizeof(pSenDat->bit.Threshold) ,TRUE);
			pSenDat->bit.Filter = MyNumToChar(RevPara[ChnName].Filt);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSenDat->bit.Filter), sizeof(pSenDat->bit.Filter) ,TRUE);			
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pSenDat->all, pCmdSENBody->part.Others, sizeof(pSenDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Blank	= MyStrToNum(pSenDat->bit.Blank , 4);
				TmpBlank = (float)((float)TranPara[ChnIndex].Blank * 1000000) / ((float)SurvPara.Velocity);				
				TranPara[ChnIndex].ClrWdth = TmpBlank;	//抑制水深转为抑制脉宽
				RevPara[ChnIndex].Shold   = MyStrToNum(pSenDat->bit.Threshold , 2);
				RevPara[ChnIndex].Filt 		= MyCharToNum(pSenDat->bit.Filter);
				SounderState.TranRefresh[ChnIndex] = 1;		//需要整合
				SounderState.SensRefresh[ChnIndex] = 1;
//				SounderState.FiltRefresh[ChnIndex] = 1;
			}						
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);				
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TVG命令执行程序	
//参数：pCmdTVGBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TRK水底跟踪命令执行程序	
//参数：pCmdTRKBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：UPD升级命令执行程序，每次发送128字节程序，带有地址	
//参数：pCmdUPDBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;			
}

*/
=======
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
u8	MsgReplyUNK[] = "$SEMUNK,013\r\n";	//应答不是南方第三版测深仪的命令

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体



//CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//命令数据体
//CMD_BUF_TypeDef CmdBuf ;	//命理处理缓冲区
//CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

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
//说明：建立命令索引函数，寻找空的索引空间，包括串口,SPI,USB等通讯接口的数据命令	
//参数：port:通讯接口类型 ；* cmddata:数据空间首地址；cmdlen:数据长度
//返回：命令建立情况	
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
	
		while(1 == CmdBuf.CmdListFlag[loopi]){	//寻找空的从模块地址空间
			loopi++;
			if(CMD_RXLIST_LMT == loopi){
				loopi = 0;
			}
			else if(loopi == pCmdBuf->CmdCurrentList){
				return NULL;		//返回空地址
			}
		}
		pCmdBuf->CmdCurrentList	=	loopi ;
		pCmdBuf->pCmd_Body_Current = & (pCmdBuf->Cmd_Body[loopi]);
		return (pCmdBuf);		//返回所建立的命令首地址
	*/

	/*
	if(CmdProc.CMD_LIST.CmdNum<CMD_LMT) {
		// 循环列表 寻找空Buffer CmdIndex最终指向空的buffer
		while(CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex]) {	//ken:找到有空的索引buffer为止
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
		pRxBuf = CmdProc.CMD_LIST.pCmdBuf+CmdProc.CMD_LIST.CmdIndex;	//ken:获得所建立的命令首地址
		pRxBuf->part.CmdFlagPos = CmdProc.CMD_LIST.CmdIndex;			// 记录当前命令对应的FLAG位置 和pCmdPos其实是一样的
																		// pCmdPos		用于外部程序
																		// CmdFlagPos 	让命令串随身携带
		if(pCmdPos) {
			(*pCmdPos) = CmdProc.CMD_LIST.CmdIndex;						//ken:获得所建立的当前串口接收的命令对应的索引号
		}

		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] &= 0xff00;//ken:清低8位
		CmdProc.CMD_LIST.pListFlag[CmdProc.CMD_LIST.CmdIndex] |= 'W';	//ken:标志着当前命令正在建立
//		CmdProc.CMD_LIST.CmdNum ++;		//ken:命令计数器
	}
	*/
	
}



//---------------------------------------------------------------------------
//说明：成功接收完整一条命令收尾函数	
//参数：void
//返回：命令处理区地址	
//---------------------------------------------------------------------------

CMD_BUF_TypeDef * CmdOver(u8 CmdFg)		//ken:建立命令索引函数
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
		pCmdBuf->CmdListNum += 1;														//待处理命令数+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//计算命令长度
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//清空当前待处理的命令处理缓冲区指针
	
	if(CMD_RXLIST_LMT == pCmdBuf->CmdListNum){		//命令待处理空间满，让EP进入RXNAK等待状态，待处理完之前的命令在使能接收
			
	}
	return pCmdBuf;		//返回空地址
}

//---------------------------------------------------------------------------
//说明：USB命令分拣程序	
//参数：void
//返回：命令待处理区空间地址	
//---------------------------------------------------------------------------
/*
CMD_BODY_TypeDef * CmdPrase(u8 ListNum)		//ken:建立命令索引函数
{	u16 StrIndex ,Strcnt;
	
	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;

	Strcnt = EP2Pindex;
		for(; Strcnt < EP2index ; Strcnt++){
			if(EP2ParseBuf[Strcnt] == '$'){	//收到命令头'$'
				pCmdBodyBuf = CmdApply();			//寻找空的命令处理索引空间地址				
			}
			if(pCmdBodyBuf) {								//命令建立成功进入	
				if(StrIndex <= CMD_BUF_LEN){	//命令内容												
					pCmdBodyBuf->all[StrIndex++] = EP2RxBuf[Strcnt];
				
				}
			}		
		}
			if(NULL == pCmdBodyBuf){
				USB_SIL_Write(EP2_IN, MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
				
			}
	//在EP2ParseBuf缓冲区的中数据处理完毕。
	SetEPRxStatus(ENDP2, EP_RX_NAK);		//EP2RX等待缓冲区复位
	EP2index = 0;
	SetEPRxStatus(ENDP2, EP_RX_VALID);	//重新使能接收				
}
*/
//---------------------------------------------------------------------------
//说明：USB命令执行程序	
//参数：void
//返回：命令待处理区空间地址	
//---------------------------------------------------------------------------

void CmdExecute(void)		//执行散转函数
{	u16	HeadHash,loopi;
//	timems_t CmdExecutePassTime;
//	void ( *pExeFunc)(CMD_BODY_TypeDef *); 
//	u16 StrLen,StrIndex;		//StrCnt,,EP2StrLen

/*	
	if(EP2index != 0){	
		//SetEPRxStatus(ENDP2, EP_RX_NAK);		//等待处理EP2RxBuf中的命令
		for(EP2Pindex = 0; EP2Pindex < EP2index ; EP2Pindex++){
			if(EP2RxBuf[EP2Pindex] == '$'){	//收到命令头'$'
				if(CmdApply()){				//寻找空的命令处理索引空间地址
					EP2RxOkFg	=	1;								//EP2收到数据
					StrIndex = 0;							
				}				
			}
			if(EP2RxOkFg) {									//找到空的命令处理空间	
				if(StrIndex <= CMD_BUF_LEN){	//命令内容												
					pCmdBuf->pCmd_Body_Current->all[StrIndex++] = EP2RxBuf[EP2Pindex];
					
					if(StrIndex == CMD_LEN_CNT){	//获得命令长度
						StrLen = MyStrToNum(pCmdBuf->pCmd_Body_Current->part.CmdTotalLen , CMD_TOTAL_LEN);	//获得命令长度			
						if(0 == StrLen){			//长度不对
							CmdOver(FALSE);			//命令接收失败
							EP2RxOkFg = 0;			
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
						}
					}
					if((StrLen != 0)&&(StrLen == StrIndex)){
						
						if('\n' == EP2RxBuf[EP2Pindex]){
							CmdOver(TRUE);			//命令接收成功
							EP2RxOkFg = 0;			//接收成功，继续解析下一条命令
							StrIndex = 0;	
						}
						else{
							CmdOver(FALSE);			//命令接收失败
							EP2RxOkFg = 0;	//接收成功，继续解析下一条命令
							StrIndex = 0;
						//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
						}
					}	
//					else{//长度与0x0D 0x0A不匹配
//						EP2RxOkFg = 0;	
//						EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK						
//					}	
				}		
				else{		//超过存放命令待处理缓冲区大小
					CmdOver(FALSE);			//命令接收失败
					EP2RxOkFg = 0;			//长度不对
					StrIndex = 0;					
					//	EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
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
		
			while(0 == pCmdBuf->CmdListFlag[loopi]){	//寻找待处理命令空间
				loopi++;
				if(CMD_RXLIST_LMT == loopi){
					loopi = 0;
				}
				else if(loopi == pCmdBuf->CmdPrcList){
					return;	//没有需要处理的命令		
				}
			}
		pCmdBuf->CmdPrcList = loopi;
		pCmdBuf->pCmd_Prc_Current = & (pCmdBuf->Cmd_Body[loopi]);									//指向当前待处理命令
	
	
		HeadHash = Hash(pCmdBuf->pCmd_Prc_Current->part.Header , CMD_HEADER_LEN);	//计算命令hash头
		//检验异或校验位
		
			
		switch(HeadHash){		// 提取令串头特征值并判断
		//	case CMD_HASH_JMP:	CmdFuncJMP(pCmdBuf->pCmd_Prc_Current);	break;	//ken:JMP命令
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
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
			break;		
			
		}
		if(pCmdBuf->CmdListNum == CMD_RXLIST_LMT){	//当带执行命令处理完
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//重新使能EP2接收
		}
		pCmdBuf->CmdListNum -= 1;
		pCmdBuf->CmdListFlag[loopi] = 0;	
		for(loopi = 0;loopi < CMD_BUF_LEN;loopi++){		//清空命令处理缓冲区
			pCmdBuf->pCmd_Prc_Current->all[loopi] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
			
}

/*
//---------------------------------------------------------------------------
//说明：STT启动测深仪命令执行程序	
//参数：pCmdJMPBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSTT(CMD_BODY_TypeDef * pCmdSTTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSTTBody;
 
 	if(CmdCheck(pCmdSTTBody)){	//检验长度	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//检验长度及异或位正确
		if('L' == pCmdSTTBody->part.CmdFuncType){
			goto ERROR;			
		}
		else if('S' == pCmdSTTBody->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pSttDat->all, pCmdSTTBody->part.Others, sizeof(pSttDat->all));
			SounderState.SwitchRefresh = 1;
			//	if('1' == pCmdBuf->pReplyBuf->part.Others[0] ){	//开启测量
			if('1' == pSttDat->bit.State ){	//开启测量	
				SounderState.OnOff         = ON;
			} 
			else{	//关闭测量
				SounderState.OnOff         = OFF;
			}
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}	
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//说明：RST复位命令执行程序	
//参数：pCmdRSTBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncRST(CMD_BODY_TypeDef * pCmdRSTBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdRSTBody;
	if(CmdCheck(pCmdRSTBody)){
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
	 	//检验长度及异或位正确	
		if('L' == pCmdRSTBody->part.CmdFuncType){	
		//	pCmdBuf->pReplyBuf = NULL;
		//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			goto ERROR;
		}
		else if('S' == pCmdRSTBody->part.CmdFuncType){
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
			RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
			EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令					
			pCmdBuf->pReplyBuf = NULL;
			RSTFg = 1; 
			DelayCom(300);
			//程序跳转到boot区
			JumpToBoot();
		}
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;			
}

//---------------------------------------------------------------------------
//说明：REG注册命令执行程序	
//参数：pCmdREGBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncREG(CMD_BODY_TypeDef * pCmdREGBody)
{	u16 RpStrLen ,iLoop;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	u32 RegData = 0x00;
	pCmdBuf->pReplyBuf = pCmdREGBody;
 	
	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			goto ERROR;
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			for(iLoop = 0; iLoop < 16;iLoop++){
				RegNum[iLoop] = pCmdREGBody->part.Others[iLoop];	//复制注册码
			}						
				if(Decrypt())
				{			 					

				  FLASH_Unlock();

					FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);					
					
					RegData 	= RegNum[19];		//将8位字符合成32位整字	关键是如何读出来
					RegData += RegNum[18] << 8;
					RegData += RegNum[17] << 16;
					RegData += RegNum[16] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//写入注册时间？
				 	FLASHStatus = FLASH_ProgramWord( (u32)REG_TIME_ADRESS, RegData);	//一次写一个整字，32位长
				
					RegData 	= RegNum[23];		//将8位字符合成32位整字	关键是如何读出来
					RegData += RegNum[22] << 8;
					RegData += RegNum[21] << 16;
					RegData += RegNum[20] << 24;
				 
	//			 Write_Flash_Byte(RegNum+16,dUseTime,8);	//写入注册时间？
				 	FLASHStatus = FLASH_ProgramWord( (u32)(REG_TIME_ADRESS + 4), RegData);	//一次写一个整字，32位长
					
					//  FLASH_LockBank1();
		  		FLASH_Lock();				
				//	Write_Flash_Byte(RegNum+16,dUseTime,8);	//ken:只把使用时间，注册时间写到flash里面，注册码没写进去
				//	Uart0_Tx(ESOK,7);								
					
//					MsgInsrt(pCmdBuf->pReplyBuf->all, &RegNum[20], 4 ,TRUE);
					MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
				}
				else{	//注册码不正确
					goto ERROR;	
				}
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：SYS注册命令执行程序	
//参数：pCmdSYSBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSYS(CMD_BODY_TypeDef * pCmdSYSBody)
{	u16 RpStrLen,iLoop,errFlag = 0;
	u8	Tmp[6];
	pCmdBuf->pReplyBuf = pCmdSYSBody;
 	
	if(CmdCheck(pCmdSYSBody)){	//检验长度	
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		//检验长度及异或位正确
		if('L' == pCmdSYSBody->part.CmdFuncType){
			for(iLoop=0; iLoop<10; iLoop++)	//ken:狗号中只能出现0-9 
			{
				if((pCmdBuf->pReplyBuf->part.Others[iLoop] < 0x30) || (pCmdBuf->pReplyBuf->part.Others[iLoop] > 0x39))	
				{
				 	errFlag = 1;
				}	
			}
			if(errFlag) 
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = 0x30;	//ken:错误的狗号
			}
			else
			{
				for(iLoop=0; iLoop<10; iLoop++) dogID[iLoop] = pCmdBuf->pReplyBuf->part.Others[iLoop];	//ken:读取正确的狗号	
			
			}
			if(Dog_Key(dogID)==1){	//ken:计算10位暗码狗号
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
			else{	//狗号不对
			//	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	
				goto ERROR;
			}
	
		}
		else if('S' == pCmdSYSBody->part.CmdFuncType){
			goto ERROR;
		}
	}
  else{	//检验长度及异或位错误
	 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:		
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;
				


	
}


//---------------------------------------------------------------------------
//说明：RNG设置测量档位命令执行程序	
//参数：pCmdRNGBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncRNG(CMD_BODY_TypeDef * pCmdRNGBody)
{	u16 RpStrLen;
	u16	TmpRange;
 	pCmdBuf->pReplyBuf = pCmdRNGBody;
		
 if(CmdCheck(pCmdRNGBody)){	
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 	//检验长度及异或位正确	
	if('L' == pCmdRNGBody->part.CmdFuncType){
		goto ERROR;
	}
	else if('S' == pCmdRNGBody->part.CmdFuncType){
		if('1' == pCmdRNGBody->part.Others[0] ){	//自动换档

		} 
		else{	//手动换档
			
		//ken:测试档位不能随时变，不然影响水深计算	
			TmpRange = 	(pCmdBuf->pReplyBuf->part.Others[2]) - '0';
		//	TmpRange = MyStrToNum( &(pCmdBuf->pReplyBuf->part.Others[2]) , 2);				 
			if(0< TmpRange < 8){	//正常28M的档位1-7档
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;
//				
//				switch(TmpRange)
//				{
//					case 1:
//					TmpRange = TIMERBASE;	//对应15米档，40hz(因为是多通道如果8个通道全开则单独一个只有5Hz)，用时25ms，PLCK1是72Mhz(65535/72*10^6 = 0.9102*10^-3 ,0.9102*10^-3 * 28 = 0.0255)
//					break;
//					case 2:
//					TmpRange = TIMERBASE * 2^(grad -1);	//对应30米档，20hz，用时50ms，
//					break;
//					case 3:
//					TmpRange = 110;	//对应120米档，10hz，用时100ms，
//					break;
//					case 4:
//					TmpRange = 220;	//对应240米档，5hz，用时200ms，
//					break;
//					case 5:
//					TmpRange = 440;	//对应480米档，2.5hz，用时400ms，
//					break;
//					case 6:
//					TmpRange = 880;	//对应960米档，1.25hz，用时800ms，
//					break;
//
//					default:
//					TmpRange = 28;	//对应30米档，20hz，用时50ms，
//					break;	
//				}				
				
				SounderState.GradRefresh = 1;			//档位更新标志位
				FiltProFlag=1;								
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);					
			}
			else if(0 == TmpRange){	
				SurvPara.Range = TmpRange;
				SurvPara.Ratio = (1<<(TmpRange -1));
				SurvPara.GradNow = TIMERBASE * SurvPara.Ratio;								
			}
			else{	//档位参数不正确
				MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);
			}	
		}		
	}
	else{
		goto ERROR;
	}
 }
 else{	//检验长度及异或位错误
 	pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
	MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
 }	
	
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
 	
}

//---------------------------------------------------------------------------
//说明：SUV设置测量档位命令执行程序	
//参数：pCmdSUVBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSUV(CMD_BODY_TypeDef * pCmdSUVBody)
{	u16 RpStrLen;
	pCmdBuf->pReplyBuf = pCmdSUVBody;

 	if(CmdCheck(pCmdSUVBody)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdSUVBody->part.CmdFuncType){

			MyNumToStr(pSuvDat->bit.Velocity ,SurvPara.Velocity, 6);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.Velocity, sizeof(pSuvDat->bit.Velocity) ,TRUE);
			MyNumToStr(pSuvDat->bit.LowLmt ,SurvPara.LowLmt, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.LowLmt, sizeof(pSuvDat->bit.LowLmt) ,TRUE);
			MyNumToStr(pSuvDat->bit.DeepLmt ,SurvPara.DeepLmt, 5);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.DeepLmt, sizeof(pSuvDat->bit.DeepLmt) ,TRUE);
			pSuvDat->bit.AlarmSw = MyNumToChar(SurvPara.AlarmSw);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSuvDat->bit.AlarmSw), sizeof(pSuvDat->bit.AlarmSw) ,TRUE);
			MyNumToStr(pSuvDat->bit.RefChn ,SurvPara.RefChn, 2);		// 以上没有插入','号		
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->bit.RefChn, sizeof(pSuvDat->bit.RefChn) ,TRUE);		
			//插入回复命令体部分。
	//		MsgInsrt(pCmdBuf->pReplyBuf->all, pSuvDat->all, sizeof(pSuvDat->all) ,TRUE);		
		}
		else if('S' == pCmdSUVBody->part.CmdFuncType){
			//分拣命令体部分。
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//说明：CHN设置测量档位命令执行程序	
//参数：pCmdCHNBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncCHN(CMD_BODY_TypeDef * pCmdCHNBody)
{	u16 RpStrLen;
	u8 Chn_Cnt,iLoop;
	pCmdBuf->pReplyBuf = pCmdCHNBody;

 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
 		//检验长度及异或位正确	
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){				
			MyNumToStr(pChnDat->bit.ChnNum,ChanPara.Chn_Num, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnNum, sizeof(pChnDat->bit.ChnNum) ,TRUE);
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				pChnDat->bit.ChnName[iLoop]	= ChanPara.Chn_Name[iLoop] + 0x30;			
			}			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pChnDat->bit.ChnName, sizeof(pChnDat->bit.ChnName) ,TRUE);				
			//插入回复命令体部分。		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){						 
			//分拣命令体部分。
			MsgCopy(pChnDat->all, pCmdCHNBody->part.Others, sizeof(pChnDat->all));			
			
			ChanPara.Chn_Num = MyStrToNum(pChnDat->bit.ChnNum, 2);
			if(ChanPara.Chn_Num > MAXCHNUM){	//通道号设置错误		
				ChanPara.Chn_Num = 0;
				goto ERROR;			
			}
			
			for(iLoop=0;iLoop<MAXCHNUM;iLoop++){
				if(0x30 == pChnDat->bit.ChnName[iLoop]){	//ken:获得具体通道号
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
			  if(0 == ChanPara.Chn_Name[Chn_Cnt]){	//清空没选中的通道回波记录数据
				for(iLoop=0; iLoop<AVEDEPTHLEN+1; iLoop++){
				     aveDepth[Chn_Cnt][iLoop] = 0; //保存各通道前50次各10次的平均值，第0单元保存指向值
					 echoTrend[Chn_Cnt][iLoop]= 0; //水深趋势
					 AveEchoWidth[Chn_Cnt][iLoop]= 0; //回波宽度平均趋势s
				}
				for(iLoop=0; iLoop<PREDEPTHLEN+1; iLoop++){
				     preDepth[Chn_Cnt][iLoop]    = 0; //保存前10次水深数据 ，第0单元保存指向值
					 echoStrenth[Chn_Cnt][iLoop] = 0; //保存每次回波的平均强度，第0单元保存指向值
					 echoWidth[Chn_Cnt][iLoop] = 0; 	//保存每次回波的宽度，第0单元保存指向值
					 TxPlusWidth[Chn_Cnt][iLoop] = 0;
				}		
		                                     
					//ken:初始化各通道回波信息变量
				RecInfo[Chn_Cnt].DepthTrend = 0;//0:平缓； 1:变浅；2:变深
				RecInfo[Chn_Cnt].Depth = 0;
				RecInfo[Chn_Cnt].MaxEchoTime = GATEB;
				RecInfo[Chn_Cnt].MinEchoTime = GATEF;
				RecInfo[Chn_Cnt].EchoQuality = 0x00;
				RecInfo[Chn_Cnt].EchoCnt     = 0;
				RecInfo[Chn_Cnt].EchoNum     = 0;
				RecInfo[Chn_Cnt].NoechoCnt   = 0;
				RecInfo[Chn_Cnt].NoechoNum   = 0;
				RecInfo[Chn_Cnt].AutoLevel   = 0;//0：自动模式下减档；1：自动模式下不定；2：自动模式下加档
				RecInfo[Chn_Cnt].CopyUnworkCnt   = 0;
				RecInfo[Chn_Cnt].GainDepthConnect   = 1;	//默认自动控制档位时，增益及水深是关联的。
				RecInfo[Chn_Cnt].GainDepthUWCnt = 0;				
			  }
			}
			SounderState.ChanRefresh = 1;	//ken:更新通道标志�

			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);		
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}

	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令
	pCmdBuf->pReplyBuf = NULL;	
		
}

//---------------------------------------------------------------------------
//说明：FRQ探头频率设置命令执行程序	
//参数：pCmdFRQBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncFRQ(CMD_BODY_TypeDef * pCmdFRQBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	pCmdBuf->pReplyBuf = pCmdFRQBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';
		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(pFrqDat->bit.Frequency,RevPara[ChnName].Frequency, 3);			
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Frequency, sizeof(pFrqDat->bit.Frequency) ,TRUE);				
			MyNumToStr(pFrqDat->bit.Draft,RevPara[ChnName].Draft, 3);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pFrqDat->bit.Draft, sizeof(pFrqDat->bit.Draft) ,TRUE);
			//插入回复命令体部分。

		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pFrqDat->all, pCmdFRQBody->part.Others, sizeof(pFrqDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TXW发射脉宽命令执行程序	
//参数：pCmdTXWBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncTXW(CMD_BODY_TypeDef * pCmdTXWBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrTranWidth[4];
	pCmdBuf->pReplyBuf = pCmdTXWBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(StrTranWidth,TranPara[ChnName].TrnWdth, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrTranWidth, sizeof(StrTranWidth) ,TRUE);				
			//插入回复命令体部分。		
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].TrnWdth   = MyStrToNum(pCmdTXWBody->part.Others , 4);	//转换发射脉宽单位微秒				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：GAN接收增益命令执行程序	
//参数：pCmdGANBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncGAN(CMD_BODY_TypeDef * pCmdGANBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrGain[2];
	pCmdBuf->pReplyBuf = pCmdGANBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			MyNumToStr(StrGain,RevPara[ChnName].Gain, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, StrGain, sizeof(StrGain) ,TRUE);				
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				RevPara[ChnIndex].Gain   = MyStrToNum(pCmdGANBody->part.Others , 2);	//转换增益
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：PWR发射功率命令执行程序	
//参数：pCmdPWRBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncPWR(CMD_BODY_TypeDef * pCmdPWRBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	u8	StrPwr;
	pCmdBuf->pReplyBuf = pCmdPWRBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//查询全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			StrPwr = TranPara[ChnName].Pwr + 0x30 ;
			MsgInsrt(pCmdBuf->pReplyBuf->all, & StrPwr, 1 ,TRUE);				
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Pwr   = MyStrToNum(pCmdPWRBody->part.Others , 1);	//转换功率				
				SounderState.TranRefresh[ChnIndex] = 1;
			}
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);	
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：SEN抑制脉宽、功率、回波阈值命令执行程序	
//参数：pCmdSENBody 命令内容
//返回：	
//---------------------------------------------------------------------------
void CmdFuncSEN(CMD_BODY_TypeDef * pCmdSENBody)
{	u16 RpStrLen;
	u8	ChnName,ChnBegin,ChnIndex,ChnEnd;
	float TmpBlank;
	pCmdBuf->pReplyBuf = pCmdSENBody;
 	if(CmdCheck(pCmdBuf->pReplyBuf)){	
 		pCmdBuf->pReplyBuf->part.Dot3 = '\0';

		if('L' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//查询全部通道
				goto ERROR;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN);	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					goto ERROR;
				}
				else{
					ChnName -= 1;	//ken:通道号改为1-8 							
				}
			}
			TmpBlank = (float)((float)TranPara[ChnName].ClrWdth / 1000) * ((float)SurvPara.Velocity / 1000);
			TranPara[ChnName].Blank = TmpBlank;	//抑制脉宽转为抑制水深
			MyNumToStr(pSenDat->bit.Blank ,TranPara[ChnName].Blank, 4);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Blank, sizeof(pSenDat->bit.Blank) ,TRUE);
			MyNumToStr(pSenDat->bit.Threshold ,RevPara[ChnName].Shold, 2);
			MsgInsrt(pCmdBuf->pReplyBuf->all, pSenDat->bit.Threshold, sizeof(pSenDat->bit.Threshold) ,TRUE);
			pSenDat->bit.Filter = MyNumToChar(RevPara[ChnName].Filt);
			MsgInsrt(pCmdBuf->pReplyBuf->all, &(pSenDat->bit.Filter), sizeof(pSenDat->bit.Filter) ,TRUE);			
			//插入回复命令体部分。	
	
		}
		else if('S' == pCmdBuf->pReplyBuf->part.CmdFuncType){
			//分拣命令体部分。
			MsgCopy(pSenDat->all, pCmdSENBody->part.Others, sizeof(pSenDat->all));			
			if('A' == pCmdBuf->pReplyBuf->part.Channel[0]){	//设置全部通道
				ChnBegin = 0;ChnEnd = MAXCHNUM - 1;
			}
			else {
				ChnName = MyStrToNum(pCmdBuf->pReplyBuf->part.Channel, CHANNEL_LEN) ;	//ken:获得通道号	
				if((0 == ChnName) ||(ChnName>MAXCHNUM)){ 	//ken:限制通道号
					ChnBegin = 0;
					ChnEnd = 0;
				}
				else{
					ChnBegin = ChnName - 1;	//ken:通道号改为1-8 
					ChnEnd = ChnName - 1;		
				}
			}
			for(ChnIndex = ChnBegin; ChnIndex <= ChnEnd; ChnIndex++){
				TranPara[ChnIndex].Blank	= MyStrToNum(pSenDat->bit.Blank , 4);
				TmpBlank = (float)((float)TranPara[ChnIndex].Blank * 1000000) / ((float)SurvPara.Velocity);				
				TranPara[ChnIndex].ClrWdth = TmpBlank;	//抑制水深转为抑制脉宽
				RevPara[ChnIndex].Shold   = MyStrToNum(pSenDat->bit.Threshold , 2);
				RevPara[ChnIndex].Filt 		= MyCharToNum(pSenDat->bit.Filter);
				SounderState.TranRefresh[ChnIndex] = 1;		//需要整合
				SounderState.SensRefresh[ChnIndex] = 1;
//				SounderState.FiltRefresh[ChnIndex] = 1;
			}						
			
			MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_OK, MyStrLen(MSGRP_OK) ,TRUE);				
		}
		else{
			goto ERROR;
		}
	}
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TVG命令执行程序	
//参数：pCmdTVGBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：TRK水底跟踪命令执行程序	
//参数：pCmdTRKBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;	
}

//---------------------------------------------------------------------------
//说明：UPD升级命令执行程序，每次发送128字节程序，带有地址	
//参数：pCmdUPDBody 命令内容
//返回：	
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
	else{	//检验长度及异或位错误
		pCmdBuf->pReplyBuf->part.Dot3 = '\0';	
ERROR:
		MsgInsrt(pCmdBuf->pReplyBuf->all, MSGRP_ERR, MyStrLen(MSGRP_ERR) ,TRUE);	 	
	}
	RpStrLen = ReplyAppend(pCmdBuf->pReplyBuf);
	EP2_TxStr(pCmdBuf->pReplyBuf->all , RpStrLen);	//向端点2发送回复命令	
	pCmdBuf->pReplyBuf = NULL;			
}

*/
>>>>>>> .r34
