/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body
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
#include "platform_config.h"
#include "Init.h"
#include "Global.h"
#include "CmdPrc.h"
#include "SPICom.h"
#include "Si4431Api.h"
#include "Si4431App.h"
#include "GloVar.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_SoftNSS
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{//  uint8_t TmpSta;
            
  SysInit_Config();
	
//  Usart_SendString_End(USART1 ,TestWord );	//不知原因，串口发送第一字节数据会丢失或出错。只能单独发送一字节来预防

//  DelayUs_Soft(10);

  
//	Usart_SendString_End(USART1 ,TestStr );	//将收到的数据往串口1发送
//  DelayUs(10);
//	Usart_SendString_End(USART1 ,TestStr );	//将收到的数据往串口1发送
//  DelayUs(10);
    
  Si4431TX_Init();
  DelayMs_Soft(100);
//  Si4431RX_Init();

	
//	DelayUs_Soft(1000);
	
	
//	Si4431RX_ReceiveMod(MOD3_TXADR);



//  SetSPI1_BroadCast();


//  SetSPI2_RXMode(RX_P0_24L01,MOD1_RXADR);	//设置SPI2连接的24L01为接收模式，设置接收通道0地址
//  SetSPI1_TXMode(MOD1_RXADR);		//设置SPI1连接的24L01为发射模式，设置发射地址及接收通道0地址


//  nRF24L01_SPI1_TxPacket(SPI1_TxBuf);	// 测试发送32字节数据，Transmit Tx buffer data
//  SPI1Sta = SPI1_Read(STATUS_24L01);
//  SPI1FIFOSta = SPI1_Read(FIFO_STATUS_24L01);

//  SPI2Sta = SPI2_Read(STATUS_24L01);
//  SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);  
//  nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
//  DelayUs(500);
//  TmpSta = SPI2_Read(FIFO_STATUS_24L01);
//  DelayUs(10);	
//	nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
			
	
  	
//测试 	SPI2_CMDCNT(1);
	
//测试	NewConnect(BroadCastRxAdr);
	
	//END测试

  WorkSta1 = STA_NETCONNECT;	//上电进入组网状态。
  
	
	while (1)
  {	
		SysRun();		
		SPI1Rx_Parse();
		CmdExecute();
//	Usart1_Rx_Parse();
//	SPI1Rx_Parse();

	
//	RandomDelayUs();
//	SetSPI1_TXMode(MOD3_RXADR);	//向新组网的模块发送组网新地址。	
//	DelayUs(100000);	//100ms
//	nRF24L01_SPI1_TxPacket(SPI1_TxBuf);	// 测试发送32字节数据，Transmit Tx buffer data

//	DelayUs(100000);	//100ms
//	nRF24L01_SPI1_TxPacket(SPI2_TxBuf);	// 测试发送32字节数据，Transmit Tx buffer data
//	TmpSta = SPI1_Read(STATUS_24L01);
//	TmpSta = SPI1_Read(FIFO_STATUS_24L01);
/*	if()
	{
		for(i=0;i<32;i++)
		{
			DelayUs(600);
		}	
	}*/    
  }
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
