/* Includes ------------------------------------------------------------------*/
#include "Global.h"


@near u8 U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
//@near u8 U2RxCmdFlag;
//u8 U1NewFlag;		//SPI1收到新数据
//u8 U2NewFlag;		//SPI2收到新数据
           
@near u8 U1RxFullFlag;
//@near u8 U2RxFullFlag;
//extern u8 pdata txIndex;
@near u8 U1RxIndex;
@near u8 U1RxPindex;
//@near u8 U2RxIndex;		 
//@near u8 U2RxPindex;        
@near u8 U1ParseBuf[USARTBUFLEN];
//@near u8 U2ParseBuf[USARTBUFLEN];

@near u8 U1TxBuf[USARTBUFLEN];
//@near u8 U2TxBuf[USARTBUFLEN];
@near u8 U1RxBuf[USARTBUFLEN];
//@near u8 U2RxBuf[USARTBUFLEN];

//__IO u8 Usart1TxIndex;
//__IO u8 Usart2TxIndex;
//__IO u8 Usart1RxIndex; 
//__IO u8 Usart2RxIndex;

@near CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//命令数据体
@near CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
@near CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

//根据长度向串口发送字符串
void Uart1_SendString(u8 *string , u16 len)
{	u8 *tstr;
	u16 iLoop;
	tstr = string;	
	for (iLoop=0; iLoop<len; iLoop++)
	{
		UART1->DR = *tstr;
		while(0 ==(UART1->SR & UART1_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
		tstr++;
	}
}
//向串口发送字符串，直至'\0'为止	
//====================================================================================//
void Uart1_SendString_End(u8 *string)
{	u8 *tstr;	
	tstr = string;
	while(*tstr != '\0')
	{
		if(*tstr == '\0'){
			Delay(1);
		}
		UART1->DR = *tstr;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//等待发送完成标志位
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
		while(0 ==(UART1->SR & UART1_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
		tstr++;	
	}
}

//向串口发送一字节，	
//====================================================================================//
void Uart1_SendByte(u8 byte)
{			
	UART1->DR = byte;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//等待发送完成标志位
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
	while(0 ==(UART1->SR & UART1_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
}


//****************************************************************************************************
//*功能：Usart1接收处理函数	
//*参数：
//****************************************************************************************************/
void Usart1_Rx_Parse(void)
{
  u8 LoopStart,LoopEnd,Loopi;
  u16 comnum;	

	if(0 != U1RxCmdFlag ){								
		for(LoopStart = U1RxPindex; LoopStart < U1RxIndex; LoopStart++){
			if(U1RxBuf[LoopStart] == '#'){//找到命令头了	
				for(LoopEnd = LoopStart; LoopEnd < U1RxIndex; LoopEnd++){	//找结尾
					if(U1RxBuf[LoopEnd]=='\n'){//找到命令头了
						U1RxCmdFlag--;	//每处理一条命令，接收命令计数器自减
						U1RxPindex = LoopEnd + 1;
					break;
					}
				}
				comnum = Hash(U1RxBuf+LoopStart+1 , UCMDHASHLEN);	//计算命令Hash头
				switch (comnum){	//命令散转
					
					case (UCMD_NETCNT):	//上位机发送的组网命令，接收从模块地址  "#NETCNT\r\n";
						WorkSta1 = STA_NETCONNECT;
					break;
					case (UCMD_PSWCTL):	//上位机的开关控制命令	"#PSWCTL,00000,0,0\r\n";
						CmdApply(U1RxBuf + LoopStart ,LoopEnd - LoopStart);		//将命令存到待处理缓冲区		
					break;
					
					default:
					//	Usart_SendString_End(USART1 ,StrError);		//接收命令有误，无法解析
					break;
							
				}
				
			//清空缓冲区
			if((0 == U1RxCmdFlag)||(U1RxIndex >= U1PARSEBUFLEN))
			for (Loopi = 0; Loopi < U1PARSEBUFLEN; Loopi++){
	 			U1RxBuf[Loopi] = 0;	
			}
	  		U1RxIndex   = 0;
			U1RxPindex = 0;
			U1RxFullFlag = 0;
		//	U0Pindex  = 0;		
			}
		} 
	//	if(0 != SPI1OkFlag){	
	//		SPI1OkFlag--;	
	//	}
	}

}

/*********************ken********************************** 
*   函数说明： 建立命令索引函数                                
*   输入：  Uint16 *pCmdPos 为获得所建立的当前串口接收的命令对应的索引号
*                  
*   输出：  命令索引建立成功，函数名返回所建立的命令首地址，返回NULL表示建立不成功                            
*   调用函数：void                                       
***********************************************************/ 
u8 CmdApply(u8 *pCmdPos , u8 CmdLen)	//ken:建立命令索引函数
{
	u8	loopi,loopj;
//	CMD_BUF_TypeDef *pRxBuf = NULL;
	if((pCmdBuf->CmdListNum < CMD_NUMLMT)&&(CmdLen < CMD_BUF_LEN)) {
		// 循环列表 寻找空Buffer CmdIndex最终指向空的buffer
		for(loopi = 0 ; loopi < CMD_NUMLMT ;loopi++){	//寻找空的命令处理空间
			if(0 == pCmdBuf->CmdListFlag[loopi]){
		 		pCmdBuf->CmdListFlag[loopi] = 0x10;		//找到空的命令处理空间
				pCmdBuf->CmdListNum++;
				break;
			}			
		}

		pCmdBuf->pCmd_Body = & (Cmd_Body[loopi]);	//指向空的从模块地址空间

		
		for(loopj = 0 ; loopj < CmdLen ; loopj++){
			pCmdBuf->pCmd_Body->all[loopj] = * (pCmdPos + loopj);	//将新接收到的命令保存到空的接收命令空间中
		}
		
		return 1;
	}
	else{
		return 0;
	}
//	return pRxBuf;		//ken:返回所建立的命令首地址
}



//====================================================================================//

