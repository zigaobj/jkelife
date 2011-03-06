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

uint8_t	SPI1OkFlag;           //Uart0成功接收信息标志
uint8_t	SPI2OkFlag;           //Uart1成功接收信息标志
uint8_t	SPI1NewFlg;		//SPI1收到新数据
uint8_t	SPI2NewFlg;		//SPI2收到新数据

uint8_t	SPI1FullFlag;        //接收缓冲区满标志位
u8 			SPI2FullFlag;        //接收缓冲区满标志位
uint8_t	SPI1ProtocolFlag;	 //协议标志，两种串口协议
uint8_t	SPI1index;		 //串口接收缓冲区定标号
uint8_t	SPI1Pindex;        //串口处理命令标号
uint8_t	SPI2index;		 //串口接收缓冲区定标号
uint8_t	SPI2Pindex;        //串口处理命令标号
//uint8_t pdata txIndex;          //串口发送缓冲区定标号
uint8_t	SPI1_ParseBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区
//u8		SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区

//uint8_t	txLog[TXLOGLEN];
uint8_t	SPI1ByteNum;		 //在协议0时串口按接收到的命令字节总数来结束一条命令的接收
uint8_t	SPI2_ParseBuf[SPI2PARSEBUFLEN];//串口1接收缓冲区

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体
CMDSPI_BUF_TypeDef		CmdSpiTxBuf;										//命令发送缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiTxBuf;								//指向命令发送缓冲区
CMDSPI_BUF_TypeDef		CmdSpiRxBuf;										//命令接收缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiRxBuf;								//指向命令接收缓冲区
CMDSPI_BODY_TypeDef  ReplyBuf;								//应答缓冲区
CMDSPI_BODY_TypeDef * pReplyBuf;								//应答缓冲区
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


//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*函数：void SPI1Rx_Parse(void)	
//*功能：SPI1接收处理函数
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //uint8_t i,j,k;
  uint8_t LoopStart,LoopEnd;
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




