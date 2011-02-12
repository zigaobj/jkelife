
#ifndef _24L01APP_H_
#define _24L01APP_H_

#define CMD_MAXRESEND	10		//�����ط�������
#define CMD_NUMLMT 5			//�����ͬʱ������������
#define NETCNT_TIMEOUT	10000	//��������״̬��ʱΪ10S(10000) ����ʱ����Ϊ1S(1000)
#define DATARECEIVE_SPAN	200	//Data�������ݽ׶Σ�����ͨ��Rx_P1~5�л�ʱ����
#define CMD_BUF_LEN	32
#define CMD_HEADER_LEN 3
#define CMD_OTHERS_START 6
#define CMD_OTHERS_LEN	19	

typedef union _CMD_BODY_TypeDef{
	u8 all[CMD_BUF_LEN];	//ken:���������������ݶ�
	struct {
		u8		CmdStartByte;					//JK������ʼ��'#'	
		u8		Header[CMD_HEADER_LEN];			//����ͷ��XXX
		u8		Dot1;							//����ͷ���1��','��
		u8		NetNum;							//����
		u8		Dot2;							//����ͷ���2��','��
		u8		Adr[RX_ADR_WIDTH_24L01];		//��ģ���ַ
		u8		Dot3;							//����ͷ���3��','��
		u8 	Others[CMD_OTHERS_LEN];			//������������������ַ�
	}part;
}CMD_BODY_TypeDef;


// �Զ��干����������մ����������� CMD_BUF
typedef struct _CMD_BUF_TypeDef{				
 	CMD_BODY_TypeDef * pCmd_Body;			//ָ�����������������
	CMD_BODY_TypeDef * pReplyBuf;			//Ӧ�𻺳���		
//	uint16_t 	HeadHash;					//���������Hashͷ������ɢת
	u8		CmdTxFlag[CMD_NUMLMT];		//�����״̬
	u8		CmdListNum;					//�������������
	u8		CmdListFlag[CMD_NUMLMT];	//��¼���������ʹ�����
			
}CMD_BUF_TypeDef;

extern @near CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
extern @near CMD_BUF_TypeDef CmdBuf;	//����������
extern @near CMD_BUF_TypeDef * pCmdBuf;	//ָ������������




//u8 HeartBeat(u8 * pHeartBeatAdr);
void SendHeartBeat(void);
u8 NetApply(u8 * pNewAdr);
u8 NewConnect(u8 * pNewAdr);
//void CheckConnect(void);
void FreHopping(u8 SPIx , u8 Fre);
void RandomDelayUs(void);
void NetConnect(bool Sta);
void SysRun(void);
void Slv_CmdCnt(u8 stacnt);
void Synchronize(u8 * pCmd);
//void DataReceive(void);
void DataSend(void);
//void Broadcast(u8 * TxStr);
void SPI1_CMDTMP(void);

#endif
