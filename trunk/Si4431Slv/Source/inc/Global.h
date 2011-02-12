#ifndef  _GLOBAL_H_
#define  _GLOBAL_H_

#include "stm8s_conf.h"
//#include "stm8s.h"

#include "stm8s_it.h"
//#include "platform_config.h"
#include "Init.h"
#include "UsartCom.h"
#include "Si4431Api.h"
#include "Si4431App.h"
#include "SPICom.h"
//#include "South_KeyBoard.h"
#include "GloVar.h"
//#include <absacc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include <time.h>
#include <stdlib.h>
#include <string.h>

/* 引脚I/O定义 */
#define LEDS_PORT (GPIOB)
#define LED0_PIN  (GPIO_PIN_0)
#define Q_PORT		(GPIOB)
#define Q1_PIN		(GPIO_PIN_3)
#define Q2_PIN		(GPIO_PIN_4)
//#define LED2_PIN  (GPIO_PIN_2)
//#define LED3_PIN  (GPIO_PIN_1)
//#define LED4_PIN  (GPIO_PIN_0)

#define BUTTON_PORT (GPIOC)
#define BUTTON_PIN  (GPIO_PIN_0)

#define	SPI1_PWR_ON()			(SPI1_CTL_GPIO->ODR  |=SPI1_PIN_PWR)
#define	SPI1_PWR_OFF()		(SPI1_CTL_GPIO->ODR  &=~SPI1_PIN_PWR)
/*
  #define SPIy                   SPI1
  #define SPIy_CLK               RCC_APB2Periph_SPI1
  #define SPIy_GPIO              GPIOA
  #define SPIy_GPIO_CLK          RCC_APB2Periph_GPIOA  
  #define SPIy_PIN_NSS			     GPIO_PIN_4
  #define SPIy_PIN_SCK           GPIO_PIN_5
  #define SPIy_PIN_MISO          GPIO_PIN_6
  #define SPIy_PIN_MOSI          GPIO_PIN_7
*/
//  #define SPI1_CLK               RCC_APB2Periph_SPI1
  #define SPI1_PIN_GPIO					GPIOC
//  #define SPI1_GPIO_CLK          RCC_APB2Periph_GPIOA  
	#define SPI1_PIN_CE						(GPIO_PIN_1) 
	#define SPI1_PIN_CSN					(GPIO_PIN_4)
	
  #define SPI1_PIN_SCK					(GPIO_PIN_5)
  #define SPI1_PIN_MOSI					(GPIO_PIN_6)  			  	
  #define SPI1_PIN_MISO					(GPIO_PIN_7)
	
	
	#define SPI1_CTL_GPIO					(GPIOD)
	#define SPI1_PIN_IRQ					(GPIO_PIN_0)
	 
	#define SPI1_PIN_PWR					(GPIO_PIN_2)

	#define	SPI1_CE_H	(SPI1_PIN_GPIO->ODR	|=SPI1_PIN_CE)
	#define	SPI1_CE_L	(SPI1_PIN_GPIO->ODR	&=~SPI1_PIN_CE)

	#define SPI1_CSN_H  (SPI1_PIN_GPIO->ODR |=SPI1_PIN_CSN)
	#define SPI1_CSN_L  (SPI1_PIN_GPIO->ODR	&=~SPI1_PIN_CSN)
	


//**************************************结束IO端口定义**********************************



//调试用
//#define DEBUGJK	(1)

#define SPI1CH	1
#define SPI2CH	2 

//随机数范围RANDMIN~RANDMAX 1~255
#define RANDMIN	0x01
#define RANDMAX	0x7D	


//TIM2_CCRx，用于规划整个系统的状态机
#define TIM2_PERIOD 0x7A12							//2S周期
#define TIM2_CCR1	(0x061A)	//同步时间TIM2_PERIOD * 0.05	
#define TIM2_CCR2	(0x249F)		//主广播时间(从接收命令)TIM2_PERIOD * 0.3
#define TIM2_CCR3	(0x3D09)		//主数据接收(从发送，心跳包及回复数据)TIM2_PERIOD * 0.5
//#define TIM2_CCR4	(TIM2_PERIOD * 0.8)		//

//SYN_DELAY，系统处理收到SYN命令的延时，需要实际调试修正
#define SYN_DELAY	0x20 


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//typedef enum {FALSE = 0, TRUE = !FALSE} TestStatus;

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

typedef enum {
STA_SLEEP = 0 ,		//休眠
STA_NETCONNECT ,	//组网退网阶段
STA_SYNCHRONIZE ,	//同步阶段
STA_BROADCAST ,		//数据发送阶段
STA_DATA ,			//维持心跳包及普通数据采集阶段
STA_P2P ,			//大量数据点对点传输
STA_STANDBY			//待机状态
}SysWorkStatus;	//整个系统的工作状态，1、组网退网阶段，2、同步阶段 ，3、广播阶段，4、维持心跳普通数据传输阶段，5、大量数据点对点传输


typedef	struct _RUN_TIME_TYPE_
{
	u32 Second;			//单位为1秒，所以换算为毫秒要*1000
//	uint16_t TenthMilliSecond;	//单位为0.1毫秒，100us，所以换算为毫秒要*10
	u32 MilliSecond;		//单位为毫秒
}RUN_TIME_TYPE;

typedef u32 timems_t;	//定义记录毫秒类型的变量类型



extern volatile RUN_TIME_TYPE GlobalRunTime;	//记录系统上电后的运行时间
extern volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2;



extern const u8 TxNoReply[] ;
extern const u8 RxNotMatch[];
extern const u8 RxMatch[];

extern const u8 StrError[] ;
extern const u8 TestStr[] ;
extern const u8 TestWord[];

extern const u8 MSGRP_OK[];
extern const u8 MSGRP_ERR[];


//extern volatile TestStatus TransferStatus1 , TransferStatus2;
//extern volatile TestStatus TransferStatus3 , TransferStatus4;
extern @near volatile SysWorkStatus WorkSta1;
extern @near volatile SysWorkStatus WorkStaPre1;
extern @near volatile SysWorkStatus WorkSta2;
extern @near volatile SysWorkStatus WorkStaPre2;

extern  bool InNetFlag;

void DelayUs(volatile u32 usTime);
void Delay (u16 nCount);
void DelayUs_Soft(u16 time);
void DelayMs_Soft(u16 time);
//#define	_MsfInsrt(T, S)		MsgInsrt(T, S, sizeof(S))

TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength);
u16 Hash(u8 *pStr, u8 len);
void MsgInsrt(u8 *pTarget, u8 *pSource, u16 MsgLen);
u16 MyStrLen(u8 str[]);

timems_t ReadRunTime(void);
timems_t CheckTimeInterval(timems_t StartTime,timems_t EndTime);

#endif
