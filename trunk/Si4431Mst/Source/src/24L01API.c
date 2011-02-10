 /* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "24L01API.h"

///*********************Global Variable**************************************************************
uint8_t   sta;   //状态标志
uint8_t	volatile SPI1FIFOSta,SPI1Sta;
uint8_t	volatile SPI2FIFOSta,SPI2Sta;
uint16_t	SPI2RxCnt,SPI1RxCnt;
uint8_t NetConnectRxAdr[RX_ADR_WIDTH_24L01] = {0xA1,0x5C,0x00,0x00,0x01};	//广播接收地址
uint8_t TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01]= {0x18,0x42,0x31,0x10,0x01};	//本地地址
uint8_t RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01]= {0x33,0x43,0x10,0x16,0x28};	//接收地址

uint8_t MOD1_TXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x28,0x01};	//本地地址
uint8_t MOD1_RXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x28,0x01};	//本地地址
uint8_t MOD2_TXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	//本地地址
uint8_t MOD2_RXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	//本地地址
uint8_t MOD3_TXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//本地地址
uint8_t MOD3_RXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//本地地址
uint8_t MOD4_TXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	//本地地址
uint8_t MOD4_RXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	//本地地址



//保存各接收模块的地址。
RxAdrTab_TypeDef * pRxAdr_Tab;
RxAdrTab_TypeDef RxAdr_Tab;



//****************************************************************************************
//*负责发射的NRF24L01初始化
//***************************************************************************************/
void Init_NRF24L01_SPI1(void)
{	//uint8_t TmpSta;
//	SPI1_PWR_ON();
	
    DelayUs(1000);
//  	CE=0;    // chip enable
// 	CSN=1;   // Spi disable 
//	SCK=0;   // Spi clock line init high
	SPI1_CE_L;	//StandBy I模式
	SPI1_CSN_H;	//NSS拉高
	//																					// 如果作为发送方，则发送地址与接收地址要一致，因为ACK自动应答需要
//	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, MOD1_RXADR, TX_ADR_WIDTH_24L01);    // 写本地地址	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_RXADR, RX_ADR_WIDTH_24L01); // 写接收端地址
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x03);      //  全频道自动ACK应答允许	
//	TmpSta = SPI1_Read(EN_AA_24L01);	
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x03);  //  允许全部6个接收地址，如果需要多频道可以参考Page21  
//	TmpSta = SPI1_Read(EN_RXADDR_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_CH_24L01, DEFAULT_FRE);        //   设置信道工作为2.4GHZ，收发必须一致 	//跳频时候要改变
//	TmpSta = SPI1_Read(RF_CH_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RX_PW_P0_24L01, RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
//	TmpSta = SPI1_Read(RX_PW_P0_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_SETUP_24L01, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB	
//	TmpSta = SPI1_Read(RF_SETUP_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		 // 不响应发送中断，IRQ收发完成中断响应，16位CRC，上电，主发送
//	TmpSta = SPI1_Read(CONFIG_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0x70);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志

	DelayUs(100);
}

//****************************************************************************************
//*负责接收的NRF24L01初始化
//***************************************************************************************/
void Init_NRF24L01_SPI2(void)
{	//uint8_t TmpSta;
//	SPI2_PWR_ON();
	DelayUs(500);
// 	CE=0;    // chip enable
// 	CSN=1;   // Spi disable 
//	SCK=0;   // Spi clock line init high
	SPI2_CE_L;	//StandBy I模式
	SPI2_CSN_H;	//NSS拉高

//	SPI2_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, MOD1_TXADR , RX_ADR_WIDTH_24L01 );    // 写本地地址	
//	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_TXADR, TX_ADR_WIDTH_24L01); // 写接收端地址
	SPI2_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x3F);      //  频道1自动ACK应答允许	//  除去0通道外全频道自动ACK应答允许	
//	TmpSta = SPI2_Read(EN_AA_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x3F);  //  允许接收地址频道1， 	//  除去0通道外全频道允许接收 
//	TmpSta = SPI2_Read(EN_RXADDR_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RF_CH_24L01, DEFAULT_FRE);        //   设置信道工作为2.4GHZ，收发必须一致，F = 2400 + RF_CH (Mhz)
//	TmpSta = SPI2_Read(RF_CH_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P0_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P1_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P2_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P3_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P4_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P5_24L01,  RX_PLOAD_WIDTH_24L01); //设置接收数据长度，本次设置为32字节
	 
