#ifndef  _USARTCOM_H_
#define  _USARTCOM_H_

/*
#define U1RXBUFLEN 250		//����1���ջ���������
#define U1TXBUFLEN 50		//����1���ͻ���������
#define U2RXBUFLEN 50		//����1���ջ���������
#define U2TXBUFLEN 50		//����1���ͻ���������
#define U1PARSEBUFLEN  50
#define U2PARSEBUFLEN  50

#define USARTBUFLEN	80

//������ظ������Hashͷ
#define UCMDHASHLEN	6	//UCMD��Hashͷ����
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL


extern @near u8 U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
extern @near u8 U2RxCmdFlag;
//extern u8 U1NewFlag;		//SPI1�յ�������
//extern u8 U2NewFlag;		//SPI2�յ�������
           
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
