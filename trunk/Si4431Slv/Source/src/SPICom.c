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

@near u8 SPI1OkFlag;           //Uart0成功接收信息标志
//u8 SPI2OkFlag;           //Uart1成功接收信息标志
@near u8 SPI1NewFlg;		//SPI1收到新数据
//u8 SPI2NewFlg;		//SPI2收到新数据

@near u8 SPI1FullFlag;        //接收缓冲区满标志位
@near u8 SPI1ProtocolFlag;	 //协议标志，两种串口协议
@near u8 SPI1index;		 //串口接收缓冲区定标号
@near u8 SPI1Pindex;        //串口处理命令标号
//u8 SPI2index;		 //串口接收缓冲区定标号
//u8 SPI2Pindex;        //串口处理命令标号
//u8 pdata txIndex;          //串口发送缓冲区定标号
@near u8 SPI1_ParseBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区
//@near u8 SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区

//@near u8 txLog[TXLOGLEN];
@near u8 SPI1ByteNum;		 //在协议0时串口按接收到的命令字节总数来结束一条命令的接收
//u8 SPI2_ParseBuf[SPI2PARSEBUFLEN];//串口1接收缓冲区

CMDSPI_BUF_TypeDef		CmdSpiTxBuf;										//命令发送缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiTxBuf;								//指向命令发送缓冲区
CMDSPI_BUF_TypeDef		CmdSpiRxBuf;										//命令接收缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiRxBuf;								//指向命令接收缓冲区
CMDSPI_BODY_TypeDef  ReplyBuf;								//应答缓冲区
CMDSPI_BODY_TypeDef * pReplyBuf;								//应答缓冲区
//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*函数：void SPI1Rx_Parse(void)	
//*功能：SPI1接收处理函数
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //u8 i,j,k;
  u8 LoopStart,LoopEnd,Loopi;
  u16 comnum;
	if(0 != SPI1OkFlag ){								
		for(LoopStart = 0; LoopStart < SPI1index; LoopStart++){
			if(SPI1_ParseBuf[LoopStart]=='#'){		//找到命令头了	
				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//找结尾
					if(SPI1_ParseBuf[LoopEnd]=='\n'){	//找到命令结尾
						SPI1OkFlag--;	//每处理一条命令，接收命令计数器自减
						SPI1Pindex = LoopEnd + 1;
						CmdSpiRxApply(&SPI1_ParseBuf[LoopStart] ,(LoopEnd-LoopStart+1));	//建立索引命令
						break;
					}
				}
			}
		}	
		//清空缓冲区				
		for (LoopStart = 0; LoopStart < SPI1PARSEBUFLEN; LoopStart++){
			SPI1_ParseBuf[LoopStart] = 0;	
		}
		SPI1index   = 0;
		SPI1Pindex = 0;
		SPI1FullFlag = 0;				 
	}	
}

