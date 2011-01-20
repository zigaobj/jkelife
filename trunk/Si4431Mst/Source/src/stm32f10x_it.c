/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Global.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_SoftNSS
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t TimingDelay; // 延时时间，注意定义为全局变量
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
  
  SysTick->VAL   =  (0x00);
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }  
//  TimingDelay_Decrement();
}



/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI0_IRQHandler(void)	//EXTI0线对应的中断，连接TX的24L01的IRQ脚
{ uint8_t TmpSta,i,TmpVal;
//uint8_t StrRXOK[] = "24L01RXOK\r\n";
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)	//SPI1的IRQ脚(TX 24L01)	
  {
    /* Toggle GPIO_LED pin 7 */		//每次按下，B_LED状态(GPB7)改变，亮暗切换
//    GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_7))));

    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);	//清挂起寄存器
	SPI1Sta = SPI1_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
//	if(SPI1Sta == 0){
//		DelayUs(10);	
//	}
	SPI1_IRQ_H;
	
	if(SPI1Sta & TX_DS){			//正常发送接收到ACK后的中断
		SPI1_RW(FLUSH_TX_24L01);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空	
	}
	
	if(SPI1Sta & MAX_RT){				// 判断是否超过重发最大数		
		
		SPI1_RW(FLUSH_TX_24L01);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
		//Usart_SendString_End(USART1 ,TxNoReply);
		//SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	}
	if(SPI1Sta & RX_DR){				// 判断是否接收到数据
	    SPI1NewFlg = 1;
		
		SPI1_CE_L;	//StandBy I模式
		SPI1_Read_Buf(RD_RX_PLOAD_24L01,SPI1_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
//		SPI1_CE_H;	//置高CE，保持接收模式
	  	//必须知道接收数据通道号RX_P_NO
	  	TmpVal = ((SPI1Sta & MASK_RX_P_NO)>>1);	//读取接收数据通道号RX_P_NO 
	  if(!SPI1FullFlag){
		for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
			SPI1_ParseBuf[SPI1index] = SPI1_RxBuf[i];	//将接收缓冲区SPI1_RxBuf数据转移到处理数据缓冲区SPI1_ParseBuf
			if(0x0A == SPI1_ParseBuf[SPI1index] ){		
				if(0x0D == SPI1_ParseBuf[SPI1index-1] ){
					SPI1OkFlag ++;		//收到0x0D 0x0A认为是一条完整的命令		
				}
			}
			SPI1index++;
			if(SPI1index >= SPI1PARSEBUFLEN){
				SPI1FullFlag = 1;	//接收缓冲区满，未来得及处理数据
			}
		}
	  }
		SPI1NewFlg = 0;

	}
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志

  }


}

void EXTI9_5_IRQHandler(void)	//EXTI8线对应的中断，连接RX的24L01的IRQ脚
{	u8 TmpSta,i,TmpVal;
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)	//SPI2的IRQ脚(RX 24L01)	
  {
    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line8);	//清挂起寄存器
		SPI2Sta = SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	//	IRDA_LED_ON();
	//	SPI2_IRQ_H;
	if(SPI2Sta & TX_DS){			//正常发送接收到ACK后的中断
		SPI2_RW(FLUSH_TX_24L01);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空	
	}
	
	if(SPI2Sta & MAX_RT){				// 判断是否超过重发最大数		
		
		SPI2_RW(FLUSH_TX_24L01);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
		//Usart_SendString_End(USART1 ,TxNoReply);
		//SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI2Sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	}	
	
	if(SPI2Sta & RX_DR){				// 判断是否接收到数据
				    
			SPI2NewFlg = 1;
			SPI2RxCnt++;  //计算进入RX中断次数
		SPI2_CE_L;	//StandBy I模式
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,SPI2_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
//		SPI2_CE_H;	//置高CE，保持接收模式
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
//	SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	SPI2_CSN_L;			//NSS拉低，SPI使能
	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
//	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
	SPI2_CSN_H;			//NSS拉高，关闭SPI

	  	//必须知道接收数据通道号RX_P_NO
	  	TmpVal = ((SPI2Sta & MASK_RX_P_NO)>>1);	//读取接收数据通道号RX_P_NO 
	  if(!SPI2FullFlag){
		for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
			SPI2_ParseBuf[SPI2index] = SPI2_RxBuf[i];	//将接收缓冲区SPI1_RxBuf数据转移到处理数据缓冲区SPI1_ParseBuf
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

	}
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志

/*	if(1 == SPI2RxCnt){
		TransferStatus1 = Buffercmp(SPI2_RxBuf, SPI1_TxBuf, BufferSize);
		if(TransferStatus1 == FAILED){
			Usart_SendString_End(USART1 ,RxNotMatch);	//如果发送接收不匹配，发警告到串口1。	
		}
		else{
			Usart_SendString_End(USART1 ,RxMatch);		//如果发送接收匹配，发接收成功到串口1。
		}
	}	*/

//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	

//	SPI2Sta = SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);

//	Usart_SendString(USART1 ,SPI2_RxBuf , BufferSize);	//将收到的数据往串口1发送
//	DelayUs(10);
	/*
	sta=SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	SPI2Sta=sta;
	if(RX_DR){				// 判断是否接收到数据
		SPI2RxCnt++;  //计算进入RX中断次数	
		TmpSta = SPI2_Read(FIFO_STATUS_24L01);
  		SPI2FIFOSta = TmpSta;
		if(TmpSta & 0x02){	//当24L01的RX FIFO满了，才一次过接收数据
			// Toggle GPIO_LED pin 8 		//每次收到完成数据包，RUN_LED状态(GPB8)改变，亮暗切换
  			nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
    		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
			Usart_SendString(USART1 ,SPI2_RxBuf , BufferSize);	//将收到的数据往串口1发送
			SPI2_RW(FLUSH_RX_24L01);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
			SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
		}
		else{
			SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
  		}
	}
	*/
  }	

}



