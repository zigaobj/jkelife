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

///*********************Global Variable**************************************************************
uint8_t   sta;   //״̬��־
uint8_t	SPI1FIFOSta,SPI1Sta;
uint8_t	SPI2FIFOSta,SPI2Sta;
uint16_t	SPI2RxCnt,SPI1RxCnt;
uint8_t NetConnectRxAdr[RX_ADR_WIDTH] = {0xA1,0x5C,0x00,0x01};	//�㲥���յ�ַ
uint8_t TX_ADDRESS_Si4431[TX_ADR_WIDTH]= {0x18,0x42,0x31,0x10};	//���ص�ַ
uint8_t RX_ADDRESS_Si4431[RX_ADR_WIDTH]= {0x33,0x43,0x10,0x28};	//���յ�ַ

uint8_t MOD1_TXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//���ص�ַ
uint8_t MOD1_RXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//���ص�ַ
uint8_t MOD2_TXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//���ص�ַ
uint8_t MOD2_RXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//���ص�ַ
uint8_t MOD3_TXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//���ص�ַ
uint8_t MOD3_RXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//���ص�ַ
uint8_t MOD4_TXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//���ص�ַ
uint8_t MOD4_RXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//���ص�ַ

