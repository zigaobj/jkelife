#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPIBUFLEN 32
#define SPI1PARSEBUFLEN	160		//ken:串口接收缓冲区长度
//#define SPI2PARSEBUFLEN 32		//串口1接收缓冲区长度
//#define TXLOGLEN	100		//ken:串口应答缓冲区长度
//RF无线模块相关各命令的Hash头
#define RFCMDHASHLEN	3	//RFCMD的Hash头长度
#define RFCMD_CNT	475		//组网
#define RFCMD_HRB	411		//心跳包
#define RFCMD_TMP	789		//温度采集
#define RFCMD_NTA	441		//组网确认命令
#define RFCMD_SYN 324		//同步命令

#define CMDSPI_HASH_NETCNT	0x065E

#define CMDSPI_HASHLEN			3				//命令hash头长度
#define CMDSPI_HEADER_LEN		6				//
#define CMDSPI_ADR_WIDTH			8				//命令中的地址长度
#define CMDSPI_TOTAL_LEN			3	
#define CMDSPI_TAIL_LEN			5
#define CMDSPI_LEN_CNT				12			//命令有效数据开始位置

#define CMDSPI_OTHERS_START 	26
#define CMDSPI_OTHERS_LEN			34
#define CMDSPI_BODY_LEN		60
#define CMDSPI_BUF_LEN				80			//命令缓冲区长度
#define CMDSPI_TXLIST_LMT		3				//待发送的命令最大数
#define CMDSPI_RXLIST_LMT		3				//待处理的命令最大数


 /* Typedef ------------------------------------------------------------------*/
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
//		u8	CmdType;											//命令类型：1表示接收待处理命令，2表示待发送命令
		u16	HeaderHash;										//发射头的Hash值
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
//	CMDSPI_BODY_TypeDef * pReplyBuf;							//应答缓冲区			
}CMDSPI_BUF_TypeDef;



/* Extern ------------------------------------------------------------------*/
//extern CMD_BODY_TypeDef Cmd_Body[CMD_RXLIST_LMT];	//命令数据体
//extern CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
//extern CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区

extern CMDSPI_BUF_TypeDef 	CmdSpiTxBuf;									//命令发送缓冲区
extern CMDSPI_BUF_TypeDef * pCmdSpiTxBuf;								//指向命令发送缓冲区
extern CMDSPI_BUF_TypeDef		CmdSpiRxBuf;									//命令接收缓冲区
extern CMDSPI_BUF_TypeDef * pCmdSpiRxBuf;								//指向命令接收缓冲区
extern CMDSPI_BODY_TypeDef  ReplyBuf;								//应答缓冲区
extern CMDSPI_BODY_TypeDef * pReplyBuf;								//应答缓冲区
				 
struct CMD_END{
	u8 cCR;
	u8 cLF;
};



extern @near u8 SPI1OkFlag;	//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
//extern @near u8 SPI2OkFlag;
extern @near u8 SPI1NewFlg;		//SPI1收到新数据
//extern @near u8 SPI2NewFlg;		//SPI2收到新数据
           
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
void CmdSpiSearch(CMDSPI_BODY_TypeDef *pCmdData);
/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


