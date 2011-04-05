/**
  ******************************************************************************
  * @file stm8s_it.c
  * @brief This file contains all the interrupt routines, for Cosmic compiler.
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
#include "Si4431Api.h"
#include "SPICom.h"	
//#include "stm8s_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern u8 ButtonState;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/** @addtogroup IT_Functions
  * @{
  */
#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
/*	//与stm8_interrupt_vector.c中的NonHandledInterrupt重定义了，注释掉
@far @interrupt void NonHandledInterrupt(void)
{
  // In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  //
}
*/
/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
@far @interrupt void TRAP_IRQHandler(void)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#else /*_RAISONANCE_*/

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
void TRAP_IRQHandler(void) trap
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*_COSMIC_*/

/**
  * @brief Top Level Interrupt Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TLI_IRQHandler(void)
#else /* _RAISONANCE_ */
void TLI_IRQHandler(void) interrupt 0
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Auto Wake Up Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void AWU_IRQHandler(void)
#else /* _RAISONANCE_ */
void AWU_IRQHandler(void) interrupt 1
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Clock Controller Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void CLK_IRQHandler(void)
#else /* _RAISONANCE_ */
void CLK_IRQHandler(void) interrupt 2
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTA Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTA_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTA_IRQHandler(void) interrupt 3
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTB Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTB_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTB_IRQHandler(void) interrupt 4
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTC_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTC_IRQHandler(void) interrupt 5
#endif /* _COSMIC_ */
{	

}

/**
  * @brief External Interrupt PORTD Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTD_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTD_IRQHandler(void) interrupt 6
#endif /* _COSMIC_ */
{

if ((GPIO_ReadInputData(SPI1_CTL_GPIO) & SPI1_PIN_IRQ) == 0x00)	//判断是否此引脚的中断
{
	u8 RX_PacketLen,i;		//TmpSta,TmpVal,

	TXItSta1 = SPI1_Read(InterruptStatus1);	// 读取状态寄存其来判断数据接收状况
	TXItSta2 = SPI1_Read(InterruptStatus2);
		
//	GPIO_WriteReverse(LEDS_PORT, LED0_PIN);	//反转LED0 


		
	if( (TXItSta1 & irxffafull) == irxffafull ){	//FIFO几乎满中断
	//	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		//(07h)
		RX_PacketLen = SPI1_Read (ReceivedPacketLength );	//(4Bh)接收包长度
		for(i = SPI1index ;i < RX_PacketLen ;i++){
			SPI1_ParseBuf[i] = SPI1_Read(FIFOAccess);	//(7Fh)接收FIFO有效数据包
				if('\n' == SPI1_ParseBuf[i]){
					SPI1OkFlag ++;	//暂时用此机制，接收到新一条命令
				}
				if(SPI1index >= SPI1PARSEBUFLEN){	//超出接收缓冲区范围
					SPI1FullFlag = 1;
					break;
				}	
		}	
		SPI1index += RX_PacketLen;	
	//	SPI1NewFlg = 0;
		
//		GPIO_WriteReverse(LEDS_PORT, LED0_PIN);
		
		SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x02);       //(08h)清发射接收FIFO
		SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);
		
//	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x10);				 //(50h)使能接收FIFO几乎满中断
// 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00); 		
		SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 5);			 //(07h)RX人工接收模式，预备模式	
	}	

	if( (TXItSta1 & itxffafull) == itxffafull ){	//FIFO几乎满中断
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清发射FIFO
 			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式	
	}
	if( (TXItSta1 & ifferr) == ifferr ){	//FIFO上下溢中断
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03); 			 //清接收FIFO
 			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式	
	}
	if( (TXItSta1 & icrcerror) == icrcerror ){	//CRC错误中断
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);				
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式	
	}	
	if( (TXItSta2 & ipreainval) == ipreainval ){	//引导码错误中断
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03); 			 //清接收FIFO
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
			SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式	
	}

}	
/*		if(!SPI1FullFlag){
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
	  }	*/
		
}

