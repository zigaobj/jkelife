#ifndef _SPICOM_H_
#define _SPICOM_H_
//---------------------------------------------------------------//
#define SPI1PARSEBUFLEN	320		//ken:串口接收缓冲区长度
#define SPI2PARSEBUFLEN 320		//串口1接收缓冲区长度
#define TXLOGLEN	100		//ken:串口应答缓冲区长度
//RF无线模块相关各命令的Hash头
#define RFCMDHASHLEN	3	//RFCMD的Hash头长度
#define RFCMD_CNT	475		//组网
#define RFCMD_CNS	472		//组网
#define RFCMD_HRB	434		//心跳包
#define RFCMD_TMP	789		//温度采集

extern uint8_t   SPI1OkFlag;	//收到一条完整的命令则自加1，数值表示当前待处理的命令数。
extern uint8_t   SPI2OkFlag;
extern uint8_t	SPI1NewFlg;		//SPI1收到新数据
extern uint8_t	SPI2NewFlg;		//SPI2收到新数据
           
extern uint8_t   SPI1ProtocolFlag;
extern uint8_t   SPI1FullFlag;
extern u8				 SPI2FullFlag;        //接收缓冲区满标志位
//extern uint8_t pdata txIndex;
extern uint8_t	SPI1index;
extern uint8_t  SPI1Pindex;
extern uint8_t  SPI2index;		 
extern uint8_t  SPI2Pindex;        
extern uint8_t  SPI1_ParseBuf[SPI1PARSEBUFLEN];
extern uint8_t  SPI2_ParseBuf[SPI2PARSEBUFLEN];
extern uint8_t  txLog[TXLOGLEN];

extern uint8_t  SPI1ByteNum;
//---------------------------------------------------------------//
void SPI1Rx_Parse(void);
void SPI2Rx_Parse(void);



/*
extern void Uart0_Tx_End(uint8_t *string);
extern void Uart0_Tx(uint8_t *string, uint16_t snum);
extern void Uart0_Rx_Parse();

void Uart1_Rx_Parse();
void Uart1_Tx(uint8_t *string, uint16_t snum);
*/
#endif