//========================================================================================//
//****************************************************************************************************
//*函数：void SPI1Rx_Parse(void)	
//*功能：SPI1接收处理函数
//****************************************************************************************************/
void SPI2Rx_Parse(void)
{ //uint8_t i,j,k;
  uint16_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;
/*	//读取 InterruptStatus还是放到中断里面去

	SPI2Sta = SPI2_Read(InterruptStatus1);	// 读取状态寄存其来判断数据接收状况
	
	//	IRDA_LED_ON();
	if(SPI2Sta & RX_DR){				// 判断是否接收到数据
		DelayCom(1000);		    
			SPI2NewFlg = 1;
			SPI2RxCnt++;  //计算进入RX中断次数
		SPI2_CE_L;	//StandBy I模式
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,SPI2_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
//	SPI2_CSN_L;			//NSS拉低，SPI使能
	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
//	SPI2_RW(FLUSH_RX_24L01);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！
	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
	SPI2_Read(FIFO_STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	
//	SPI2_CSN_H;			//NSS拉高，关闭SPI

	SPI2_CE_H;	//置高CE，保持接收模式
	  	//必须知道接收数据通道号RX_P_NO
//	  	TmpVal = ((SPI2Sta & MASK_RX_P_NO)>>1);	//读取接收数据通道号RX_P_NO 
	  if(!SPI2FullFlag){
		for(Loopi=0 ; Loopi<RX_PLOAD_WIDTH_24L01 ; Loopi++){
			SPI2_ParseBuf[SPI2index] = SPI2_RxBuf[Loopi];	//将接收缓冲区SPI1_RxBuf数据转移到处理数据缓冲区SPI1_ParseBuf
			if(0x0A == SPI2_ParseBuf[SPI2index] ){		
				if(0x0D == SPI2_ParseBuf[SPI2index-1] ){
					SPI2OkFlag ++;		//收到0x0D 0x0A认为是一条完整的命令		
				}
			}
			SPI2index++;
			if(SPI2index >= SPI2PARSEBUFLEN){
				SPI2FullFlag = 1;	//接收缓冲区满，未来得及处理数据
			}
		}
	  }
		SPI2NewFlg = 0;



//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	
//	SPI2_CSN_L;			//NSS拉低，SPI使能
//	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
//	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
//	SPI2_CSN_H;			//NSS拉高，关闭SPI
//	SPI2Sta = SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	}

	*/

//	Init_NRF24L01_SPI2();
//	NetConnect(TRUE);				//设置为组网模式

	if(0 != SPI2OkFlag ){								
		for(LoopStart = SPI2Pindex; LoopStart < SPI2index; LoopStart++){
			if(SPI2_ParseBuf[LoopStart]=='#'){//找到命令头了	
				for(LoopEnd = LoopStart; LoopEnd < SPI2index; LoopEnd++){	//找结尾
					if(SPI2_ParseBuf[LoopEnd]=='\n'){//找到命令头了
						SPI2OkFlag--;	//每处理一条命令，接收命令计数器自减
						SPI2Pindex = LoopEnd + 1;
						break;
					}
				}
				comnum = Hash(SPI2_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//计算命令Hash头
				switch (comnum){	//命令散转
					case (RFCMD_CNT):	//CNT握手命令，接收从模块地址  "#CNT,00000\r\n";
					//	if(STA_NETCONNECT == WorkSta1){		//只有当系统在组网模式才执行
							
							if(! NewConnect(SPI2_ParseBuf+LoopStart+5 )){
							//	Usart_SendString_End(USART1 ,StrError);		//从模块地址空间已满
							}	

						/*	else{
								SPI1OkFlag = 0;	//或SPI1OkFlag--
							}*/

						
				//		}
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//将新连接的从模块地址保存到空的接收地址列表
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//如果CNT组网命令接收成功，发接新收到的地址到串口1。
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//指向下一个空的从模块地址空间
						*/
					break;
					case (RFCMD_CNS):	//测试包	"#CNS,00000\r\n";
					__NOP();
					
					break;
					case (RFCMD_HRB):	//心跳包	"#HRB,00000\r\n";
					//	if(STA_DATA == WorkSta2){	//只有当系统在数据接收阶段才执行							
							if(! HeartBeat(SPI2_ParseBuf+LoopStart+5 )){	//检查心跳包里包含的从模块地址
							//	Usart_SendString_End(USART1 ,StrError);		//从模块地址空间已满
							}
						/*	else{
								SPI1OkFlag = 0;	//或SPI1OkFlag--
							}	*/												
					//	}

					break;
					case (RFCMD_TMP):	//温度采集	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta2){	//只有当系统在数据接收阶段才执行							
					//		Usart_SendString(USART1 ,SPI2_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//直接往上位机发送												
						}

					break;
					

					default:
						__NOP();
					//	Usart_SendString_End(USART1 ,StrError);		//接收命令有误，无法解析
					break;
							
				}
				
			//清空缓冲区
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
//说明：成功接收完整一条命令收尾函数	
//参数：void
//返回：命令处理区地址	
//---------------------------------------------------------------------------
/*
u8 CmdOver(u8 CmdFg)		//ken:建立命令索引函数
{
//	CMD_BODY_TypeDef * pCmdBodyBuf = NULL;
	if(CmdFg){
		pCmdBuf->CmdListFlag[pCmdBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
		pCmdBuf->CmdListNum += 1;														//待处理命令数+1			
	}
	//pCmdBuf->pCmd_Body_Current->part.TotalLength = MyStrLen( pCmdBuf->pCmd_Body_Current->all );		//计算命令长度
//	pCmdBuf->CmdCurrentList = 0xFF;
	pCmdBuf->pCmd_Body_Current = NULL;										//清空当前待处理的命令处理缓冲区指针
	
	if(CMDSPI_RXLIST_LMT == pCmdBuf->CmdListNum){		//命令待处理空间满，让EP进入RXNAK等待状态，待处理完之前的命令在使能接收
			
	}
	return pCmdBuf;		//返回空地址
}
*/
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
			case CMDSPI_HASH_NETCNT:	CmdFuncNETCNT(pCmdSpiRxBuf->pCmd_Prc_Current);	break;	//ken:JMP命令
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
//				EP2_TxStr(MsgReplyUNK, MyStrLen(MsgReplyUNK));	//向端点2发送MsgReplyUNK
					__NOP();
			
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
	uint8_t loopi,loopj,NetFlag = 0;//TmpSta;
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
	
	NET_LED_TURN();							//有模块组网成功
	CmdSpiTxApply(FALSE ,pReplyBuf->all ,MyStrLen(pReplyBuf->all));				//将命令存到待处理缓冲区
	return 1;	//已记录新组网模块地址
}


//======================================no  more==========================================//

