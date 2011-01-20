#ifndef _GLOVAR_H_
#define _GLOVAR_H_

//#include "Global.h"

/* typedef -----------------------------------------------------------*/


extern uint8_t U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
extern uint8_t U2RxCmdFlag;
//uint8_t U1NewFlag;		//SPI1�յ�������
//uint8_t U2NewFlag;		//SPI2�յ�������
           
extern uint8_t U1RxFullFlag;
extern uint8_t U2RxFullFlag;
//extern uint8_t pdata txIndex;
extern volatile uint8_t U1RxIndex;
extern volatile uint8_t U1RxPindex;
extern volatile uint8_t U2RxIndex;		 
extern volatile uint8_t U2RxPindex;        
extern uint8_t U1ParseBuf[USARTBUFLEN];
extern uint8_t U2ParseBuf[USARTBUFLEN];

extern uint8_t U1TxBuf[USARTBUFLEN];
extern uint8_t U2TxBuf[USARTBUFLEN];
extern uint8_t U1RxBuf[USARTBUFLEN];
extern uint8_t U2RxBuf[USARTBUFLEN];

//__IO uint8_t Usart1TxIndex;
//__IO uint8_t Usart2TxIndex;
//__IO uint8_t Usart1RxIndex; 
//__IO uint8_t Usart2RxIndex;

extern CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
extern CMD_BUF_TypeDef CmdBuf;	//����������
extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������
