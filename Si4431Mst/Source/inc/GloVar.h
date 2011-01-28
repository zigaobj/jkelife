#ifndef _GLOVAR_H_
#define _GLOVAR_H_

//#include "Global.h"

/* typedef -----------------------------------------------------------*/


/* define -----------------------------------------------------------*/
#define U1RXBUFLEN 250		//����1���ջ���������
#define U1TXBUFLEN 50		//����1���ͻ���������
#define U2RXBUFLEN 50		//����1���ջ���������
#define U2TXBUFLEN 50		//����1���ͻ���������
#define U1PARSEBUFLEN  50
#define U2PARSEBUFLEN  50

#define USARTBUFLEN	200

#define TX_ADR_WIDTH    4   	// 4 uints TX address width
#define RX_ADR_WIDTH    4   	// 4 uints RX address width
//#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
//#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload

#define CMD_MAXRESEND	5		//�����ط�������
#define CMD_NUMLMT 5			//�����ͬʱ������������
#define NETCNT_TIMEOUT	1000	//��������״̬��ʱΪ10S ����ʱ����Ϊ1S
#define DATARECEIVE_SPAN	200	//Data�������ݽ׶Σ�����ͨ��Rx_P1~5�л�ʱ����
#define CMD_BUF_LEN	32
#define CMD_HEADER_LEN 3
#define CMD_OTHERS_START 6
#define CMD_OTHERS_LEN	19

//������ظ������Hashͷ
#define UCMDHASHLEN	6	//UCMD��Hashͷ����
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL


/*************************��������*****************************************************/
extern uint8_t   sta;   //״̬��־	
extern uint8_t	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
extern uint8_t	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;	//SPI2������յ�24L01��FIFO��STATUS,SPI2RxCnt��������RX����
extern uint8_t	TXItSta1,TXItSta2;
extern uint8_t	RXItSta1,RXItSta2;


extern uint16_t	SPI2RxCnt,SPI1RxCnt;
extern uint8_t NetConnectRxAdr[RX_ADR_WIDTH];		//�㲥���յ�ַ
extern uint8_t TX_ADDRESS_24L01[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t RX_ADDRESS_24L01[RX_ADR_WIDTH];	//���յ�ַ

extern uint8_t MOD1_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD1_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD2_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD2_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD3_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD3_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD4_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD4_RXADR[TX_ADR_WIDTH];	//���ص�ַ

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



	

typedef union _CMD_BODY_TypeDef{
	uint8_t all[CMD_BUF_LEN];	//ken:���������������ݶ�
	struct {
		uint8_t		CmdStartByte;					//JK������ʼ��'#'	
		uint8_t		Header[CMD_HEADER_LEN];			//����ͷ��XXX
		uint8_t		Dot1;							//����ͷ���1��','��
		uint8_t		NetNum;							//����
		uint8_t		Dot2;							//����ͷ���2��','��
		uint8_t		Adr[RX_ADR_WIDTH];		//��ģ���ַ
		uint8_t		Dot3;							//����ͷ���3��','��
		uint8_t 	Others[CMD_OTHERS_LEN];			//������������������ַ�
	}part;
}CMD_BODY_TypeDef;


// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMD_BUF_TypeDef{				
 	CMD_BODY_TypeDef * pCmd_Body;			//ָ�����������������
	CMD_BODY_TypeDef * pReplyBuf;			//Ӧ�𻺳���		
//	uint16_t 	HeadHash;					//���������Hashͷ������ɢת
	uint8_t		CmdTxFlag[CMD_NUMLMT];		//�����״̬
	uint8_t		CmdListNum;					//�������������
	uint8_t		CmdListFlag[CMD_NUMLMT];	//��¼���������ʹ�����
			
}CMD_BUF_TypeDef;	
extern CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
extern CMD_BUF_TypeDef CmdBuf;	//����������
extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������


#define DEFAULT_FRE		0x28   //Ĭ��Ƶ��

#define RXADRTABLEN	6	//�ӵ�ַ�ռ��С	//�ݶ�һ�������֧��255����ģ��
#define MAXMISSHEART 5	//����������������� 
typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_RxAdrTab_TypeDef
{
	uint8_t	RxAdrTabCnt;							//��¼��ʹ�õĵ�ַ�ռ����
	uint8_t * pRxAdrTabCnt;						//ָ��յĽ��յ�ַ���ռ䡣
	uint8_t LoopRxAdrIndex;						//��ѯ���յ�ַ
	uint8_t TabFlag[RXADRTABLEN];			//��¼��ַ�ռ�ʹ���������,0x00:δʹ�û�Ͽ������ˣ�0x01:������������TabFlag[1]��ʼ��¼ 
	uint8_t HeartBeatSta[RXADRTABLEN];		//��HeartBeatSta[1]��ʼ�����ģ����������������������״̬
//	uint8_t RxPnSequence[RXADRTABLEN];		//����ͨ������
	uint8_t RxAdrIndex;		//����ģ���ַ����
	uint8_t * pCmdTxBuf[RXADRTABLEN];		//ָ��������Ĵ�ģ�����������ռ�
	uint8_t RxAdrTab0[RX_ADR_WIDTH];	//RxAdrTab0[]�����ģ���ַ��
	uint8_t RxAdrTab1[RX_ADR_WIDTH];	//��RxAdrTab1[]��ʼ�洢��ģ���ַ
	uint8_t RxAdrTab2[RX_ADR_WIDTH];
	uint8_t RxAdrTab3[RX_ADR_WIDTH];
	uint8_t RxAdrTab4[RX_ADR_WIDTH];
	uint8_t RxAdrTab5[RX_ADR_WIDTH];
	uint8_t RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH];
}RxAdrTab_TypeDef;	//��¼������ģ��ĵ�ַ



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;



#endif

