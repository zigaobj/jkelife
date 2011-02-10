 /* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "24L01API.h"

///*********************Global Variable**************************************************************
uint8_t   sta;   //״̬��־
uint8_t	volatile SPI1FIFOSta,SPI1Sta;
uint8_t	volatile SPI2FIFOSta,SPI2Sta;
uint16_t	SPI2RxCnt,SPI1RxCnt;
uint8_t NetConnectRxAdr[RX_ADR_WIDTH_24L01] = {0xA1,0x5C,0x00,0x00,0x01};	//�㲥���յ�ַ
uint8_t TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01]= {0x18,0x42,0x31,0x10,0x01};	//���ص�ַ
uint8_t RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01]= {0x33,0x43,0x10,0x16,0x28};	//���յ�ַ

uint8_t MOD1_TXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x28,0x01};	//���ص�ַ
uint8_t MOD1_RXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x28,0x01};	//���ص�ַ
uint8_t MOD2_TXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	//���ص�ַ
uint8_t MOD2_RXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	//���ص�ַ
uint8_t MOD3_TXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//���ص�ַ
uint8_t MOD3_RXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//���ص�ַ
uint8_t MOD4_TXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	//���ص�ַ
uint8_t MOD4_RXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	//���ص�ַ



//���������ģ��ĵ�ַ��
RxAdrTab_TypeDef * pRxAdr_Tab;
RxAdrTab_TypeDef RxAdr_Tab;



//****************************************************************************************
//*�������NRF24L01��ʼ��
//***************************************************************************************/
void Init_NRF24L01_SPI1(void)
{	//uint8_t TmpSta;
//	SPI1_PWR_ON();
	
    DelayUs(1000);
//  	CE=0;    // chip enable
// 	CSN=1;   // Spi disable 
//	SCK=0;   // Spi clock line init high
	SPI1_CE_L;	//StandBy Iģʽ
	SPI1_CSN_H;	//NSS����
	//																					// �����Ϊ���ͷ������͵�ַ����յ�ַҪһ�£���ΪACK�Զ�Ӧ����Ҫ
//	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, MOD1_RXADR, TX_ADR_WIDTH_24L01);    // д���ص�ַ	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_RXADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x03);      //  ȫƵ���Զ�ACKӦ������	
//	TmpSta = SPI1_Read(EN_AA_24L01);	
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x03);  //  ����ȫ��6�����յ�ַ�������Ҫ��Ƶ�����Բο�Page21  
//	TmpSta = SPI1_Read(EN_RXADDR_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_CH_24L01, DEFAULT_FRE);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ�� 	//��Ƶʱ��Ҫ�ı�
//	TmpSta = SPI1_Read(RF_CH_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RX_PW_P0_24L01, RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
//	TmpSta = SPI1_Read(RX_PW_P0_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_SETUP_24L01, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB	
//	TmpSta = SPI1_Read(RF_SETUP_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		 // ����Ӧ�����жϣ�IRQ�շ�����ж���Ӧ��16λCRC���ϵ磬������
//	TmpSta = SPI1_Read(CONFIG_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0x70);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־

	DelayUs(100);
}

//****************************************************************************************
//*������յ�NRF24L01��ʼ��
//***************************************************************************************/
void Init_NRF24L01_SPI2(void)
{	//uint8_t TmpSta;
//	SPI2_PWR_ON();
	DelayUs(500);
// 	CE=0;    // chip enable
// 	CSN=1;   // Spi disable 
//	SCK=0;   // Spi clock line init high
	SPI2_CE_L;	//StandBy Iģʽ
	SPI2_CSN_H;	//NSS����

//	SPI2_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, MOD1_TXADR , RX_ADR_WIDTH_24L01 );    // д���ص�ַ	
//	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_TXADR, TX_ADR_WIDTH_24L01); // д���ն˵�ַ
	SPI2_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x3F);      //  Ƶ��1�Զ�ACKӦ������	//  ��ȥ0ͨ����ȫƵ���Զ�ACKӦ������	
//	TmpSta = SPI2_Read(EN_AA_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x3F);  //  ������յ�ַƵ��1�� 	//  ��ȥ0ͨ����ȫƵ��������� 
//	TmpSta = SPI2_Read(EN_RXADDR_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RF_CH_24L01, DEFAULT_FRE);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ�£�F = 2400 + RF_CH (Mhz)
//	TmpSta = SPI2_Read(RF_CH_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P0_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P1_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P2_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P3_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P4_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	SPI2_RW_Reg(WRITE_REG_24L01 + RX_PW_P5_24L01,  RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
	 
//	TmpSta = SPI2_Read(RX_PW_P0_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + RF_SETUP_24L01, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB	
//	TmpSta = SPI2_Read(RF_SETUP_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   			//����Ӧ�����жϣ� IRQ�շ�����ж���Ӧ��16λCRC���ϵ磬������
//	TmpSta = SPI2_Read(CONFIG_24L01);
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0x70);   			//���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	SPI2_CE_H;	//RXģʽ
	DelayUs(200);
}

