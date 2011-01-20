/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Global.h"



//根据长度向串口发送字符串
void Usart_SendString(USART_TypeDef* USARTx , uint8_t *string , uint16_t len)
{	uint8_t *tstr;
	uint16_t iLoop;
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	tstr = string;	
	for (iLoop=0; iLoop<len; iLoop++)
	{
		USARTx->DR = *tstr;
		while(0 ==(USARTx->SR & USART_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
		tstr++;
	}
}
//向串口发送字符串，直至'\0'为止	
//====================================================================================//
void Usart_SendString_End(USART_TypeDef* USARTx , uint8_t *string)
{	uint8_t *tstr;	
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
  
	tstr = string;
	while(*tstr != '\0')
	{
		if(*tstr == '\0'){
			DelayUs(1);
		
		}
		
		USARTx->DR = *tstr;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//等待发送完成标志位
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
		while(0 ==(USARTx->SR & USART_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
		tstr++;	
	}
}

//向串口发送一字节，	
//====================================================================================//
void Usart_SendByte(USART_TypeDef* USARTx , uint8_t byte)
{		
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));		
	USARTx->DR = byte;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//等待发送完成标志位
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
	while(0 ==(USARTx->SR & USART_FLAG_TC));	//等待发送完成标志位
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//清发送完成标志位
}


//****************************************************************************************************
//*功能：Usart1接收处理函数	
//*参数：
//****************************************************************************************************/
void Usart1_Rx_Parse(void)
{
  uint8_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;	

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
uint8_t CmdApply(uint8_t *pCmdPos , uint8_t CmdLen)	//ken:建立命令索引函数
{
	uint8_t	loopi,loopj;
//	CMD_BUF_TypeDef *pRxBuf = NULL;
	if((pCmdBuf->CmdListNum < CMD_NUMLMT)&&(CmdLen <= CMD_BUF_LEN)) {
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

