//应用程序文件


 /* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "stm32f10x.h"
#include "platform_config.h"
#include "Global.h"
#include "Si4431Api.h"
#include "Si4431App.h"

#include "CmdPrc.h"
#include "UsartCom.h"
#include "SPICom.h"
#include "GloVar.h"

//#include "24L01App.h"
//#include <time.h>

 /* Constant ------------------------------------------------------------------*/
//跳频频道表
/*
const uint8_t FreHopBuf[80] = {\
0x28,0x4A,0x38,0x10,0x74,0x62,0x0B,0x5D,0x3C,0x61,\
0x6B,0x71,0x68,0x11,0x16,0x2A,0x30,0x41,0x5A,0x03,\
0x12,0x14,0x17,0x79,0x08,0x41,0x2A,0x0F,0x58,0x0B,\
0x0A,0x74,0x36,0x27,0x15,0x14,0x31,0x28,0x36,0x23,\
0x05,0x32,0x5C,0x73,0x03,0x06,0x19,0x45,0x09,0x6E,\
0x33,0x74,0x38,0x65,0x17,0x45,0x52,0x06,0x17,0x2B,\
0x51,0x75,0x63,0x30,0x34,0x08,0x38,0x5D,0x13,0x04,\
0x42,0x54,0x48,0x4A,0x35,0x08,0x4B,0x64,0x78,0x35\
} ;		*/
 /* Global Variable ------------------------------------------------------------------*/
// 以下变量用于程序运行
//CMD_BUF_TypeDef	CmdBuf[CMD_NUMLMT] = {0};	
//uint8_t	CmdListFlag[CMD_NUMLMT] = {0};	

/*********************ken********************************** 
*   函数说明： 命令中的八字节ASCII地址与32位变量转换                               
*   输入：  pStrAdr - 字符串首地址; NumAdr - 32位变量 ;sta = TRUE八字节ASCII地址转32位变量,sta = FALSE 32位变量转八字节ASCII地址     				
*   输出：  函数名为转换后的数值 长度为32位                            
*   调用函数：void                                      
***********************************************************/ 
/*
u32 Si4431AdrCover(u8 *pStrAdr, u32 NumAdr ,bool sta )		
{	longWord32	tmpval ;
	u8 i;
	if(sta){	//八字节ASCII地址转32位变量
		tmpval.All32 = MyStrToHex(pStrAdr , CMDSPI_ADR_WIDTH);
//		pNumAdr[0] = tmpval.Bit8[0];
//		pNumAdr[1] = tmpval.Bit8[1];
//		pNumAdr[2] = tmpval.Bit8[2];
//		pNumAdr[3] = tmpval.Bit8[3];
		return 	tmpval.All32;
	}
	else{			//32位变量转八字节ASCII地址
		MyHexToStr(pStrAdr , NumAdr ,CMDSPI_ADR_WIDTH);			
		return 	NumAdr;
	}
}	
*/
/*	if(NumLen>10) {return result;}
	for(i=0;i<NumLen;i++) {
		if((pStr[i]>='0')&&(pStr[i]<='9')){
			result *= 10;
			result += (pStr[i] - '0');
		}
		else{
			return 	0;
		}
	}
	return 	result;	*/



//=============================================================================================
//说明:跳频函数
//参数:SPIx:选择SPI口，Fre：需要设置的频率取值范围0x00-0x7D
//=============================================================================================
void FreHopping(uint8_t SPIx , uint8_t Fre)
{
/*
	SPI1_CE_L;	//StandBy I模式
	if(SPI1CH == SPIx){
		SPI1_RWReg(WRITE_REG_24L01 + RF_CH_24L01, Fre);	//设置信道工作为F0= 2400 + RF_CH [MHz]，收发必须一致 	//跳频时候要改变
	}
	else if(SPI2CH == SPIx){
		SPI2_RWReg(WRITE_REG_24L01 + RF_CH_24L01, Fre);	//设置信道工作为F0= 2400 + RF_CH [MHz]，收发必须一致 	//跳频时候要改变		
	}
	*/
}

