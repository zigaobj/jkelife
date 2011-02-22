/***********************************************
*Copyright 2010,South Marine R&D Dpt.
*All rights reserved.
*
*File Name: CmdPrc.h
*ID       : 
*Abstract : Command Process Header File
*
*Version NO.:1.0
*Writer     :Ken
*Date       :2010-10-26
**************************************************/

#ifndef _CMDPRC_H_
#define _CMDPRC_H_

//#include "Global.h"

/* Define ------------------------------------------------------------*/

//#define CMD_HASH_JMP	0x049F
//#define CMD_HASH_STT	0x02FC
//#define CMD_HASH_RST	0x045D
//#define CMD_HASH_SUV	0x0402
//#define CMD_HASH_SYS	0x0689
//#define CMD_HASH_UPD	0x0370
//#define CMD_HASH_RNG	0x04A2
//#define CMD_HASH_CHN	0x01EC
//#define CMD_HASH_FRQ	0x04D2
//#define CMD_HASH_TXW	0x043C
//#define CMD_HASH_GAN	0x0470
//#define CMD_HASH_PWR	0x048B
//#define CMD_HASH_SEN	0x044E
//#define CMD_HASH_TVG	0x0424
//#define CMD_HASH_TRK	0x0440
//#define CMD_HASH_REG	0x0540
//#define CMD_HASH_JMP	0x049F
//
//#define CMDSPI_HASH_LEN			3				//����hashͷ����
//#define CMDSPI_HEADER_LEN		6				//
//#define CMDSPI_ADR_WIDTH			8				//�����еĵ�ַ����
//#define CMDSPI_TOTAL_LEN			3	
//#define CMDSPI_TAIL_LEN			5
//#define CMDSPI_LEN_CNT				12			//������Ч���ݿ�ʼλ��
//
//#define CMDSPI_OTHERS_START 	6
//#define CMDSPI_OTHERS_LEN		19
//#define CMDSPI_BUF_LEN				270			//�����������
//#define CMDSPI_TXLIST_LMT		5				//�����͵����������
//#define CMDSPI_RXLIST_LMT		5				//����������������
//
//#define CMD_MAXRESEND			5				//�����ط�������
//#define NETCNT_TIMEOUT		1000		//��������״̬��ʱΪ10S ����ʱ����Ϊ1S
//#define DATARECEIVE_SPAN	200			//Data�������ݽ׶Σ�����ͨ��Rx_P1~5�л�ʱ����




 /* Typedef ------------------------------------------------------------------*/
//ͨѶ���������ͨ������( USART,SPI,USB)
typedef enum _CMD_PORT_TPYE					
{	       
	Null_Cmd_Port			,
	Usart1_Cmd_TxPort		,
	Usart1_Cmd_RxPort		,
	Usart2_Cmd_TxPort		,
	Usart2_Cmd_RxPort		,
//	Usart3_Cmd_Port		,
	Spi1_Cmd_TxPort			,
	Spi1_Cmd_RxPort			,
	Spi2_Cmd_TxPort			,
	Spi2_Cmd_RxPort			,
//	UsbEpIn1_Cmd_Port	,
//	UsbEpIn2_Cmd_Port	,
//	UsbEpIn3_Cmd_Port			
} CMD_PORT_TPYE;


