 /* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "24L01API.h"

///*********************Global Variable**************************************************************
u8   sta;   //״̬��־
u8	SPI1FIFOSta,SPI1Sta;
//u8	SPI2FIFOSta,SPI2Sta;
u8	SPI2RxCnt,SPI1RxCnt;
const u8 NetConnectRxAdr[RX_ADR_WIDTH_24L01] = {0xA1,0x5C,0x00,0x00,0x01};	//�㲥���յ�ַ

//const u8 TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01]= {0x18,0x42,0x31,0x10,0x01};	//���ص�ַ
//const u8 RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01]= {0x33,0x43,0x10,0x16,0x28};	//���յ�ַ

//const u8 MOD1_TXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x00,0x01};	
//const u8 MOD1_RXADR[TX_ADR_WIDTH_24L01]= {0x21,0xA1,0x0A,0x00,0x01};	
//const u8 MOD2_TXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	
//const u8 MOD2_RXADR[TX_ADR_WIDTH_24L01]= {0x31,0xA1,0x0B,0x10,0x02};	
const u8 MOD3_TXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//���ص�ַ	
const u8 MOD3_RXADR[TX_ADR_WIDTH_24L01]= {0x32,0xA1,0x0C,0xB6,0xA4};	//���ص�ַ
//const u8 MOD4_TXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	
//const u8 MOD4_RXADR[TX_ADR_WIDTH_24L01]= {0x33,0xA1,0x0D,0x79,0xE8};	
@near u8 Net_TXADR[TX_ADR_WIDTH_24L01]= {0};	//��������ַ	
@near u8 Net_RXADR[TX_ADR_WIDTH_24L01]= {0};	//��������ַ


//���������ģ��ĵ�ַ��
RxAdrTab_TypeDef * pRxAdr_Tab;
RxAdrTab_TypeDef RxAdr_Tab;



//****************************************************************************************
//*�������NRF24L01��ʼ��
//***************************************************************************************/
void Init_NRF24L01_SPI1(void)
{	 u8  TmpSta;
	SPI1_PWR_ON();
    Delay(300);
//  	CE=0;    // chip enable
// 	CSN=1;   // Spi disable 
//	SCK=0;   // Spi clock line init high
	SPI1_CE_L;	//StandBy Iģʽ
	SPI1_CSN_H;	//NSS����
	//																					// �����Ϊ���ͷ������͵�ַ����յ�ַҪһ�£���ΪACK�Զ�Ӧ����Ҫ
//	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, MOD1_RXADR, TX_ADR_WIDTH_24L01);    // д���ص�ַ	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, MOD1_RXADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x03);      //  ȫƵ���Զ�ACKӦ������	
	TmpSta = SPI1_Read(EN_AA_24L01);	
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x03);  //  ����ȫ��6�����յ�ַ�������Ҫ��Ƶ�����Բο�Page21  
	TmpSta = SPI1_Read(EN_RXADDR_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_CH_24L01, DEFAULT_FRE);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ�� 	//��Ƶʱ��Ҫ�ı�
	TmpSta = SPI1_Read(RF_CH_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RX_PW_P0_24L01, RX_PLOAD_WIDTH_24L01); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	TmpSta = SPI1_Read(RX_PW_P0_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + RF_SETUP_24L01, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB	
	TmpSta = SPI1_Read(RF_SETUP_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		 // ����Ӧ�����жϣ�IRQ�շ�����ж���Ӧ��16λCRC���ϵ磬������
	TmpSta = SPI1_Read(CONFIG_24L01);
	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0x70);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־

	Delay(300);
}



//****************************************************************************************************
//*������uint SPI1_RW(uint uchar)	���1�ֽ�����ͬʱ����1�ֽ�
//*���ܣ�NRF24L01��SPIдʱ��
//****************************************************************************************************/

u8 SPI1_RW(u8 string)
{
//	uint8_t bit_ctr;
 
	SPI_SendData(string);
    /* Wait for SPIz data reception */
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	string = SPI_ReceiveData();
	
/*  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (uchar & 0x80);         // output 'uchar', MSB to MOSI
		uchar = (uchar << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchar |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}*/

    return(string);           		  // return read uchar
}

//****************************************************************************************************
//*������uchar SPI_Read(uchar reg)
//*���ܣ�NRF24L01��SPIʱ��
//****************************************************************************************************/

u8 SPI1_Read(u8 reg)
{
	u8 reg_val;
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

u8 SPI1_RW_Reg(u8 reg, u8 value)
{
	u8 status;
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
u8 SPI1_Read_Buf(u8 reg, u8 *pBuf, u8 strlen)
{
//	uint16_t status,uchar_ctr;
	u8 status,strcnt;
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
u8 SPI1_Write_Buf(u8 reg, u8 *pBuf, u8 strlen)
{
	u8 status,strcnt;

	SPI1_CSN_L;			//NSS���ͣ�SPIʹ��
//	CSN = 0;            //SPIʹ��
  
	status = SPI1_RW(reg);   
	for(strcnt=0; strcnt<strlen; strcnt++) //
		SPI1_RW(*pBuf++);

	SPI1_CSN_H;			//NSS���ߣ��ر�SPI

	return(status);    // 
}

//****************************************************************************************************/
//*������void SetSlv_RxMode(unsigned char RX_Px,unsigned char* RX_ADR)
// ���룺RX_ADRҪ���õ�����ͨ�������׵�ַ
//*���ܣ�ͨ��1���ݽ������� 
//****************************************************************************************************/
void SetSlv_RxMode(unsigned char * RX_ADR)
{
	SPI1_CE_L;	//StandBy Iģʽ
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_AA_24L01, 0x03);      //  ȫƵ���Զ�ACKӦ������		
	SPI1_RW_Reg(WRITE_REG_24L01 + EN_RXADDR_24L01, 0x03);  //  ����ȫ��6�����յ�ַ�������Ҫ��Ƶ�����Բο�Page21 
	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P1_24L01, RX_ADR, RX_ADR_WIDTH_24L01); // д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI1_CE_H;	//�ø�CE���������ݷ��� 
	Delay(330);	
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
	Delay(330);
} 

//****************************************************************************************************/
//������void SetSPI1_TXMode(unsigned char* pTX_ADR)
//���ܣ�����SPI1��24L01Ϊ����ģʽ
//������pTX_ADR
//****************************************************************************************************/

void SetSPI1_TXMode(unsigned char* pTX_ADR)
{
	SPI1_CE_L;	//StandBy Iģʽ	
	SPI1_Write_Buf(WRITE_REG_24L01 + TX_ADDR_24L01, pTX_ADR , TX_ADR_WIDTH_24L01 );		// д���͵�ַ	
	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, pTX_ADR, RX_ADR_WIDTH_24L01);		// д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG_24L01 + CONFIG_24L01, 0x0e);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI1_CE_H;	//�ø�CE���������ݷ��� 
	Delay(330);
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
	Delay(250);
//	SPI1_CE_L;	//StandBy Iģʽ	
}