//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�NRF24L01��SPIдʱ��
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
//*������uchar SPI_Read(uchar reg)
//*���ܣ�NRF24L01��SPIʱ��
//****************************************************************************************************/

uint8_t SPI1_Read(uint8_t reg)
{
	uint8_t reg_val;
	SPI1_CSN_L;			//NSS����
//	CSN = 0;                // CSN low, initialize SPI communication...
	SPI1_RW(reg);            // Select register to read from..
	reg_val = SPI1_RW(0);    // ..then read registervalue
//	CSN = 1;                // CSN high, terminate SPI communication
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI
	return(reg_val);        // return register value
}

//****************************************************************************************************/
//*���ܣ�NRF24L01��д�Ĵ�������
//****************************************************************************************************/

uint8_t SPI1_RW_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	SPI1_CSN_L;			//NSS����	
//	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI1_RW(reg);      // select register
	SPI1_RW(value);             // ..and write value to it..
//	CSN = 1;                   // CSN high again
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI	
	return(status);            // return nRF24L01 status uchar
}
//****************************************************************************************************/
//*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
//****************************************************************************************************/
uint8_t SPI1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
//	uint16_t status,uchar_ctr;
	uint8_t status,strcnt;
	SPI1_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI1_RW(reg);       		// Select register to write to and read status uchar
	
	for(strcnt=0; strcnt<strlen; strcnt++) //
		pBuf[strcnt] = SPI1_RW(0);    // 
//	CSN = 1;                           
	SPI1_CSN_H;			//NSS���ߣ��ر�SPI	
	return(status);                    // return nRF24L01 status uchar
}
//*********************************************************************************************************
//*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
//*********************************************************************************************************/
uint8_t SPI1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
	uint8_t status,strcnt;

	SPI1_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;            //SPIʹ��
  
	status = SPI1_RW(reg);   
	for(strcnt=0; strcnt<strlen; strcnt++) //
		SPI1_RW(*pBuf++);

	SPI1_CSN_H;			//NSS���ߣ��ر�SPI

	return(status);    // 
}



//****************************************************************************************************/
//*������void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
// ���룺RX_Px����ͨ����0~5��RX_ADRҪ���õ�����ͨ�������׵�ַ
//*���ܣ����ݽ������� 
//****************************************************************************************************/

void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
{
	SPI1_CE_L;	//StandBy Iģʽ	
	switch (RX_Px){
		case (0):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (1):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P1_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;	
		case (2):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P2_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (3):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P3_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;			
		case (4):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P4_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (5):
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P5_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
	    default:
			SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
	}
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	
	
	SPI1_CE_H;	//�ø�CE���������ݷ��� 
	DelayUs(130);
} 

//****************************************************************************************************/
//������void SetSPI1_TXMode(unsigned char* pTX_ADR)
//���ܣ�����SPI1��24L01Ϊ����ģʽ
//������pTX_ADR
//****************************************************************************************************/

void SetSPI1_TXMode(unsigned char* pTX_ADR)
{	/*unsigned char TmpTX_ADR[TX_ADR_WIDTH_24L01];
	unsigned char i;
	for(i = 0;i < TX_ADR_WIDTH_24L01; i++){	// д���͵�ַ��Ҫ��д���ֽ�	
		TmpTX_ADR[i] = pTX_ADR[TX_ADR_WIDTH_24L01 -1 - i];	
	}  */
	SPI1_CE_L;	//StandBy Iģʽ	
	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, pTX_ADR , TX_ADR_WIDTH_24L01 );		// д���͵�ַ��Ҫ��д���ֽ�	
	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, pTX_ADR, RX_ADR_WIDTH_24L01);		// д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI1_CE_H;	//�ø�CE���������ݷ��� 
//	DelayUs(130);
	DelayCom(2000);
}  
//******************************************************************************************************/
//*������unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf)
//*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
//******************************************************************************************************/

unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	SPI1Sta=SPI1_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(SPI1Sta & RX_DR)				// �ж��Ƿ���յ�����
	{
	    SPI1_CE_L;	//StandBy Iģʽ
		SPI1_Read_Buf(RD_RX_PLOAD_24L01,rx_buf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		revale =1;			//��ȡ������ɱ�־
	}
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI1Sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}
//***********************************************************************************************************
//*������void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf)
//*���ܣ����� tx_buf������
//**********************************************************************************************************/

void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf)
{//	uint8_t TmpSta;
	SPI1_CE_L;	//StandBy Iģʽ	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_TXADR, TX_ADR_WIDTH_24L01); // װ�ؽ��ն˵�ַ
	SPI1_Write_Buf(WR_TX_PLOAD_24L01, tx_buf,  TX_PLOAD_WIDTH_24L01); 			 // װ������	
//	TmpSta = SPI1_Read(CONFIG_24L01);
//	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x2e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	SPI1_CE_H;	//�ø�CE���������ݷ���
//	DelayUs(50);
	DelayCom(130);
//	SPI1_CE_L;	//StandBy Iģʽ	
}