/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  :系统运行的状态转换时钟
  * @param  None
  * @retval : None
  */
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);	//清除 TIMx 的中断待处理位TIM_IT_CC1 
//	GPIO_WriteBit(GPIOC, GPIO_Pin_6,Bit_SET);

//	if(STA_STANDBY == WorkSta1){	//只有从STA_STANDBY模式才能转入
		WorkSta1 = STA_SYNCHRONIZE;	//同步工作状态。
//	}
    /* Pin PC.06 toggling with frequency = 73.24 Hz */
  	 
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));	//翻转管脚电平
  //  capture = TIM_GetCapture1(TIM2);
  //  TIM_SetCompare1(TIM2, capture + CCR1_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);	//收发两个模块，同时进入发送与接收主处理阶段
//	GPIO_WriteBit(GPIOC, GPIO_Pin_7,Bit_SET);
	if(STA_SYNCHRONIZE == WorkSta1){	//只有从STA_SYNCHRONIZE模式才能转入
		WorkSta1 = STA_BROADCAST;	//广播阶段
	}
	
    /* Pin PC.07 toggling with frequency = 109.8 Hz */
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
  //  capture = TIM_GetCapture2(TIM2);
  //  TIM_SetCompare2(TIM2, capture + CCR2_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
		WorkSta2 = STA_DATA ;		//维持心跳普通数据传输阶段	//注释测试SPI1


//	GPIO_WriteBit(GPIOC, GPIO_Pin_8,Bit_SET);
	
    /* Pin PC.08 toggling with frequency = 219.7 Hz */
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8)));
  //  capture = TIM_GetCapture3(TIM2);
  //  TIM_SetCompare3(TIM2, capture + CCR3_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
		

//	GPIO_WriteBit(GPIOC, GPIO_Pin_9,Bit_SET);

//	WorkSta1 = STA_P2P;		//大量数据点对点传输
    /* Pin PC.09 toggling with frequency = 439.4 Hz */
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9)));
  //  capture = TIM_GetCapture4(TIM2);
  //  TIM_SetCompare4(TIM2, capture + CCR4_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//  	GPIO_WriteBit(GPIOC, GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6,Bit_RESET);	//复位管脚
//	RUN_LED_TURN();
	CheckConnect();	//一个周期检查一次从模块组网状态
//	SPI2_Read(EN_AA_24L01);
//	SPI2_Read(EN_RXADDR_24L01);
//	SPI2_Read(FIFO_STATUS_24L01);	
//	SPI2_Read(CONFIG_24L01);
//	SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况	
//	WorkSta = STA_NETCONNECT;	//组网状态必须由上位机控制，例如用户需要接入新的无线控制模块才打开
  
  }


}


//2秒中断一次， 作为系统的整体时基，用于同步网络各模块时基
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){  
//	GPIO_WriteBit(LED_GPIO_PORT, RUN_LED_CN_PIN, (BitAction)((1-GPIO_ReadOutputDataBit(LED_GPIO_PORT, RUN_LED_CN_PIN))));
  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	//清除 TIMx 的中断待处理位TIM_IT_Update 
	GlobalRunTime.Second++;
//	IRDA_LED_TURN();
//	NET_LED_OFF();
//	IRDA_LED_OFF();
	/*
	if(TXSTATUS == Mst24L01Sta){
		SetSPI1_RXMode();	//每隔2秒
  	}
	else{
		SetSPI1_TXMode();	//每隔2秒
	}
	*/
//	SetSPI1_TXMode(MOD2_RXADR);	//2秒作为一个周期，1/4时间用于接收，3/4时间作为发射
	Mst24L01Sta = TXSTATUS;
//	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
//  TIM_ITConfig(TIM6 , TIM_IT_Update ,ENABLE);	//启动TIM6更新中断	
    /* TIM6 enable counter */
//  TIM_Cmd(TIM6, ENABLE);  
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);	//清除 TIMx 的中断待处理位TIM_IT_CC1
//	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
//	SetSPI1_BroadCast();	//2秒作为一个周期，1/4时间用于接收，3/4时间作为发射
//	SetSPI1_RXMode();
	Mst24L01Sta = RXSTATUS;
  }
}

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval : None
  */
void USART1_IRQHandler(void)
{ //uint8_t String_tmp;

//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  if((USART1->SR & USART_FLAG_RXNE) != RESET)
  {
    
    /* Read one byte from the receive data register */
    if(!U1RxFullFlag){
		U1RxBuf[U1RxIndex] = USART_ReceiveData(USART1);
			if(0x0A == U1RxBuf[U1RxIndex] ){		
				if(0x0D == U1RxBuf[U1RxIndex-1] ){
					U1RxCmdFlag ++;		//收到0x0D 0x0A认为是一条完整的命令		
				}
			}
			U1RxIndex++;
			if(U1RxIndex >= U1PARSEBUFLEN){
				U1RxFullFlag = 1;	//接收缓冲区满，未来得及处理数据
			}	
	
	}
//	String_tmp = USART_ReceiveData(USART1);
//	Usart_SendString(USART1 , &String_tmp , 1);
//	USART_ClearITPendingBit(USART1 , USART_IT_TXE);
//	USART_ClearITPendingBit(USART1 , USART_IT_TC);
//    if(RxCounter1 == NbrOfDataToRead1)
//    {
      /* Disable the USART1 Receive interrupt */
//      USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//    }
  }
  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   


//    if(TxCounter1 == NbrOfDataToTransfer1)
//    {
      /* Disable the USART1 Transmit interrupt */
//      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
//    }    
  }
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */  
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
