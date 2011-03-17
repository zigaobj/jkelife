//Ӧ�ó����ļ�


 /* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "stm32f10x.h"
#include "platform_config.h"
#include "Global.h"
#include "Si4431Api.h"
#include "Si4431App.h"

#include "CmdPrc.h"
#include "UsartCom.h"
#include "SPICom.h"
#include "GloVar.h"

//#include "24L01App.h"
//#include <time.h>

 /* Constant ------------------------------------------------------------------*/
//��ƵƵ����
/*
const uint8_t FreHopBuf[80] = {\
0x28,0x4A,0x38,0x10,0x74,0x62,0x0B,0x5D,0x3C,0x61,\
0x6B,0x71,0x68,0x11,0x16,0x2A,0x30,0x41,0x5A,0x03,\
0x12,0x14,0x17,0x79,0x08,0x41,0x2A,0x0F,0x58,0x0B,\
0x0A,0x74,0x36,0x27,0x15,0x14,0x31,0x28,0x36,0x23,\
0x05,0x32,0x5C,0x73,0x03,0x06,0x19,0x45,0x09,0x6E,\
0x33,0x74,0x38,0x65,0x17,0x45,0x52,0x06,0x17,0x2B,\
0x51,0x75,0x63,0x30,0x34,0x08,0x38,0x5D,0x13,0x04,\
0x42,0x54,0x48,0x4A,0x35,0x08,0x4B,0x64,0x78,0x35\
} ;		*/
 /* Global Variable ------------------------------------------------------------------*/
// ���±������ڳ�������
//CMD_BUF_TypeDef	CmdBuf[CMD_NUMLMT] = {0};	
//uint8_t	CmdListFlag[CMD_NUMLMT] = {0};	

/*********************ken********************************** 
*   ����˵���� �����еİ��ֽ�ASCII��ַ��32λ����ת��                               
*   ���룺  pStrAdr - �ַ����׵�ַ; NumAdr - 32λ���� ;sta = TRUE���ֽ�ASCII��ַת32λ����,sta = FALSE 32λ����ת���ֽ�ASCII��ַ     				
*   �����  ������Ϊת�������ֵ ����Ϊ32λ                            
*   ���ú�����void                                      
***********************************************************/ 
/*
u32 Si4431AdrCover(u8 *pStrAdr, u32 NumAdr ,bool sta )		
{	longWord32	tmpval ;
	u8 i;
	if(sta){	//���ֽ�ASCII��ַת32λ����
		tmpval.All32 = MyStrToHex(pStrAdr , CMDSPI_ADR_WIDTH);
//		pNumAdr[0] = tmpval.Bit8[0];
//		pNumAdr[1] = tmpval.Bit8[1];
//		pNumAdr[2] = tmpval.Bit8[2];
//		pNumAdr[3] = tmpval.Bit8[3];
		return 	tmpval.All32;
	}
	else{			//32λ����ת���ֽ�ASCII��ַ
		MyHexToStr(pStrAdr , NumAdr ,CMDSPI_ADR_WIDTH);			
		return 	NumAdr;
	}
}	
*/
/*	if(NumLen>10) {return result;}
	for(i=0;i<NumLen;i++) {
		if((pStr[i]>='0')&&(pStr[i]<='9')){
			result *= 10;
			result += (pStr[i] - '0');
		}
		else{
			return 	0;
		}
	}
	return 	result;	*/



//=============================================================================================
//˵��:��Ƶ����
//����:SPIx:ѡ��SPI�ڣ�Fre����Ҫ���õ�Ƶ��ȡֵ��Χ0x00-0x7D
//=============================================================================================
void FreHopping(uint8_t SPIx , uint8_t Fre)
{
/*
	SPI1_CE_L;	//StandBy Iģʽ
	if(SPI1CH == SPIx){
		SPI1_RWReg(WRITE_REG_24L01 + RF_CH_24L01, Fre);	//�����ŵ�����ΪF0= 2400 + RF_CH [MHz]���շ�����һ�� 	//��Ƶʱ��Ҫ�ı�
	}
	else if(SPI2CH == SPIx){
		SPI2_RWReg(WRITE_REG_24L01 + RF_CH_24L01, Fre);	//�����ŵ�����ΪF0= 2400 + RF_CH [MHz]���շ�����һ�� 	//��Ƶʱ��Ҫ�ı�		
	}
	*/
}

