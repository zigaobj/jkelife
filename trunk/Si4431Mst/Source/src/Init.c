 /* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "platform_config.h"
#include "Global.h"
#include "CmdPrc.h"	
#include "Init.h"
#include "SPICom.h"
#include "Si4431App.h"
#include "GloVar.h"
#include <stdlib.h>


void SysInit_Config(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* Configure the systick */    
  SysTick_Configurations();

  /* SPI configuration ------------------------------------------------------*/
  SPI_Config();

  /* NVIC configuration */
  NVIC_Configuration();

  USART_Config();	//���ڳ�ʼ��

  TIM3_Config();	//ϵͳʱ�ӣ��ṩ10us����С��ʱ��Ԫ

 // TIM2_Config();

  VarInit();	//ϵͳ������״̬��ʼ��

	
}



 void USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

	USART_DeInit(USART1);
	USART_DeInit(USART2);
	USART_DeInit(UART4);
	USART_DeInit(UART5);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART4 Tx (PC.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure USART4 Rx (PC.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure USART5 Tx (PC.12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure USART5 Rx (PD.02) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);
  /* Configure UART4 */
  USART_Init(UART4, &USART_InitStructure);
  /* Configure UART5 */
  USART_Init(UART5, &USART_InitStructure);

  
//	USART_ClearITPendingBit(USART1 , USART_IT_RXNE);
//	USART_ClearITPendingBit(USART1 , USART_IT_TXE);
//	USART_ClearITPendingBit(USART1 , USART_IT_TC);

//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

  /* Enable USART2 Receive and Transmit interrupts */
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);
  /* Enable the USART2 */
  USART_Cmd(USART2, ENABLE);
  /* Enable the USART4 */
  USART_Cmd(UART4, ENABLE);
  /* Enable the USART5 */
  USART_Cmd(UART5, ENABLE);

  /* Enable USART1 Receive and Transmit interrupts */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

//	USART_ClearITPendingBit(USART1 , USART_IT_RXNE);
//	USART_ReceiveData(USART1);
//  USART_ClearITPendingBit(USART1 , USART_IT_TC);
//  USART_ClearFlag(USART1, USART_FLAG_TC);	
}

void VarInit(void)
{	u8 i;	
	WorkStaPre1	= STA_SLEEP;
	WorkSta1		= STA_SLEEP;
	WorkSta2		= STA_SLEEP;
	WorkStaPre2 = STA_SLEEP;	
//	GlobalRunTime = 0;

	sta = 0;   //״̬��־
	TXItSta1 = 0;
	TXItSta2 = 0;
	RXItSta1 = 0;
	RXItSta2 = 0;
	SPI2RxCnt = 0;

	for(i = 0;i < SPI1PARSEBUFLEN;i++){
		SPI1_ParseBuf[i] = 0;	
	}
	SPI1index = 0;
	SPI1Pindex = 0;

	pCmdSpiTxBuf =&CmdSpiTxBuf;	//ָ������������
	pCmdSpiRxBuf =&CmdSpiRxBuf;	//ָ������������

//	pRxAdr_Tab = &RxAdr_Tab;	
	for(i = 0;i < CMDSPI_RXLIST_LMT;i++){
		pCmdSpiTxBuf->CmdListFlag[i] = 0;
		pCmdSpiRxBuf->CmdListFlag[i] = 0;
	}
	pCmdSpiTxBuf->pCmd_Prc_Current = 	pCmdSpiRxBuf->Cmd_Body;
	pCmdSpiTxBuf->pCmd_Body_Current = pCmdSpiRxBuf->Cmd_Body;

	pCmdSpiTxBuf->CmdListNum = 0;
	pCmdSpiRxBuf->CmdListNum = 0;
	pCmdSpiTxBuf->CmdCurrentList = 0;
	pCmdSpiRxBuf->CmdCurrentList = 0;

	pJKNetAdr_Tab = &JKNetAdr_Tab;
	pJKNetAdr_Tab->JKNetAdrTabCnt = 0;
//	pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0;	//��pRxAdrTabCntָ��յĽ��յ�ַ���ռ䡣
	
	for(i = 0; i < JKNETADRTABLEN; i++){
		pJKNetAdr_Tab->TabFlag[i] = 0;
		pJKNetAdr_Tab->JKNetNumTab[i] = 0;
	}	
	
	pReplyBuf = &ReplyBuf;	//��������Ӧ��������
//����	pRxAdr_Tab->TabFlag[0]	=0x10;
/*
	for(i = 0;i < SI4431_ADR_WIDTH;i++){
		pRxAdr_Tab->RxAdrTab0[i] = i;
		pRxAdr_Tab->RxAdrTab1[i] = i;
		pRxAdr_Tab->RxAdrTab2[i] = i;
		pRxAdr_Tab->RxAdrTab3[i] = i;
		pRxAdr_Tab->RxAdrTab4[i] = i;
		pRxAdr_Tab->RxAdrTab5[i] = i;	
	}
*/


	srand((unsigned) RX_ADDRESS_Si4431[3]);	//������������Ӻ����������ڱ�ֵ�ĵط����ã���������
}


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval : None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */	//����STM32F103C8��˵ʹ��16���ɱ�̵����ȵȼ�(ʹ����4λ�ж����ȼ�)
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�������ȼ����飬��ռ���ȼ�2λ4���������ȼ�2λ4��
  
  /* Enable the EXTI15_10 Interrupt */						//STM32F103C8��0-15��16���ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//�ⲿ�ж��� 9-5 �ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�1��ʵ���ǵ�4�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//�ⲿ�ж��� 0 �ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�0��ʵ���ǵ�5�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

   /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//USART0�ж������ȼ�����USART1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM3_IRQn Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//ʵ���ǵ�8��	  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);

}

