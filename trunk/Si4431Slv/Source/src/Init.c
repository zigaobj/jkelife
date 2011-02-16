 /* Includes ------------------------------------------------------------------*/
#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"
#include "Init.h"
#include "SPICom.h"
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
  CLK_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* Configure the systick */    
//  SysTick_Configurations();

  /* SPI configuration ------------------------------------------------------*/
	SPI_Config();

  /* ITC configuration */
  ITC_Configuration();

  USART_Config();	//���ڳ�ʼ��

  TIM3_Config();	//ϵͳʱ�ӣ��ṩ10us����С��ʱ��Ԫ

	Delay(100);
  TIM2_Config();

  VarInit();	//ϵͳ������״̬��ʼ��

	
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void CLK_Configuration(void)
{
  CLK_DeInit();
	
	/*High speed internal clock prescaler: 1*/
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, DISABLE);	//ѡ���ڲ�����ʱ��
//	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, DISABLE);	//ѡ���ڲ�����ʱ��
	
	CLK_HSICmd(ENABLE);	//ʹ���ڲ�����ʱ��
	
	CLK_PeripheralClockConfig( CLK_PERIPHERAL_UART1 , ENABLE);	//��UARTʱ��
	CLK_PeripheralClockConfig( CLK_PERIPHERAL_SPI, ENABLE);
	CLK_PeripheralClockConfig( CLK_PERIPHERAL_TIMER2, ENABLE);
	CLK_PeripheralClockConfig( CLK_PERIPHERAL_TIMER3 , ENABLE);


}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{

  /* Initialize I/Os in Output Mode */
  GPIO_Init(LEDS_PORT, (LED0_PIN | Q1_PIN | Q2_PIN), GPIO_MODE_OUT_PP_LOW_FAST);		//�������
	GPIO_Init(SPI1_PIN_GPIO, (SPI1_PIN_CSN | SPI1_PIN_CE ), GPIO_MODE_OUT_PP_HIGH_FAST);		//�������
	GPIO_Init(SPI1_CTL_GPIO, SPI1_PIN_PWR , GPIO_MODE_OUT_PP_HIGH_FAST);		//�������
	
//	GPIO_Init(SPI1_PIN_GPIO, (SPI1_PIN_SCK | SPI1_PIN_MOSI | SPI1_PIN_MISO), GPIO_MODE_OUT_PP_HIGH_FAST);		//�������
	// Initialize I/O in Input Mode with Interrupt for SPI1_PIN_IRQ
	GPIO_Init(SPI1_CTL_GPIO , SPI1_PIN_IRQ , GPIO_MODE_IN_FL_IT );
	
  /* Initialize the Interrupt sensitivity */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);	//����������·�½���Ϊ�ж�����
//  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);	
	SPI1_PWR_OFF();	//�ϵ�����24L01ģ��
}


 void USART_Config(void)
{
	/* Deinitializes the UART1 and UART3 peripheral */
	UART1_DeInit();

    /* Configure the UART1 */
  UART1_Init((u32)15200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /* Enable the UART1 */
  UART1_Cmd(ENABLE);
  /* Enable the USART2 */
//  USART_Cmd(USART2, ENABLE);

  /* Enable UART1 Receive and Transmit interrupts */
  UART1_ITConfig(UART1_IT_RXNE, ENABLE);

//	USART_ClearITPendingBit(USART1 , USART_IT_RXNE);
//	USART_ReceiveData(USART1);
//  USART_ClearITPendingBit(USART1 , USART_IT_TC);
//  USART_ClearFlag(USART1, USART_FLAG_TC);	
}



void VarInit(void)
{	u8 i;
	
	WorkStaPre1 = STA_SLEEP;
	WorkSta1	= STA_SLEEP;	
//	GlobalRunTime = 0;
	
	pCmdBuf =&CmdBuf;	//ָ������������
	pRxAdr_Tab = &RxAdr_Tab;
	for(i = 0;i < SPIBUFLEN ;i++){
		SPI1_RxBuf[i] = 0;
//		SPI2_RxBuf[i] = 0;
		SPI1_TxBuf[i] = i;
//		SPI2_TxBuf[i] = i+BufferSize;		
	}
	sta = 0;   //״̬��־
//	SPI2FIFOSta = 0;
//	SPI2Sta = 0;
//	SPI2RxCnt = 0;
//	pRxAdr_Tab->pTabFlag = pRxAdr_Tab->TabFlag ;
#ifdef DEBUGJK
	pRxAdr_Tab->RxAdrTabCnt = 5;
	pCmdBuf->CmdListNum = 5;
#else 
	pRxAdr_Tab->RxAdrTabCnt = 0;
#endif

	pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0;	//��pRxAdrTabCntָ��յĽ��յ�ַ���ռ䡣

	for(i = 0; i < RXADRTABLEN; i++){
#ifdef DEBUGJK
		pRxAdr_Tab->TabFlag[i] = 0x10;
		pRxAdr_Tab->HeartBeatSta[i]	= MAXMISSHEART;		//��ʼ������������
		pCmdBuf->CmdListFlag[i] = 0x10;

#else
		pRxAdr_Tab->TabFlag[i] = 0;
		pCmdBuf->CmdListFlag[i] = 0;
#endif
	}
	pRxAdr_Tab->TabFlag[5] = 0;

	
//����	pRxAdr_Tab->TabFlag[0]	=0x10;

	for(i = 0;i < RX_ADR_WIDTH;i++){
		pRxAdr_Tab->RxAdrTab0[i] = i;
		pRxAdr_Tab->RxAdrTab1[i] = i;
		pRxAdr_Tab->RxAdrTab2[i] = i;
		pRxAdr_Tab->RxAdrTab3[i] = i;
		pRxAdr_Tab->RxAdrTab4[i] = i;
		pRxAdr_Tab->RxAdrTab5[i] = i;	
	}
	
	srand((unsigned) MOD3_TXADR[4]);	//������������Ӻ����������ڱ�ֵ�ĵط����ã���������
}



//--------------------------------SPI configuration ----------------------------------
//SPI1�ӷ����24L01��SPI2�ӽ��յ�24L01����Ϊ���豸
void SPI_Config(void)
{
	// Initialize SPI for 24L01 
	//SPIʱ��Ϊ16/16 = 1MHZ;
	//���ݴ���� MSB λ��ʼ 
	//����Ϊ�� SPI
	//ʱ�����յ�
	//���ݲ����ڵ�һ��ʱ����
	//SPI����Ϊ˫��˫��ȫ˫��
	//NSS ������ܽŹ���
	//���� CRCֵ����Ķ���ʽ	
  SPI_DeInit();
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_16, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00);
	SPI_Cmd(ENABLE);

}






