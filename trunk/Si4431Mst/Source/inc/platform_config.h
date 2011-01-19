/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/platform_config.h 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Evaluation board specific configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM32100B_EVAL) && !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM3210C_EVAL)
 //#define USE_STM32100B_EVAL
 //#define USE_STM3210B_EVAL
 #define USE_STM3210E_EVAL
// #define USE_STM3210C_EVAL
#endif

//调试用
//#define DEBUGJK	(1)

//#define SOUTHBOARD	(1)

#define JKVER1BOARD	(1)

#define nRF24L01_board	(1)



//****************************************IO端口定义***************************************
#ifdef 	JKVER1BOARD
/* 引脚I/O定义 */
#define LEDS_PORT			GPIOC
#define RUN_LED_PIN		(GPIO_Pin_4)
#define NET_LED_PIN		(GPIO_Pin_5)
#define IRLED_PORT		GPIOA
#define IRDA_LED_PIN	(GPIO_Pin_8)
//#define RF_NSEL_PIN		(SPI1_PIN_CSN)


#define	RUN_LED_OFF()		(LEDS_PORT->ODR  |=RUN_LED_PIN)
#define	RUN_LED_ON()		(LEDS_PORT->ODR &=~RUN_LED_PIN)
#define RUN_LED_TURN()	GPIO_WriteBit(LEDS_PORT, RUN_LED_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LEDS_PORT, RUN_LED_PIN)))	
#define	NET_LED_OFF()		(LEDS_PORT->ODR  |=NET_LED_PIN)
#define	NET_LED_ON()		(LEDS_PORT->ODR &=~NET_LED_PIN)
#define NET_LED_TURN()	GPIO_WriteBit(LEDS_PORT, NET_LED_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LEDS_PORT, NET_LED_PIN)))
#define	IRDA_LED_OFF()		(IRLED_PORT->ODR  |=IRDA_LED_PIN)
#define	IRDA_LED_ON()	(IRLED_PORT->ODR &=~IRDA_LED_PIN)
#define IRDA_LED_TURN()	GPIO_WriteBit(IRLED_PORT, IRDA_LED_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(IRLED_PORT, IRDA_LED_PIN)))

#define	SPI1_PWR_ON()			(SPI1_CTL_GPIO->ODR  |=SPI1_PIN_PWR)
#define	SPI1_PWR_OFF()		(SPI1_CTL_GPIO->ODR  &=~SPI1_PIN_PWR)
#define	SPI2_PWR_ON()			(SPI2_CTL_GPIO->ODR  |=SPI2_PIN_PWR)
#define	SPI2_PWR_OFF()		(SPI2_CTL_GPIO->ODR  &=~SPI2_PIN_PWR)

#define Q_PORT				(GPIOB)
#define Q1_PIN				(GPIO_Pin_0)
#define Q2_PIN				(GPIO_Pin_1)
#define	Q1_PIN_ON()			(Q_PORT->ODR  |=Q1_PIN)
#define	Q1_PIN_OFF()		(Q_PORT->ODR  &=~Q1_PIN)
#define	Q2_PIN_ON()			(Q_PORT->ODR  |=Q2_PIN)
#define	Q2_PIN_OFF()		(Q_PORT->ODR  &=~Q2_PIN)


#define OUT_CO_PORT		(GPIOB)
#define OUT_CO1_PIN		(GPIO_Pin_2)
#define OUT_CO2_PIN		(GPIO_Pin_5)
#define OUT_CO3_PIN		(GPIO_Pin_8)
#define OUT_CO4_PIN		(GPIO_Pin_9)

#define PWR_OUT_PORT	(GPIOA)
#define PWR_OUT_PIN		(GPIO_Pin_1)


  #define SPI1_CLK            RCC_APB2Periph_SPI1
  #define SPI1_GPIO           GPIOA
  #define SPI1_GPIO_CLK       RCC_APB2Periph_GPIOA  
  
  #define SPI1_PIN_SCK        GPIO_Pin_5
  #define SPI1_PIN_MISO       GPIO_Pin_6
  #define SPI1_PIN_MOSI       GPIO_Pin_7  

  #define SPI2_CLK            RCC_APB1Periph_SPI2
  #define SPI2_GPIO           GPIOB
  #define SPI2_GPIO_CLK       RCC_APB2Periph_GPIOB

  #define SPI2_PIN_SCK        GPIO_Pin_13
  #define SPI2_PIN_MISO       GPIO_Pin_14
  #define SPI2_PIN_MOSI       GPIO_Pin_15 

//SPI1的CE使用PWR_ON2，SPI2的CE使用BEEP_CN ，SPI1的IRQ使用AD9313_CN，SPI2的IRQ使用AD9313_UD，
//SPI1连接发送，SPI2接收 

  #define SPI1_CTL_GPIO       GPIOC
  #define SPI2_CTL_GPIO       GPIOC
  #define SPI1_PIN_IRQ			  GPIO_Pin_0
  #define SPI1_PIN_CSN			  GPIO_Pin_1
  #define SPI1_PIN_CE			  	GPIO_Pin_2
  #define SPI1_PIN_PWR			  GPIO_Pin_3

  #define SPI2_PIN_CE			  	GPIO_Pin_6
  #define SPI2_PIN_CSN 			  GPIO_Pin_7
  #define SPI2_PIN_IRQ			  GPIO_Pin_8
  #define SPI2_PIN_PWR			  GPIO_Pin_9


	#define	SPI1_CE_H	(SPI1_CTL_GPIO->BSRR |=SPI1_PIN_CE)
	#define	SPI1_CE_L	(SPI1_CTL_GPIO->BRR |=SPI1_PIN_CE)
	#define	SPI2_CE_H	(SPI2_CTL_GPIO->BSRR |=SPI2_PIN_CE)
	#define	SPI2_CE_L	(SPI2_CTL_GPIO->BRR |=SPI2_PIN_CE)

	#define SPI1_CSN_H  (SPI1_CTL_GPIO->BSRR |=SPI1_PIN_CSN)
	#define SPI1_CSN_L  (SPI1_CTL_GPIO->BRR |=SPI1_PIN_CSN)
	#define SPI2_CSN_H  (SPI2_CTL_GPIO->BSRR |=SPI2_PIN_CSN)
	#define SPI2_CSN_L  (SPI2_CTL_GPIO->BRR |=SPI2_PIN_CSN)

	#define SPI1_IRQ_H  (SPI1_CTL_GPIO->BSRR |= SPI1_PIN_IRQ)
	#define SPI2_IRQ_H  (SPI2_CTL_GPIO->BSRR |= SPI2_PIN_IRQ)


#endif






/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