//--------------------------------SPI configuration ----------------------------------
//SPI1�ӷ����24L01��SPI2�ӽ��յ�24L01����Ϊ���豸
void SPI_Config(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
  SPI_Cmd(SPI1, DISABLE);             //�����Ƚ���,���ܸı�MODE
	SPI_Cmd(SPI2, DISABLE);             //�����Ƚ���,���ܸı�MODE

  /* 1st phase: SPIy Master and SPIz Slave */
  /* SPI1 Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//����Ϊ�� SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//SPI���ͽ��� 8 λ֡�ṹ 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;			//ʱ�����յ� 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//���ݲ����ڵ�һ��ʱ����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//NSS ������ܽŹ��� 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//SPIʱ��Ϊ36/32 = 1.125MHZ;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ���� MSB λ��ʼ 
  SPI_InitStructure.SPI_CRCPolynomial = 7;	//���� CRCֵ����Ķ���ʽ
  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  /* Enable SPIz Periph clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  SPI_Init(SPI1, &SPI_InitStructure);
  /* SPIz Config -------------------------------------------------------------*/
//  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI1 NSS output for master mode */
//  SPI_SSOutputCmd(SPI1, DISABLE);
  /* Enable SPI2 NSS output for master mode */
//  SPI_SSOutputCmd(SPI2, DISABLE);
//	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);

  /* Enable SPIy */
  SPI_Cmd(SPI1, ENABLE);
  /* Enable SPIz */
  SPI_Cmd(SPI2, ENABLE);

	

}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK/2 */
    RCC_PCLK2Config(RCC_HCLK_Div2);	//��ΪSPI1��SPI2�ֱ���APB2��APB1�У�����ʱ�ӷ�ƵҪһ�£�����36MHZ 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);	//APB1��Ƶϵ��������1��Ƶ��X2֮����͵�TIMxCLK��������TIMxCLK = 36MHZ

	  /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }

