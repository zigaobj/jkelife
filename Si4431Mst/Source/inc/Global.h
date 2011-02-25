#ifndef  _GLOBAL_H_
#define  _GLOBAL_H_

/*
#include "stm32f10x.h"
#include "platform_config.h"

#include "Init.h"
#include "UsartCom.h"
#include "stm32f10x_it.h"
//#include "24L01API.h"
//#include "24L01App.h"
#include "SPICom.h"
//#include "South_KeyBoard.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

*/
#ifndef    NULL
  #define  NULL   (void *)0  
#endif 
#ifndef    null
 #define   null   (void *)0  
#endif 


//�������ΧRANDMIN~RANDMAX 1~50
#define RANDMIN	0x01
#define RANDMAX	0x32	


//TIM2_CCRx�����ڹ滮����ϵͳ��״̬��
#define TIM2_PERIOD 0x7A12							//2S����	31250
#define TIM2_CCR1	(TIM2_PERIOD * 0.05)	//ͬ��ʱ��	
#define TIM2_CCR2	(TIM2_PERIOD * 0.3)		//�㲥���ݷ���ʱ��
#define TIM2_CCR3	(TIM2_PERIOD * 0.5)		//���ݽ���
#define TIM2_CCR4	(TIM2_PERIOD * 0.8)		//

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//typedef enum {FALSE = 0, TRUE = !FALSE} TestStatus;

typedef	union _LONGWORD32_
{
	u32 All32;			//��λΪ1�룬���Ի���Ϊ����Ҫ*1000
	u8 Bit8[4];			//��λΪ����
}longWord32;


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
	uint32_t Second;			//��λΪ1�룬���Ի���Ϊ����Ҫ*1000
//	u16 TenthMilliSecond;	//��λΪ0.1���룬100us�����Ի���Ϊ����Ҫ*10
	uint32_t MilliSecond;		//��λΪ����
}RUN_TIME_TYPE;

typedef uint32_t timems_t;	//�����¼�������͵ı�������

extern volatile RUN_TIME_TYPE GlobalRunTime;	//��¼ϵͳ�ϵ�������ʱ��
extern volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2,StartTimeMs3,EndTimeMs3;



extern u8 TxNoReply[] ;
extern u8 RxNotMatch[];
extern u8 RxMatch[];

extern u8 StrError[] ;
extern u8 TestStr[] ;
extern u8 TestWord[];

extern u8 MSGRP_OK[];
extern u8 MSGRP_ERR[];


extern volatile TestStatus TransferStatus1 , TransferStatus2;
extern volatile TestStatus TransferStatus3 , TransferStatus4;
extern volatile SysWorkStatus WorkSta1;
extern volatile SysWorkStatus WorkStaPre1;
extern volatile SysWorkStatus WorkSta2;
extern volatile SysWorkStatus WorkStaPre2;

//extern volatile STA24L01 Mst24L01Sta,Slv24L01Sta;


void DelayUs(__IO uint32_t usTime);
void DelayCom(u16 nCount);
void DelayUs_Soft(u16 time);
void DelayMs_Soft(u16 time);

//#define	_MsfInsrt(T, S)		MsgInsrt(T, S, sizeof(S))

timems_t ReadRunTime(void);
timems_t CheckTimeInterval(timems_t StartTime,timems_t EndTime);

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint16_t Hash(uint8_t *pStr, uint8_t len);
//u8 CmdCheck(CMD_BODY_TypeDef * pCmdDat);
void MsgCopy(u8 * pTarget, u8 * pSource, u16 MsgLen);
void MsgInsrt(uint8_t * pTarget, uint8_t * pSource, uint16_t MsgLen ,u8 AddDotFg);
uint16_t MyStrLen(uint8_t str[]);
//u16 ReplyAppend(CMD_BODY_TypeDef *pRplyStr);

u32 MyStrToNum(u8 *pStr, u8	NumLen);
u8 MyNumToStr(u8 *pStr,u32 Num , u16 NumLen);
u8 MyLongToStr(u8 *pTarget ,u32 * pLSource , u16 NumLen);

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint16_t Hash(uint8_t *pStr, uint8_t len);
//u8 CmdCheck(CMD_BODY_TypeDef * pCmdDat);
void MsgCopy(u8 * pTarget, u8 * pSource, u16 MsgLen);
void MsgInsrt(uint8_t * pTarget, uint8_t * pSource, uint16_t MsgLen ,u8 AddDotFg);
uint16_t MyStrLen(uint8_t str[]);
//u16 ReplyAppend(CMD_BODY_TypeDef *pRplyStr);

u32 MyStrToNum(u8 *pStr, u8	NumLen);
u8 MyNumToStr(u8 *pStr,u32 Num , u16 NumLen);
u8 MyLongToStr(u8 *pTarget ,u32 * pLSource , u16 NumLen);
u32 MyStrToHex(u8 *pStr, u8	NumLen)	;
u8 MyHexToStr(u8 *pStr,u32 Num , u16 NumLen);

#endif