//=============================================================================================
//说明:(伪)随机延时函数
//参数:需要设置的频率
//=============================================================================================
void RandomDelayUs(void)
{
	uint8_t k; 	//i,
//	uint32_t t;
//	__NOP();	//空操作
//	srand((unsigned) time(&t));//这个函数是给随机数rand()产生一个随机种子（seed），函数原型是srand（ （unsigned） time（NULL））
//	srand((unsigned) time(NULL));
//	t = clock();
//	t = SysTick->VAL;	//读SysTick当前数值寄存器，是一个0~72的随机值
//	srand((unsigned) t);	//随机函数的种子函数，可以在变值的地方调用，提高随机性
//	printf("Ten random numbers from 0 to 99nn");
//	for(i=0; i<10; i++)
	k = rand()%(RANDMAX - RANDMIN + 1) + RANDMIN ;	//随机数，范围从RANDMIN~RANDMAX
//	printf("%dn", rand()%100);
	DelayUs_Soft(k);
#ifdef DEBUGJK
//	Usart_SendByte(USART1 , k);
#endif
}

//****************************************************************************************************/
//*函数：void SetSPI1_BroadCast(void)
//*功能：将SPI1连接的24L01设置为广播地址，且接收模式 
//****************************************************************************************************/

void NetConnect(bool Sta)
{
	if(TRUE == Sta){	//组网		
		Si4431TX_ReceiveMod(TRUE ,NetConnectRxAdr);		//组网接收地址	
		WorkStaPre1 = STA_NETCONNECT;
	}
  else{	//退出组网状态 	
  	Si4431TX_ReceiveMod(TRUE ,RX_ADDRESS_Si4431);	//回到原来接收地址	
		WorkStaPre1 = STA_STANDBY;
//  IRDA_LED_OFF();
	}
//	SPI1_CE_L;	//StandBy I模式
//	SPI1_CSN_H;	//NSS拉高	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, NetConnectRxAdr, RX_ADR_WIDTH_24L01); // 写接收端地址	
//	SPI1_RWReg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
//	SPI1_CE_H;	//置高CE，激发数据发送
//	SetSPI1_RXMode();
} 

//=============================================================================================
//说明:保存新组网的模块地址，按链表方式保存，每次在上一次保存地址空间后插入
//参数:pNewAdr指向新组网地址，AdrLen地址长度，成功插入地址函数名返回1，否则返回0表示地址空间已满。
//=============================================================================================
uint8_t NewConnect(uint8_t * pNewAdr)
{	uint8_t loopi,loopj;//TmpSta;
	uint8_t strNTA[32] = "#NTA,00000,00000\r\n";	//发送至从模块
//	uint8_t strACN[14] = "#ACN,0,00000\r\n";		//发送给上位机
	u8	OrgSlvAdd[5] = {0};
  if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){	//超过从模块地址保存空间了
  	Usart_SendString_End(USART1 , "JKNetAdrTab is Full!\r\n");
		return 0;

  }
  else{
	
	for(loopi = 1 ; loopi < JKNETADRTABLEN ;loopi++){	//寻找空的从模块地址空间
		if(0 == pJKNetAdr_Tab->TabFlag[loopi]){
		 	pJKNetAdr_Tab->TabFlag[loopi] = 0x10;	//找到空从模块地址空间
			pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//初始化心跳包个数
			break;
		}			
	}
	pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * loopi);	//指向空的从模块地址空间
	
//	strACN[5] = loopi;		//组网编号
	//为新连接的从模块设置组网新地址，保存到空的接收地址列表
	pJKNetAdr_Tab->pJKNetAdrTabCnt[0] = MOD1_RXADR[1];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[1] = MOD1_RXADR[2];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[2] = MOD1_RXADR[3];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[4] = loopi;	//根据组网顺序添加的字段


	for(loopj = 0 ;loopj < SI4431_ADR_WIDTH ; loopj++){
		OrgSlvAdd[loopj]	= * (pNewAdr+loopj);	//原来的从模块的Rx地址
//		pJKNetAdr_Tab->pJKNetAdrTabCnt[loopj] = * (pNewAdr+loopj);	//将新连接的从模块地址保存到空的接收地址列表
//		strACN[loopj + 7] = * (pNewAdr+loopj);	//从模块的Rx地址
	}
		
	
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

 	NET_LED_TURN();							//有模块组网成功
	CmdSpiTxApply(TRUE ,strNTA ,32);				//将命令存到待处理缓冲区

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

  }
	return 0;
}

