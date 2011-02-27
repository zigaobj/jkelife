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
	
//  Usart_SendString_End(USART1 ,TestWord );	//��֪ԭ�򣬴��ڷ��͵�һ�ֽ����ݻᶪʧ�����ֻ�ܵ�������һ�ֽ���Ԥ��

//  DelayUs_Soft(10);

  
//	Usart_SendString_End(USART1 ,TestStr );	//���յ�������������1����
//  DelayUs(10);
//	Usart_SendString_End(USART1 ,TestStr );	//���յ�������������1����
//  DelayUs(10);
    
  Si4431TX_Init();
  DelayMs_Soft(100);
//  Si4431RX_Init();

	
//	DelayUs_Soft(1000);
	
	
//	Si4431RX_ReceiveMod(MOD3_TXADR);



//  SetSPI1_BroadCast();


//  SetSPI2_RXMode(RX_P0_24L01,MOD1_RXADR);	//����SPI2���ӵ�24L01Ϊ����ģʽ�����ý���ͨ��0��ַ
//  SetSPI1_TXMode(MOD1_RXADR);		//����SPI1���ӵ�24L01Ϊ����ģʽ�����÷����ַ������ͨ��0��ַ


//  nRF24L01_SPI1_TxPacket(SPI1_TxBuf);	// ���Է���32�ֽ����ݣ�Transmit Tx buffer data
//  SPI1Sta = SPI1_Read(STATUS_24L01);
//  SPI1FIFOSta = SPI1_Read(FIFO_STATUS_24L01);

//  SPI2Sta = SPI2_Read(STATUS_24L01);
//  SPI2FIFOSta = SPI2_Read(FIFO_STATUS_24L01);  
//  nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
//  DelayUs(500);
//  TmpSta = SPI2_Read(FIFO_STATUS_24L01);
//  DelayUs(10);	
//	nRF24L01_SPI2_RxPacket(SPI2_RxBuf);
			
	
  	
//���� 	SPI2_CMDCNT(1);
	
//����	NewConnect(BroadCastRxAdr);
	
	//END����

  WorkSta1 = STA_NETCONNECT;	//�ϵ��������״̬��
  
	
	while (1)
  {	
		SysRun();		
		SPI1Rx_Parse();
		CmdExecute();
//	Usart1_Rx_Parse();
//	SPI1Rx_Parse();

	
//	RandomDelayUs();
//	SetSPI1_TXMode(MOD3_RXADR);	//����������ģ�鷢�������µ�ַ��	
//	DelayUs(100000);	//100ms
//	nRF24L01_SPI1_TxPacket(SPI1_TxBuf);	// ���Է���32�ֽ����ݣ�Transmit Tx buffer data

//	DelayUs(100000);	//100ms
//	nRF24L01_SPI1_TxPacket(SPI2_TxBuf);	// ���Է���32�ֽ����ݣ�Transmit Tx buffer data
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
