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

/* ����I/O���� */
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
	


//**************************************����IO�˿ڶ���**********************************



//������
//#define DEBUGJK	(1)

#define SPI1CH	1
#define SPI2CH	2 

//�������ΧRANDMIN~RANDMAX 1~255
#define RANDMIN	0x01
#define RANDMAX	0x7D	


//TIM2_CCRx�����ڹ滮����ϵͳ��״̬��
#define TIM2_PERIOD 0x7A12							//2S����
#define TIM2_CCR1	(0x061A)	//ͬ��ʱ��TIM2_PERIOD * 0.05	
#define TIM2_CCR2	(0x249F)		//���㲥ʱ��(�ӽ�������)TIM2_PERIOD * 0.3
#define TIM2_CCR3	(0x3D09)		//�����ݽ���(�ӷ��ͣ����������ظ�����)TIM2_PERIOD * 0.5
//#define TIM2_CCR4	(TIM2_PERIOD * 0.8)		//

//SYN_DELAY��ϵͳ�����յ�SYN�������ʱ����Ҫʵ�ʵ�������
#define SYN_DELAY	0x20 


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//typedef enum {FALSE = 0, TRUE = !FALSE} TestStatus;

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

typedef enum {
STA_SLEEP = 0 ,		//����
STA_NETCONNECT ,	//���������׶�
STA_SYNCHRONIZE ,	//ͬ���׶�
STA_BROADCAST ,		//���ݷ��ͽ׶�
STA_DATA ,			//ά������������ͨ���ݲɼ��׶�
STA_P2P ,			//�������ݵ�Ե㴫��
STA_STANDBY			//����״̬
}SysWorkStatus;	//����ϵͳ�Ĺ���״̬��1�����������׶Σ�2��ͬ���׶� ��3���㲥�׶Σ�4��ά��������ͨ���ݴ���׶Σ�5���������ݵ�Ե㴫��


typedef	struct _RUN_TIME_TYPE_
{
	u32 Second;			//��λΪ1�룬���Ի���Ϊ����Ҫ*1000
//	uint16_t TenthMilliSecond;	//��λΪ0.1���룬100us�����Ի���Ϊ����Ҫ*10
	u32 MilliSecond;		//��λΪ����
}RUN_TIME_TYPE;

typedef u32 timems_t;	//�����¼�������͵ı�������



extern volatile RUN_TIME_TYPE GlobalRunTime;	//��¼ϵͳ�ϵ�������ʱ��
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