//=============================================================================================
//˵��:(α)�����ʱ����
//����:��Ҫ���õ�Ƶ��
//=============================================================================================
void RandomDelayUs(void)
{
	uint8_t k; 	//i,
//	uint32_t t;
//	__NOP();	//�ղ���
//	srand((unsigned) time(&t));//��������Ǹ������rand()����һ��������ӣ�seed��������ԭ����srand�� ��unsigned�� time��NULL����
//	srand((unsigned) time(NULL));
//	t = clock();
//	t = SysTick->VAL;	//��SysTick��ǰ��ֵ�Ĵ�������һ��0~72�����ֵ
//	srand((unsigned) t);	//������������Ӻ����������ڱ�ֵ�ĵط����ã���������
//	printf("Ten random numbers from 0 to 99nn");
//	for(i=0; i<10; i++)
	k = rand()%(RANDMAX - RANDMIN + 1) + RANDMIN ;	//���������Χ��RANDMIN~RANDMAX
//	printf("%dn", rand()%100);
	DelayUs_Soft(k);
#ifdef DEBUGJK
//	Usart_SendByte(USART1 , k);
#endif
}

//****************************************************************************************************/
//*������void SetSPI1_BroadCast(void)
//*���ܣ���SPI1���ӵ�24L01����Ϊ�㲥��ַ���ҽ���ģʽ 
//****************************************************************************************************/

void NetConnect(bool Sta)
{
	if(TRUE == Sta){	//����		
		Si4431TX_ReceiveMod(TRUE ,NetConnectRxAdr);		//�������յ�ַ	
		WorkStaPre1 = STA_NETCONNECT;
	}
  else{	//�˳�����״̬ 	
  	Si4431TX_ReceiveMod(TRUE ,RX_ADDRESS_Si4431);	//�ص�ԭ�����յ�ַ	
		WorkStaPre1 = STA_STANDBY;
//  IRDA_LED_OFF();
	}
//	SPI1_CE_L;	//StandBy Iģʽ
//	SPI1_CSN_H;	//NSS����	
//	SPI1_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0_24L01, NetConnectRxAdr, RX_ADR_WIDTH_24L01); // д���ն˵�ַ	
//	SPI1_RWReg(WRITE_REG_24L01 + CONFIG_24L01, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
//	SPI1_CE_H;	//�ø�CE���������ݷ���
//	SetSPI1_RXMode();
} 

//=============================================================================================
//˵��:������������ģ���ַ��������ʽ���棬ÿ������һ�α����ַ�ռ�����
//����:pNewAdrָ����������ַ��AdrLen��ַ���ȣ��ɹ������ַ����������1�����򷵻�0��ʾ��ַ�ռ�������
//=============================================================================================
uint8_t NewConnect(uint8_t * pNewAdr)
{	uint8_t loopi,loopj;//TmpSta;
	uint8_t strNTA[32] = "#NTA,00000,00000\r\n";	//��������ģ��
//	uint8_t strACN[14] = "#ACN,0,00000\r\n";		//���͸���λ��
	u8	OrgSlvAdd[5] = {0};
  if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){	//������ģ���ַ����ռ���
  	Usart_SendString_End(USART1 , "JKNetAdrTab is Full!\r\n");
		return 0;

  }
  else{
	
	for(loopi = 1 ; loopi < JKNETADRTABLEN ;loopi++){	//Ѱ�ҿյĴ�ģ���ַ�ռ�
		if(0 == pJKNetAdr_Tab->TabFlag[loopi]){
		 	pJKNetAdr_Tab->TabFlag[loopi] = 0x10;	//�ҵ��մ�ģ���ַ�ռ�
			pJKNetAdr_Tab->HeartBeatSta[loopi]	= MAXMISSHEART;		//��ʼ������������
			break;
		}			
	}
	pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * loopi);	//ָ��յĴ�ģ���ַ�ռ�
	