//	TmpSta = SPI2_Read(RX_PW_P0_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RF_SETUP_24L01, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB	
//	TmpSta = SPI2_Read(RF_SETUP_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   			//不响应发送中断， IRQ收发完成中断响应，16位CRC，上电，主接收
//	TmpSta = SPI2_Read(CONFIG_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0x70);   			//接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	SPI2_CE_H;	//RX模式
	DelayUs(200);
}

//****************************************************************************************************
//*函数：uint SPI1_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：NRF24L01的SPI写时序
//****************************************************************************************************/

uint8_t SPI1_RW(uint8_t uchar)
{
//	uint8_t bit_ctr;

	SPI_I2S_SendData(SPI1 , uchar);
    /* Wait for SPIz data reception */
//#ifdef nRF24L01_board
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	uchar = SPI_I2S_ReceiveData(SPI1);
/*
#else
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	uchar = SPI_I2S_ReceiveData(SPI2);

#endif
*/
	
/*  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (uchar & 0x80);         // output 'uchar', MSB to MOSI
		uchar = (uchar << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchar |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}*/
	

    return(uchar);           		  // return read uchar
}

//****************************************************************************************************
//*函数：uchar SPI_Read(uchar reg)
//*功能：NRF24L01的SPI时序
//****************************************************************************************************/

uint8_t SPI1_Read(uint8_t reg)
{
	uint8_t reg_val;
	SPI1_CSN_L;			//NSS拉低
//	CSN = 0;                // CSN low, initialize SPI communication...
	SPI1_RW(reg);            // Select register to read from..
	reg_val = SPI1_RW(0);    // ..then read registervalue
//	CSN = 1;                // CSN high, terminate SPI communication
	SPI1_CSN_H;			//NSS拉高，关闭SPI
	return(reg_val);        // return register value
}

//****************************************************************************************************/
//*功能：NRF24L01读写寄存器函数
//****************************************************************************************************/

uint8_t SPI1_RW_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	SPI1_CSN_L;			//NSS拉低	
//	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI1_RW(reg);      // select register
	SPI1_RW(value);             // ..and write value to it..
//	CSN = 1;                   // CSN high again
	SPI1_CSN_H;			//NSS拉高，关闭SPI	
	return(status);            // return nRF24L01 status uchar
}
//****************************************************************************************************/
//*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
//****************************************************************************************************/
uint8_t SPI1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
//	uint16_t status,uchar_ctr;
	uint8_t status,strcnt;
	SPI1_CSN_L;			//NSS拉低，SPI使能
//	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI1_RW(reg);       		// Select register to write to and read status uchar
	
	for(strcnt=0; strcnt<strlen; strcnt++) //
		pBuf[strcnt] = SPI1_RW(0);    // 
//	CSN = 1;                           
	SPI1_CSN_H;			//NSS拉高，关闭SPI	
	return(status);                    // return nRF24L01 status uchar
}
//*********************************************************************************************************
//*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
//*********************************************************************************************************/
uint8_t SPI1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
	uint8_t status,strcnt;

	SPI1_CSN_L;			//NSS拉低，SPI使能
//	CSN = 0;            //SPI使能
  
	status = SPI1_RW(reg);   
	for(strcnt=0; strcnt<strlen; strcnt++) //
		SPI1_RW(*pBuf++);

	SPI1_CSN_H;			//NSS拉高，关闭SPI

	return(status);    // 
}



//****************************************************************************************************/
//*函数：void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
// 输入：RX_Px数据通道号0~5，RX_ADR要设置的数据通道接收首地址
//*功能：数据接收配置 
//****************************************************************************************************/

void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
{
	SPI1_CE_L;	//StandBy I模式	
	switch (RX_Px){
		case (0):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (1):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P1_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;	
		case (2):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P2_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (3):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P3_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;			
		case (4):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P4_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (5):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P5_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
	    default:
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
	}
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	
	
	SPI1_CE_H;	//置高CE，激发数据发送 
	DelayUs(130);
} 

