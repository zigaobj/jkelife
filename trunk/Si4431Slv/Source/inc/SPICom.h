#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPIBUFLEN 32
#define SPI1PARSEBUFLEN	160		//ken:串口接收缓冲区长度
#define SPI2PARSEBUFLEN 32		//串口1接收缓冲区长度
//#define TXLOGLEN	100		//ken:串口应答缓冲区长度
//RF无线模块相关各命令的Hash头
#define RFCMDHASHLEN	3	//RFCMD的Hash头长度
#define RFCMD_CNT	475		//组网
#define RFCMD_HRB	411		//心跳包
#define RFCMD_TMP	789		//温度采集
#define RFCMD_NTA	441		//组网确认命令
#define RFCMD_SYN 324		//同步命令


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



/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