//=============================================================================================
//说明:监听网络上各模块发送的心跳包，监听到的心跳包个数用队列存储，
//参数:函数名返回1找到从模块并记录心跳，返回0表示未找到从模块地址
//=============================================================================================
uint8_t HeartBeat(uint8_t * pHeartBeatAdr)
{	uint8_t TmpTabCnt,CmpFlag;
	uint8_t * pTmpTab;
//	RUN_LED_TURN();	//新收到数据IR灯跳转一次
	if(0 != pJKNetAdr_Tab->JKNetAdrTabCnt){	//无从模块组网则不用检查心跳包地址
		for(TmpTabCnt = 0; TmpTabCnt < JKNETADRTABLEN; TmpTabCnt++){	//遍历从模块地址
			pTmpTab = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * TmpTabCnt);
			CmpFlag = Buffercmp(pTmpTab , pHeartBeatAdr , SI4431_ADR_WIDTH);
			if(1 == CmpFlag){	//检查到地址
				pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]++;	//心跳计数+1	
				return 1;				
			}						
		}
	}
	return 0;
}



//=============================================================================================
//说明:检查网络上各模块连接状态，如果超时没检测到心跳包，则认为断网了
//参数:函数名返回断开连接的从模块个数
//=============================================================================================
void CheckConnect(void)
{	uint8_t TmpTabCnt,TmpDelCount;
	u8 strMod[] =	"Miss Mod000!\r\n"; 
//	SetSPI1_TXMode
	if(0 != pJKNetAdr_Tab->JKNetAdrTabCnt){	//无从模块组网则不用检查心跳包地址
		for(TmpTabCnt = 1; TmpTabCnt < JKNETADRTABLEN; TmpTabCnt++){	//	
			if(0x10 == pJKNetAdr_Tab->TabFlag[TmpTabCnt]){	//有从模块地址的空间进入		
				if(0 != pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]){
					pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]--;	//	
				}
				else{	//认为有从模块离网了
				/*	Usart_SendString_End(USART1 ,"Miss Mod");		//往串口发模块号		 
					Usart_SendByte(USART1 ,TmpTabCnt/100 + 0x30);
					Usart_SendByte(USART1 ,TmpTabCnt%100/10 + 0x30);
					Usart_SendByte(USART1 ,TmpTabCnt%100%10 + 0x30);
					Usart_SendByte(USART1 ,"!\r\n");	*/
					strMod[8] = TmpTabCnt/100 + 0x30;
					strMod[9] = TmpTabCnt%100/10 + 0x30;
					strMod[10] = TmpTabCnt%100%10 + 0x30;
				//	Usart_SendString_End(USART1 , strMod);
					pJKNetAdr_Tab->TabFlag[TmpTabCnt] = 0;
					IRDA_LED_TURN();	//有模块离网了	
				}
			}
		}
	}

	for(TmpDelCount = TmpTabCnt ;TmpDelCount < pJKNetAdr_Tab->JKNetAdrTabCnt; TmpDelCount++ ){
			
	}

/*	if(i==0) preDepth[channel][++i] = iDepth; //第一个水深值直接赋值
	else
	{
		for(j=i; j>0; j--)		//ken:preDepth[]中，水深值从小到大排
		{
			if(iDepth<preDepth[channel][j])//如果当前水深值比查到的水深值小
			{
				 preDepth[channel][j+1] = preDepth[channel][j];//所查位置水深值往后挪一格
			 	 if(j==1) preDepth[channel][j] = iDepth;//到了最前端，将当前水深值插入
			}
			else
			{
				preDepth[channel][j+1] = iDepth;	//如果当前水深值大于等于所查水深值，插入其后
				break;//找到位置后跳出轮比循环
			}
		}
		i++;
	}
	*/
}

//=============================================================================================
//说明:同步函数，用于发送同步时基
//参数:
//=============================================================================================
/*
void Synchronize(void)	//同步命令，包含时钟信息，
{
	uint8_t strSYN[32] = "#SYN,00\r\n";	//16位TIM3->CNT高位在前
//	uint8_t strindex,Temp_TIM3CNT;	,TempSta = 0
	uint8_t loopi;	

	for(loopi = 1 ; loopi < JKNETADRTABLEN ;loopi++){	//寻找从模块地址空间
		if(0x10 == pJKNetAdr_Tab->TabFlag[loopi]){	//找到存有从模块地址的空间				
			pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * loopi);	//指向从模块地址空间
			Si4431TX_TransmitMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);		//设置SPI1连接的24L01为发射模式，且设置其发射地址为各从模块地址
			strSYN[5] = 0x00FF & (TIM3->CNT)>>8;	//从模块接收后立刻修正自身的TIMx->CNTRH 与 TIMx->CNTRL
			strSYN[6] = 0x00FF & TIM3->CNT;	
			Si4431TX_TxPacket(strSYN, sizeof(strSYN));	//发送同步命令
		}			
	}
		WorkStaPre1 = STA_SYNCHRONIZE;

}*/

