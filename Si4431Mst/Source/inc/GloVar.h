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


//#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
//#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload



//������ظ������Hashͷ
#define UCMDHASHLEN	6	//UCMD��Hashͷ����
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL

//Si4431��ַ����
#define SI4431_ADR_WIDTH    4   	// 4 uints TX address width
//#define Si4431_TXADR_WIDTH    4   	// 4 uints TX address width
//#define Si4431_RXADR_WIDTH    4   	// 4 uints RX address width



#define CMD_MAXRESEND			5				//�����ط�������
#define NETCNT_TIMEOUT		1000		//��������״̬��ʱΪ10S ����ʱ����Ϊ1S
#define DATARECEIVE_SPAN	200			//Data�������ݽ׶Σ�����ͨ��Rx_P1~5�л�ʱ����


/*************************��������*****************************************************/
extern uint8_t   sta;   //״̬��־	
extern uint8_t	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
extern uint8_t	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;	//SPI2������յ�24L01��FIFO��STATUS,SPI2RxCnt��������RX����
extern uint8_t	TXItSta1,TXItSta2;
extern uint8_t	RXItSta1,RXItSta2;


extern uint16_t	SPI2RxCnt,SPI1RxCnt;
extern uint8_t NetConnectRxAdr[SI4431_ADR_WIDTH];		//�㲥���յ�ַ
extern uint8_t TX_ADDRESS_Si4431[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t RX_ADDRESS_Si4431[SI4431_ADR_WIDTH];	//���յ�ַ

extern uint8_t MOD1_TXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD1_RXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD2_TXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD2_RXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD3_TXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD3_RXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD4_TXADR[SI4431_ADR_WIDTH];	//���ص�ַ
extern uint8_t MOD4_RXADR[SI4431_ADR_WIDTH];	//���ص�ַ

extern u8 StrTest[16];

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


//extern u8 SPI1_TxBuf[SPIBUFLEN];
//extern u8 SPI2_TxBuf[SPIBUFLEN];
//extern u8 SPI1_RxBuf[SPIBUFLEN]; 
//extern u8 SPI2_RxBuf[SPIBUFLEN];
	




#define DEFAULT_FRE		0x28   //Ĭ��Ƶ��

#define JKNETADRTABLEN	6	//�ӵ�ַ�ռ��С	//�ݶ�һ�������֧��255����ģ��
#define MAXMISSHEART 5	//����������������� 

typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_JKNetAdrTab_TypeDef
{
	uint8_t	JKNetAdrTabCnt;							//��¼��ʹ�õĵ�ַ�ռ����
	uint8_t * pJKNetAdrTabCnt;						//ָ��յĽ��յ�ַ���ռ䡣
	uint8_t LoopJKNetAdrIndex;						//��ѯ���յ�ַ
	uint8_t TabFlag[JKNETADRTABLEN];			//��¼��ַ�ռ�ʹ���������,0x00:δʹ�û�Ͽ������ˣ�0x01:������������TabFlag[1]��ʼ��¼ 
	uint8_t HeartBeatSta[JKNETADRTABLEN];		//��HeartBeatSta[1]��ʼ�����ģ����������������������״̬
//	uint8_t RxPnSequence[JKNetAdrTABLEN];		//����ͨ������
	uint8_t JKNetAdrIndex;		//����ģ���ַ����
	uint8_t * pCmdTxBuf[JKNETADRTABLEN];		//ָ��������Ĵ�ģ�����������ռ�
	uint8_t JKNetAdrTab0[SI4431_ADR_WIDTH];	//JKNetAdrTab0[]�����ģ���ַ��
	uint8_t JKNetAdrTab1[SI4431_ADR_WIDTH];	//��JKNetAdrTab1[]��ʼ�洢��ģ���ַ
	uint8_t JKNetAdrTab2[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab3[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab4[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab5[SI4431_ADR_WIDTH];
//	uint8_t JKNetAdrAll[JKNETADRTABLEN][SI4431_ADR_WIDTH];
}JKNetAdrTab_TypeDef;	//��¼������ģ��ĵ�ַ



extern JKNetAdrTab_TypeDef * pJKNetAdr_Tab;
extern JKNetAdrTab_TypeDef JKNetAdr_Tab;



#endif

