

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
#define CD_24L01              0x09  // ��ַ���           
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
#define MAXMISSHEART 5	//����������������� 
typedef enum {TXSTATUS = 0, RXSTATUS = !TXSTATUS} STA24L01;
typedef struct	_RxAdrTab_TypeDef
{
	u8	RxAdrTabCnt;	//��¼��ʹ�õĵ�ַ�ռ����
	u8 * pRxAdrTabCnt;	//ָ��յĽ��յ�ַ���ռ䡣
	u8 TabIndex;		//��־���͵�ַ
	u8 TabFlag[RXADRTABLEN];	//��¼��ַ�ռ�ʹ���������,0x00:δʹ�û�Ͽ������ˣ�0x01:������������TabFlag[1]��ʼ��¼ 
	u8 HeartBeatSta[RXADRTABLEN];		//��HeartBeatSta[1]��ʼ�����ģ����������������������״̬
//	u8 RxPnSequence[RXADRTABLEN];		//����ͨ������
	u8 RxAdrIndex;		//����ģ���ַ����
	u8 * pCmdTxBuf[RXADRTABLEN];		//ָ��������Ĵ�ģ�����������ռ�
	u8 RxAdrTab0[RX_ADR_WIDTH_24L01];	//RxAdrTab0[]�����ģ���ַ��
	u8 RxAdrTab1[RX_ADR_WIDTH_24L01];	//��RxAdrTab1[]��ʼ�洢��ģ���ַ
	u8 RxAdrTab2[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab3[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab4[RX_ADR_WIDTH_24L01];
	u8 RxAdrTab5[RX_ADR_WIDTH_24L01];
	u8 RxAdrAll[RXADRTABLEN][RX_ADR_WIDTH_24L01];
}RxAdrTab_TypeDef;	//��¼������ģ��ĵ�ַ



extern RxAdrTab_TypeDef * pRxAdr_Tab;
extern RxAdrTab_TypeDef RxAdr_Tab;

/*************************��������*****************************************************/
extern u8   sta;   //״̬��־
extern u8	SPI1FIFOSta,SPI1Sta;
//extern u8	SPI2FIFOSta,SPI2Sta;	//SPI2������յ�24L01��FIFO��STATUS,SPI2RxCnt��������RX����
extern u8	SPI2RxCnt,SPI1RxCnt;
extern const u8 NetConnectRxAdr[RX_ADR_WIDTH_24L01];		//�㲥���յ�ַ
extern const u8 TX_ADDRESS_24L01[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 RX_ADDRESS_24L01[RX_ADR_WIDTH_24L01];	//���յ�ַ

extern const u8 MOD1_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD1_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD2_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD2_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD3_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD3_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD4_TXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ
extern const u8 MOD4_RXADR[TX_ADR_WIDTH_24L01];	//���ص�ַ

extern @near u8 Net_TXADR[TX_ADR_WIDTH_24L01];	//��������ַ	
extern @near u8 Net_RXADR[TX_ADR_WIDTH_24L01];	//��������ַ

/*************************��������*****************************************************/
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

