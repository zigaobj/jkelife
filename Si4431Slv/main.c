/**
  ******************************************************************************
  * @file GPIO_IOToggle_InterruptMode\main.c
  * @brief This file contains the main function for GPIO IOToggle_PollingMode example.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.1
  * @date 06/05/2009
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"
#include "Init.h"
#include "Si4431Api.h"

/**
  * @addtogroup GPIO_IOToggle_InterruptMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/
u8 ButtonState = 0x00;

/* Public functions ----------------------------------------------------------*/

/**
  * @brief Example firmware main entry point.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
void main(void)
{

//  u8 Leds; /* Contains which LEDs to operate */

	SysInit_Config();	//系统配置
	
	DelayMs_Soft(100);
	
	Si4431TX_Init();
	

  /* Initialize I/O in Input Mode with Interrupt */
//  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_MODE_IN_FL_IT);

  /* Initialize the Interrupt sensitivity */
//  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);

  enableInterrupts();		//开全局中断
	
	WorkSta1 = STA_NETCONNECT;	//上电组网

  /* Toggles LEDs */
	
//  Uart1_SendString_End(TestStr);		//
	GPIO_WriteHigh(LEDS_PORT, LED0_PIN);

	Si4431TX_ReceiveMod(MOD3_RXADR);
	
	while (1)
  {
//		SysRun();
//		SPI1Rx_Parse();

  }

}




#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval 
  * None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
