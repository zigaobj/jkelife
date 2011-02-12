#ifndef  _USARTCOM_H_
#define  _USARTCOM_H_

/*
#define U1RXBUFLEN 250		//串口1接收缓冲区长度
#define U1TXBUFLEN 50		//串口1发送缓冲区长度
#define U2RXBUFLEN 50		//串口1接收缓冲区长度
#define U2TXBUFLEN 50		//串口1发送缓冲区长度
#define U1PARSEBUFLEN  50
#define U2PARSEBUFLEN  50

#define USARTBUFLEN	80

//串口相关各命令的Hash头
#define UCMDHASHLEN	6	//UCMD的Hash头长度
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL


extern @near u8 U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
extern @near u8 U2RxCmdFlag;
//extern u8 U1NewFlag;		//SPI1收到新数据
//extern u8 U2NewFlag;		//SPI2收到新数据
           
extern @near u8 U1RxFullFlag;
//extern @near u8 U2RxFullFlag;
//extern u8 pdata txIndex;
extern @near u8 U1RxIndex;
extern @near u8 U1RxPindex;
//extern @near u8 U2RxIndex;		 
//extern @near u8 U2RxPindex;        
extern @near u8 U1ParseBuf[USARTBUFLEN];
//extern @near u8 U2ParseBuf[USARTBUFLEN];


extern @near u8 U1TxBuf[USARTBUFLEN];
//extern @near u8 U2TxBuf[USARTBUFLEN];
extern @near u8 U1RxBuf[USARTBUFLEN];
//extern @near u8 U2RxBuf[USARTBUFLEN];

*/
//extern __IO u8 Usart1TxIndex;
//extern __IO u8 Usart2TxIndex;
//extern __IO u8 Usart1RxIndex; 
//extern __IO u8 Usart2RxIndex;

void Uart1_SendString_End(u8 *string);
void Uart1_SendString(u8 *string , u16 len);
void Uart1_SendByte(u8 byte);
void Usart1_Rx_Parse(void);
u8 CmdApply(u8 *pCmdPos , u8 CmdLen);

#endif
