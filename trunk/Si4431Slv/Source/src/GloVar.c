#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"

u8 U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
u8 U2RxCmdFlag;
//u8 U1NewFlag;		//SPI1收到新数据
//u8 U2NewFlag;		//SPI2收到新数据
           
u8 U1RxFullFlag;
u8 U2RxFullFlag;
//extern u8 pdata txIndex;
volatile u8 U1RxIndex;
volatile u8 U1RxPindex;
volatile u8 U2RxIndex;		 
volatile u8 U2RxPindex;        

//u8 U1ParseBuf[USARTBUFLEN];
//u8 U2ParseBuf[USARTBUFLEN];

//u8 U1TxBuf[USARTBUFLEN];
//u8 U2TxBuf[USARTBUFLEN];
u8 U1RxBuf[USARTBUFLEN];
//u8 U2RxBuf[USARTBUFLEN];

//__IO u8 Usart1TxIndex;
//__IO u8 Usart2TxIndex;
//__IO u8 Usart1RxIndex; 
//__IO u8 Usart2RxIndex;

//CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//命令数据体
//CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
//CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

///*********************Global Variable**************************************************************
u8   sta;   //状态标志
u8	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
u8	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;
u8	TXItSta1,TXItSta2;
u8	RXItSta1,RXItSta2;

u16	SPI2RxCnt,SPI1RxCnt;
si4431adrtype NetConnectRxAdr;	//广播接收地址
const u8 TX_ADDRESS_Si4431[TX_ADR_WIDTH]= {0x18,0x42,0x31,0x10};	//本地地址
si4431adrtype RX_ADDRESS_Si4431 ;	//接收地址

//u8 MOD1_TXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//本地地址
//u8 MOD1_RXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//本地地址
//const u8 MOD2_TXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//本地地址
//const u8 MOD2_RXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//本地地址
//const u8 MOD3_TXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//本地地址
//const u8 MOD3_RXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//本地地址
//u8 MOD4_TXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//本地地址
//u8 MOD4_RXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//本地地址

u8 StrTest[64] = "#NETCNT,31100001,A15C0001\r\n";	////#NETCNT,源地址(8字节),目标地址(8字节)\r\n

@near u8 Net_TXADR[TX_ADR_WIDTH];	//新组网地址	
@near u8 Net_RXADR[TX_ADR_WIDTH];	//新组网地址
//保存各接收模块的地址。
JKNetAdrTab_TypeDef * pJKNetAdr_Tab;
JKNetAdrTab_TypeDef JKNetAdr_Tab;