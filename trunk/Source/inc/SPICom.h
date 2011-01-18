#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPI1PARSEBUFLEN	320		//ken:���ڽ��ջ���������
#define SPI2PARSEBUFLEN 320		//����1���ջ���������
#define TXLOGLEN	100		//ken:����Ӧ�𻺳�������
//RF����ģ����ظ������Hashͷ
#define RFCMDHASHLEN	3	//RFCMD��Hashͷ����
#define RFCMD_CNT	475		//����
#define RFCMD_CNS	472		//����
#define RFCMD_HRB	434		//������
#define RFCMD_TMP	789		//�¶Ȳɼ�

extern uint8_t   SPI1OkFlag;	//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
extern uint8_t   SPI2OkFlag;
extern uint8_t	SPI1NewFlg;		//SPI1�յ�������
extern uint8_t	SPI2NewFlg;		//SPI2�յ�������
           
extern uint8_t   SPI1ProtocolFlag;
extern uint8_t   SPI1FullFlag;
extern u8				 SPI2FullFlag;        //���ջ���������־λ
//extern uint8_t pdata txIndex;
extern uint8_t	SPI1index;
extern uint8_t  SPI1Pindex;
extern uint8_t  SPI2index;		 
extern uint8_t  SPI2Pindex;        
extern uint8_t  SPI1_ParseBuf[SPI1PARSEBUFLEN];
extern uint8_t  SPI2_ParseBuf[SPI2PARSEBUFLEN];
extern uint8_t  txLog[TXLOGLEN];

extern uint8_t  SPI1ByteNum;
//---------------------------------------------------------------//
void SPI1Rx_Parse(void);
void SPI2Rx_Parse(void);



/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


