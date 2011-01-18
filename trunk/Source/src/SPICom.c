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
#include "SPICom.h"	
//------------------------------------------------------------------------------------//

uint8_t SPI1_TxBuf[BufferSize] = "#NTA,0,12345\r\n";		//SPIy_Buffer_Tx
uint8_t SPI2_TxBuf[BufferSize] = {0};		//SPIz_Buffer_Tx
uint8_t SPI1_RxBuf[BufferSize] = {0};		//SPIy_Buffer_Rx
uint8_t SPI2_RxBuf[BufferSize] = {0};		//SPIz_Buffer_Rx

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
u8		SPI1_SendBuf[SPI1PARSEBUFLEN];	//SPI1接收缓冲区

uint8_t	txLog[TXLOGLEN];
uint8_t	SPI1ByteNum;		 //在协议0时串口按接收到的命令字节总数来结束一条命令的接收
uint8_t	SPI2_ParseBuf[SPI2PARSEBUFLEN];//串口1接收缓冲区

//====================================================================================//
//====================================================================================// 

//****************************************************************************************************
//*函数：void SPI1Rx_Parse(void)	
//*功能：SPI1接收处理函数
//****************************************************************************************************/
void SPI1Rx_Parse(void)
{ //uint8_t i,j,k;
  uint8_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;
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
			/*		case (RFCMD_CNT):	//CNT握手命令，接收从模块地址  "#CNT,00000\r\n";
						if(STA_NETCONNECT == WorkSta1){		//只有当系统在组网模式才执行
							if(! NewConnect(SPI1_ParseBuf+LoopStart+5 )){
								Usart_SendString_End(USART1 ,StrError);		//从模块地址空间已满
							}
						}	
					break;*/

						/*	else{
								SPI1OkFlag = 0;	//或SPI1OkFlag--
							}*/

						
						
					/*	for(k=0;k<RX_ADR_WIDTH_24L01;k++){
							pRxAdr_Tab->pRxAdrTabCnt[k] = * (SPI1_ParseBuf+i+5+k);	//将新连接的从模块地址保存到空的接收地址列表
						}
						Usart_SendString(USART1 ,pRxAdr_Tab->pRxAdrTabCnt , TX_ADR_WIDTH_24L01);		//如果CNT组网命令接收成功，发接新收到的地址到串口1。
						pRxAdr_Tab->RxAdrTabCnt++;
						pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0 + (TX_ADR_WIDTH_24L01*pRxAdr_Tab->RxAdrTabCnt);	//指向下一个空的从模块地址空间
						*/
					
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
							Usart_SendString(USART1 ,SPI1_ParseBuf + LoopStart ,LoopEnd - LoopStart);	//直接往上位机发送												
						}

					break;
					

					default:
						Usart_SendString_End(USART1 ,StrError);		//接收命令有误，无法解析
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
//****************************************************************************************************
//*函数：void SPI1Rx_Parse(void)	
//*功能：SPI1接收处理函数
//****************************************************************************************************/
void SPI2Rx_Parse(void)
{ //uint8_t i,j,k;
  uint16_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;

	DelayCom(2000);

	SPI2Sta = SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
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



//======================================no  more==========================================//