//	strACN[5] = loopi;		//�������
	//Ϊ�����ӵĴ�ģ�����������µ�ַ�����浽�յĽ��յ�ַ�б�
	pJKNetAdr_Tab->pJKNetAdrTabCnt[0] = MOD1_RXADR[1];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[1] = MOD1_RXADR[2];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[2] = MOD1_RXADR[3];
	pJKNetAdr_Tab->pJKNetAdrTabCnt[4] = loopi;	//��������˳����ӵ��ֶ�


	for(loopj = 0 ;loopj < SI4431_ADR_WIDTH ; loopj++){
		OrgSlvAdd[loopj]	= * (pNewAdr+loopj);	//ԭ���Ĵ�ģ���Rx��ַ
//		pJKNetAdr_Tab->pJKNetAdrTabCnt[loopj] = * (pNewAdr+loopj);	//�������ӵĴ�ģ���ַ���浽�յĽ��յ�ַ�б�
//		strACN[loopj + 7] = * (pNewAdr+loopj);	//��ģ���Rx��ַ
	}
		
	
	//�����ɹ������ģ�鷢���µ�TX��ַ(����ģ��RX_P1~P5��RX��ַ)
	//����������ģ���϶�Ӧ�ĵĴ�ģ�����ͨ����ַ�����淶 :(��Ҫ����24L01�淶)
	//��ģ��2 3 4 5�ֶε�ַ + ��������˳����ӵ��ֶ�
//	SetSPI1_TXMode(OrgSlvAdd);	//����������ģ�鷢�������µ�ַ��
	
//	DelayCom(50000);
//	TmpSta = SPI1_Read(TX_ADDR_24L01);	//����ģ���ַ�����Ƿ���ȷ
//	TmpSta = SPI1_Read(RX_ADDR_P0_24L01);	//����ģ���ַ�����Ƿ���ȷ



	strNTA[5] = OrgSlvAdd[0];
	strNTA[6] = OrgSlvAdd[1];
	strNTA[7] = OrgSlvAdd[2];
	strNTA[8] = OrgSlvAdd[3];
	strNTA[9] = OrgSlvAdd[4];		//ԭģ���ַ

	strNTA[11] = MOD1_RXADR[1];
	strNTA[12] = MOD1_RXADR[2];
	strNTA[13] = MOD1_RXADR[3];
	strNTA[14] = loopi;					//��������˳����ӵ��ֶ�

 	NET_LED_TURN();							//��ģ�������ɹ�
	CmdSpiTxApply(TRUE ,strNTA ,32);				//������浽����������

		/*
		for(loopj = 0 ;loopj < CMD_MAXRESEND ;loopj++){	
			nRF24L01_SPI1_TxPacket(strNTA);		//NTA�����µĴӽڵ�Tx��ַ

			StartTimeMs2 = ReadRunTime();
			while(!(SPI1Sta & MASK_TX_STA)){	//�ȴ�TX_DS��MAX_RT�ж�
				EndTimeMs2 = ReadRunTime();
				if( 50 < CheckTimeInterval(StartTimeMs2 , EndTimeMs2)){	//�����½ڵ��ַ��ʱ
					break;
				}	
			}
			#ifdef DEBUGJK
//			SPI1Sta = MAX_RT;	//������
			#endif			
			if(SPI1Sta & TX_DS){	//��������ͳɹ����������ģʽ���ȴ���ģ�鷢���µ�ַ
//				Usart_SendString(USART1 ,strACN , 14);		//ACN����������ճɹ����������յ��Ĵӽڵ�Rx��ַ��������ŵ�����1��
			//	SPI2_PWR_OFF();
			//	DelayUs(500);
				NET_LED_TURN();		//��ģ�������ɹ�
				DataReceive();
			//	WorkSta2 = STA_DATA;					
//				SPI2_CE_L;	//StandBy Iģʽ
				
				Init_NRF24L01_SPI2();
				NetConnect(TRUE);				//����Ϊ����ģʽ
				return 1;				
			}
			else if(SPI1Sta & MAX_RT){		//����ʧ�ܣ��ȴ��ط�
				RandomDelayUs();
				if(loopj == CMD_MAXRESEND-1){	//����������ط����������������ʧ��
//					Usart_SendString_End(USART1 , "CMDNTANoReply\r\n");
					//ACN����������ճɹ����������յ��Ĵӽڵ�Rx��ַ��������ŵ�����1��
					pJKNetAdr_Tab->TabFlag[loopi] = 0x00;	//�����������ַ���Ͳ��ɹ����������ģ���ַ��¼����Ϊ�������ɹ�
					return 0;
				}
			}			
		}	
		*/
