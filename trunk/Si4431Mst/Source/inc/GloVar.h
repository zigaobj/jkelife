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


//#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
//#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload



//串口相关各命令的Hash头
#define UCMDHASHLEN	6	//UCMD的Hash头长度
#define UCMD_NETCNT		0x065E	//NETCNT
#define UCMD_PSWCTL		0x0371	//PSWCTL

//Si4431地址长度
#define SI4431_ADR_WIDTH    4   	// 4 uints TX address width
//#define Si4431_TXADR_WIDTH    4   	// 4 uints TX address width
//#define Si4431_RXADR_WIDTH    4   	// 4 uints RX address width



#define CMD_MAXRESEND			5				//命令重发最大次数
#define NETCNT_TIMEOUT		1000		//组网退网状态超时为10S 测试时设置为1S
#define DATARECEIVE_SPAN	200			//Data接收数据阶段，接收通道Rx_P1~5切换时间间隔


/*************************变量声明*****************************************************/
extern uint8_t   sta;   //状态标志	
extern uint8_t	SPI1FIFOSta,SPI1Sta1,SPI1Sta2;
extern uint8_t	SPI2FIFOSta,SPI2Sta1,SPI2Sta2;	//SPI2负责接收的24L01的FIFO与STATUS,SPI2RxCnt计数进入RX次数
extern uint8_t	TXItSta1,TXItSta2;
extern uint8_t	RXItSta1,RXItSta2;


extern uint16_t	SPI2RxCnt,SPI1RxCnt;
extern uint8_t NetConnectRxAdr[SI4431_ADR_WIDTH];		//广播接收地址
extern uint8_t TX_ADDRESS_Si4431[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t RX_ADDRESS_Si4431[SI4431_ADR_WIDTH];	//接收地址

extern uint8_t MOD1_TXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD1_RXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD2_TXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD2_RXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD3_TXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD3_RXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD4_TXADR[SI4431_ADR_WIDTH];	//本地地址
extern uint8_t MOD4_RXADR[SI4431_ADR_WIDTH];	//本地地址

extern u8 StrTest[16];

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


//extern u8 SPI1_TxBuf[SPIBUFLEN];
//extern u8 SPI2_TxBuf[SPIBUFLEN];
//extern u8 SPI1_RxBuf[SPIBUFLEN]; 
//extern u8 SPI2_RxBuf[SPIBUFLEN];
	




#define DEFAULT_FRE		0x28   //默认频率

#define JKNETADRTABLEN	6	//从地址空间大小	//暂定一个网最大支持255个从模块
#define MAXMISSHEART 5	//最大心跳包丢包个数 

typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_JKNetAdrTab_TypeDef
{
	uint8_t	JKNetAdrTabCnt;							//记录已使用的地址空间个数
	uint8_t * pJKNetAdrTabCnt;						//指向空的接收地址表格空间。
	uint8_t LoopJKNetAdrIndex;						//轮询接收地址
	uint8_t TabFlag[JKNETADRTABLEN];			//记录地址空间使用情况索引,0x00:未使用或断开连接了，0x01:正常组网，从TabFlag[1]开始记录 
	uint8_t HeartBeatSta[JKNETADRTABLEN];		//从HeartBeatSta[1]开始保存从模块心跳包个数，监听连接状态
//	uint8_t RxPnSequence[JKNetAdrTABLEN];		//接收通道次序
	uint8_t JKNetAdrIndex;		//接收模块地址计数
	uint8_t * pCmdTxBuf[JKNETADRTABLEN];		//指向组网后的从模块待发送命令空间
	uint8_t JKNetAdrTab0[SI4431_ADR_WIDTH];	//JKNetAdrTab0[]不存从模块地址，
	uint8_t JKNetAdrTab1[SI4431_ADR_WIDTH];	//从JKNetAdrTab1[]开始存储从模块地址
	uint8_t JKNetAdrTab2[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab3[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab4[SI4431_ADR_WIDTH];
	uint8_t JKNetAdrTab5[SI4431_ADR_WIDTH];
//	uint8_t JKNetAdrAll[JKNETADRTABLEN][SI4431_ADR_WIDTH];
}JKNetAdrTab_TypeDef;	//记录组网从模块的地址



extern JKNetAdrTab_TypeDef * pJKNetAdr_Tab;
extern JKNetAdrTab_TypeDef JKNetAdr_Tab;



#endif