//*********************************************************************************************************
//*功能：发送组网连接命令
//*参数: stacnt表示是组网1还是断网0
//*********************************************************************************************************/
void SPI2_CMDCNT(uint8_t stacnt)
{
	uint8_t strCNT[32] = "#CNT,00000\r\n";
	uint8_t strindex;
	if(1 == stacnt){	//从模块转为握手模式
	//	SetSPI2_TXMode(NetConnectRxAdr);		//设置SPI2连接的24L01为发射模式，且设置其发射地址为广播地址
		
		for(strindex=0;strindex<SI4431_ADR_WIDTH;strindex++){
			strCNT[5+strindex] = MOD2_TXADR[strindex];	
		}
		Si4431TX_TxPacket(strCNT ,sizeof(strCNT));
	}
	else{
	
	}
 
}

//*********************************************************************************************************
//*功能：广播阶段，向所有组网的从节点发送广播信息
//*参数: 
//*********************************************************************************************************/
/*
void Broadcast(uint8_t * TxStr)
{u8 Loopi;
	for(Loopi = 1 ; Loopi < JKNETADRTABLEN ;Loopi++){	//寻找从模块地址空间
		if(0x10 == pJKNetAdr_Tab->TabFlag[Loopi]){	//找到存有从模块地址的空间				
			pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * Loopi);	//指向从模块地址空间
			Si4431TX_TransmitMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);		//设置SPI1连接的24L01为发射模式，且设置其发射地址为各从模块地址
			Si4431TX_TxPacket(TxStr ,sizeof(TxStr));
		//	pJKNetAdr_Tab->LoopJKNetAdrIndex = Loopi;
		//	TempSta = 1;
			break;
		}			
	}		

}	 */

//*********************************************************************************************************
//*功能：数据发送，向需要控制的从模块发送命令，将待发命令缓冲区中的命令数据发送至从节点
//*参数: 
//*********************************************************************************************************/
void DataSend(void)
{
//	uint8_t strindex,Temp_TIM3CNT;	,TempSta = 0
	uint8_t loopi,loopj;
	si4431adrtype TxAdr;	
	if(0 != pCmdSpiTxBuf->CmdListNum){			
		for(loopi = 0 ; loopi < CMDSPI_TXLIST_LMT ;loopi++){	//寻找存有待发命令的空间
			if(0 != pCmdSpiTxBuf->CmdListFlag[loopi]){	
				pCmdSpiTxBuf->pCmd_Prc_Current = &(pCmdSpiTxBuf->Cmd_Body[loopi]);	//找到待发送的命令体
				TxAdr.HexAdr.All32 =  MyStrToHex (pCmdSpiTxBuf->pCmd_Prc_Current->part.TargetAdr, CMDSPI_ADR_WIDTH);
		
				Si4431TX_TransmitMod(TxAdr);		//设置为发射模式，发射地址			
				Si4431TX_TxPacket(pCmdSpiTxBuf->pCmd_Prc_Current->all , FIFO_THRESHOLD);	//向从节点发送命令
				DelayMs_Soft(100);
				if(CMD_REPLYSEND_NUM == pCmdSpiTxBuf->CmdListFlag[loopi]){				//找到要发送命令对应的从模块地址							
					pCmdSpiTxBuf->CmdListFlag[loopi] = 0;	//回复命令直发一次  
					pCmdSpiTxBuf->CmdListNum --;						//发送命令计数值减一
				}
				else{
					if(1 == pCmdSpiTxBuf->CmdListFlag[loopi]){	//发送命令失败
						__NOP();	//需要报告上位机，命令发送不成功 
						pCmdSpiTxBuf->CmdListFlag[loopi] = 0;	//回复命令直发一次  
						pCmdSpiTxBuf->CmdListNum --;						//发送命令计数值减一
					}
					else{
						pCmdSpiTxBuf->CmdListFlag[loopi] --;	//每发送一次，减少一次发送计数器值 
					}
				}
			}	
				//StartTimeMs2 = ReadRunTime();	
		}
	}
	//发送完毕回到接收状态
	Si4431TX_ReceiveMod(FALSE , RX_ADDRESS_Si4431);
		
}