/*	if(JKNETADRTABLEN > pJKNetAdr_Tab->JKNetAdrTabCnt){	//����JKNETADRTABLEN����ַ���ڴ洢
		pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (TX_ADR_WIDTH*pJKNetAdr_Tab->JKNetAdrTabCnt);	//ָ����һ���յĴ�ģ���ַ�ռ�
  	}	*/

  }
	return 0;
}

//=============================================================================================
//˵��:���������ϸ�ģ�鷢�͵����������������������������ö��д洢��
//����:����������1�ҵ���ģ�鲢��¼����������0��ʾδ�ҵ���ģ���ַ
//=============================================================================================
uint8_t HeartBeat(uint8_t * pHeartBeatAdr)
{	uint8_t TmpTabCnt,CmpFlag;
	uint8_t * pTmpTab;
//	RUN_LED_TURN();	//���յ�����IR����תһ��
	if(0 != pJKNetAdr_Tab->JKNetAdrTabCnt){	//�޴�ģ���������ü����������ַ
		for(TmpTabCnt = 0; TmpTabCnt < JKNETADRTABLEN; TmpTabCnt++){	//������ģ���ַ
			pTmpTab = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * TmpTabCnt);
			CmpFlag = Buffercmp(pTmpTab , pHeartBeatAdr , SI4431_ADR_WIDTH);
			if(1 == CmpFlag){	//��鵽��ַ
				pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]++;	//��������+1	
				return 1;				
			}						
		}
	}
	return 0;
}



//=============================================================================================
//˵��:��������ϸ�ģ������״̬�������ʱû��⵽������������Ϊ������
//����:���������ضϿ����ӵĴ�ģ�����
//=============================================================================================
void CheckConnect(void)
{	uint8_t TmpTabCnt,TmpDelCount;
	u8 strMod[] =	"Miss Mod000!\r\n"; 
//	SetSPI1_TXMode
	if(0 != pJKNetAdr_Tab->JKNetAdrTabCnt){	//�޴�ģ���������ü����������ַ
		for(TmpTabCnt = 1; TmpTabCnt < JKNETADRTABLEN; TmpTabCnt++){	//	
			if(0x10 == pJKNetAdr_Tab->TabFlag[TmpTabCnt]){	//�д�ģ���ַ�Ŀռ����		
				if(0 != pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]){
					pJKNetAdr_Tab->HeartBeatSta[TmpTabCnt]--;	//	
				}
				else{	//��Ϊ�д�ģ��������
				/*	Usart_SendString_End(USART1 ,"Miss Mod");		//�����ڷ�ģ���		 
					Usart_SendByte(USART1 ,TmpTabCnt/100 + 0x30);
					Usart_SendByte(USART1 ,TmpTabCnt%100/10 + 0x30);
					Usart_SendByte(USART1 ,TmpTabCnt%100%10 + 0x30);
					Usart_SendByte(USART1 ,"!\r\n");	*/
					strMod[8] = TmpTabCnt/100 + 0x30;
					strMod[9] = TmpTabCnt%100/10 + 0x30;
					strMod[10] = TmpTabCnt%100%10 + 0x30;
				//	Usart_SendString_End(USART1 , strMod);
					pJKNetAdr_Tab->TabFlag[TmpTabCnt] = 0;
					IRDA_LED_TURN();	//��ģ��������	
				}
			}
		}
	}

	for(TmpDelCount = TmpTabCnt ;TmpDelCount < pJKNetAdr_Tab->JKNetAdrTabCnt; TmpDelCount++ ){
			
	}

