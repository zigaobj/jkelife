#include "stm8s_conf.h"
#include "Global.h"
#include "GloVar.h"

u8 U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
u8 U2RxCmdFlag;
//u8 U1NewFlag;		//SPI1�յ�������
//u8 U2NewFlag;		//SPI2�յ�������
           
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

//CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
//CMD_BUF_TypeDef CmdBuf;	//����������
//CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

///*********************Global Variable**************************************************************
u8   sta;   //״̬��־
u8	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
u8	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;
u8	TXItSta1,TXItSta2;
u8	RXItSta1,RXItSta2;

u16	SPI2RxCnt,SPI1RxCnt;
si4431adrtype NetConnectRxAdr;	//�㲥���յ�ַ
const u8 TX_ADDRESS_Si4431[TX_ADR_WIDTH]= {0x18,0x42,0x31,0x10};	//���ص�ַ
si4431adrtype RX_ADDRESS_Si4431 ;	//���յ�ַ

//u8 MOD1_TXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//���ص�ַ
//u8 MOD1_RXADR[TX_ADR_WIDTH]= {0x21,0xA1,0x0A,0x01};	//���ص�ַ
//const u8 MOD2_TXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//���ص�ַ
//const u8 MOD2_RXADR[TX_ADR_WIDTH]= {0x31,0xA1,0x0B,0x02};	//���ص�ַ
//const u8 MOD3_TXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//���ص�ַ
//const u8 MOD3_RXADR[TX_ADR_WIDTH]= {0x32,0xA1,0x0C,0xA4};	//���ص�ַ
//u8 MOD4_TXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//���ص�ַ
//u8 MOD4_RXADR[TX_ADR_WIDTH]= {0x33,0xA1,0x0D,0xE8};	//���ص�ַ

u8 StrTest[64] = "#NETCNT,31100001,A15C0001\r\n";	////#NETCNT,Դ��ַ(8�ֽ�),Ŀ���ַ(8�ֽ�)\r\n

@near u8 Net_TXADR[TX_ADR_WIDTH];	//��������ַ	
@near u8 Net_RXADR[TX_ADR_WIDTH];	//��������ַ
//���������ģ��ĵ�ַ��
JKNetAdrTab_TypeDef * pJKNetAdr_Tab;
JKNetAdrTab_TypeDef JKNetAdr_Tab;