/* Enable peripheral clocks --------------------------------------------------*/
  /* Enable USART1, GPIOA clock and GPIOB clock for SPI1 and SPI2 */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO , ENABLE);
  
  /* Enable the TIM6 clock */
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2 , ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI1_PIN_SCK | SPI1_PIN_MISO | SPI1_PIN_MOSI;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);

  /* Configure SPI2 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI2_PIN_SCK | SPI2_PIN_MISO | SPI2_PIN_MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SPI1_PIN_CSN | SPI1_PIN_CE ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI1_CTL_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SPI2_PIN_CSN | SPI2_PIN_CE ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI2_CTL_GPIO, &GPIO_InitStructure);

	SPI1_CE_L;
	SPI2_CE_L;

//	SPI1_PWR_OFF();
//	SPI2_PWR_OFF();

	GPIO_InitStructure.GPIO_Pin = SPI1_PIN_PWR ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(SPI1_CTL_GPIO, &GPIO_InitStructure);

	DelayCom(5000);

	GPIO_InitStructure.GPIO_Pin = SPI2_PIN_PWR ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(SPI2_CTL_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SPI1_PIN_IRQ | SPI2_PIN_IRQ ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;	// GPIO_Mode_IN_FLOATING
  GPIO_Init(SPI1_CTL_GPIO, &GPIO_InitStructure);
/*  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
*/
#ifdef SOUTHBOARD
  /* GPIOB Configuration:Pin6, 7, 8 and  as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = PWR_LED_CN_PIN | B_LED_CN_PIN | RUN_LED_CN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
#endif 

#ifdef JKVER1BOARD
  GPIO_InitStructure.GPIO_Pin = RUN_LED_PIN | NET_LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LEDS_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = IRDA_LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(IRLED_PORT, &GPIO_InitStructure);

	RUN_LED_OFF();
	NET_LED_OFF();
	IRDA_LED_OFF();


  GPIO_InitStructure.GPIO_Pin = Q1_PIN | Q2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(Q_PORT, &GPIO_InitStructure);
	Q1_PIN_OFF();
	Q2_PIN_OFF();

#endif 
 

  /* Connect Key Button EXTI Line to Key Button GPIO Pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0 );	//��IOC_0��ΪEXTI ��.
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8 );	//��IOC_8��ΪEXTI ��.

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line8;	//
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//���� EXTI��·Ϊ�ж�����
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//����������·�½���Ϊ�ж�����
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	//��ʼ������EXTI��

  EXTI->PR = 0xFFFFF;	//����Ĵ������
}

//��Сʱ���������ģ��һ�£�������������ϵ������ϵͳʱ��64us����ϵͳ��С��ʱ��λ0.064ms
void TIM3_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//  TIM_OCInitTypeDef  TIM_OCInitStructure;
  /* Time Base configuration */
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	//�� TIM_TimeBaseInitStruct �е�ÿһ��������ȱʡֵ���� 

  TIM_DeInit(TIM3);
  TIM_TimeBaseStructure.TIM_Period = 0x3D09;		//1000ms��ʱ          
  TIM_TimeBaseStructure.TIM_Prescaler = 0x1200;		//TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 72/4608 = 0.015625MHz 64US      
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	////���ϼ���ģʽ  
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
/* 
  // Output Compare Timing Mode configuration: Channel1 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;	//TIM ����Ƚ�����ģʽ	//ǿ��OC1REFΪ�� 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;	//	
  TIM_OCInitStructure.TIM_Pulse = 0x0BB8;	//װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//TIM ����Ƚϼ��Ը� 

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//TIMx ��CCR1 �ϵ�Ԥװ�ؼĴ���ʹ�� 
*/

//  TIM_PrescalerConfig (TIM4 , 4 ,TIM_PSCReloadMode_Immediate);	//

  //���ж� 
  TIM_ClearFlag(TIM3, TIM_IT_Update );  //	  | TIM_IT_CC1
  TIM_ITConfig(TIM3 , TIM_IT_Update ,ENABLE);	//����TIM3�����ж�	| TIM_IT_CC1 

//  TIM_ClearITPendingBit(TIM6 , TIM_IT_Update); 	//��� TIM1���жϴ�����λTIM_IT_Update	
    /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

void TIM2_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Selects the internal clock for TIM2 */ 
//  TIM_InternalClockConfig(TIM2);	//���� TIM2 �ڲ�ʱ�� 
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = TIM2_PERIOD;			//�ӽ�2000ms��ʱ
  TIM_TimeBaseStructure.TIM_Prescaler = 0x1200;		//TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 72/4608 = 0.015625MHz 64US
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration */	//���� TIMx Ԥ��Ƶ 
//  TIM_PrescalerConfig(TIM2, 4, TIM_PSCReloadMode_Update);
//  TIM_PrescalerConfig(TIM2, 4, TIM_PSCReloadMode_Immediate);	//TIM Ԥ��Ƶֵ��ʱװ��

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;	//TIM ����Ƚ�����ģʽ	//ǿ��OC1REFΪ�� 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;	//	
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1;	//װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//TIM ����Ƚϼ��Ը� 

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx ��CCR1 �ϵ�Ԥװ�ؼĴ���ʧ�� 

  /* Output Compare Timing Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR2;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx ��CCR2 �ϵ�Ԥװ�ؼĴ���ʧ�� 

  /* Output Compare Timing Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR3;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx ��CCR3 �ϵ�Ԥװ�ؼĴ���ʧ�� 

  /* Output Compare Timing Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR4;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx ��CCR4 �ϵ�Ԥװ�ؼĴ���ʧ�� 

  //���ж� 
  TIM_ClearFlag(TIM2, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);	//ʹ��TIM�Ƚ�1-4�ж�
  //TIM_IT_Update |
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);	
}



/*******************************************************************************
* Function Name  : SysTick_Configurations
* Description    : Configure a SysTick Base time to 1 us.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configurations(void)
{
   SysTick->VAL  =0x00;	//SysTick��װ����ֵ�Ĵ�������
   SysTick->CTRL =0x05;	// HCLK��ΪSystickʱ�ӣ�ʹ��SysTick����SysTick������0ʱ������ SysTick �쳣����
   SysTick->LOAD = 72; 	//��װ�ؼĴ��������ϵͳʱ��Ϊ72MHz��ÿ1us�ж�һ��
}


