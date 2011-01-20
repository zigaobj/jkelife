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
extern __IO uint32_t TimingDelay; // ��ʱʱ�䣬ע�ⶨ��Ϊȫ�ֱ���
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
void EXTI0_IRQHandler(void)	//EXTI0�߶�Ӧ���жϣ�����TX��24L01��IRQ��
{ uint8_t TmpSta,i,TmpVal;
//uint8_t StrRXOK[] = "24L01RXOK\r\n";
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)	//SPI1��IRQ��(TX 24L01)	
  {
    /* Toggle GPIO_LED pin 7 */		//ÿ�ΰ��£�B_LED״̬(GPB7)�ı䣬�����л�
//    GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_7))));

    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);	//�����Ĵ���
	SPI1Sta = SPI1_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
//	if(SPI1Sta == 0){
//		DelayUs(10);	
//	}
	SPI1_IRQ_H;
	
	if(SPI1Sta & TX_DS){			//�������ͽ��յ�ACK����ж�
		SPI1_RW(FLUSH_TX_24L01);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����	
	}
	
	if(SPI1Sta & MAX_RT){				// �ж��Ƿ񳬹��ط������		
		
		SPI1_RW(FLUSH_TX_24L01);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
		//Usart_SendString_End(USART1 ,TxNoReply);
		//SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	}
	if(SPI1Sta & RX_DR){				// �ж��Ƿ���յ�����
	    SPI1NewFlg = 1;
		
		SPI1_CE_L;	//StandBy Iģʽ
		SPI1_Read_Buf(RD_RX_PLOAD_24L01,SPI1_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
//		SPI1_CE_H;	//�ø�CE�����ֽ���ģʽ
	  	//����֪����������ͨ����RX_P_NO
	  	TmpVal = ((SPI1Sta & MASK_RX_P_NO)>>1);	//��ȡ��������ͨ����RX_P_NO 
	  if(!SPI1FullFlag){
		for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
			SPI1_ParseBuf[SPI1index] = SPI1_RxBuf[i];	//�����ջ�����SPI1_RxBuf����ת�Ƶ��������ݻ�����SPI1_ParseBuf
			if(0x0A == SPI1_ParseBuf[SPI1index] ){		
				if(0x0D == SPI1_ParseBuf[SPI1index-1] ){
					SPI1OkFlag ++;		//�յ�0x0D 0x0A��Ϊ��һ������������		
				}
			}
			SPI1index++;
			if(SPI1index >= SPI1PARSEBUFLEN){
				SPI1FullFlag = 1;	//���ջ���������δ���ü���������
			}
		}
	  }
		SPI1NewFlg = 0;

	}
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־

  }


}

void EXTI9_5_IRQHandler(void)	//EXTI8�߶�Ӧ���жϣ�����RX��24L01��IRQ��
{	u8 TmpSta,i,TmpVal;
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)	//SPI2��IRQ��(RX 24L01)	
  {
    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line8);	//�����Ĵ���
		SPI2Sta = SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	//	IRDA_LED_ON();
	//	SPI2_IRQ_H;
	if(SPI2Sta & TX_DS){			//�������ͽ��յ�ACK����ж�
		SPI2_RW(FLUSH_TX_24L01);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����	
	}
	
	if(SPI2Sta & MAX_RT){				// �ж��Ƿ񳬹��ط������		
		
		SPI2_RW(FLUSH_TX_24L01);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
		//Usart_SendString_End(USART1 ,TxNoReply);
		//SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI2Sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	}	
	
	if(SPI2Sta & RX_DR){				// �ж��Ƿ���յ�����
				    
			SPI2NewFlg = 1;
			SPI2RxCnt++;  //�������RX�жϴ���
		SPI2_CE_L;	//StandBy Iģʽ
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,SPI2_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
//		SPI2_CE_H;	//�ø�CE�����ֽ���ģʽ
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
//	SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
	SPI2_RW_Reg(FLUSH_RX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
//	SPI2_RW_Reg(FLUSH_TX_24L01 , 0);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI

	  	//����֪����������ͨ����RX_P_NO
	  	TmpVal = ((SPI2Sta & MASK_RX_P_NO)>>1);	//��ȡ��������ͨ����RX_P_NO 
	  if(!SPI2FullFlag){
		for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
			SPI2_ParseBuf[SPI2index] = SPI2_RxBuf[i];	//�����ջ�����SPI1_RxBuf����ת�Ƶ��������ݻ�����SPI1_ParseBuf
			if(0x0A == SPI2_ParseBuf[SPI2index] ){		
				if(0x0D == SPI2_ParseBuf[SPI2index-1] ){
					SPI2OkFlag ++;		//�յ�0x0D 0x0A��Ϊ��һ������������		
				}
			}
			SPI2index++;
			if(SPI2index >= SPI2PARSEBUFLEN){
				SPI2FullFlag = 1;	//���ջ���������δ���ü���������
			}
		}
	  }
		SPI2NewFlg = 0;

	}
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־

/*	if(1 == SPI2RxCnt){
		TransferStatus1 = Buffercmp(SPI2_RxBuf, SPI1_TxBuf, BufferSize);
		if(TransferStatus1 == FAILED){
			Usart_SendString_End(USART1 ,RxNotMatch);	//������ͽ��ղ�ƥ�䣬�����浽����1��	
		}
		else{
			Usart_SendString_End(USART1 ,RxMatch);		//������ͽ���ƥ�䣬�����ճɹ�������1��
		}
	}	*/

//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
	

//	SPI2Sta = SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
//	SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);

//	Usart_SendString(USART1 ,SPI2_RxBuf , BufferSize);	//���յ�������������1����
//	DelayUs(10);
	/*
	sta=SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	SPI2Sta=sta;
	if(RX_DR){				// �ж��Ƿ���յ�����
		SPI2RxCnt++;  //�������RX�жϴ���	
		TmpSta = SPI2_Read(FIFO_STATUS_24L01);
  		SPI2FIFOSta = TmpSta;
		if(TmpSta & 0x02){	//��24L01��RX FIFO���ˣ���һ�ι���������
			// Toggle GPIO_LED pin 8 		//ÿ���յ�������ݰ���RUN_LED״̬(GPB8)�ı䣬�����л�
  			nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
    		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
			Usart_SendString(USART1 ,SPI2_RxBuf , BufferSize);	//���յ�������������1����
			SPI2_RW(FLUSH_RX_24L01);	//��֪���Ƿ�Ҫ���FIFO�����Ƕ�ȡFIFOֵ���Զ����
			SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);
		}
		else{
			SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
  		}
	}
	*/
  }	

}