/*	if(i==0) preDepth[channel][++i] = iDepth; //��һ��ˮ��ֱֵ�Ӹ�ֵ
	else
	{
		for(j=i; j>0; j--)		//ken:preDepth[]�У�ˮ��ֵ��С������
		{
			if(iDepth<preDepth[channel][j])//�����ǰˮ��ֵ�Ȳ鵽��ˮ��ֵС
			{
				 preDepth[channel][j+1] = preDepth[channel][j];//����λ��ˮ��ֵ����Ųһ��
			 	 if(j==1) preDepth[channel][j] = iDepth;//������ǰ�ˣ�����ǰˮ��ֵ����
			}
			else
			{
				preDepth[channel][j+1] = iDepth;	//�����ǰˮ��ֵ���ڵ�������ˮ��ֵ���������
				break;//�ҵ�λ�ú������ֱ�ѭ��
			}
		}
		i++;
	}
	*/
}

//=============================================================================================
//˵��:ͬ�����������ڷ���ͬ��ʱ��
//����:
//=============================================================================================
/*
void Synchronize(void)	//ͬ���������ʱ����Ϣ��
{
	uint8_t strSYN[32] = "#SYN,00\r\n";	//16λTIM3->CNT��λ��ǰ
//	uint8_t strindex,Temp_TIM3CNT;	,TempSta = 0
	uint8_t loopi;	

	for(loopi = 1 ; loopi < JKNETADRTABLEN ;loopi++){	//Ѱ�Ҵ�ģ���ַ�ռ�
		if(0x10 == pJKNetAdr_Tab->TabFlag[loopi]){	//�ҵ����д�ģ���ַ�Ŀռ�				
			pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * loopi);	//ָ���ģ���ַ�ռ�
			Si4431TX_TransmitMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);		//����SPI1���ӵ�24L01Ϊ����ģʽ���������䷢���ַΪ����ģ���ַ
			strSYN[5] = 0x00FF & (TIM3->CNT)>>8;	//��ģ����պ��������������TIMx->CNTRH �� TIMx->CNTRL
			strSYN[6] = 0x00FF & TIM3->CNT;	
			Si4431TX_TxPacket(strSYN, sizeof(strSYN));	//����ͬ������
		}			
	}
		WorkStaPre1 = STA_SYNCHRONIZE;

}*/

//*********************************************************************************************************
//*���ܣ�����������������
//*����: stacnt��ʾ������1���Ƕ���0
//*********************************************************************************************************/
void SPI2_CMDCNT(uint8_t stacnt)
{
	uint8_t strCNT[32] = "#CNT,00000\r\n";
	uint8_t strindex;
	if(1 == stacnt){	//��ģ��תΪ����ģʽ
	//	SetSPI2_TXMode(NetConnectRxAdr);		//����SPI2���ӵ�24L01Ϊ����ģʽ���������䷢���ַΪ�㲥��ַ
		
		for(strindex=0;strindex<SI4431_ADR_WIDTH;strindex++){
			strCNT[5+strindex] = MOD2_TXADR[strindex];	
		}
		Si4431TX_TxPacket(strCNT ,sizeof(strCNT));
	}
	else{
	
	}
 
}