//---------------------------------------------------------------------------
//说明：SpiTx建立命令索引函数，寻找空的索引空间
//参数：sta:TRUE表示是主动发送的命令，需要重发机制，FALSE表示是回复命令，不需要重发；* cmddata:数据空间首地址；cmdlen:数据长度
//返回：命令建立情况	
//---------------------------------------------------------------------------
u8 CmdSpiTxApply(bool sta ,u8 * cmddata ,u16 cmdlen)		
{
	u8	i = 0,j = 0;
										//建立待发送命令索引
			i = pCmdSpiTxBuf->CmdCurrentList ;			//获得此前命令索引位置
			while(0 != CmdSpiTxBuf.CmdListFlag[i]){	//寻找发送命令索引
				i++;
				if(CMDSPI_TXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiTxBuf->CmdCurrentList){
					return 0;		//建立命令索引不成功
				}
			}
			pCmdSpiTxBuf->CmdCurrentList	=	i ;	 //当前命令索引位置
			pCmdSpiTxBuf->pCmd_Body_Current = & (pCmdSpiTxBuf->Cmd_Body[i]);	//获得命令索引首地址

			for(j = 0; j < cmdlen ; j++){
				pCmdSpiTxBuf->pCmd_Body_Current->all[j] = cmddata[j];
			}
			pCmdSpiTxBuf->pCmd_Body_Current->part.TotalLength = cmdlen;		//记录命令长度
			pCmdSpiTxBuf->pCmd_Body_Current->part.HeaderHash	= Hash(pCmdSpiTxBuf->pCmd_Body_Current->part.Header , CMDSPI_HEADER_LEN);	//计算命令hash头			
			if(sta){
				pCmdSpiTxBuf->CmdListFlag[pCmdSpiTxBuf->CmdCurrentList]	= CMD_MAXRESEND_NUM;	//当前命令为主动发送命令，需要重发		
			}
			else{
				pCmdSpiTxBuf->CmdListFlag[pCmdSpiTxBuf->CmdCurrentList]	= CMD_REPLYSEND_NUM;	//当前命令为回复命令不需要重发		
			}
			pCmdSpiTxBuf->CmdListNum += 1;																//待处理命令数+1
			
	return 1;//建立命令索引成功
	
}
//---------------------------------------------------------------------------
//说明：SpiRx建立命令索引函数，寻找空的索引空间
//参数：* cmddata:数据空间首地址；cmdlen:数据长度
//返回：命令建立情况	
//---------------------------------------------------------------------------
u8 CmdSpiRxApply(u8 * cmddata ,u16 cmdlen)		
{
	u8	i = 0,j = 0;
										//建立处理命令索引
			i = pCmdSpiRxBuf->CmdCurrentList ;			//获得此前命令索引位置
			while(1 == CmdSpiRxBuf.CmdListFlag[i]){	//寻找空的从模块地址空间
				i++;
				if(CMDSPI_RXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiRxBuf->CmdCurrentList){
					return 0;		//建立命令索引不成功
				}
			}
			pCmdSpiRxBuf->CmdCurrentList	=	i ;	 //当前命令索引位置
			pCmdSpiRxBuf->pCmd_Body_Current = & (pCmdSpiRxBuf->Cmd_Body[i]);	//获得命令索引首地址
			
			for(j = 0; j < cmdlen ; j++){
				pCmdSpiRxBuf->pCmd_Body_Current->all[j] = cmddata[j];
			}
			pCmdSpiRxBuf->pCmd_Body_Current->part.HeaderHash	= Hash(pCmdSpiRxBuf->pCmd_Body_Current->part.Header , CMDSPI_HEADER_LEN);	//计算命令hash头
			pCmdSpiRxBuf->pCmd_Body_Current->part.TotalLength = cmdlen;		//记录命令长度
			pCmdSpiRxBuf->CmdListFlag[pCmdSpiRxBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
			pCmdSpiRxBuf->CmdListNum += 1;																//待处理命令数+1

	return 1;//建立命令索引成功
	
}

//--------------------------------------------------------------------------- 	
// 回复内容组合函数
// ken:会算出发送字符串长度	
u16 CmdSpiReplyAppend(CMDSPI_BODY_TypeDef *pRplyStr)
{	u16	nRplyStrLen = 0;

	while(pRplyStr->all[nRplyStrLen] != '\0'){nRplyStrLen++;}	//寻找结尾
	//插入长度					
	pRplyStr->all[nRplyStrLen++] = '\r';
	pRplyStr->all[nRplyStrLen++] = '\n';	
	return nRplyStrLen;
}


//---------------------------------------------------------------------------
//说明：USB命令执行程序	
//参数：void
//返回：命令待处理区空间地址	
//---------------------------------------------------------------------------

void CmdSpiExecute(void)		//执行散转函数
{	u16	HeadHash,i,j;	
	
	
	if(0 != pCmdSpiRxBuf->CmdListNum){			
//		StartTimeMs2 = ReadRunTime();
	 for(j = 0;j < pCmdSpiRxBuf->CmdListNum; j++){	//处理命令
		i = pCmdSpiRxBuf->CmdPrcList ;
		
			while(0 == pCmdSpiRxBuf->CmdListFlag[i]){	//寻找待处理命令空间
				i++;
				if(CMDSPI_RXLIST_LMT == i){
					i = 0;
				}
				else if(i == pCmdSpiRxBuf->CmdPrcList){
					return;	//没有需要处理的命令		
				}
			}
		pCmdSpiRxBuf->CmdPrcList = i;
		pCmdSpiRxBuf->pCmd_Prc_Current = & (pCmdSpiRxBuf->Cmd_Body[i]);									//指向当前待处理命令
	
		HeadHash = pCmdSpiRxBuf->pCmd_Prc_Current->part.HeaderHash;	//获得Hash头
//		HeadHash = Hash(pCmdSpiRxBuf->pCmd_Prc_Current->part.Header , CMDSPI_HEADER_LEN);	//计算命令hash头
		//检验异或校验位
							
		switch(HeadHash){		// 提取令串头特征值并判断
			case CMDSPI_HASH_NETCNT:	CmdFuncNETCNT(pCmdSpiRxBuf->pCmd_Prc_Current);	break;	

			default:
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
					nop();
			
			break;		
			
		}
		if(pCmdSpiRxBuf->CmdListNum == CMDSPI_RXLIST_LMT){	//当带执行命令处理完
//			SetEPRxStatus(ENDP2, EP_RX_VALID);		//重新使能EP2接收
		}
		pCmdSpiRxBuf->CmdListNum -= 1;
		pCmdSpiRxBuf->CmdListFlag[i] = 0;	
		for(i = 0;i < CMDSPI_BUF_LEN;i++){		//清空命令处理缓冲区
			pCmdSpiRxBuf->pCmd_Prc_Current->all[j] = 0;
		}
//	EndTimeMs2 = ReadRunTime();
//	CmdExecutePassTime = CheckTimeInterval(StartTimeMs2,EndTimeMs2);
	}
 }			
}

//=============================================================================================
//说明:保存新组网的模块地址，按链表方式保存，先跟现有组网地址比较，不同才组网，每次在上一次保存地址空间后插入
//参数:pNewAdr指向新组网地址，AdrLen地址长度，成功插入地址函数名返回1，否则返回0表示地址空间已满。
//=============================================================================================
u8 CmdFuncNETCNT(CMDSPI_BODY_TypeDef * pCmdData)
{	si4431adrtype	NewAdr;	 //	u16 RpStrLen;	 
	u8 loopi,loopj,NetFlag = 0;//TmpSta;
	pReplyBuf = pCmdData;
	pReplyBuf->part.Dot0 = '\0';
		
	NewAdr.HexAdr.All32 = MyStrToHex(pCmdData->part.SourceAdr, CMDSPI_ADR_WIDTH);	//获得组网模块地址	
	MyHexToStr(NewAdr.StrAdr ,NewAdr.HexAdr.All32 , CMDSPI_ADR_WIDTH)	;			
	
	for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){		//首先与已组网地址比较
		if(1 == pJKNetAdr_Tab->TabFlag[loopi]){	
		 	if(pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 == NewAdr.HexAdr.All32){				
				NetFlag = 1;																					//此模块已组网
				pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//重置心跳包个数				
				break;
			}
		}			
	}  
	if(0 == NetFlag){		//新模块未组网
		if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){		//超过从模块地址保存空间了
	  //	Usart_SendString_End(USART1 , "JKNetAdrTab is Full!\r\n");
	  	return 0;	//没地址空间再组网
		}
	  else{		//有新模块组网
			for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){	//寻找空的从模块地址空间
				if(0 == pJKNetAdr_Tab->TabFlag[loopi]){
				 	pJKNetAdr_Tab->TabFlag[loopi] = 0x01;	//找到空从模块地址空间
					pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//初始化心跳包个数
					pJKNetAdr_Tab->JKNetAdrTabCnt++;	//从模块地址计数器加1
					break;
				}			
			}
		//	pJKNetAdr_Tab->JKNetNumTab[loopi] = NewAdr.All32;	//记录新组网地址
			pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 = NewAdr.HexAdr.All32;	//记录新组网地址
			MyHexToStr(pJKNetAdr_Tab->JKNetAdrTab[loopi].StrAdr ,pJKNetAdr_Tab->JKNetAdrTab[loopi].HexAdr.All32 , CMDSPI_ADR_WIDTH)	;			
		}
	}
	MsgInsrt(pReplyBuf->all , RX_ADDRESS_Si4431.StrAdr , CMDSPI_ADR_WIDTH , TRUE);	//插入源地址
	MsgInsrt(pReplyBuf->all , NewAdr.StrAdr , CMDSPI_ADR_WIDTH , TRUE);	//插入目标地址
	MsgInsrt(pReplyBuf->all , MSGRP_OK , MyStrLen(MSGRP_OK) , TRUE);	//插入OK

	CmdSpiReplyAppend(pReplyBuf);	//回复命令结尾
	
//	NET_LED_TURN();							//有模块组网成功
	CmdSpiTxApply(FALSE ,pReplyBuf->all ,MyStrLen(pReplyBuf->all));				//将命令存到待处理缓冲区
	return 1;	//已记录新组网模块地址
}

//========================================================================================//




//======================================no  more==========================================//

