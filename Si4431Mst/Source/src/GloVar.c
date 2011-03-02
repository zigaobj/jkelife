//#include "Global.h"
#include "stm32f10x.h"
#include "Global.h"
#include "CmdPrc.h"
#include "GloVar.h"
#include <absacc.h>

uint8_t U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
uint8_t U2RxCmdFlag;
//uint8_t U1NewFlag;		//SPI1收到新数据
//uint8_t U2NewFlag;		//SPI2收到新数据
           
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



///*********************Global Variable**************************************************************
uint8_t   sta;   //状态标志
uint8_t	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
uint8_t	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;
uint8_t	TXItSta1,TXItSta2;
uint8_t	RXItSta1,RXItSta2;

uint16_t	SPI2RxCnt,SPI1RxCnt;
si4431adrtype NetConnectRxAdr;	//广播接收地址
uint8_t TX_ADDRESS_Si4431[SI4431_ADR_WIDTH]= {0x18,0x42,0x31,0x10};	//本地地址
si4431adrtype RX_ADDRESS_Si4431 ;	//接收地址


uint8_t MOD1_TXADR[SI4431_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//本地地址
uint8_t MOD1_RXADR[SI4431_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//本地地址
uint8_t MOD2_TXADR[SI4431_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//本地地址
uint8_t MOD2_RXADR[SI4431_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//本地地址
uint8_t MOD3_TXADR[SI4431_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//本地地址
uint8_t MOD3_RXADR[SI4431_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//本地地址
uint8_t MOD4_TXADR[SI4431_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//本地地址
uint8_t MOD4_RXADR[SI4431_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//本地地址

u8 StrTest[16] = "Hello Si4431!";

//保存各接收模块的地址。
JKNetAdrTab_TypeDef * pJKNetAdr_Tab;
JKNetAdrTab_TypeDef JKNetAdr_Tab;
