/***********************************************
*Copyright 2010,South Marine R&D Dpt.
*All rights reserved.
*
*File Name: South_KeyBoard.h
*ID       : 
*Abstract : South KeyBoard function 
*
*Version NO.:1.0
*Writer     :Ken
*Date       :2010-07-29
**************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SOUTH_KEYBOARD_H_
#define _SOUTH_KEYBOARD_H_

#define LED_NUM							5

#define LED_GPIO_PORT					GPIOB
#define LED_GPIO_CLK					RCC_APB2Periph_GPIOB

//#define LED1_PIN						GPIO_Pin_5
#define PWR_ON2_CN_PIN					GPIO_Pin_5
#define PWR_ON2_CN_GPIO_PORT			GPIOB
#define PWR_ON2_CN_GPIO_CLK				RCC_APB2Periph_GPIOB  
  
//#define LED2_PIN						GPIO_Pin_6
#define PWR_LED_CN_PIN					GPIO_Pin_6
#define PWR_LED_CN_GPIO_PORT			GPIOB
#define PWR_LED_CN_GPIO_CLK				RCC_APB2Periph_GPIOB  
//B_LED 实际是DIFF灯
//#define LED3_PIN						GPIO_Pin_7
#define B_LED_CN_PIN					GPIO_Pin_7  
#define B_LED_CN_GPIO_PORT				GPIOB
#define B_LED_CN_GPIO_CLK				RCC_APB2Periph_GPIOB  
//RUN_LED 实际是GPS灯
//#define LED4_PIN						GPIO_Pin_8
#define RUN_LED_CN_PIN					GPIO_Pin_8
#define RUN_LED_CN_GPIO_PORT			GPIOB
#define RUN_LED_CN_GPIO_CLK				RCC_APB2Periph_GPIOB

//#define LED5_PIN						GPIO_Pin_9
#define BEEP_CN_PIN						GPIO_Pin_9
#define BEEP_CN_GPIO_PORT				GPIOB
#define BEEP_CN_GPIO_CLK				RCC_APB2Periph_GPIOB

/*****************华丽的分割线*******************/
#define KEY_NUM							7

#define KEY_GPIO_PORT					GPIOD
#define KEY_GPIO_CLK					RCC_APB2Periph_GPIOD
#define KEY_ALL_EXTI_LINE				(KEY_RHT_EXTI_LINE | KEY_UP_EXTI_LINE | KEY_ENT_EXTI_LINE | KEY_PWR_EXTI_LINE \
										 KEY_DWN_EXTI_LINE | KEY_LFT_EXTI_LINE | KEY_ESC_EXTI_LINE)


#define KEY_RHT_PIN						GPIO_Pin_8
#define KEY_RHT_GPIO_PORT				GPIOD
#define KEY_RHT_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_RHT_EXTI_LINE				EXTI_Line8
#define KEY_RHT_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_RHT_EXTI_PIN_SOURCE			GPIO_PinSource8
#define KEY_RHT_EXTI_IRQn				EXTI9_5_IRQn 
 
#define KEY_UP_PIN						GPIO_Pin_9
#define KEY_UP_GPIO_PORT				GPIOD
#define KEY_UP_GPIO_CLK					RCC_APB2Periph_GPIOD
#define KEY_UP_EXTI_LINE				EXTI_Line9
#define KEY_UP_EXTI_PORT_SOURCE			GPIO_PortSourceGPIOD
#define KEY_UP_EXTI_PIN_SOURCE			GPIO_PinSource9
#define KEY_UP_EXTI_IRQn				EXTI9_5_IRQn 


#define KEY_ENT_PIN						GPIO_Pin_10
#define KEY_ENT_GPIO_PORT				GPIOD
#define KEY_ENT_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_ENT_EXTI_LINE				EXTI_Line10
#define KEY_ENT_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_ENT_EXTI_PIN_SOURCE			GPIO_PinSource10
#define KEY_ENT_EXTI_IRQn				EXTI15_10_IRQn
/**
 * @brief KEY_PWR push-button
 */
//PWR按钮接法比较特殊，可以控制板子的电源，
#define KEY_PWR_PIN						GPIO_Pin_11
#define KEY_PWR_GPIO_PORT				GPIOD
#define KEY_PWR_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_PWR_EXTI_LINE				EXTI_Line11
#define KEY_PWR_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_PWR_EXTI_PIN_SOURCE			GPIO_PinSource11
#define KEY_PWR_EXTI_IRQn				EXTI15_10_IRQn
/**
 * @brief KEY_DWN push-button
 */    
#define KEY_DWN_PIN						GPIO_Pin_12
#define KEY_DWN_GPIO_PORT				GPIOD
#define KEY_DWN_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_DWN_EXTI_LINE				EXTI_Line12
#define KEY_DWN_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_DWN_EXTI_PIN_SOURCE			GPIO_PinSource12
#define KEY_DWN_EXTI_IRQn				EXTI15_10_IRQn  
/**
 * @brief KEY_LFT push-button
 */
#define KEY_LFT_PIN						GPIO_Pin_13
#define KEY_LFT_GPIO_PORT				GPIOD
#define KEY_LFT_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_LFT_EXTI_LINE				EXTI_Line13
#define KEY_LFT_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_LFT_EXTI_PIN_SOURCE			GPIO_PinSource13
#define KEY_LFT_EXTI_IRQn				EXTI15_10_IRQn  
/**
 * @brief KEY_ESC push-button
 */   
#define KEY_ESC_PIN						GPIO_Pin_14
#define KEY_ESC_GPIO_PORT				GPIOD
#define KEY_ESC_GPIO_CLK				RCC_APB2Periph_GPIOD
#define KEY_ESC_EXTI_LINE				EXTI_Line14
#define KEY_ESC_EXTI_PORT_SOURCE		GPIO_PortSourceGPIOD
#define KEY_ESC_EXTI_PIN_SOURCE			GPIO_PinSource14
#define KEY_ESC_EXTI_IRQn				EXTI15_10_IRQn  

 



#endif

