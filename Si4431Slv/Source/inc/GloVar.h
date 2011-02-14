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
extern u8   sta;   //״̬��־	
extern u8	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
extern u8	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;	//SPI2������յ�24L01��FIFO��STATUS,SPI2RxCnt��������RX����
extern u8	TXItSta1,TXItSta2;
extern u8	RXItSta1,RXItSta2;


extern u16	SPI2RxCnt,SPI1RxCnt;
extern u8 NetConnectRxAdr[RX_ADR_WIDTH];		//�㲥���յ�ַ
extern u8 TX_ADDRESS_24L01[TX_ADR_WIDTH];	//���ص�ַ
extern u8 RX_ADDRESS_24L01[RX_ADR_WIDTH];	//���յ�ַ

extern u8 MOD1_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD1_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD2_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD2_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD3_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD3_RXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD4_TXADR[TX_ADR_WIDTH];	//���ص�ַ
extern u8 MOD4_RXADR[TX_ADR_WIDTH];	//���ص�ַ

extern u8 StrTest[13];

extern @near u8 Net_TXADR[TX_ADR_WIDTH];	//��������ַ	
extern @near u8 Net_RXADR[TX_ADR_WIDTH];	//��������ַ

extern u8 U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
extern u8 U2RxCmdFlag;
//u8 U1NewFlag;		//SPI1�յ�������
//u8 U2NewFlag;		//SPI2�յ�������
           
extern u8 U1RxFullFlag;
extern u8 U2RxFullFlag;
//extern u8 pdata txIndex;
extern volatile u8 U1RxIndex;
extern volatile u8 U1RxPindex;
extern volatile u8 U2RxIndex;		 
extern volatile u8 U2RxPindex;        
extern u8 U1ParseBuf[USARTBUFLEN];
extern u8 U2ParseBuf[USARTBUFLEN];

extern u8 U1TxBuf[USARTBUFLEN];
extern u8 U2TxBuf[USARTBUFLEN];
extern u8 U1RxBuf[USARTBUFLEN];
extern u8 U2RxBuf[USARTBUFLEN];

//__IO u8 Usart1TxIndex;
//__IO u8 Usart2TxIndex;
//__IO u8 Usart1RxIndex; 
//__IO u8 Usart2RxIndex;



	

typedef union _CMD_BODY_TypeDef{
	u8 all[CMD_BUF_LEN];	//ken:���������������ݶ�
	struct {
		u8		CmdStartByte;					//JK������ʼ��'#'	
		u8		Header[CMD_HEADER_LEN];			//����ͷ��XXX
		u8		Dot1;							//����ͷ���1��','��
		u8		NetNum;							//����
		u8		Dot2;							//����ͷ���2��','��
		u8		Adr[RX_ADR_WIDTH];		//��ģ���ַ
		u8		Dot3;							//����ͷ���3��','��
		u8 	Others[CMD_OTHERS_LEN];			//������������������ַ�
	}part;
}CMD_BODY_TypeDef;


// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMD_BUF_TypeDef{				
 	CMD_BODY_TypeDef * pCmd_Body;			//ָ�����������������
	CMD_BODY_TypeDef * pReplyBuf;			//Ӧ�𻺳���		
//	u16 	HeadHash;					//���������Hashͷ������ɢת
	u8		CmdTxFlag[CMD_NUMLMT];		//�����״̬
	u8		CmdListNum;					//�������������
	u8		CmdListFlag[CMD_NUMLMT];	//��¼���������ʹ�����
			
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
	u8	RxAdrTabCnt;							//��¼��ʹ�õĵ�ַ�ռ����
	u8 * pRxAdrTabCnt;						//ָ��յĽ��յ�ַ���ռ䡣
	u8 LoopRxAdrIndex;						//��ѯ���յ�ַ
	u8 TabFlag[RXADRTABLEN];			//��¼��ַ�ռ�ʹ���������,0x00:δʹ�û�Ͽ������ˣ�0x01:������������TabFlag[1]��ʼ��¼ 
	u8 HeartBeatSta[RXADRTABLEN];		//��HeartBeatSta[1]��ʼ�����ģ����������������������״̬
//	u8 RxPnSequence[RXADRTABLEN];		//����ͨ������
	u8 RxAdrIndex;		//����ģ���ַ����
	u8 * pCmdTxBuf[RXADRTABLEN];		//ָ��������Ĵ�ģ�����������ռ�
	u8 RxAdrTab0[RX_ADR_WIDTH];	//RxAdrTab0[]�����ģ���ַ��
	u8 RxAdrTab1[RX_ADR_WIDTH];	//��RxAdrTab1[]��ʼ�洢��ģ���ַ
	u8 RxAdrTab2[RX_ADR_WIDTH];
	u8 RxAdrTab3[RX_ADR_WIDTH];
	u8 RxAdrTab4[RX_ADR_WIDTH];
	u8 RxAdrTab5[RX_ADR_WIDTH];
	u8 RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH];
}RxAdrTab_TypeDef;	//��¼������ģ��ĵ�ַ



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;



#endif