/**
  * @brief External Interrupt PORTE Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTE_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTE_IRQHandler(void) interrupt 7
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#ifdef STM8S903
/**
  * @brief External Interrupt PORTF Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EXTI_PORTF_IRQHandler(void)
#else /* _RAISONANCE_ */
void EXTI_PORTF_IRQHandler(void) interrupt 8
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S903*/

#ifdef STM8S208
/**
  * @brief CAN RX Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void CAN_RX_IRQHandler(void)
#else /* _RAISONANCE_ */
void CAN_RX_IRQHandler(void) interrupt 8
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief CAN TX Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void CAN_TX_IRQHandler(void)
#else /* _RAISONANCE_ */
void CAN_TX_IRQHandler(void) interrupt 9
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S208*/

/**
  * @brief SPI Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void SPI_IRQHandler(void)
#else /* _RAISONANCE_ */
void SPI_IRQHandler(void) interrupt 10
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Update/Overflow/Trigger/Break Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) interrupt 11
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Capture/Compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM1_CAP_COM_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM1_CAP_COM_IRQHandler(void) interrupt 12
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#ifdef STM8S903
/**
  * @brief Timer5 Update/Overflow/Break/Trigger Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM5_UPD_OVF_BRK_TRG_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM5_UPD_OVF_BRK_TRG_IRQHandler(void) interrupt 13
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief Timer5 Capture/Compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM5_CAP_COM_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM5_CAP_COM_IRQHandler(void) interrupt 14
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#else /*STM8S208, STM8S207, STM8S105 or STM8S103*/
/**
  * @brief Timer2 Update/Overflow/Break Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM2_UPD_OVF_BRK_IRQHandler(void) interrupt 13
#endif /* _COSMIC_ */
{
//2秒中断一次， 作为系统的整体时基，用于同步网络各模块时基
	if(TIM2_GetITStatus(TIM2_IT_UPDATE) != RESET){		//待机状态	  
/*		if(GPIO_ReadInputPin(LEDS_PORT, Q1_PIN)){
			GPIO_WriteLow(LEDS_PORT, Q1_PIN);
		}
		else{
			GPIO_WriteHigh(LEDS_PORT, Q1_PIN);
		}
*/		
		//WorkSta1 = STA_STANDBY;  
		TIM2_ClearITPendingBit(TIM2_IT_UPDATE);	//清除 TIMx 的中断待处理位TIM_IT_Update 
		TIM2_ClearFlag(TIM2_FLAG_UPDATE );		
//		if(STA_NETCONNECT == WorkStaPre1){
//			Si4431TX_TxPacket(StrTest ,sizeof(StrTest));	
//		}
		
			
	}		
}

/**
  * @brief Timer2 Capture/Compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM2_CAP_COM_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM2_CAP_COM_IRQHandler(void) interrupt 14
#endif /* _COSMIC_ */
{
	if(TIM2_GetITStatus(TIM2_IT_CC1) != RESET){	//同步工作状态。接收
		TIM2_ClearITPendingBit(TIM2_IT_CC1);	//清除 TIMx 的中断待处理位TIM_IT_Update 
//		TIM2_ClearFlag(TIM2_FLAG_CC1 );
	//	if(STA_STANDBY == WorkSta1){	//只有从STA_STANDBY模式才能转入
			WorkSta1 = STA_SYNCHRONIZE;	//同步工作状态。
		//	SetSlv_RxMode(Net_RXADR);		//设置为接收模式
	//	}
	}
	else if(TIM2_GetITStatus(TIM2_IT_CC2) != RESET){	//广播阶段，接收来自主模块的命令与数据 接收
		TIM2_ClearITPendingBit(TIM2_IT_CC2);	//清除 TIMx 的中断待处理位TIM_IT_Update
//		TIM2_ClearFlag(TIM2_FLAG_CC2 );
	//	if(STA_SYNCHRONIZE == WorkSta1){	//只有从STA_SYNCHRONIZE模式才能转入
			WorkSta1 = STA_BROADCAST;		//广播阶段
		//	SetSlv_RxMode(Net_RXADR);		//设置为接收模式
	//	}		
	}	
	else if(TIM2_GetITStatus(TIM2_IT_CC3) != RESET){	//数据阶段，发送回复命令及心跳包到主模块 发送
		TIM2_ClearITPendingBit(TIM2_IT_CC3);	//清除 TIMx 的中断待处理位TIM_IT_Update 
//		TIM2_ClearFlag(TIM2_FLAG_CC3 );
	//	if(STA_BROADCAST == WorkSta1){	//只有从STA_SYNCHRONIZE模式才能转入{
			WorkSta1 = STA_DATA ;		//维持心跳普通数据传输阶段
	//	}	
	}

}
#endif /*STM8S903*/

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105)
/**
  * @brief Timer3 Update/Overflow/Break Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM3_UPD_OVF_BRK_IRQHandler(void) interrupt 15
#endif /* _COSMIC_ */
{	//1秒中断一次， 作为系统的整体时基，用于同步网络各模块时基
	if(TIM3_GetITStatus(TIM3_IT_UPDATE) != RESET){	  
//	if( FALSE == InNetFlag){

//	}	
		TIM3_ClearITPendingBit(TIM3_IT_UPDATE);	//清除 TIMx 的中断待处理位TIM_IT_Update 
		TIM3_ClearFlag(TIM3_FLAG_UPDATE );
		GlobalRunTime.Second++;

	}
}

