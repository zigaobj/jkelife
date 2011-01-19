
#ifndef _24L01APP_H_
#define _24L01APP_H_

#define CMD_MAXRESEND	20		//命令重发最大次数
#define CMD_NUMLMT 5			//最多能同时处理的命令个数
#define NETCNT_TIMEOUT	10000	//组网退网状态超时为10S 测试时设置为1S
#define DATARECEIVE_SPAN	200	//Data接收数据阶段，接收通道Rx_P1~5切换时间间隔
#define CMD_BUF_LEN	32
#define CMD_HEADER_LEN 3
#define CMD_OTHERS_START 6
#define CMD_OTHERS_LEN	19	

typedef union _CMD_BODY_TypeDef{
	uint8_t all[CMD_BUF_LEN];	//ken:保存整个命令数据段
	struct {
		uint8_t		CmdStartByte;					//JK命令起始符'#'	
		uint8_t		Header[CMD_HEADER_LEN];			//命令头，XXX
		uint8_t		Dot1;							//命令头后第1个','号
		uint8_t		NetNum;							//命令
		uint8_t		Dot2;							//命令头后第2个','号
		uint8_t		Adr[RX_ADR_WIDTH_24L01];		//从模块地址
		uint8_t		Dot3;							//命令头后第3个','号
		uint8_t 	Others[CMD_OTHERS_LEN];			//命令数据里面的其余字符
	}part;
}CMD_BODY_TypeDef;


// 自定义共用体命令接收处理数据类型 CMD_BUF
typedef struct _CMD_BUF_TypeDef{				
 	CMD_BODY_TypeDef * pCmd_Body;			//指向待处理的命令处理缓冲区
	CMD_BODY_TypeDef * pReplyBuf;			//应答缓冲区		
//	uint16_t 	HeadHash;					//计算出来的Hash头，用于散转
	uint8_t		CmdTxFlag[CMD_NUMLMT];		//命令发送状态
	uint8_t		CmdListNum;					//待处理的命令数
	uint8_t		CmdListFlag[CMD_NUMLMT];	//记录命令处理缓冲区使用情况
			
}CMD_BUF_TypeDef;	
extern CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//命令数据体
extern CMD_BUF_TypeDef CmdBuf;	//命理处理缓冲区
extern CMD_BUF_TypeDef * pCmdBuf;	//指向命理处理缓冲区




uint8_t HeartBeat(uint8_t * pHeartBeatAdr);
uint8_t NewConnect(uint8_t * pNewAdr);
void CheckConnect(void);
void FreHopping(uint8_t SPIx , uint8_t Fre);
void RandomDelayUs(void);
void NetConnect(bool Sta);
void SysRun(void);
void SPI2_CMDCNT(uint8_t stacnt);
void Synchronize(void);
void DataReceive(void);
void DataSend(void);
void Broadcast(uint8_t * TxStr);

#endif
