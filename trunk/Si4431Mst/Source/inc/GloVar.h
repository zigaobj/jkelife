#ifndef _GLOVAR_H_
#define _GLOVAR_H_

//#include "Global.h"

/* typedef -----------------------------------------------------------*/


/* define -----------------------------------------------------------*/
#define U1RXBUFLEN 250		//串口1接收缓冲区长度
#define U1TXBUFLEN 50		//串口1发送缓冲区长度
#define U2RXBUFLEN 50		//串口1接收缓冲区长度
#define U2TXBUFLEN 50		//串口1发送缓冲区长度
#define U1PARSEBUFLEN  50
#define U2PARSEBUFLEN  50

#define USARTBUFLEN	200

#define TX_ADR_WIDTH    4   	// 4 uints TX address width
#define RX_ADR_WIDTH    4   	// 4 uints RX address width
//#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
//#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload

#define CMD_MAXRESEND	5		//命令重发最大次数
#define CMD_NUMLMT 5			//最多能同时处理的命令个数
#define NETCNT_TIMEOUT	1000	//组网退网状态超时为10S 测试时设置为1S
#define DATARECEIVE_SPAN	200	//Data接收数据阶段，接收通道Rx_P1~5切换时间间隔
#define CMD_BUF_LEN	32
#define CMD_HEADER_LEN 3
#define CMD_OTHERS_START 6
#define CMD_OTHERS_LEN	19

//串口相关各命令的Hash头
#define UCMDHASHLEN	6	//UCMD的Hash头长度
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL


/*************************变量声明*****************************************************/
extern uint8_t   sta;   //状态标志	
extern uint8_t	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
extern uint8_t	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;	//SPI2负责接收的24L01的FIFO与STATUS,SPI2RxCnt计数进入RX次数
extern uint8_t	TXItSta1,TXItSta2;
extern uint8_t	RXItSta1,RXItSta2;


extern uint16_t	SPI2RxCnt,SPI1RxCnt;
extern uint8_t NetConnectRxAdr[RX_ADR_WIDTH];		//广播接收地址
extern uint8_t TX_ADDRESS_24L01[TX_ADR_WIDTH];	//本地地址
extern uint8_t RX_ADDRESS_24L01[RX_ADR_WIDTH];	//接收地址

extern uint8_t MOD1_TXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD1_RXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD2_TXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD2_RXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD3_TXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD3_RXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD4_TXADR[TX_ADR_WIDTH];	//本地地址
extern uint8_t MOD4_RXADR[TX_ADR_WIDTH];	//本地地址

extern uint8_t U1RxCmdFlag;		//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
extern uint8_t U2RxCmdFlag;
//uint8_t U1NewFlag;		//SPI1收到新数据
//uint8_t U2NewFlag;		//SPI2收到新数据
           
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



	

typedef union _CMD_BODY_TypeDef{
	uint8_t all[CMD_BUF_LEN];	//ken:保存整个命令数据段
	struct {
		uint8_t		CmdStartByte;					//JK命令起始符'#'	
		uint8_t		Header[CMD_HEADER_LEN];			//命令头，XXX
		uint8_t		Dot1;							//命令头后第1个','号
		uint8_t		NetNum;							//命令
		uint8_t		Dot2;							//命令头后第2个','号
		uint8_t		Adr[RX_ADR_WIDTH];		//从模块地址
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


#define DEFAULT_FRE		0x28   //默认频率

#define RXADRTABLEN	6	//从地址空间大小	//暂定一个网最大支持255个从模块
#define MAXMISSHEART 5	//最大心跳包丢包个数 
typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_RxAdrTab_TypeDef
{
	uint8_t	RxAdrTabCnt;							//记录已使用的地址空间个数
	uint8_t * pRxAdrTabCnt;						//指向空的接收地址表格空间。
	uint8_t LoopRxAdrIndex;						//轮询接收地址
	uint8_t TabFlag[RXADRTABLEN];			//记录地址空间使用情况索引,0x00:未使用或断开连接了，0x01:正常组网，从TabFlag[1]开始记录 
	uint8_t HeartBeatSta[RXADRTABLEN];		//从HeartBeatSta[1]开始保存从模块心跳包个数，监听连接状态
//	uint8_t RxPnSequence[RXADRTABLEN];		//接收通道次序
	uint8_t RxAdrIndex;		//接收模块地址计数
	uint8_t * pCmdTxBuf[RXADRTABLEN];		//指向组网后的从模块待发送命令空间
	uint8_t RxAdrTab0[RX_ADR_WIDTH];	//RxAdrTab0[]不存从模块地址，
	uint8_t RxAdrTab1[RX_ADR_WIDTH];	//从RxAdrTab1[]开始存储从模块地址
	uint8_t RxAdrTab2[RX_ADR_WIDTH];
	uint8_t RxAdrTab3[RX_ADR_WIDTH];
	uint8_t RxAdrTab4[RX_ADR_WIDTH];
	uint8_t RxAdrTab5[RX_ADR_WIDTH];
	uint8_t RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH];
}RxAdrTab_TypeDef;	//记录组网从模块的地址



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;



#endif