/**
  * @brief Timer3 Capture/Compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM3_CAP_COM_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM3_CAP_COM_IRQHandler(void) interrupt 16
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S208, STM8S207 or STM8S105*/

#ifndef STM8S105
/**
  * @brief UART1 TX Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART1_TX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART1_TX_IRQHandler(void) interrupt 17
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief UART1 RX Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART1_RX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART1_RX_IRQHandler(void) interrupt 18
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
    /* Read one byte from the receive data register */
    if(!U1RxFullFlag){
		U1RxBuf[U1RxIndex] = UART1_ReceiveData8();
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
	
}
#endif /*STM8S105*/

/**
  * @brief I2C Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void I2C_IRQHandler(void)
#else /* _RAISONANCE_ */
void I2C_IRQHandler(void) interrupt 19
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#ifdef STM8S105
/**
  * @brief UART2 TX interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART2_TX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART2_TX_IRQHandler(void) interrupt 20
#endif /* _COSMIC_ */
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  }

/**
  * @brief UART2 RX interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART2_RX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART2_RX_IRQHandler(void) interrupt 21
#endif /* _COSMIC_ */
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  }
#endif /* STM8S105*/

#if defined(STM8S207) || defined(STM8S208)
/**
  * @brief UART3 TX interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART3_TX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART3_TX_IRQHandler(void) interrupt 20
#endif /* _COSMIC_ */
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  }

/**
  * @brief UART3 RX interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void UART3_RX_IRQHandler(void)
#else /* _RAISONANCE_ */
void UART3_RX_IRQHandler(void) interrupt 21
#endif /* _COSMIC_ */
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  }
#endif /*STM8S208 or STM8S207*/

#if defined(STM8S207) || defined(STM8S208)
/**
  * @brief ADC2 interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void ADC2_IRQHandler(void)
#else /* _RAISONANCE_ */
void ADC2_IRQHandler(void) interrupt 22
#endif /* _COSMIC_ */
{

    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    return;

}
#else /*STM8S105, STM8S103 or STM8S903*/
/**
  * @brief ADC1 interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void ADC1_IRQHandler(void)
#else /* _RAISONANCE_ */
void ADC1_IRQHandler(void) interrupt 22
#endif /* _COSMIC_ */
{

    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    return;

}
#endif /*STM8S208 or STM8S207*/

#ifdef STM8S903
/**
  * @brief Timer6 Update/Overflow/Trigger Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM6_UPD_OVF_TRG_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM6_UPD_OVF_TRG_IRQHandler(void) interrupt 23
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#else /*STM8S208, STM8S207, STM8S105 or STM8S103*/
/**
  * @brief Timer4 Update/Overflow Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM4_UPD_OVF_IRQHandler(void) interrupt 23
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S903*/

/**
  * @brief Eeprom EEC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void EEPROM_EEC_IRQHandler(void)
#else /* _RAISONANCE_ */
void EEPROM_EEC_IRQHandler(void) interrupt 24
#endif /* _COSMIC_ */
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
