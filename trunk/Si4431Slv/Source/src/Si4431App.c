//应用程序文件


 /* Includes ------------------------------------------------------------------*/
#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"
//#include "UsartCom.h"
#include "Si4431Api.h"
#include "Si4431App.h"
#include "SPICom.h"
#include <stdlib.h>

//#include <time.h>
//#include <stdlib.h>
 /* Constant ------------------------------------------------------------------*/
//跳频频道表
/*
const u8 FreHopBuf[80] = {\
0x28,0x4A,0x38,0x10,0x74,0x62,0x0B,0x5D,0x3C,0x61,\
0x6B,0x71,0x68,0x11,0x16,0x2A,0x30,0x41,0x5A,0x03,\
0x12,0x14,0x17,0x79,0x08,0x41,0x2A,0x0F,0x58,0x0B,\
0x0A,0x74,0x36,0x27,0x15,0x14,0x31,0x28,0x36,0x23,\
0x05,0x32,0x5C,0x73,0x03,0x06,0x19,0x45,0x09,0x6E,\
0x33,0x74,0x38,0x65,0x17,0x45,0x52,0x06,0x17,0x2B,\
0x51,0x75,0x63,0x30,0x34,0x08,0x38,0x5D,0x13,0x04,\
0x42,0x54,0x48,0x4A,0x35,0x08,0x4B,0x64,0x78,0x35\
} ;	*/
 /* Global Variable ------------------------------------------------------------------*/
// 以下变量用于程序运行
//CMD_BUF_TypeDef	CmdBuf[CMD_NUMLMT] = {0};	
//u8	CmdListFlag[CMD_NUMLMT] = {0};	
//保存各接收模块的地址。
//RxAdrTab_TypeDef * pRxAdr_Tab;
//RxAdrTab_TypeDef RxAdr_Tab;