//*********************************************************************************************************
//*���ܣ��㲥�׶Σ������������Ĵӽڵ㷢�͹㲥��Ϣ
//*����: 
//*********************************************************************************************************/
/*
void Broadcast(uint8_t * TxStr)
{u8 Loopi;
	for(Loopi = 1 ; Loopi < JKNETADRTABLEN ;Loopi++){	//Ѱ�Ҵ�ģ���ַ�ռ�
		if(0x10 == pJKNetAdr_Tab->TabFlag[Loopi]){	//�ҵ����д�ģ���ַ�Ŀռ�				
			pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * Loopi);	//ָ���ģ���ַ�ռ�
			Si4431TX_TransmitMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);		//����SPI1���ӵ�24L01Ϊ����ģʽ���������䷢���ַΪ����ģ���ַ
			Si4431TX_TxPacket(TxStr ,sizeof(TxStr));
		//	pJKNetAdr_Tab->LoopJKNetAdrIndex = Loopi;
		//	TempSta = 1;
			break;
		}			
	}		

}	 */

//*********************************************************************************************************
//*���ܣ����ݷ��ͣ�����Ҫ���ƵĴ�ģ�鷢�������������������е��������ݷ������ӽڵ�
//*����: 
//*********************************************************************************************************/
void DataSend(void)
{
//	uint8_t strindex,Temp_TIM3CNT;	,TempSta = 0
	uint8_t loopi,loopj;
	si4431adrtype TxAdr;	
	if(0 != pCmdSpiTxBuf->CmdListNum){			
		for(loopi = 0 ; loopi < CMDSPI_TXLIST_LMT ;loopi++){	//Ѱ�Ҵ��д�������Ŀռ�
			if(0 != pCmdSpiTxBuf->CmdListFlag[loopi]){	
				pCmdSpiTxBuf->pCmd_Prc_Current = &(pCmdSpiTxBuf->Cmd_Body[loopi]);	//�ҵ������͵�������
				TxAdr.HexAdr.All32 =  MyStrToHex (pCmdSpiTxBuf->pCmd_Prc_Current->part.TargetAdr, CMDSPI_ADR_WIDTH);
		
				Si4431TX_TransmitMod(TxAdr);		//����Ϊ����ģʽ�������ַ			
				Si4431TX_TxPacket(pCmdSpiTxBuf->pCmd_Prc_Current->all , FIFO_THRESHOLD);	//��ӽڵ㷢������
				DelayMs_Soft(100);
				if(CMD_REPLYSEND_NUM == pCmdSpiTxBuf->CmdListFlag[loopi]){				//�ҵ�Ҫ���������Ӧ�Ĵ�ģ���ַ							
					pCmdSpiTxBuf->CmdListFlag[loopi] = 0;	//�ظ�����ֱ��һ��  
					pCmdSpiTxBuf->CmdListNum --;						//�����������ֵ��һ
				}
				else{
					if(1 == pCmdSpiTxBuf->CmdListFlag[loopi]){	//��������ʧ��
						__NOP();	//��Ҫ������λ��������Ͳ��ɹ� 
						pCmdSpiTxBuf->CmdListFlag[loopi] = 0;	//�ظ�����ֱ��һ��  
						pCmdSpiTxBuf->CmdListNum --;						//�����������ֵ��һ
					}
					else{
						pCmdSpiTxBuf->CmdListFlag[loopi] --;	//ÿ����һ�Σ�����һ�η��ͼ�����ֵ 
					}
				}
			}	
				//StartTimeMs2 = ReadRunTime();	
		}
	}
	//������ϻص�����״̬
	Si4431TX_ReceiveMod(FALSE , RX_ADDRESS_Si4431);
		
}