//****************************************************************************************************/
//函数：void SetSPI1_TXMode(unsigned char* pTX_ADR)
//功能：设置SPI1的24L01为发射模式
//参数：pTX_ADR
//****************************************************************************************************/

void SetSPI1_TXMode(unsigned char* pTX_ADR)
{	/*unsigned char TmpTX_ADR[TX_ADR_WIDTH_24L01];
	unsigned char i;
	for(i = 0;i < TX_ADR_WIDTH_24L01; i++){	// 写发送地址，要先写低字节	
		TmpTX_ADR[i] = pTX_ADR[TX_ADR_WIDTH_24L01 -1 - i];	
	}  */
	SPI1_CE_L;	//StandBy I模式	
	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, pTX_ADR , TX_ADR_WIDTH_24L01 );		// 写发送地址，要先写低字节	
	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, pTX_ADR, RX_ADR_WIDTH_24L01);		// 写接收端地址
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		// IRQ收发完成中断响应，16位CRC	，主接收
	SPI1_CE_H;	//置高CE，激发数据发送 
//	DelayUs(130);
	DelayCom(2000);
}  
//******************************************************************************************************/
//*函数：unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf)
//*功能：数据读取后放如rx_buf接收缓冲区中
//******************************************************************************************************/

unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	SPI1Sta=SPI1_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	if(SPI1Sta & RX_DR)				// 判断是否接收到数据
	{
	    SPI1_CE_L;	//StandBy I模式
		SPI1_Read_Buf(RD_RX_PLOAD_24L01,rx_buf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		revale =1;			//读取数据完成标志
	}
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	return revale;
}
//***********************************************************************************************************
//*函数：void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf)
//*功能：发送 tx_buf中数据
//**********************************************************************************************************/

void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf)
{//	uint8_t TmpSta;
	SPI1_CE_L;	//StandBy I模式	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_TXADR, TX_ADR_WIDTH_24L01); // 装载接收端地址
	SPI1_Write_Buf(WR_TX_PLOAD_24L01, tx_buf,  TX_PLOAD_WIDTH_24L01); 			 // 装载数据	
//	TmpSta = SPI1_Read(CONFIG_24L01);
//	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x2e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	SPI1_CE_H;	//置高CE，激发数据发送
//	DelayUs(50);
	DelayCom(130);
//	SPI1_CE_L;	//StandBy I模式	
}


/******************************************************************************************************/
/**************************************SPI2分割线*****************************************************/
/******************************************************************************************************/

//****************************************************************************************************
//*函数：uint SPI2_RW(uint uchar)	输出1字节数据同时返回1字节
//*功能：NRF24L01的SPI写时序
//****************************************************************************************************/

uint8_t SPI2_RW(uint8_t data)
{
//	uint8_t bit_ctr;
	SPI_I2S_SendData(SPI2 , data);
    /* Wait for SPIz data reception */
//#ifdef nRF24L01_board
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	data = SPI_I2S_ReceiveData(SPI2);
	return(data);           		  // return read uchar
/*
#else
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	uchar = SPI_I2S_ReceiveData(SPI1);

#endif
*/
	
/*  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (uchar & 0x80);         // output 'uchar', MSB to MOSI
		uchar = (uchar << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchar |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}*/
	

    
}

//****************************************************************************************************
//*函数：uchar SPI2_Read(uchar reg)
//*功能：NRF24L01的SPI时序
//****************************************************************************************************/

uint8_t SPI2_Read(uint8_t reg)
{
	uint8_t reg_val;
	SPI2_CSN_L;			//NSS拉低，SPI使能
//	CSN = 0;                // CSN low, initialize SPI communication...
	SPI2_RW(reg);            // Select register to read from..
	reg_val = SPI2_RW(0);    // ..then read registervalue
//	CSN = 1;                // CSN high, terminate SPI communication
	SPI2_CSN_H;			//NSS拉高，关闭SPI
	return(reg_val);        // return register value
}

//****************************************************************************************************/
//*功能：NRF24L01读写寄存器函数
//****************************************************************************************************/

