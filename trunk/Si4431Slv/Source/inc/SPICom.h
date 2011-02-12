#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPIBUFLEN 32
#define SPI1PARSEBUFLEN	160		//ken:���ڽ��ջ���������
#define SPI2PARSEBUFLEN 32		//����1���ջ���������
//#define TXLOGLEN	100		//ken:����Ӧ�𻺳�������
//RF����ģ����ظ������Hashͷ
#define RFCMDHASHLEN	3	//RFCMD��Hashͷ����
#define RFCMD_CNT	475		//����
#define RFCMD_HRB	411		//������
#define RFCMD_TMP	789		//�¶Ȳɼ�
#define RFCMD_NTA	441		//����ȷ������
#define RFCMD_SYN 324		//ͬ������


extern @near u8 SPI1OkFlag;	//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
//extern @near u8 SPI2OkFlag;
extern @near u8 SPI1NewFlg;		//SPI1�յ�������
//extern @near u8 SPI2NewFlg;		//SPI2�յ�������
           
extern @near u8 SPI1ProtocolFlag;
extern @near u8 SPI1FullFlag;
//extern uint8_t pdata txIndex;
extern @near u8 SPI1index;
extern @near u8 SPI1Pindex;
//extern @near u8 SPI2index;		 
//extern @near u8 SPI2Pindex;        
extern @near u8 SPI1_ParseBuf[SPI1PARSEBUFLEN];
//extern @near u8 SPI2_ParseBuf[SPI2PARSEBUFLEN];
//extern uint8_t  txLog[TXLOGLEN];

extern @near u8 SPI1ByteNum;
extern @near u8 SPI1_TxBuf[SPIBUFLEN];
//extern u8 SPI2_TxBuf[BufferSize];
extern @near u8 SPI1_RxBuf[SPIBUFLEN]; 
//extern u8 SPI2_RxBuf[BufferSize];

//---------------------------------------------------------------//
void SPI1Rx_Parse(void);



/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


