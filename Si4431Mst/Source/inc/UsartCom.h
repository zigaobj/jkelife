#ifndef  _USARTCOM_H_
#define  _USARTCOM_H_

#define U1RXBUFLEN 250		//串口1接收缓冲区长度
#define U1TXBUFLEN 50		//串口1发送缓冲区长度
#define U2RXBUFLEN 50		//串口1接收缓冲区长度
#define U2TXBUFLEN 50		//串口1发送缓冲区长度
#define U1PARSEBUFLEN  50
#define U2PARSEBUFLEN  50

#define USARTBUFLEN	200

//串口相关各命令的Hash头
#define UCMDHASHLEN	6	//UCMD的Hash头长度
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL


extern uint8_t U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
extern uint8_t U2RxCmdFlag;
//extern uint8_t U1NewFlag;		//SPI1收到新数据
//extern uint8_t U2NewFlag;		//SPI2收到新数据
           
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

//extern __IO uint8_t Usart1TxIndex;
//extern __IO uint8_t Usart2TxIndex;
//extern __IO uint8_t Usart1RxIndex; 
//extern __IO uint8_t Usart2RxIndex;

void Usart_SendString_End(USART_TypeDef* USARTx , uint8_t *string);
void Usart_SendString(USART_TypeDef* USARTx , uint8_t *string , uint16_t len);
void Usart_SendByte(USART_TypeDef* USARTx , uint8_t byte);
void Usart1_Rx_Parse(void);

#endif
