
#ifndef _24L01APP_H_
#define _24L01APP_H_

#define CMD_MAXRESEND	20		//�����ط�������
#define CMD_NUMLMT 5			//�����ͬʱ������������
#define NETCNT_TIMEOUT	10000	//��������״̬��ʱΪ10S ����ʱ����Ϊ1S
#define DATARECEIVE_SPAN	200	//Data�������ݽ׶Σ�����ͨ��Rx_P1~5�л�ʱ����
#define CMD_BUF_LEN	32
#define CMD_HEADER_LEN 3
#define CMD_OTHERS_START 6
#define CMD_OTHERS_LEN	19	

typedef union _CMD_BODY_TypeDef{
	uint8_t all[CMD_BUF_LEN];	//ken:���������������ݶ�
	struct {
		uint8_t		CmdStartByte;					//JK������ʼ��'#'	
		uint8_t		Header[CMD_HEADER_LEN];			//����ͷ��XXX
		uint8_t		Dot1;							//����ͷ���1��','��
		uint8_t		NetNum;							//����
		uint8_t		Dot2;							//����ͷ���2��','��
		uint8_t		Adr[RX_ADR_WIDTH_24L01];		//��ģ���ַ
		uint8_t		Dot3;							//����ͷ���3��','��
		uint8_t 	Others[CMD_OTHERS_LEN];			//������������������ַ�
	}part;
}CMD_BODY_TypeDef;


// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMD_BUF_TypeDef{				
 	CMD_BODY_TypeDef * pCmd_Body;			//ָ�����������������
	CMD_BODY_TypeDef * pReplyBuf;			//Ӧ�𻺳���		
//	uint16_t 	HeadHash;					//���������Hashͷ������ɢת
	uint8_t		CmdTxFlag[CMD_NUMLMT];		//�����״̬
	uint8_t		CmdListNum;					//�������������
	uint8_t		CmdListFlag[CMD_NUMLMT];	//��¼���������ʹ�����
			
}CMD_BUF_TypeDef;	
extern CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
extern CMD_BUF_TypeDef CmdBuf;	//����������
extern CMD_BUF_TypeDef * pCmdBuf;	//ָ������������




uint8_t HeartBeat(uint8_t * pHeartBeatAdr);
uint8_t NewConnect(uint8_t * pNewAdr);
void CheckConnect(void);
void FreHopping(uint8_t SPIx , uint8_t Fre);
void RandomDelayUs(void);
void NetConnect(bool Sta);
void SysRun(void);
void SPI2_CMDCNT(uint8_t stacnt);
void Synchronize(void);
void DataReceive(void);
void DataSend(void);
void Broadcast(uint8_t * TxStr);

#endif