//=============================================================================================
//说明:跳频函数
//参数:SPIx:选择SPI口，Fre：需要设置的频率取值范围0x00-0x7D
//=============================================================================================
void FreHopping(u8 SPIx , u8 Fre)
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
	u8 k; 	//i,
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
	//	Si4431TX_TransmitMod(NetConnectRxAdr);					//组网发射地址
		CmdSpiTxApply(TRUE,StrTest ,MyStrLen(StrTest));				//将命令存到待处理缓冲区   TRUE

		WorkStaPre1 = STA_NETCONNECT;
	}
  else{	//退出组网状态 	
		Si4431TX_ReceiveMod(TRUE ,RX_ADDRESS_Si4431);						//	无效的接收地址	
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
/*
u8 NewConnect(u8 * pNewAdr)
{	u8 loopi,loopj;
	u8 strNTA[32] = "#NTA,0,00000\r\n";	//发送至从模块
	u8 strACN[14] = "#ACN,0,00000\r\n";		//发送给上位机
  if(pRxAdr_Tab->RxAdrTabCnt > RXADRTABLEN){	//超过从模块地址保存空间了
  	return 0;
  }
  else{
	
	for(loopi = 1 ; loopi < RXADRTABLEN ;loopi++){	//寻找空的从模块地址空间
		if(0 == pRxAdr_Tab->TabFlag[loopi]){
		 	pRxAdr_Tab->TabFlag[loopi] = 0x10;	//找到空从模块地址空间
			pRxAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//初始化心跳包个数
			break;
		}			
	}
	pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01 * loopi);	//指向空的从模块地址空间
	
	strACN[5] = loopi;		//组网编号
	for(loopj = 0 ;loopj < TX_ADR_WIDTH_24L01 ; loopj++){
		pRxAdr_Tab->pRxAdrTabCnt[loopj] = * (pNewAdr+loopj);	//将新连接的从模块地址保存到空的接收地址列表
		strACN[loopj + 7] = * (pNewAdr+loopj);	//从模块的Rx地址
	}
	
	Uart1_SendString(strACN , 14);		//ACN组网命令接收成功，发接新收到的从节点Rx地址及组网编号到串口1。
	
	
	pRxAdr_Tab->RxAdrTabCnt++;	//从模块地址计数器加1
	//组网成功，向从模块发送新的TX地址(即主模块RX_P1~P5的RX地址)
	//组网后在主模块上对应的的从模块接收通道地址命名规范 :(需要符合24L01规范)
	//主模块2 3 4 5字段地址 + 根据组网顺序添加的字段
	SetSPI1_TXMode(pRxAdr_Tab->pRxAdrTabCnt);

	strNTA[5] = MOD1_RXADR[1];
	strNTA[6] = MOD1_RXADR[2];
	strNTA[7] = MOD1_RXADR[3];
	strNTA[8] = MOD1_RXADR[4];
	strNTA[9] = loopi;	//根据组网顺序添加的字段

	nRF24L01_SPI1_TxPacket(strNTA);		//NTA发送新的从节点Tx地址

//	if(RXADRTABLEN > pRxAdr_Tab->RxAdrTabCnt){	//超过RXADRTABLEN个地址不在存储
//		pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//指向下一个空的从模块地址空间
//  	}	
	return 1;
  }

}
*/
/*
u8 NetApply(u8 * pNewAdr)
{	u8 loopi,loopj;
	
	for(loopj = 0 ;loopj < TX_ADR_WIDTH ; loopj++){
		Net_TXADR[loopj] = * (pNewAdr+loopj);	//将新连接的从模块地址保存到空的接收地址列表
		Net_RXADR[loopj] = * (pNewAdr+loopj);	//将新连接的从模块地址保存到空的接收地址列表
	}
//	SetSlv_RxMode(Net_RXADR);	
	WorkSta1 = STA_STANDBY;
	InNetFlag = TRUE;
	//GPIO_WriteLow(LEDS_PORT, LED0_PIN);
//	TIM2_Cmd(DISABLE); 
  //TIMx 时钟频率除数的预分频值 16/1024 = 0.015625MHz 64US	 	
//  TIM2_TimeBaseInit(TIM2_PRESCALER_1024, 15624);	//正好两秒
// TIM2_Cmd(ENABLE);

}*/
//=============================================================================================
//说明:监听网络上各模块发送的心跳包，监听到的心跳包个数用队列存储，
//参数:函数名返回1找到从模块并记录心跳，返回0表示未找到从模块地址
//=============================================================================================
/*
u8 HeartBeat(u8 * pHeartBeatAdr)
{	u8 TmpTabCnt,CmpFlag;
	u8 * pTmpTab;
//	RUN_LED_TURN();	//新收到数据IR灯跳转一次
	if(0 != pRxAdr_Tab->RxAdrTabCnt){	//无从模块组网则不用检查心跳包地址
		for(TmpTabCnt = 0; TmpTabCnt < RXADRTABLEN; TmpTabCnt++){	//遍历从模块地址
			pTmpTab = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH * TmpTabCnt);
			CmpFlag = Buffercmp(pTmpTab , pHeartBeatAdr , TX_ADR_WIDTH);
			if(1 == CmpFlag){	//检查到地址
				pRxAdr_Tab->HeartBeatSta[TmpTabCnt]++;	//心跳计数+1	
				return 1;				
			}						
		}
	}
	return 0;
}
*/


//=============================================================================================
//说明:检查网络上各模块连接状态，如果超时没检测到心跳包，则认为断网了
//参数:函数名返回断开连接的从模块个数
//=============================================================================================
/*
void CheckConnect(void)
{	u8 TmpTabCnt,TmpDelCount;
	u8 strMod[] =	"Miss Mod000!\r\n"; 
//	SetSPI1_TXMode
	if(0 != pRxAdr_Tab->RxAdrTabCnt){	//无从模块组网则不用检查心跳包地址
		for(TmpTabCnt = 1; TmpTabCnt < RXADRTABLEN; TmpTabCnt++){	//	
			if(0x10 == pRxAdr_Tab->TabFlag[TmpTabCnt]){	//有从模块地址的空间进入		
				if(0 != pRxAdr_Tab->HeartBeatSta[TmpTabCnt]){
					pRxAdr_Tab->HeartBeatSta[TmpTabCnt]--;	//	
				}
				else{	//认为有从模块离网了
				//	Usart_SendString_End(USART1 ,"Miss Mod");		//往串口发模块号		 
				//	Usart_SendByte(USART1 ,TmpTabCnt/100 + 0x30);
				//	Usart_SendByte(USART1 ,TmpTabCnt%100/10 + 0x30);
				//	Usart_SendByte(USART1 ,TmpTabCnt%100%10 + 0x30);
				//	Usart_SendByte(USART1 ,"!\r\n");	
					strMod[8] = TmpTabCnt/100 + 0x30;
					strMod[9] = TmpTabCnt%100/10 + 0x30;
					strMod[10] = TmpTabCnt%100%10 + 0x30;
				//	Usart_SendString_End(USART1 , strMod);
					pRxAdr_Tab->TabFlag[TmpTabCnt] = 0;
//					IRDA_LED_TURN();	//有模块离网了	
				}
			}
		}
	}

	for(TmpDelCount = TmpTabCnt ;TmpDelCount < pRxAdr_Tab->RxAdrTabCnt; TmpDelCount++ ){
			
	}
*/
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
	
}
*/
//=============================================================================================
//说明:同步函数，用于发送同步时基
//参数:
//=============================================================================================
/*
void Synchronize(void)	//同步命令，包含时钟信息，
{
	u8 strSYN[32] = "#SYN,00\r\n";	//16位TIM3->CNT高位在前
//	u8 strindex,Temp_TIM3CNT;	,TempSta = 0
	u8 loopi;	

	for(loopi = 1 ; loopi < RXADRTABLEN ;loopi++){	//寻找从模块地址空间
		if(0x10 == pRxAdr_Tab->TabFlag[loopi]){	//找到存有从模块地址的空间				
			pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH * loopi);	//指向从模块地址空间
			Si4431TX_TransmitMod(pRxAdr_Tab->pRxAdrTabCnt);		//设置SPI1连接的24L01为发射模式，且设置其发射地址为各从模块地址
			strSYN[5] = 0x00FF & (TIM3->CNTRH);	//从模块接收后立刻修正自身的TIMx->CNTRH 与 TIMx->CNTRL
			strSYN[6] = 0x00FF & TIM3->CNTRL;	
			Si4431TX_TxPacket(strSYN, sizeof(strSYN));	//发送同步命令
		}			
	}
		WorkStaPre1 = STA_SYNCHRONIZE;

}	*/