/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  :ϵͳ���е�״̬ת��ʱ��
  * @param  None
  * @retval : None
  */
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);	//��� TIMx ���жϴ�����λTIM_IT_CC1 
//	GPIO_WriteBit(GPIOC, GPIO_Pin_6,Bit_SET);

//	if(STA_STANDBY == WorkSta1){	//ֻ�д�STA_STANDBYģʽ����ת��
		WorkSta1 = STA_SYNCHRONIZE;	//ͬ������״̬��
//	}
    /* Pin PC.06 toggling with frequency = 73.24 Hz */
  	 
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));	//��ת�ܽŵ�ƽ
  //  capture = TIM_GetCapture1(TIM2);
  //  TIM_SetCompare1(TIM2, capture + CCR1_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);	//�շ�����ģ�飬ͬʱ���뷢�������������׶�
//	GPIO_WriteBit(GPIOC, GPIO_Pin_7,Bit_SET);
	if(STA_SYNCHRONIZE == WorkSta1){	//ֻ�д�STA_SYNCHRONIZEģʽ����ת��
		WorkSta1 = STA_BROADCAST;	//�㲥�׶�
	}
	
    /* Pin PC.07 toggling with frequency = 109.8 Hz */
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
  //  capture = TIM_GetCapture2(TIM2);
  //  TIM_SetCompare2(TIM2, capture + CCR2_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
		WorkSta2 = STA_DATA ;		//ά��������ͨ���ݴ���׶�	//ע�Ͳ���SPI1


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

//	WorkSta1 = STA_P2P;		//�������ݵ�Ե㴫��
    /* Pin PC.09 toggling with frequency = 439.4 Hz */
  //  GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9)));
  //  capture = TIM_GetCapture4(TIM2);
  //  TIM_SetCompare4(TIM2, capture + CCR4_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//  	GPIO_WriteBit(GPIOC, GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6,Bit_RESET);	//��λ�ܽ�
//	RUN_LED_TURN();
	CheckConnect();	//һ�����ڼ��һ�δ�ģ������״̬
//	SPI2_Read(EN_AA_24L01);
//	SPI2_Read(EN_RXADDR_24L01);
//	SPI2_Read(FIFO_STATUS_24L01);	
//	SPI2_Read(CONFIG_24L01);
//	SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��	
//	WorkSta = STA_NETCONNECT;	//����״̬��������λ�����ƣ������û���Ҫ�����µ����߿���ģ��Ŵ�
  
  }


}


//2���ж�һ�Σ� ��Ϊϵͳ������ʱ��������ͬ�������ģ��ʱ��
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){  
//	GPIO_WriteBit(LED_GPIO_PORT, RUN_LED_CN_PIN, (BitAction)((1-GPIO_ReadOutputDataBit(LED_GPIO_PORT, RUN_LED_CN_PIN))));
  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	//��� TIMx ���жϴ�����λTIM_IT_Update 
	GlobalRunTime.Second++;
//	IRDA_LED_TURN();
//	NET_LED_OFF();
//	IRDA_LED_OFF();
	/*
	if(TXSTATUS == Mst24L01Sta){
		SetSPI1_RXMode();	//ÿ��2��
  	}
	else{
		SetSPI1_TXMode();	//ÿ��2��
	}
	*/
//	SetSPI1_TXMode(MOD2_RXADR);	//2����Ϊһ�����ڣ�1/4ʱ�����ڽ��գ�3/4ʱ����Ϊ����
	Mst24L01Sta = TXSTATUS;
//	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
//  TIM_ITConfig(TIM6 , TIM_IT_Update ,ENABLE);	//����TIM6�����ж�	
    /* TIM6 enable counter */
//  TIM_Cmd(TIM6, ENABLE);  
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);	//��� TIMx ���жϴ�����λTIM_IT_CC1
//	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
//	SetSPI1_BroadCast();	//2����Ϊһ�����ڣ�1/4ʱ�����ڽ��գ�3/4ʱ����Ϊ����
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
					U1RxCmdFlag ++;		//�յ�0x0D 0x0A��Ϊ��һ������������		
				}
			}
			U1RxIndex++;
			if(U1RxIndex >= U1PARSEBUFLEN){
				U1RxFullFlag = 1;	//���ջ���������δ���ü���������
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
