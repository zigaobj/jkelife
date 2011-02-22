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
//#define CMDSPI_HASH_LEN			3				//命令hash头长度
//#define CMDSPI_HEADER_LEN		6				//
//#define CMDSPI_ADR_WIDTH			8				//命令中的地址长度
//#define CMDSPI_TOTAL_LEN			3	
//#define CMDSPI_TAIL_LEN			5
//#define CMDSPI_LEN_CNT				12			//命令有效数据开始位置
//
//#define CMDSPI_OTHERS_START 	6
//#define CMDSPI_OTHERS_LEN		19
//#define CMDSPI_BUF_LEN				270			//命令缓冲区长度
//#define CMDSPI_TXLIST_LMT		5				//待发送的命令最大数
//#define CMDSPI_RXLIST_LMT		5				//待处理的命令最大数
//
//#define CMD_MAXRESEND			5				//命令重发最大次数
//#define NETCNT_TIMEOUT		1000		//组网退网状态超时为10S 测试时设置为1S
//#define DATARECEIVE_SPAN	200			//Data接收数据阶段，接收通道Rx_P1~5切换时间间隔




 /* Typedef ------------------------------------------------------------------*/
//通讯数据命令的通道类型( USART,SPI,USB)
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
	u8 all[CMDSPI_BUF_LEN];	//ken:保存整个命令数据段
	struct {
		u8	CmdStartByte;									//命令起始符'#'		
		u8	Header[CMDSPI_HEADER_LEN];				//命令名hash部分，XXXXXX
		u8	Dot0;													//命令头后第1个','号
		u8	SourceAdr[CMDSPI_ADR_WIDTH];			//源地址(8字节)
		u8	Dot1;													//命令头后第2个','号
		u8	TargetAdr[CMDSPI_ADR_WIDTH];			//目标地址(8字节)
		u8	Dot2;													//命令头后第3个','号						
//		u8	CmdTotalLen[CMD_TOTAL_LEN];	//整条命令长度，包括从$到\n
//		u8	Dot3;												//命令头后第4个','号
		u8	Others[CMDSPI_OTHERS_LEN];				//命令参数体
		u8	CmdType;											//命令类型：1表示接收待处理命令，2表示待发送命令
		u16	TotalLength;									//命令长度
	}part;
	
}CMDSPI_BODY_TypeDef;

// 自定义共用体命令接收处理数据类型 CMD_BUF
typedef struct _CMDSPI_BUF_TypeDef{				
		
//	uint16_t 	HeadHash;											//计算出来的Hash头，用于散转
//	u8		CmdTxFlag[CMD_LISTLMT];						//命令发送状态
	u8		CmdListNum;													//待处理的命令个数
	u8		CmdCurrentList;											//当前接收的命令位置
	u8		CmdPrcList;													//当前处理的命令位置
	u8		CmdListFlag[CMDSPI_RXLIST_LMT];						//记录命令处理缓冲使用情况，0表示对应索引空，1表示索引内有待处理的命令
 	CMDSPI_BODY_TypeDef * pCmd_Prc_Current;			//指向处理中的命令处理缓冲区
	CMDSPI_BODY_TypeDef * pCmd_Body_Current;			//指向存放待处理的命令处理缓冲区
	CMDSPI_BODY_TypeDef	 Cmd_Body[CMDSPI_RXLIST_LMT];	//命令处理缓冲空间
	CMDSPI_BODY_TypeDef * pReplyBuf;							//应答缓冲区			
}CMDSPI_BUF_TypeDef;


//extern CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体
//extern CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
//extern CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

extern CMDSPI_BUF_TypeDef 	CmdSpiTxBuf;									//命令发送缓冲区
extern CMDSPI_BUF_TypeDef * pCmdSpiTxBuf;								//指向命令发送缓冲区
extern CMDSPI_BUF_TypeDef		CmdSpiRxBuf;									//命令接收缓冲区
extern CMDSPI_BUF_TypeDef * pCmdSpiRxBuf;								//指向命令接收缓冲区
				 
struct CMD_END{
	u8 cCR;
	u8 cLF;
};


// 01. STT命令数据结构-------------------------------------------
struct STT_basic {
	u8 State;
	u8 dot1;
	u8 Auto;					
};

union STT_DAT{
	u8 	all[sizeof(struct STT_basic)];
	struct 	STT_basic 		bit;
};

// 02. RNG命令数据结构-------------------------------------------
struct RNG_basic {
	u8 Auto;
	u8 dot1;
	u16 Range;					
};

union RNG_DAT{
	u8 	all[sizeof(struct RNG_basic)];
	struct 	RNG_basic 		bit;
};

// 03. SUV命令数据结构-------------------------------------------
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

// 04. SYS命令数据结构-------------------------------------------

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


// 05. CHN命令数据结构-------------------------------------------
struct CHN_basic {
	u8 ChnNum[2];
	u8 dot1;
	u8 ChnName[MAXCHNUM];					
};

union CHN_DAT{
	u8 	all[sizeof(struct CHN_basic)];
	struct 	CHN_basic 		bit;
};

// 06. FRQ命令数据结构-------------------------------------------
struct FRQ_basic {
	u8 Frequency[3];
	u8 dot1;
	u8 Draft[3];					
};

union FRQ_DAT{
	u8 	all[sizeof(struct FRQ_basic)];
	struct 	FRQ_basic 		bit;
};

// 07. SEN命令数据结构-------------------------------------------
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

//extern CMD_BODY_TypeDef Cmd_Body[CMD_LISTLMT];	//命令数据体
//extern CMDSPI_BUF_TypeDef CmdBuf;	//命理处理缓冲区
//extern CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

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
u8  CmdSpiApply(CMD_PORT_TPYE port ,u8 * cmddata ,u16 cmdlen);	//ken:建立命令索引函数
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