/*
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
		
//	uint16_t 	HeadHash;											//���������Hashͷ������ɢת
//	u8		CmdTxFlag[CMD_LISTLMT];						//�����״̬
	u8		CmdListNum;													//��������������
	u8		CmdCurrentList;											//��ǰ���յ�����λ��
	u8		CmdPrcList;													//��ǰ���������λ��
	u8		CmdListFlag[CMDSPI_RXLIST_LMT];						//��¼�������ʹ�������0��ʾ��Ӧ�����գ�1��ʾ�������д����������
 	CMDSPI_BODY_TypeDef * pCmd_Prc_Current;			//ָ�����е����������
	CMDSPI_BODY_TypeDef * pCmd_Body_Current;			//ָ���Ŵ���������������
	CMDSPI_BODY_TypeDef	 Cmd_Body[CMDSPI_RXLIST_LMT];	//�������ռ�
	CMDSPI_BODY_TypeDef * pReplyBuf;							//Ӧ�𻺳���			
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


// 01. STT�������ݽṹ-------------------------------------------
struct STT_basic {
	u8 State;
	u8 dot1;
	u8 Auto;					
};

union STT_DAT{
	u8 	all[sizeof(struct STT_basic)];
	struct 	STT_basic 		bit;
};

// 02. RNG�������ݽṹ-------------------------------------------
struct RNG_basic {
	u8 Auto;
	u8 dot1;
	u16 Range;					
};

union RNG_DAT{
	u8 	all[sizeof(struct RNG_basic)];
	struct 	RNG_basic 		bit;
};

// 03. SUV�������ݽṹ-------------------------------------------
struct SUV_basic {
	u8 Velocity[6];
	u8 dot1;
	u8 LowLmt[4];
	u8 dot2;	
	u8 DeepLmt[5];
	u8 dot3;
	u8 AlarmSw;
	u8 dot4;	
	u8 RefChn[2];						
};

union SUV_DAT{
	u8 	all[sizeof(struct SUV_basic)];
	struct 	SUV_basic 		bit;
};

// 04. SYS�������ݽṹ-------------------------------------------

struct SYS_basic {
	u8 FirmWare[6];
	u8 dot1;
	u8 HardWare[6];
	u8 dot2;
	u8 Serial[11];
	u8 dot3;	
	u8 DogID[10];
	u8 dot4;
	u8 SDE28M[6];						
};

union SYS_DAT{
	u8 	all[sizeof(struct SYS_basic)];
	struct 	SYS_basic 		bit;
};


// 05. CHN�������ݽṹ-------------------------------------------
struct CHN_basic {
	u8 ChnNum[2];
	u8 dot1;
	u8 ChnName[MAXCHNUM];					
};

union CHN_DAT{
	u8 	all[sizeof(struct CHN_basic)];
	struct 	CHN_basic 		bit;
};

// 06. FRQ�������ݽṹ-------------------------------------------
struct FRQ_basic {
	u8 Frequency[3];
	u8 dot1;
	u8 Draft[3];					
};

union FRQ_DAT{
	u8 	all[sizeof(struct FRQ_basic)];
	struct 	FRQ_basic 		bit;
};

// 07. SEN�������ݽṹ-------------------------------------------
struct SEN_basic {
	u8 Blank[4];
	u8 dot1;
	u8 Threshold[2];
	u8 dot2;
	u8 Filter; 					
};

union SEN_DAT{
	u8 	all[sizeof(struct SEN_basic)];
	struct 	SEN_basic 		bit;
};
*/


/* Extern ------------------------------------------------------------------*/
extern	u8	MsgReplyUNK[]	;

//extern CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//����������
//extern CMDSPI_BUF_TypeDef CmdBuf;	//����������
//extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

//extern union STT_DAT SttDat;
//extern union STT_DAT * pSttDat;
//extern union SUV_DAT	SuvDat;
//extern union SUV_DAT * pSuvDat;
////extern union SYS_DAT	SysDat;
////extern union SYS_DAT * pSysDat;
//extern union CHN_DAT	ChnDat;
//extern union CHN_DAT * pChnDat; 
//extern union FRQ_DAT	FrqDat;
//extern union FRQ_DAT * pFrqDat; 

/* Function Declare ------------------------------------------------------------------*/
u8  CmdSpiApply(CMD_PORT_TPYE port ,u8 * cmddata ,u16 cmdlen);	//ken:����������������
u8 	CmdOver(u8 CmdFg);

void CmdExecute(void);
/*
void CmdFuncSTT(CMD_BODY_TypeDef * pCmdSTTBody);
void CmdFuncRST(CMD_BODY_TypeDef * pCmdRSTBody);
void CmdFuncREG(CMD_BODY_TypeDef * pCmdREGBody);
void CmdFuncSYS(CMD_BODY_TypeDef * pCmdSYSBody);
//void CmdFuncUTB(CMD_BODY_TypeDef * pCmdUTBBody);
void CmdFuncRNG(CMD_BODY_TypeDef * pCmdRNGBody);
void CmdFuncSUV(CMD_BODY_TypeDef * pCmdSUVBody);
void CmdFuncCHN(CMD_BODY_TypeDef * pCmdCHNBody);
void CmdFuncFRQ(CMD_BODY_TypeDef * pCmdFRQBody);
void CmdFuncUPD(CMD_BODY_TypeDef * pCmdUPDBody);
void CmdFuncTXW(CMD_BODY_TypeDef * pCmdTXWBody);
void CmdFuncGAN(CMD_BODY_TypeDef * pCmdGANBody);
void CmdFuncPWR(CMD_BODY_TypeDef * pCmdPWRBody);
void CmdFuncSEN(CMD_BODY_TypeDef * pCmdSENBody);
void CmdFuncTVG(CMD_BODY_TypeDef * pCmdTVGBody);
void CmdFuncTRK(CMD_BODY_TypeDef * pCmdTRKBody);
*/
#endif 

/******************* (C) Copyright 2010,South Marine R&D Dpt. *****END OF FILE****/

