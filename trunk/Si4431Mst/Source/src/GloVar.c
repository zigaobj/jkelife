//#include "Global.h"
#include "stm32f10x.h"
#include "GloVar.h"
#include <absacc.h>

uint8_t U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
uint8_t U2RxCmdFlag;
//uint8_t U1NewFlag;		//SPI1�յ�������
//uint8_t U2NewFlag;		//SPI2�յ�������
           
uint8_t U1RxFullFlag;
uint8_t U2RxFullFlag;
//extern uint8_t pdata txIndex;
volatile uint8_t U1RxIndex;
volatile uint8_t U1RxPindex;
volatile uint8_t U2RxIndex;		 
volatile uint8_t U2RxPindex;        
uint8_t U1ParseBuf[USARTBUFLEN];
uint8_t U2ParseBuf[USARTBUFLEN];

uint8_t U1TxBuf[USARTBUFLEN];
uint8_t U2TxBuf[USARTBUFLEN];
uint8_t U1RxBuf[USARTBUFLEN];
uint8_t U2RxBuf[USARTBUFLEN];

//__IO uint8_t Usart1TxIndex;
//__IO uint8_t Usart2TxIndex;
//__IO uint8_t Usart1RxIndex; 
//__IO uint8_t Usart2RxIndex;

CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
CMD_BUF_TypeDef CmdBuf;	//����������
CMD_BUF_TypeDef * pCmdBuf;	//ָ������������



