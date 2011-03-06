#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPIBUFLEN 32
#define SPI1PARSEBUFLEN	160		//ken:���ڽ��ջ���������
//#define SPI2PARSEBUFLEN 32		//����1���ջ���������
//#define TXLOGLEN	100		//ken:����Ӧ�𻺳�������
//RF����ģ����ظ������Hashͷ
#define RFCMDHASHLEN	3	//RFCMD��Hashͷ����
#define RFCMD_CNT	475		//����
#define RFCMD_HRB	411		//������
#define RFCMD_TMP	789		//�¶Ȳɼ�
#define RFCMD_NTA	441		//����ȷ������
#define RFCMD_SYN 324		//ͬ������

#define CMDSPI_HASH_NETCNT	0x065E

#define CMDSPI_HASHLEN			3				//����hashͷ����
#define CMDSPI_HEADER_LEN		6				//
#define CMDSPI_ADR_WIDTH			8				//�����еĵ�ַ����
#define CMDSPI_TOTAL_LEN			3	
#define CMDSPI_TAIL_LEN			5
#define CMDSPI_LEN_CNT				12			//������Ч���ݿ�ʼλ��

#define CMDSPI_OTHERS_START 	26
#define CMDSPI_OTHERS_LEN			64
#define CMDSPI_BUF_LEN				100			//�����������
#define CMDSPI_TXLIST_LMT		3				//�����͵����������
#define CMDSPI_RXLIST_LMT		3				//����������������


 /* Typedef ------------------------------------------------------------------*/
typedef union _CMDSPI_BODY_TypeDef{
	u8 all[CMDSPI_BUF_LEN];	//ken:���������������ݶ�
	struct {
		u8	CmdStartByte;									//������ʼ��'#'		
		u8	Header[CMDSPI_HEADER_LEN];				//������hash���֣�XXXXXX
		u8	Dot0;													//����ͷ���1��','��
		u8	SourceAdr[CMDSPI_ADR_WIDTH];			//Դ��ַ(8�ֽ�)
		u8	Dot1;													//����ͷ���2��','��
		u8	TargetAdr[CMDSPI_ADR_WIDTH];			//Ŀ���ַ(8�ֽ�)
		u8	Dot2;													//����ͷ���3��','��						
//		u8	CmdTotalLen[CMD_TOTAL_LEN];	//��������ȣ�������$��\n
//		u8	Dot3;												//����ͷ���4��','��
		u8	Others[CMDSPI_OTHERS_LEN];				//���������
//		u8	CmdType;											//�������ͣ�1��ʾ���մ��������2��ʾ����������
		u16	HeaderHash;										//����ͷ��Hashֵ
		u16	TotalLength;									//�����
	}part;
	
}CMDSPI_BODY_TypeDef;

// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMDSPI_BUF_TypeDef{				
		
//	uint16_t 	HeadHash;											//���������Hashͷ������ɢת
//	u8		CmdTxFlag[CMD_LISTLMT];						//�����״̬
	u8		CmdListNum;													//��������������
	u8		CmdCurrentList;											//��ǰ���յ�����λ��
	u8		CmdPrcList;													//��ǰ���������λ��
	u8		CmdListFlag[CMDSPI_RXLIST_LMT];						//��¼�������ʹ�������0��ʾ��Ӧ�����գ�1��ʾ�������д����������
 	CMDSPI_BODY_TypeDef * pCmd_Prc_Current;			//ָ�����е����������
	CMDSPI_BODY_TypeDef * pCmd_Body_Current;			//ָ���Ŵ���������������
	CMDSPI_BODY_TypeDef	 Cmd_Body[CMDSPI_RXLIST_LMT];	//�������ռ�
//	CMDSPI_BODY_TypeDef * pReplyBuf;							//Ӧ�𻺳���			
}CMDSPI_BUF_TypeDef;



/* Extern ------------------------------------------------------------------*/
//extern CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//����������
//extern CMD_BUF_TypeDef CmdBuf;	//����������
//extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

extern CMDSPI_BUF_TypeDef 	CmdSpiTxBuf;									//����ͻ�����
extern CMDSPI_BUF_TypeDef * pCmdSpiTxBuf;								//ָ������ͻ�����
extern CMDSPI_BUF_TypeDef		CmdSpiRxBuf;									//������ջ�����
extern CMDSPI_BUF_TypeDef * pCmdSpiRxBuf;								//ָ��������ջ�����
extern CMDSPI_BODY_TypeDef  ReplyBuf;								//Ӧ�𻺳���
extern CMDSPI_BODY_TypeDef * pReplyBuf;								//Ӧ�𻺳���
				 
struct CMD_END{
	u8 cCR;
	u8 cLF;
};



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

u16 CmdSpiReplyAppend(CMDSPI_BODY_TypeDef *pRplyStr);
u8 CmdSpiTxApply(bool sta ,u8 * cmddata ,u16 cmdlen);
u8 CmdSpiRxApply(u8 * cmddata ,u16 cmdlen);

u8 CmdFuncNETCNT(CMDSPI_BODY_TypeDef * pCmdData);
void CmdSpiExecute(void);

/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