//=============================================================================================
//˵��:Si4431���ݽ��ս׶Σ�������������ͨ���ĵ�ַ
//����:void
//���:void
//����:Si4431RX_ReceiveMod;SPI2_Read();
//�޸�:2011-01-26			KEN			����
//=============================================================================================
/*
void DataReceive(void)
{uint8_t iLoop;				 //,RxPnCnt = 1
//  if(pJKNetAdr_Tab->JKNetAdrTabCnt > JKNETADRTABLEN){	//��������Ĵ�ģ����������JKNETADRTABLEN������DATA�׶���Ҫ�ֻ�Rx_P0~P5����ͨ���ĵ�ַ
//	for(Loopi = pJKNetAdr_Tab->TabIndex ; Loopi < JKNETADRTABLEN ;Loopi++){	//Ѱ�Ҵ�ģ���ַ�ռ�
	
	if(pJKNetAdr_Tab->JKNetAdrTabCnt){										//��ģ�������Ž���		
		iLoop = pJKNetAdr_Tab->LoopJKNetAdrIndex + 1;				//����ϴ���ѯ����������ַpJKNetAdr_Tab->TabIndex
		if(JKNETADRTABLEN == iLoop) {
			iLoop = 0;	
		}				//ѭ����ѯ
		while(0x10 != pJKNetAdr_Tab->TabFlag[iLoop]){ 		//�ҵ����д�ģ���ַ�Ŀռ�
			iLoop++;			
		};	
		
		pJKNetAdr_Tab->pJKNetAdrTabCnt = pJKNetAdr_Tab->JKNetAdrTab0 + (SI4431_ADR_WIDTH * iLoop);	//ָ���ģ���ַ�ռ�
		Si4431RX_ReceiveMod(pJKNetAdr_Tab->pJKNetAdrTabCnt);			//����SPI2����ͨ����ַΪ����ģ���ַ
		
	  pJKNetAdr_Tab->LoopJKNetAdrIndex = iLoop;		//��¼�����ѯ����������ַ			
	}
}
*/

//=============================================================================================
//˵��:״̬��������������ģ���������״̬�µ�����
//����:
//=============================================================================================
void SysRun(void)
{
  switch(WorkSta1){
	case(STA_NETCONNECT):		//���������׶�
		if(STA_NETCONNECT != WorkStaPre1){
			NetConnect(TRUE);				//����Ϊ����ģʽ
	  	StartTimeMs1 = ReadRunTime(); 
	  }
/*	  else {
	  	EndTimeMs1 = ReadRunTime();
		if( NETCNT_TIMEOUT < CheckTimeInterval(StartTimeMs1 , EndTimeMs1)){	//������ʱ
		  NetConnect(FALSE);			//�˳�����ģʽ
		  WorkSta1 = STA_STANDBY;		//�������״̬
	  	
			} 
	  }*/
	break;
	case(STA_SYNCHRONIZE):	//ͬ���׶�
  //    if(STA_SYNCHRONIZE != WorkStaPre1){  
	//	Synchronize();		//ͬ���������ʱ����Ϣ��
	//  }
	break;
	case(STA_BROADCAST):	//�㲥�׶Σ�����Ҫ���ƵĴ�ģ�鷢������
 //     	Broadcast();		//�����ģ�鷢�Ϳ�������
		DataSend();
		WorkSta1 = STA_STANDBY;
	break;

	case(STA_P2P):			//�������ݵ�Ե㴫��
      
	break;
	case(STA_SLEEP):		//����ģʽ
      
	break;    
	case(STA_STANDBY):		//����״̬
		WorkStaPre1 = STA_STANDBY;
	break;
	default:
	
    break;
  }


  switch(WorkSta2){  
	case(STA_DATA):			//ά������������ͨ���ݲɼ��׶�	
//		DataReceive();

	/*	if(STA_DATA != WorkStaPre2){
	//	SetSPI1_RXMode(RX_P0_24L01,MOD1_RXADR);	//����Ϊ����ĵ�ַ
			DataReceive();
			WorkStaPre2 = STA_DATA;
			StartTimeMs3 = ReadRunTime();
		}
		else{
	  	EndTimeMs3 = ReadRunTime();
			if( DATARECEIVE_SPAN < CheckTimeInterval(StartTimeMs3 , EndTimeMs3)){	//������ʱ
				WorkSta2 = STA_STANDBY;	
			
			}			
		}	*/		        
	break;
	case(STA_STANDBY):			//ά������������ͨ���ݲɼ��׶�
	
	break; 
	case(STA_SLEEP):		//����ģʽ
      
	break;
	default:
	
    break;  
  }  		
}
