

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

/***************************************NRF24L01�Ĵ���ָ��*******************************************************/
#define READ_REG_24L01        0x00  	// ���Ĵ���ָ��
#define WRITE_REG_24L01       0x20 	    // д�Ĵ���ָ��
#define RD_RX_PLOAD_24L01     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD_24L01     0xA0  	// д��������ָ��
#define FLUSH_TX_24L01        0xE1 	    // ��ϴ���� FIFOָ��
#define FLUSH_RX_24L01        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL_24L01     0xE3  	// �����ظ�װ������ָ��
#define NOP_24L01             0xFF  	// ����
/*************************************SPI(nRF24L01)�Ĵ�����ַ****************************************************/
#define CONFIG_24L01          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA_24L01           0x01  // �Զ�Ӧ��������
#define EN_RXADDR_24L01       0x02  // �����ŵ�����
#define SETUP_AW_24L01        0x03  // �շ���ַ�������
#define SETUP_RETR_24L01      0x04  // �Զ��ط���������
#define RF_CH_24L01           0x05  // ����Ƶ������
#define RF_SETUP_24L01        0x06  // �������ʡ����Ĺ�������
#define STATUS_24L01          0x07  // ״̬�Ĵ���
#define OBSERVE_TX_24L01      0x08  // ���ͼ�⹦��
#define CD_24L01              0x09  // �ز�����           
#define RX_ADDR_P0_24L01      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1_24L01      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2_24L01      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3_24L01      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4_24L01      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5_24L01      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR_24L01         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0_24L01        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1_24L01        0x12  // ����Ƶ��0�������ݳ���
#define RX_PW_P2_24L01        0x13  // ����Ƶ��0�������ݳ���
#define RX_PW_P3_24L01        0x14  // ����Ƶ��0�������ݳ���
#define RX_PW_P4_24L01        0x15  // ����Ƶ��0�������ݳ���
#define RX_PW_P5_24L01        0x16  // ����Ƶ��0�������ݳ���
#define FIFO_STATUS_24L01     0x17  // FIFOջ��ջ��״̬�Ĵ�������

//********************************�Զ���******************************
#define RX_P0_24L01      0x00  // Ƶ��0
#define RX_P1_24L01      0x01  // Ƶ��1
#define RX_P2_24L01      0x02  // Ƶ��2
#define RX_P3_24L01      0x03  // Ƶ��3
#define RX_P4_24L01      0x04  // Ƶ��4
#define RX_P5_24L01      0x05  // Ƶ��5

#define DEFAULT_FRE		0x28   //Ĭ��Ƶ��

#define RXADRTABLEN	6	//�ӵ�ַ�ռ��С	//�ݶ�һ�������֧��255����ģ��
#define MAXMISSHEART 10	//����������������� 
typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_RxAdrTab_TypeDef
{
	uint8_t	RxAdrTabCnt;	//��¼��ʹ�õĵ�ַ�ռ����
	uint8_t * pRxAdrTabCnt;	//ָ��յĽ��յ�ַ���ռ䡣
	uint8_t TabIndex;		//��־���͵�ַ
	uint8_t TabFlag[RXADRTABLEN];	//��¼��ַ�ռ�ʹ���������,0x00:δʹ�û�Ͽ������ˣ�0x01:������������TabFlag[1]��ʼ��¼ 
	uint8_t HeartBeatSta[RXADRTABLEN];		//��HeartBeatSta[1]��ʼ�����ģ����������������������״̬
//	uint8_t RxPnSequence[RXADRTABLEN];		//����ͨ������
	uint8_t RxAdrIndex;		//����ģ���ַ����
	uint8_t * pCmdTxBuf[RXADRTABLEN];		//ָ��������Ĵ�ģ�����������ռ�
	uint8_t RxAdrTab0[RX_ADR_WIDTH_24L01];	//RxAdrTab0[]�����ģ���ַ��
	uint8_t RxAdrTab1[RX_ADR_WIDTH_24L01];	//��RxAdrTab1[]��ʼ�洢��ģ���ַ
	uint8_t RxAdrTab2[RX_ADR_WIDTH_24L01];
	uint8_t RxAdrTab3[RX_ADR_WIDTH_24L01];
	uint8_t RxAdrTab4[RX_ADR_WIDTH_24L01];
	uint8_t RxAdrTab5[RX_ADR_WIDTH_24L01];
	uint8_t RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH_24L01];
}RxAdrTab_TypeDef;	//��¼������ģ��ĵ�ַ



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;

/*************************��������*****************************************************/
extern uint8_t   sta;   //״̬��־
extern uint8_t	volatile SPI1FIFOSta,SPI1Sta;
extern uint8_t	volatile SPI2FIFOSta,SPI2Sta;	//SPI2������յ�24L01��FIFO��STATUS,SPI2RxCnt��������RX����
extern uint16_t	SPI2RxCnt,SPI1RxCnt;
extern uint8_t NetConnectRxAdr[RX_ADR_WIDTH_24L01];		//�㲥���յ�ַ
extern uint8_t TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01];	//���յ�ַ

extern uint8_t MOD1_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD1_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD2_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD2_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD3_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD3_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD4_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern uint8_t MOD4_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ



/*************************��������*****************************************************/
void Init_NRF24L01_SPI1(void);
void Init_NRF24L01_SPI2(void);
uint8_t SPI1_RW(uint8_t uchar);
uint8_t SPI1_Read(uint8_t reg);
//void SetSPI1_BroadCast(void);
void SetSPI1_RXMode(unsigned char RX_Px,unsigned char* RX_ADR);
void SetSPI1_TXMode(unsigned char* pTX_ADR);
uint8_t SPI1_RW_Reg(uint8_t reg, uint8_t value);
uint8_t SPI1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen);
uint8_t SPI1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen);
unsigned char nRF24L01_SPI1_RxPacket(unsigned char* rx_buf);
void nRF24L01_SPI1_TxPacket(unsigned char * tx_buf);

uint8_t SPI2_RW(uint8_t data);
uint8_t SPI2_Read(uint8_t reg);
void SetSPI2_RXMode(unsigned char RX_Px,unsigned char* RX_ADR);
void SetSPI2_TXMode(unsigned char* TX_ADR);
uint8_t SPI2_RW_Reg(uint8_t reg, uint8_t value);
uint8_t SPI2_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen);
uint8_t SPI2_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t strlen);
unsigned char nRF24L01_SPI2_RxPacket(unsigned char* rx_buf);
void nRF24L01_SPI2_TxPacket(unsigned char * tx_buf);
//void SPI2_CMDCNT(uint8_t stacnt);



#endif