//*********************************************************************************************************
//*功能：发送组网连接命令
//*参数: stacnt表示是组网1还是断网0
//*********************************************************************************************************/
/*
void SPI2_CMDCNT(u8 stacnt)
{
	u8 strCNT[32] = "#CNT,00000\r\n";
	u8 strindex;
	if(1 == stacnt){	//从模块转为握手模式
	//	SetSPI2_TXMode(NetConnectRxAdr);		//设置SPI2连接的24L01为发射模式，且设置其发射地址为广播地址
		
		for(strindex=0;strindex<TX_ADR_WIDTH;strindex++){
			strCNT[5+strindex] = MOD2_TXADR[strindex];	
		}
		Si4431TX_TxPacket(strCNT ,sizeof(strCNT));
	}
	else{
	
	}
 
}
*/
//*********************************************************************************************************
//*功能：广播阶段，向所有组网的从节点发送广播信息
//*参数: 
//*********************************************************************************************************/
/*
void Broadcast(u8 * TxStr)
{u8 Loopi;
	for(Loopi = 1 ; Loopi < RXADRTABLEN ;Loopi++){	//寻找从模块地址空间
		if(0x10 == pRxAdr_Tab->TabFlag[Loopi]){	//找到存有从模块地址的空间				
			pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH * Loopi);	//指向从模块地址空间
			Si4431TX_TransmitMod(pRxAdr_Tab->pRxAdrTabCnt);		//设置SPI1连接的24L01为发射模式，且设置其发射地址为各从模块地址
			Si4431TX_TxPacket(TxStr ,sizeof(TxStr));
		//	pRxAdr_Tab->LoopRxAdrIndex = Loopi;
		//	TempSta = 1;
			break;
		}			
	}		

}
*/
//*********************************************************************************************************
//*功能：数据发送，向需要控制的从模块发送命令，将待发命令缓冲区中的命令数据发送至从节点
//*参数: 
//*********************************************************************************************************/
void DataSend(void)
{
//	uint8_t strindex,Temp_TIM3CNT;	,TempSta = 0
	u8 loopi,loopj;
	si4431adrtype TxAdr;	
	if(0 != pCmdSpiTxBuf->CmdListNum){			
		for(loopi = 0 ; loopi < CMDSPI_TXLIST_LMT ;loopi++){	//寻找存有待发命令的空间
			if(0 != pCmdSpiTxBuf->CmdListFlag[loopi]){	
				pCmdSpiTxBuf->pCmd_Prc_Current = &(pCmdSpiTxBuf->Cmd_Body[loopi]);	//找到待发送的命令体
				TxAdr.HexAdr.All32 =  MyStrToHex (pCmdSpiTxBuf->pCmd_Prc_Current->part.TargetAdr, CMDSPI_ADR_WIDTH);
		
				Si4431TX_TransmitMod(TxAdr);		//设置为发射模式，发射地址			
				Si4431TX_TxPacket(pCmdSpiTxBuf->pCmd_Prc_Current->all , MyStrLen(pCmdSpiTxBuf->pCmd_Prc_Current->all));	//向从节点发送命令
				DelayMs_Soft(100);
				GPIO_WriteReverse(LEDS_PORT, LED0_PIN);
				if(CMD_REPLYSEND_NUM == pCmdSpiTxBuf->CmdListFlag[loopi]){				//找到要发送命令对应的从模块地址							
					pCmdSpiTxBuf->CmdListFlag[loopi] = 0;	//回复命令直发一次  
					pCmdSpiTxBuf->CmdListNum --;						//发送命令计数值减一
				}
				else{
					if(1 == pCmdSpiTxBuf->CmdListFlag[loopi]){	//发送命令失败
						nop();	//需要报告上位机，命令发送不成功 
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
	Si4431TX_ReceiveMod(TRUE , RX_ADDRESS_Si4431);
		
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
{u8 iLoop,Tempi,RxPnCnt = 1;	
//  if(pRxAdr_Tab->RxAdrTabCnt > RXADRTABLEN){	//如果组网的从模块数量大于RXADRTABLEN，则在DATA阶段需要轮换Rx_P0~P5接收通道的地址
//	for(Loopi = pRxAdr_Tab->TabIndex ; Loopi < RXADRTABLEN ;Loopi++){	//寻找从模块地址空间
	
	if(pRxAdr_Tab->RxAdrTabCnt){										//有模块组网才进入		
		iLoop = pRxAdr_Tab->LoopRxAdrIndex + 1;				//获得上次轮询到的组网地址pRxAdr_Tab->TabIndex
		if(RXADRTABLEN == iLoop) {
			iLoop = 0;	
		}				//循环轮询
		while(0x10 != pRxAdr_Tab->TabFlag[iLoop]){ 		//找到存有从模块地址的空间
			iLoop++;			
		};	
		
		pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH * iLoop);	//指向从模块地址空间
		Si4431TX_ReceiveMod(pRxAdr_Tab->pRxAdrTabCnt);			//设置SPI2接收通道地址为各从模块地址
		
	  pRxAdr_Tab->LoopRxAdrIndex = iLoop;		//记录这次轮询到的组网地址			
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
	  //	StartTimeMs1 = ReadRunTime(); 
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
	//	DataReceive();

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