//����ϵͳʱ��100us����ϵͳ��С��ʱ��λ0.1ms	��Сʱ����������ģ��һ�£�������������ϵ
void TIM3_Config(void)
{
  TIM3_DeInit(); 
  
  //Time base configuration 
  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 16/1024 = 0.015625MHz 64US	 	
  TIM3_TimeBaseInit(TIM3_PRESCALER_1024, 15625);	//����һ��
	
  /* Prescaler configuration */
  TIM3_PrescalerConfig(TIM3_PRESCALER_1024, TIM3_PSCRELOADMODE_IMMEDIATE);	

	//  �Զ���װ��Ԥװ������λ
  TIM3_ARRPreloadConfig(ENABLE);
	TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);	//����TIM3�����ж�

  /* Enable TIM3 */
  TIM3_Cmd(ENABLE);

}

void TIM2_Config(void)
{
  TIM2_DeInit();

  //Time base configuration 
  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 16/1024 = 0.015625MHz 64US	 	
  TIM2_TimeBaseInit(TIM2_PRESCALER_1024, TIM2_PERIOD);	//��������
	
  /* Prescaler configuration */
  TIM2_PrescalerConfig(TIM2_PRESCALER_1024, TIM2_PSCRELOADMODE_IMMEDIATE);	

//	TIM2_CCxCmd(TIM2_CHANNEL_1 , ENABLE);
//	TIM2_CCxCmd(TIM2_CHANNEL_2 , ENABLE);
//	TIM2_CCxCmd(TIM2_CHANNEL_3 , ENABLE);

  /* Output Compare Active Mode configuration: Channel1 */
  /*
	  TIM2_OCMode = TIM2_OCMODE_ACTIVE
       TIM2_OutputState = TIM2_OUTPUTSTATE_ENABLE
       TIM2_Pulse = CCR1_Val
	 TIM2_OCPolarity = TIM2_OCPOLARITY_HIGH
	*/
	TIM2_OC1Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR1, TIM2_OCPOLARITY_HIGH);
	
  TIM2_OC1PreloadConfig(DISABLE);

  /* Output Compare Active Mode configuration: Channel2 */
  
  /*TIM2_Pulse = CCR2_Val  */
	
  TIM2_OC2Init(TIM2_OCMODE_TIMING,TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR2,TIM2_OCPOLARITY_HIGH); 
  TIM2_OC2PreloadConfig(DISABLE);

  /* Output Compare Active Mode configuration: Channel3 */
  /*
	TIM2_Pulse = CCR3_Val
	*/
  TIM2_OC3Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR3, TIM2_OCPOLARITY_HIGH);
  TIM2_OC3PreloadConfig(DISABLE);
	//  �Զ���װ��Ԥװ������λ
  TIM2_ARRPreloadConfig(ENABLE);
  /* TIM IT enable */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);
  TIM2_ITConfig(TIM2_IT_CC2, ENABLE);
  TIM2_ITConfig(TIM2_IT_CC3, ENABLE);
	TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);	//����TIM2�ж� 
//	TIM2_ITConfig((TIM2_IT_UPDATE | TIM2_IT_CC1 | TIM2_IT_CC2 | TIM2_IT_CC3), ENABLE);	//����TIM2�ж�
	  
  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);

}



/*******************************************************************************
* Function Name  : SysTick_Configurations	STM8S207û��SysTick
* Description    : Configure a SysTick Base time to 1 us.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void SysTick_Configurations(void)
{
   SysTick->VAL  =0x00;	//SysTick��װ����ֵ�Ĵ�������
   SysTick->CTRL =0x05;	// HCLK��ΪSystickʱ�ӣ�ʹ��SysTick����SysTick������0ʱ������ SysTick �쳣����
   SysTick->LOAD = 72; 	//��װ�ؼĴ��������ϵͳʱ��Ϊ72MHz��ÿ1us�ж�һ��
}
*/
//���ø��ж����ȼ�
void ITC_Configuration(void)
{
	ITC_SetSoftwarePriority(ITC_IRQ_UART1_RX , ITC_PRIORITYLEVEL_1);	//��UART1_RX�ж����ȼ�����Ϊ1��
	ITC_SetSoftwarePriority(ITC_IRQ_TIM2_OVF , ITC_PRIORITYLEVEL_2);	//��TIM2_OVF�ж����ȼ�����Ϊ3��
}


