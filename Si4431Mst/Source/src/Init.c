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

  USART_Config();	//串口初始化

  TIM3_Config();	//系统时钟，提供10us的最小计时单元

 // TIM2_Config();

  VarInit();	//系统变量，状态初始化

	
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

	sta = 0;   //状态标志
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

	pCmdSpiTxBuf =&CmdSpiTxBuf;	//指向命理处理缓冲区
	pCmdSpiRxBuf =&CmdSpiRxBuf;	//指向命理处理缓冲区

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
//	pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0;	//将pRxAdrTabCnt指向空的接收地址表格空间。
	
	for(i = 0; i < JKNETADRTABLEN; i++){
		pJKNetAdr_Tab->TabFlag[i] = 0;
		pJKNetAdr_Tab->JKNetNumTab[i] = 0;
	}	
	
	pReplyBuf = &ReplyBuf;	//接收命令应答处理缓冲区
//测试	pRxAdr_Tab->TabFlag[0]	=0x10;
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


	srand((unsigned) RX_ADDRESS_Si4431[3]);	//随机函数的种子函数，可以在变值的地方调用，提高随机性
}


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval : None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */	//对于STM32F103C8来说使用16个可编程的优先等级(使用了4位中断优先级)
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置优先级分组，先占优先级2位4级，从优先级2位4级
  
  /* Enable the EXTI15_10 Interrupt */						//STM32F103C8有0-15共16个外部中断
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//外部中断线 9-5 中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//先占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//从优先级1，实际是第4级优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//外部中断线 0 中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//先占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//从优先级0，实际是第5级优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

   /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//USART0中断子优先级高于USART1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM3_IRQn Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//实际是第8级	  
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
//SPI1接发射的24L01，SPI2接接收的24L01，都为主设备
void SPI_Config(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
  SPI_Cmd(SPI1, DISABLE);             //必须先禁能,才能改变MODE
	SPI_Cmd(SPI2, DISABLE);             //必须先禁能,才能改变MODE

  /* 1st phase: SPIy Master and SPIz Slave */
  /* SPI1 Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//设置为主 SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//SPI发送接收 8 位帧结构 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;			//时钟悬空低 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//数据捕获于第一个时钟沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//NSS 由软件管脚管理 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//SPI时钟为36/32 = 1.125MHZ;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//数据传输从 MSB 位开始 
  SPI_InitStructure.SPI_CRCPolynomial = 7;	//用于 CRC值计算的多项式
  

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
    RCC_PCLK2Config(RCC_HCLK_Div2);	//因为SPI1与SPI2分别在APB2，APB1中，所以时钟分频要一致，定在36MHZ 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);	//APB1分频系数不等于1，频率X2之后才送到TIMxCLK，所以是TIMxCLK = 36MHZ

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
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0 );	//将IOC_0设为EXTI 线.
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8 );	//将IOC_8设为EXTI 线.

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line8;	//
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//设置 EXTI线路为中断请求
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//设置输入线路下降沿为中断请求
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	//初始化配置EXTI线

  EXTI->PR = 0xFFFFF;	//挂起寄存器清空
}

//最小时基必须与从模块一致，或整数倍数关系，产生系统时基64us，本系统最小计时单位0.064ms
void TIM3_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//  TIM_OCInitTypeDef  TIM_OCInitStructure;
  /* Time Base configuration */
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	//把 TIM_TimeBaseInitStruct 中的每一个参数按缺省值填入 

  TIM_DeInit(TIM3);
  TIM_TimeBaseStructure.TIM_Period = 0x3D09;		//1000ms定时          
  TIM_TimeBaseStructure.TIM_Prescaler = 0x1200;		//TIMx 时钟频率除数的预分频值 72/4608 = 0.015625MHz 64US      
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	////向上计数模式  
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
/* 
  // Output Compare Timing Mode configuration: Channel1 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;	//TIM 输出比较主动模式	//强制OC1REF为高 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;	//	
  TIM_OCInitStructure.TIM_Pulse = 0x0BB8;	//装入捕获比较寄存器的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//TIM 输出比较极性高 

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//TIMx 在CCR1 上的预装载寄存器使能 
*/

//  TIM_PrescalerConfig (TIM4 , 4 ,TIM_PSCReloadMode_Immediate);	//

  //清中断 
  TIM_ClearFlag(TIM3, TIM_IT_Update );  //	  | TIM_IT_CC1
  TIM_ITConfig(TIM3 , TIM_IT_Update ,ENABLE);	//启动TIM3更新中断	| TIM_IT_CC1 

//  TIM_ClearITPendingBit(TIM6 , TIM_IT_Update); 	//清除 TIM1的中断待处理位TIM_IT_Update	
    /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

void TIM2_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Selects the internal clock for TIM2 */ 
//  TIM_InternalClockConfig(TIM2);	//设置 TIM2 内部时钟 
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = TIM2_PERIOD;			//接近2000ms定时
  TIM_TimeBaseStructure.TIM_Prescaler = 0x1200;		//TIMx 时钟频率除数的预分频值 72/4608 = 0.015625MHz 64US
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数模式

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration */	//设置 TIMx 预分频 
//  TIM_PrescalerConfig(TIM2, 4, TIM_PSCReloadMode_Update);
//  TIM_PrescalerConfig(TIM2, 4, TIM_PSCReloadMode_Immediate);	//TIM 预分频值即时装入

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;	//TIM 输出比较主动模式	//强制OC1REF为高 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;	//	
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1;	//装入捕获比较寄存器的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//TIM 输出比较极性高 

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx 在CCR1 上的预装载寄存器失能 

  /* Output Compare Timing Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR2;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx 在CCR2 上的预装载寄存器失能 

  /* Output Compare Timing Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR3;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx 在CCR3 上的预装载寄存器失能 

  /* Output Compare Timing Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR4;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);	//TIMx 在CCR4 上的预装载寄存器失能 

  //清中断 
  TIM_ClearFlag(TIM2, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);	//使能TIM比较1-4中断
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
   SysTick->VAL  =0x00;	//SysTick重装载数值寄存器清零
   SysTick->CTRL =0x05;	// HCLK作为Systick时钟，使能SysTick，但SysTick倒数到0时不产生 SysTick 异常请求
   SysTick->LOAD = 72; 	//重装载寄存器，如果系统时钟为72MHz，每1us中断一次
}


