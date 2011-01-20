//#include "Global.h"
#include "stm32f10x.h"
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

CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//命令数据体
CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区



