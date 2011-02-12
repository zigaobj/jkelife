

#ifndef _24L01API_H_
#define _24L01API_H_

#define MASK_TX_STA		0x30
#define MASK_RX_P_NO	0x0E
#define	RX_DR	0x40
#define	TX_DS	0x20
#define	MAX_RT	0x10
/*********************************************NRF24L01*************************************/
#define TX_ADR_WIDTH_24L01    5   	// 5 uints TX address width
#define RX_ADR_WIDTH_24L01    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH_24L01  32  	// 20 uints TX payload
#define RX_PLOAD_WIDTH_24L01  32  	// 20 uints TX payload

/***************************************NRF24L01寄存器指令*******************************************************/
#define READ_REG_24L01        0x00  	// 读寄存器指令
#define WRITE_REG_24L01       0x20 	    // 写寄存器指令
#define RD_RX_PLOAD_24L01     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD_24L01     0xA0  	// 写待发数据指令
#define FLUSH_TX_24L01        0xE1 	    // 冲洗发送 FIFO指令
#define FLUSH_RX_24L01        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL_24L01     0xE3  	// 定义重复装载数据指令
#define NOP_24L01             0xFF  	// 保留
/*************************************SPI(nRF24L01)寄存器地址****************************************************/
#define CONFIG_24L01          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA_24L01           0x01  // 自动应答功能设置
#define EN_RXADDR_24L01       0x02  // 可用信道设置
#define SETUP_AW_24L01        0x03  // 收发地址宽度设置
#define SETUP_RETR_24L01      0x04  // 自动重发功能设置
#define RF_CH_24L01           0x05  // 工作频率设置
#define RF_SETUP_24L01        0x06  // 发射速率、功耗功能设置
#define STATUS_24L01          0x07  // 状态寄存器
#define OBSERVE_TX_24L01      0x08  // 发送监测功能
#define CD_24L01              0x09  // 地址检测           
#define RX_ADDR_P0_24L01      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1_24L01      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2_24L01      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3_24L01      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4_24L01      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5_24L01      0x0F  // 频道5接收数据地址
#define TX_ADDR_24L01         0x10  // 发送地址寄存器
#define RX_PW_P0_24L01        0x11  // 接收频道0接收数据长度
#define RX_PW_P1_24L01        0x12  // 接收频道0接收数据长度
#define RX_PW_P2_24L01        0x13  // 接收频道0接收数据长度
#define RX_PW_P3_24L01        0x14  // 接收频道0接收数据长度
#define RX_PW_P4_24L01        0x15  // 接收频道0接收数据长度
#define RX_PW_P5_24L01        0x16  // 接收频道0接收数据长度
#define FIFO_STATUS_24L01     0x17  // FIFO栈入栈出状态寄存器设置

//********************************自定义******************************
#define RX_P0_24L01      0x00  // 频道0
#define RX_P1_24L01      0x01  // 频道1
#define RX_P2_24L01      0x02  // 频道2
#define RX_P3_24L01      0x03  // 频道3
#define RX_P4_24L01      0x04  // 频道4
#define RX_P5_24L01      0x05  // 频道5

#define DEFAULT_FRE		0x28   //默认频率

#define RXADRTABLEN	6	//从地址空间大小	//暂定一个网最大支持255个从模块
#define MAXMISSHEART 5	//最大心跳包丢包个数 
typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_RxAdrTab_TypeDef
{
	u8	RxAdrTabCnt;	//记录已使用的地址空间个数
	u8 * pRxAdrTabCnt;	//指向空的接收地址表格空间。
	u8 TabIndex;		//标志发送地址
	u8 TabFlag[RXADRTABLEN];	//记录地址空间使用情况索引,0x00:未使用或断开连接了，0x01:正常组网，从TabFlag[1]开始记录 
	u8 HeartBeatSta[RXADRTABLEN];		//从HeartBeatSta[1]开始保存从模块心跳包个数，监听连接状态
//	u8 RxPnSequence[RXADRTABLEN];		//接收通道次序
	u8 RxAdrIndex;		//接收模块地址计数
	u8 * pCmdTxBuf[RXADRTABLEN];		//指向组网后的从模块待发送命令空间
	u8 RxAdrTab0[RX_ADR_WIDTH_24L01];	//RxAdrTab0[]不存从模块地址，
	u8 RxAdrTab1[RX_ADR_WIDTH_24L01];	//从RxAdrTab1[]开始存储从模块地址
	u8 RxAdrTab2[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab3[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab4[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab5[RX_ADR_WIDTH_24L01];
	u8 RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH_24L01];
}RxAdrTab_TypeDef;	//记录组网从模块的地址



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;

/*************************变量声明*****************************************************/
extern u8   sta;   //状态标志
extern u8	SPI1FIFOSta,SPI1Sta;
//extern u8	SPI2FIFOSta,SPI2Sta;	//SPI2负责接收的24L01的FIFO与STATUS,SPI2RxCnt计数进入RX次数
extern u8	SPI2RxCnt,SPI1RxCnt;
extern const u8 NetConnectRxAdr[RX_ADR_WIDTH_24L01];		//广播接收地址
extern const u8 TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01];	//接收地址

extern const u8 MOD1_TXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD1_RXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD2_TXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD2_RXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD3_TXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD3_RXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD4_TXADR[TX_ADR_WIDTH_24L01];	//本地地址
extern const u8 MOD4_RXADR[TX_ADR_WIDTH_24L01];	//本地地址

extern @near u8 Net_TXADR[TX_ADR_WIDTH_24L01];	//新组网地址	
extern @near u8 Net_RXADR[TX_ADR_WIDTH_24L01];	//新组网地址

/*************************函数声明*****************************************************/
void Init_NRF24L01_SPI1(void);
//void Init_NRF24L01_SPI2(void);
u8 SPI1_RW(u8 string);
u8 SPI1_Read(u8 reg);
//void SetSPI1_BroadCast(void);
void SetSlv_RxMode(unsigned char * RX_ADR);
void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR);
void SetSPI1_TXMode(unsigned char* pTX_ADR);
u8 SPI1_RW_Reg(u8 reg, u8 value);
u8 SPI1_Read_Buf(u8 reg, u8 *pBuf, u8 strlen);
u8 SPI1_Write_Buf(u8 reg, u8 *pBuf, u8 strlen);
unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf);
void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf);





#endif