uint8_t SPI2_RW_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	SPI2_CSN_L;			//NSS拉低，SPI使能	
//	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI2_RW(reg);      // select register
	SPI2_RW(value);             // ..and write value to it..
//	CSN = 1;                   // CSN high again
	SPI2_CSN_H;			//NSS拉高，关闭SPI
	return(status);            // return nRF24L01 status uchar
}
//****************************************************************************************************/
//*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
//****************************************************************************************************/
uint8_t SPI2_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
//	uint16_t status,uchar_ctr;
	uint8_t status,strcnt;
	SPI2_CSN_L;			//NSS拉低，SPI使能
//	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI2_RW(reg);       		// Select register to write to and read status uchar
	
	for(strcnt=0; strcnt<strlen; strcnt++) //
		pBuf[strcnt] = SPI2_RW(0);    // 
	
//	CSN = 1;                           
	SPI2_CSN_H;			//NSS拉高，关闭SPI	
	return(status);                    // return nRF24L01 status uchar
}
//*********************************************************************************************************
//*函数：uint SPI2_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
//*********************************************************************************************************/
uint8_t SPI2_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
	uint8_t status,strcnt;

	SPI2_CSN_L;			//NSS拉低，SPI使能
//	CSN = 0;            //SPI使能       
	status = SPI2_RW(reg);   
	for(strcnt=0; strcnt<strlen; strcnt++) //
		SPI2_RW(*pBuf++);
//	CSN = 1;           //关闭SPI
	SPI2_CSN_H;			//NSS拉高，关闭SPI
	return(status);    // 
}
//****************************************************************************************************/
//*函数：void SetSPI2_RXMode(unsigned char* )
//*功能：数据接收配置 
//****************************************************************************************************/

void SetSPI2_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
{
	SPI2_CE_L;	//StandBy I模式	
	switch (RX_Px){
		case (0):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (1):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P1_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;	
		case (2):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P2_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (3):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P3_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;			
		case (4):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P4_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
		case (5):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P5_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
	    default:
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // 写接收端地址	
		break;
	}


	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	SPI2_CE_H;	//置高CE，激发数据发送 
	DelayUs(330);
} 

//****************************************************************************************************/
//*函数：void SetSPI2_TXMode(unsigned char* )
//*功能：数据接收配置 
//****************************************************************************************************/

void SetSPI2_TXMode(unsigned char* TX_ADR)
{
	SPI2_CE_L;	//StandBy I模式	
	SPI2_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, TX_ADR , TX_ADR_WIDTH_24L01 );		// 写发送地址，要先写低字节	
	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, TX_ADR, RX_ADR_WIDTH_24L01);		// 写接收端地址
	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		// IRQ收发完成中断响应，16位CRC	，主发射
	SPI2_CE_H;	//置高CE，激发数据发送 
	DelayUs(130);
} 
//******************************************************************************************************/
//*函数：unsigned char nRF24L01_SPI2_RxPacket(unsigned char* rx_buf)
//*功能：数据读取后放如rx_buf接收缓冲区中
//******************************************************************************************************/

unsigned char nRF24L01_SPI2_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	SPI2Sta=SPI2_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况
	if(SPI2Sta & RX_DR)				// 判断是否接收到数据
	{
	    SPI2_CE_L;	//StandBy I模式
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,rx_buf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		SPI2_CE_H;	//置高CE，保持接收模式
		revale =1;			//读取数据完成标志
	}
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI2Sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	return revale;
}
//***********************************************************************************************************
//*函数：void nRF24L01_SPI2_TxPacket(unsigned char * tx_buf) s
//*功能：发送 tx_buf中数据
//**********************************************************************************************************/

void nRF24L01_SPI2_TxPacket(unsigned char * tx_buf)
{
	SPI2_CE_L;	//StandBy I模式	
//	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, TX_ADDRESS_24L01, TX_ADR_WIDTH_24L01); // 装载接收端地址
	SPI2_Write_Buf(WR_TX_PLOAD_24L01, tx_buf, TX_PLOAD_WIDTH_24L01); 			 // 装载数据	
//	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	SPI2_CE_H;	//置高CE，激发数据发送
	DelayUs(10);
}



