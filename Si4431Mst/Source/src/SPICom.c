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

//CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体
CMDSPI_BUF_TypeDef		CmdSpiTxBuf;										//命令发送缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiTxBuf;								//指向命令发送缓冲区
CMDSPI_BUF_TypeDef		CmdSpiRxBuf;										//命令接收缓冲区
CMDSPI_BUF_TypeDef	*	pCmdSpiRxBuf;								//指向命令接收缓冲区
CMDSPI_BODY_TypeDef  ReplyBuf;								//应答缓冲区
CMDSPI_BODY_TypeDef * pReplyBuf;								//应答缓冲区

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
//  static uint8_t strCNT[]  = "CNT";             
//  static uint8_t LOG[] = "$log,ES";		   //  7
//  static uint8_t SET[] = "$set,ES";		   //  7
/*	if(1 == SPI1NewFlg){	//SPI1收到新数据
		for(i=0;i<TX_PLOAD_WIDTH_24L01;i++){
			SPI1_ParseBuf[SPI1index] = SPI1_RxBuf[i];
			if(0x0A == SPI1_ParseBuf[SPI1index] ){		
				if(0x0D == SPI1_ParseBuf[SPI1index-1] ){
					SPI1OkFlag ++;		//收到0x0D 0x0A认为是一条完整的命令		
				}
			}
			SPI1index++;
		}
		SPI1NewFlg = 0;	
	}	*/
	if(0 != SPI1OkFlag ){								
		for(LoopStart = 0; LoopStart < SPI1index; LoopStart++){
			if(SPI1_ParseBuf[LoopStart]=='#'){		//找到命令头了	
				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//找结尾
					if(SPI1_ParseBuf[LoopEnd]=='\n'){	//找到命令结尾
						SPI1OkFlag--;	//每处理一条命令，接收命令计数器自减
						SPI1Pindex = LoopEnd + 1;
						CmdSpiApply(Spi1_Cmd_RxPort , &SPI1_ParseBuf[LoopStart] ,(LoopEnd-LoopStart+1));	//建立索引命令
						break;
					}
				}
			}
		}	
			/*	
				comnum = Hash(SPI1_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//计算命令Hash头
				switch (comnum){	//命令散转
					case (RFCMD_CNT):	//CNT握手命令，接收从模块地址  "#CNT,00000\r\n";
						if(STA_NETCONNECT == WorkSta1){		//只有当系统在组网模式才执行
							if(! NewConnect(SPI1_ParseBuf+LoopStart+5 )){
								Usart_SendString_End(USART1 ,StrError);		//从模块地址空间已满
							}
						}	
					break;


					
					case (RFCMD_HRB):	//心跳包	"#HRB,00000\r\n";
						if(STA_DATA == WorkSta2){	//只有当系统在数据接收阶段才执行							
							if(! HeartBeat(SPI1_ParseBuf+LoopStart+5 )){	//检查心跳包里包含的从模块地址
							//	Usart_SendString_End(USART1 ,StrError);		//从模块地址空间已满
							}
						//	else{
						//		SPI1OkFlag = 0;	//或SPI1OkFlag--
						//	}													
						}

					break;
					case (RFCMD_TMP):	//温度采集	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta2){	//只有当系统在数据接收阶段才执行							
						//	Usart_SendString(USART1 ,SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//直接往上位机发送												
						}

					break;
					

					default:
					//	Usart_SendString_End(USART1 ,StrError);		//接收命令有误，无法解析
					break;
							
				}
			*/	
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
//说明：Spi建立命令索引函数，寻找空的索引空间
//参数：port:通讯接口类型 ；* cmddata:数据空间首地址；cmdlen:数据长度
//返回：命令建立情况	
//---------------------------------------------------------------------------
u8 CmdSpiApply(CMD_PORT_TPYE port ,u8 * cmddata ,u16 cmdlen)		
{
	u8	i = 0,j = 0;
//	CMD_BUF_TypeDef * pCmdBufApp = NULL;
	switch(port){
		case (Spi1_Cmd_TxPort):										//建立待发送命令索引
			i = pCmdSpiTxBuf->CmdCurrentList ;			//获得此前命令索引位置
			while(1 == CmdSpiTxBuf.CmdListFlag[i]){	//寻找空的从模块地址空间
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
			pCmdSpiTxBuf->CmdListFlag[pCmdSpiTxBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
			pCmdSpiTxBuf->CmdListNum += 1;																//待处理命令数+1
			
		break;
		case (Spi1_Cmd_RxPort):										//建立处理命令索引
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
			pCmdSpiRxBuf->CmdListFlag[pCmdSpiRxBuf->CmdCurrentList]	= 1;	//当前命令建立成功		
			pCmdSpiRxBuf->CmdListNum += 1;																//待处理命令数+1
					
		break;
		default :
		break;
	}

	return 1;//建立命令索引成功
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

void CmdExecute(void)		//执行散转函数
{	u16	HeadHash,i,j;
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
	
	
		HeadHash = Hash(pCmdSpiRxBuf->pCmd_Prc_Current->part.Header , CMDSPI_HEADER_LEN);	//计算命令hash头
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
{			
	longWord32	NewAdr;
	u16 RpStrLen;	 
	uint8_t loopi,loopj,NetFlag;//TmpSta;
	uint8_t strNETAPL[32] = "#NETAPL\0";	//发送至从模块


//	uint8_t strACN[14] = "#ACN,0,00000\r\n";		//发送给上位机
//	u8	OrgSlvAdd[5] = {0};
//	Si4431AdrCover(pCmdData->part.SourceAdr ,pJKNetAdr_Tab->pJKNetAdrTabCnt ,TRUE);		//八字节ASCII地址转hex四字节地址
	
	NewAdr.All32 = MyStrToHex(pCmdData->part.SourceAdr, CMDSPI_ADR_WIDTH);
	
	for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){		//首先与已组网地址比较
		if(1 == pJKNetAdr_Tab->TabFlag[loopi]){	
		 	if(pJKNetAdr_Tab->JKNetNumTab[loopi] == NewAdr.All32){
				NetFlag = 1;																					//此模块已组网
				pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//重置心跳包个数				
			}
		}			
	}  
if(0 == NetFlag){		//新模块未组网
	if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){		//超过从模块地址保存空间了
  //	Usart_SendString_End(USART1 , "JKNetAdrTab is Full!\r\n");
  	return 0;	//此模块以组网
	}
  else{
		for(loopi = 0 ; loopi < JKNETADRTABLEN ;loopi++){	//寻找空的从模块地址空间
			if(0 == pJKNetAdr_Tab->TabFlag[loopi]){
			 	pJKNetAdr_Tab->TabFlag[loopi] = 0x01;	//找到空从模块地址空间
				pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//初始化心跳包个数
				break;
			}			
		}
	pJKNetAdr_Tab->JKNetNumTab[loopi] = NewAdr.All32;	//记录新组网地址
/*	
	pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * loopi);	//指向空的从模块地址空间
	for(loopj = 0; loopj < SI4431_ADR_WIDTH; loopj++){
		pJKNetAdr_Tab->pJKNetAdrTabCnt[loopj] = NewAdr.Bit8[loopj];
	}*/
	

	//为新连接的从模块设置组网新地址，保存到空的接收地址列表
//	pJKNetAdr_Tab->pJKNetAdrTabCnt[0] = pCmdData->part.SourceAdr[1];
//	pJKNetAdr_Tab->pJKNetAdrTabCnt[1] = pCmdData->part.SourceAdr[2];
//	pJKNetAdr_Tab->pJKNetAdrTabCnt[2] = pCmdData->part.SourceAdr[3];
//	pJKNetAdr_Tab->pJKNetAdrTabCnt[4] = pCmdData->part.SourceAdr[4];;	//根据组网顺序添加的字段

//	Si4431AdrCover(pCmdData->part.SourceAdr ,pJKNetAdr_Tab->pJKNetAdrTabCnt ,TRUE);		//八字节ASCII地址转hex四字节地址

	MsgInsrt(pReplyBuf->all , strNETAPL , MyStrLen(strNETAPL) , TRUE);	//插入命令头
	MsgInsrt(pReplyBuf->all , RX_ADDRESS_Si4431 , MyStrLen(RX_ADDRESS_Si4431) , TRUE);	//插入源地址
	MsgInsrt(pReplyBuf->all , pJKNetAdr_Tab->pJKNetAdrTabCnt , MyStrLen(pJKNetAdr_Tab->pJKNetAdrTabCnt) , TRUE);	//插入目标地址


/*	
	for(loopj = 0 ;loopj < SI4431_ADR_WIDTH ; loopj++){
		OrgSlvAdd[loopj]	= * (pNewAdr+loopj);	//原来的从模块的Rx地址
//		pJKNetAdr_Tab->pJKNetAdrTabCnt[loopj] = * (pNewAdr+loopj);	//将新连接的从模块地址保存到空的接收地址列表
//		strACN[loopj + 7] = * (pNewAdr+loopj);	//从模块的Rx地址
	}
		
	pJKNetAdr_Tab->JKNetAdrTabCnt++;	//从模块地址计数器加1
	//组网成功，向从模块发送新的TX地址(即主模块RX_P1~P5的RX地址)
	//组网后在主模块上对应的的从模块接收通道地址命名规范 :(需要符合24L01规范)
	//主模块2 3 4 5字段地址 + 根据组网顺序添加的字段
//	SetSPI1_TXMode(OrgSlvAdd);	//向新组网的模块发送组网新地址。
	
//	DelayCom(50000);
//	TmpSta = SPI1_Read(TX_ADDR_24L01);	//测试模块地址设置是否正确
//	TmpSta = SPI1_Read(RX_ADDR_P0_24L01);	//测试模块地址设置是否正确



	strNTA[5] = OrgSlvAdd[0];
	strNTA[6] = OrgSlvAdd[1];
	strNTA[7] = OrgSlvAdd[2];
	strNTA[8] = OrgSlvAdd[3];
	strNTA[9] = OrgSlvAdd[4];		//原模块地址

	strNTA[11] = MOD1_RXADR[1];
	strNTA[12] = MOD1_RXADR[2];
	strNTA[13] = MOD1_RXADR[3];
	strNTA[14] = loopi;					//根据组网顺序添加的字段

 	*/
	
	NET_LED_TURN();							//有模块组网成功
	CmdSpiApply(Spi1_Cmd_TxPort ,pReplyBuf->all ,MyStrLen(pReplyBuf->all));				//将命令存到待处理缓冲区
	return 1;	//已记录新组网模块地址
	}
 }
		/*
		for(loopj = 0 ;loopj < CMD_MAXRESEND ;loopj++){	
			nRF24L01_SPI1_TxPacket(strNTA);		//NTA发送新的从节点Tx地址

			StartTimeMs2 = ReadRunTime();
			while(!(SPI1Sta & MASK_TX_STA)){	//等待TX_DS或MAX_RT中断
				EndTimeMs2 = ReadRunTime();
				if( 50 < CheckTimeInterval(StartTimeMs2 , EndTimeMs2)){	//发送新节点地址超时
					break;
				}	
			}
			#ifdef DEBUGJK
//			SPI1Sta = MAX_RT;	//测试用
			#endif			
			if(SPI1Sta & TX_DS){	//组网命令发送成功，进入接收模式，等待主模块发送新地址
//				Usart_SendString(USART1 ,strACN , 14);		//ACN组网命令接收成功，发接新收到的从节点Rx地址及组网编号到串口1。
			//	SPI2_PWR_OFF();
			//	DelayUs(500);
				NET_LED_TURN();		//有模块组网成功
				DataReceive();
			//	WorkSta2 = STA_DATA;					
//				SPI2_CE_L;	//StandBy I模式
				
				Init_NRF24L01_SPI2();
				NetConnect(TRUE);				//设置为组网模式
				return 1;				
			}
			else if(SPI1Sta & MAX_RT){		//发送失败，等待重发
				RandomDelayUs();
				if(loopj == CMD_MAXRESEND-1){	//若到达最大重发次数，表明命令发送失败
//					Usart_SendString_End(USART1 , "CMDNTANoReply\r\n");
					//ACN组网命令接收成功，发接新收到的从节点Rx地址及组网编号到串口1。
					pJKNetAdr_Tab->TabFlag[loopi] = 0x00;	//如果新组网地址发送不成功，不保存此模块地址记录，认为组网不成功
					return 0;
				}
			}			
		}	
		*/
/*	if(JKNETADRTABLEN > pJKNetAdr_Tab->JKNetAdrTabCnt){	//超过JKNETADRTABLEN个地址不在存储
		pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (TX_ADR_WIDTH*pJKNetAdr_Tab->JKNetAdrTabCnt);	//指向下一个空的从模块地址空间
  	}	*/

  
		
	
/*	pCmdBuf->pReplyBuf = pCmdSTTBody;
 
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
	*/			
}

//======================================no  more==========================================//

