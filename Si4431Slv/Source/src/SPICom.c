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
#include "Global.h"
//#include "SPICom.h"	
//------------------------------------------------------------------------------------//

@near u8 SPI1_TxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Tx
//u8 SPI2_TxBuf[BufferSize] = {0};		//SPIz_Buffer_Tx
@near u8 SPI1_RxBuf[SPIBUFLEN] ;		//SPIy_Buffer_Rx
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
@near u8 SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区

//@near u8 txLog[TXLOGLEN];
@near u8 SPI1ByteNum;		 //在协议0时串口按接收到的命令字节总数来结束一条命令的接收
//u8 SPI2_ParseBuf[SPI2PARSEBUFLEN];//串口1接收缓冲区

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
//  static u8 strCNT[]  = "CNT";             
//  static u8 LOG[] = "$log,ES";		   //  7
//  static u8 SET[] = "$set,ES";		   //  7

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
		for(LoopStart = SPI1Pindex; LoopStart < SPI1index; LoopStart++){
			if(SPI1_ParseBuf[LoopStart]=='#'){//找到命令头了	
				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//找结尾
					if(SPI1_ParseBuf[LoopEnd]=='\n'){//找到命令头了
						SPI1OkFlag--;	//每处理一条命令，接收命令计数器自减
						SPI1Pindex = LoopEnd + 1;
						break;
					}
				}
						
				comnum = Hash(SPI1_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//计算命令Hash头
				switch (comnum){	//命令散转
					case (RFCMD_NTA):	//NTA握手命令，接收从模块地址  "#NTA,00000\r\n";
				
						NetApply(SPI1_ParseBuf+LoopStart+5 );
					//	if(STA_NETCONNECT == WorkSta1){		//只有当系统在组网模式才执行
							
							
						//	Uart1_SendString_End("NetApply\0");		//从模块地址空间已满
							/*	else{
								SPI1OkFlag = 0;	//或SPI1OkFlag--
							}*/
					//	}
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//将新连接的从模块地址保存到空的接收地址列表
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//如果CNT组网命令接收成功，发接新收到的地址到串口1。
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//指向下一个空的从模块地址空间
						*/
					break;
					
					case (RFCMD_SYN):	//收到同步命令	"#SYN,00\r\n";	//16位TIM3->CNT高位在前
						if(STA_SYNCHRONIZE == WorkSta1){	//只有当系统在同步阶段才执行							
							Synchronize(SPI1_ParseBuf + LoopStart);
						//	Uart1_SendString(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//直接往上位机发送												
						}
					break;					
					
					case (RFCMD_TMP):	//温度采集	"#TMP,0,00000\r\n";
						if(STA_DATA == WorkSta1){	//只有当系统在数据接收阶段才执行							
							SPI1_CMDTMP();
						//	CmdApply(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);		//将命令存到待处理缓冲区
						//	Uart1_SendString(SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//直接往上位机发送												
						}

					break;
					
					default:
					//	Uart1_SendString_End(StrError);		//接收命令有误，无法解析
					break;
							
				}
				
			//清空缓冲区
			if((0 == SPI1OkFlag)||(SPI1index >= SPI1PARSEBUFLEN))
			for (Loopi = 0; Loopi < SPI1PARSEBUFLEN; Loopi++){
	 			SPI1_ParseBuf[Loopi] = 0;	
			}
	  		SPI1index   = 0;
			SPI1Pindex = 0;
			SPI1FullFlag = 0;
		//	U0Pindex  = 0;
	  				   			
				
							
			}
		} 
	//	if(0 != SPI1OkFlag){	
	//		SPI1OkFlag--;	
	//	}
	}
				

}




//========================================================================================//




//======================================no  more==========================================//

