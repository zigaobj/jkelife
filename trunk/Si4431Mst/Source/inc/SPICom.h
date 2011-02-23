#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPI1PARSEBUFLEN	200		//ken:���ڽ��ջ���������
#define SPI2PARSEBUFLEN 200		//����1���ջ���������
#define SPIBUFLEN	128

#define TXLOGLEN	100		//ken:����Ӧ�𻺳�������
//RF����ģ����ظ������Hashͷ
#define RFCMDHASHLEN	3	//RFCMD��Hashͷ����
#define RFCMD_CNT	475		//����
#define RFCMD_CNS	472		//����
#define RFCMD_HRB	434		//������
#define RFCMD_TMP	789		//�¶Ȳɼ�

/* Define ------------------------------------------------------------*/

#define CMDSPI_HASH_NETCNT	0x065E
#define CMDSPI_HASH_STT	0x02FC
#define CMDSPI_HASH_RST	0x045D
#define CMDSPI_HASH_SUV	0x0402
#define CMDSPI_HASH_SYS	0x0689
#define CMDSPI_HASH_UPD	0x0370
#define CMDSPI_HASH_RNG	0x04A2
#define CMDSPI_HASH_CHN	0x01EC
#define CMDSPI_HASH_FRQ	0x04D2
#define CMDSPI_HASH_TXW	0x043C
#define CMDSPI_HASH_GAN	0x0470
#define CMDSPI_HASH_PWR	0x048B
#define CMDSPI_HASH_SEN	0x044E
#define CMDSPI_HASH_TVG	0x0424
#define CMDSPI_HASH_TRK	0x0440
#define CMDSPI_HASH_REG	0x0540
#define CMDSPI_HASH_JMP	0x049F

#define CMDSPI_HASHLEN			3				//����hashͷ����
#define CMDSPI_HEADER_LEN		6				//
#define CMDSPI_ADR_WIDTH			8				//�����еĵ�ַ����
#define CMDSPI_TOTAL_LEN			3	
#define CMDSPI_TAIL_LEN			5
#define CMDSPI_LEN_CNT				12			//������Ч���ݿ�ʼλ��

#define CMDSPI_OTHERS_START 	6
#define CMDSPI_OTHERS_LEN		19
#define CMDSPI_BUF_LEN				270			//�����������
#define CMDSPI_TXLIST_LMT		5				//�����͵����������
#define CMDSPI_RXLIST_LMT		5				//����������������






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
		u8	CmdType;											//�������ͣ�1��ʾ���մ��������2��ʾ����������
		u16	TotalLength;									//�����
	}part;
	
}CMDSPI_BODY_TypeDef;

// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMDSPI_BUF_TypeDef{				
		
//	uint16_t 	HeadHash;															//���������Hashͷ������ɢת
//	u8		CmdTxFlag[CMD_LISTLMT];										//�����״̬
	u8		CmdListNum;																	//��������������
	u8		CmdCurrentList;															//��ǰ���յ�����λ��
	u8		CmdPrcList;																	//��ǰ���������λ��
	u8		CmdListFlag[CMDSPI_RXLIST_LMT];							//��¼�������ʹ�������0��ʾ��Ӧ�����գ�1��ʾ�������д����������,2��ʾ�����ѷ��͵ȴ��ظ�
 	CMDSPI_BODY_TypeDef * pCmd_Prc_Current;						//ָ�����е����������
	CMDSPI_BODY_TypeDef * pCmd_Body_Current;					//ָ���Ŵ���������������
	CMDSPI_BODY_TypeDef	 Cmd_Body[CMDSPI_RXLIST_LMT];	//�������ռ�
				
}CMDSPI_BUF_TypeDef;


//extern CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//����������
//extern CMD_BUF_TypeDef CmdBuf;	//����������
//extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

extern CMDSPI_BUF_TypeDef 	CmdSpiTxBuf;									//����ͻ�����
extern CMDSPI_BUF_TypeDef * pCmdSpiTxBuf;								//ָ������ͻ�����
extern CMDSPI_BUF_TypeDef		CmdSpiRxBuf;									//������ջ�����
extern CMDSPI_BUF_TypeDef * pCmdSpiRxBuf;								//ָ��������ջ�����
				 
struct CMD_END{
	u8 cCR;
	u8 cLF;
};

u8 CmdFuncNETCNT(CMDSPI_BODY_TypeDef * pCmdData);



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

void SPI1Rx_Parse(void);
void SPI2Rx_Parse(void);
//---------------------------------------------------------------//


/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