//=============================================================================================
//说明:Si4431数据接收阶段，轮流更换接收通道的地址
//输入:void
//输出:void
//调用:Si4431RX_ReceiveMod;SPI2_Read();
//修改:2011-01-26			KEN			初定
//=============================================================================================
/*
void DataReceive(void)
{uint8_t iLoop;				 //,RxPnCnt = 1
//  if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){	//如果组网的从模块数量大于JKNETADRTABLEN，则在DATA阶段需要轮换Rx_P0~P5接收通道的地址
//	for(Loopi = pJKNetAdr_Tab->TabIndex ; Loopi < JKNETADRTABLEN ;Loopi++){	//寻找从模块地址空间
	
	if(pJKNetAdr_Tab->JKNetAdrTabCnt){										//有模块组网才进入		
		iLoop = pJKNetAdr_Tab->LoopJKNetAdrIndex + 1;				//获得上次轮询到的组网地址pJKNetAdr_Tab->TabIndex
		if(JKNETADRTABLEN == iLoop) {
			iLoop = 0;	
		}				//循环轮询
		while(0x10 != pJKNetAdr_Tab->TabFlag[iLoop]){ 		//找到存有从模块地址的空间
			iLoop++;			
		};	
		
		pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * iLoop);	//指向从模块地址空间
		Si4431RX_ReceiveMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);			//设置SPI2接收通道地址为各从模块地址
		
	  pJKNetAdr_Tab->LoopJKNetAdrIndex = iLoop;		//记录这次轮询到的组网地址			
	}
}
*/

//=============================================================================================
//说明:状态机函数，负责主模块各个工作状态下的运作
//参数:
//=============================================================================================
void SysRun(void)
{
  switch(WorkSta1){
	case(STA_NETCONNECT):		//组网退网阶段
		if(STA_NETCONNECT != WorkStaPre1){
			NetConnect(TRUE);				//设置为组网模式
	  	StartTimeMs1 = ReadRunTime(); 
	  }
/*	  else {
	  	EndTimeMs1 = ReadRunTime();
		if( NETCNT_TIMEOUT < CheckTimeInterval(StartTimeMs1 , EndTimeMs1)){	//组网超时
		  NetConnect(FALSE);			//退出组网模式
		  WorkSta1 = STA_STANDBY;		//进入待机状态
	  	
			} 
	  }*/
	break;
	case(STA_SYNCHRONIZE):	//同步阶段
  //    if(STA_SYNCHRONIZE != WorkStaPre1){  
	//	Synchronize();		//同步命令，包含时钟信息，
	//  }
	break;
	case(STA_BROADCAST):	//广播阶段，向需要控制的从模块发送命令
 //     	Broadcast();		//向各从模块发送控制命令
		DataSend();
		WorkSta1 = STA_STANDBY;
	break;

	case(STA_P2P):			//大量数据点对点传输
      
	break;
	case(STA_SLEEP):		//休眠模式
      
	break;    
	case(STA_STANDBY):		//待机状态
		WorkStaPre1 = STA_STANDBY;
	break;
	default:
	
    break;
  }


  switch(WorkSta2){  
	case(STA_DATA):			//维持心跳包及普通数据采集阶段	
//		DataReceive();

	/*	if(STA_DATA != WorkStaPre2){
	//	SetSPI1_RXMode(RX_P0_24L01,MOD1_RXADR);	//设置为自身的地址
			DataReceive();
			WorkStaPre2 = STA_DATA;
			StartTimeMs3 = ReadRunTime();
		}
		else{
	  	EndTimeMs3 = ReadRunTime();
			if( DATARECEIVE_SPAN < CheckTimeInterval(StartTimeMs3 , EndTimeMs3)){	//组网超时
				WorkSta2 = STA_STANDBY;	
			
			}			
		}	*/		        
	break;
	case(STA_STANDBY):			//维持心跳包及普通数据采集阶段
	
	break; 
	case(STA_SLEEP):		//休眠模式
      
	break;
	default:
	
    break;  
  }  		
}