/******************************************************************************************************/
/**************************************SPI2�ָ���*****************************************************/
/******************************************************************************************************/

//****************************************************************************************************
//*������uint SPI2_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�NRF24L01��SPIдʱ��
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
//*������uchar SPI2_Read(uchar reg)
//*���ܣ�NRF24L01��SPIʱ��
//****************************************************************************************************/

uint8_t SPI2_Read(uint8_t reg)
{
	uint8_t reg_val;
	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;                // CSN low, initialize SPI communication...
	SPI2_RW(reg);            // Select register to read from..
	reg_val = SPI2_RW(0);    // ..then read registervalue
//	CSN = 1;                // CSN high, terminate SPI communication
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI
	return(reg_val);        // return register value
}

//****************************************************************************************************/
//*���ܣ�NRF24L01��д�Ĵ�������
//****************************************************************************************************/

uint8_t SPI2_RW_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��	
//	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI2_RW(reg);      // select register
	SPI2_RW(value);             // ..and write value to it..
//	CSN = 1;                   // CSN high again
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI
	return(status);            // return nRF24L01 status uchar
}
//****************************************************************************************************/
//*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
//****************************************************************************************************/
uint8_t SPI2_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
//	uint16_t status,uchar_ctr;
	uint8_t status,strcnt;
	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI2_RW(reg);       		// Select register to write to and read status uchar
	
	for(strcnt=0; strcnt<strlen; strcnt++) //
		pBuf[strcnt] = SPI2_RW(0);    // 
	
//	CSN = 1;                           
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI	
	return(status);                    // return nRF24L01 status uchar
}
//*********************************************************************************************************
//*������uint SPI2_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
//*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
//*********************************************************************************************************/
uint8_t SPI2_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen)
{
	uint8_t status,strcnt;

	SPI2_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;            //SPIʹ��       
	status = SPI2_RW(reg);   
	for(strcnt=0; strcnt<strlen; strcnt++) //
		SPI2_RW(*pBuf++);
//	CSN = 1;           //�ر�SPI
	SPI2_CSN_H;			//NSS���ߣ��ر�SPI
	return(status);    // 
}
//****************************************************************************************************/
//*������void SetSPI2_RXMode(unsigned char* )
//*���ܣ����ݽ������� 
//****************************************************************************************************/

void SetSPI2_RXMode(unsigned char RX_Px,unsigned char* RX_ADR)
{
	SPI2_CE_L;	//StandBy Iģʽ	
	switch (RX_Px){
		case (0):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (1):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P1_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;	
		case (2):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P2_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (3):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P3_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;			
		case (4):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P4_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
		case (5):
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P5_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
	    default:
			SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
		break;
	}


	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI2_CE_H;	//�ø�CE���������ݷ��� 
	DelayUs(330);
} 

//****************************************************************************************************/
//*������void SetSPI2_TXMode(unsigned char* )
//*���ܣ����ݽ������� 
//****************************************************************************************************/

void SetSPI2_TXMode(unsigned char* TX_ADR)
{
	SPI2_CE_L;	//StandBy Iģʽ	
	SPI2_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, TX_ADR , TX_ADR_WIDTH_24L01 );		// д���͵�ַ��Ҫ��д���ֽ�	
	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, TX_ADR, RX_ADR_WIDTH_24L01);		// д���ն˵�ַ
	SPI2_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI2_CE_H;	//�ø�CE���������ݷ��� 
	DelayUs(130);
} 
//******************************************************************************************************/
//*������unsigned char nRF24L01_SPI2_RxPacket(unsigned char* rx_buf)
//*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
//******************************************************************************************************/

unsigned char nRF24L01_SPI2_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	SPI2Sta=SPI2_Read(STATUS_24L01);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(SPI2Sta & RX_DR)				// �ж��Ƿ���յ�����
	{
	    SPI2_CE_L;	//StandBy Iģʽ
		SPI2_Read_Buf(RD_RX_PLOAD_24L01,rx_buf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
		SPI2_CE_H;	//�ø�CE�����ֽ���ģʽ
		revale =1;			//��ȡ������ɱ�־
	}
	SPI2_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,SPI2Sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}
//***********************************************************************************************************
//*������void nRF24L01_SPI2_TxPacket(unsigned char * tx_buf) s
//*���ܣ����� tx_buf������
//**********************************************************************************************************/

void nRF24L01_SPI2_TxPacket(unsigned char * tx_buf)
{
	SPI2_CE_L;	//StandBy Iģʽ	
//	SPI2_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, TX_ADDRESS_24L01, TX_ADR_WIDTH_24L01); // װ�ؽ��ն˵�ַ
	SPI2_Write_Buf(WR_TX_PLOAD_24L01, tx_buf, TX_PLOAD_WIDTH_24L01); 			 // װ������	
//	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	SPI2_CE_H;	//�ø�CE���������ݷ���
	DelayUs(10);
}



