/* Includes ------------------------------------------------------------------*/
#include "Global.h"


@near u8 U1RxCmdFlag;		//�յ�һ���������������Լ�1����ֵ��ʾ��ǰ���������������
//@near u8 U2RxCmdFlag;
//u8 U1NewFlag;		//SPI1�յ�������
//u8 U2NewFlag;		//SPI2�յ�������
           
@near u8 U1RxFullFlag;
//@near u8 U2RxFullFlag;
//extern u8 pdata txIndex;
@near u8 U1RxIndex;
@near u8 U1RxPindex;
//@near u8 U2RxIndex;		 
//@near u8 U2RxPindex;        
@near u8 U1ParseBuf[USARTBUFLEN];
//@near u8 U2ParseBuf[USARTBUFLEN];

@near u8 U1TxBuf[USARTBUFLEN];
//@near u8 U2TxBuf[USARTBUFLEN];
@near u8 U1RxBuf[USARTBUFLEN];
//@near u8 U2RxBuf[USARTBUFLEN];

//__IO u8 Usart1TxIndex;
//__IO u8 Usart2TxIndex;
//__IO u8 Usart1RxIndex; 
//__IO u8 Usart2RxIndex;

@near CMD_BODY_TypeDef Cmd_Body[CMD_NUMLMT];	//����������
@near CMD_BUF_TypeDef CmdBuf;	//����������
@near CMD_BUF_TypeDef * pCmdBuf;	//ָ������������

//���ݳ����򴮿ڷ����ַ���
void Uart1_SendString(u8 *string , u16 len)
{	u8 *tstr;
	u16 iLoop;
	tstr = string;	
	for (iLoop=0; iLoop<len; iLoop++)
	{
		UART1->DR = *tstr;
		while(0 ==(UART1->SR & UART1_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
		tstr++;
	}
}
//�򴮿ڷ����ַ�����ֱ��'\0'Ϊֹ	
//====================================================================================//
void Uart1_SendString_End(u8 *string)
{	u8 *tstr;	
	tstr = string;
	while(*tstr != '\0')
	{
		if(*tstr == '\0'){
			Delay(1);
		}
		UART1->DR = *tstr;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
		while(0 ==(UART1->SR & UART1_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
		tstr++;	
	}
}

//�򴮿ڷ���һ�ֽڣ�	
//====================================================================================//
void Uart1_SendByte(u8 byte)
{			
	UART1->DR = byte;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
	while(0 ==(UART1->SR & UART1_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
}


//****************************************************************************************************
//*���ܣ�Usart1���մ�����	
//*������
//****************************************************************************************************/
void Usart1_Rx_Parse(void)
{
  u8 LoopStart,LoopEnd,Loopi;
  u16 comnum;	

	if(0 != U1RxCmdFlag ){								
		for(LoopStart = U1RxPindex; LoopStart < U1RxIndex; LoopStart++){
			if(U1RxBuf[LoopStart] == '#'){//�ҵ�����ͷ��	
				for(LoopEnd = LoopStart; LoopEnd < U1RxIndex; LoopEnd++){	//�ҽ�β
					if(U1RxBuf[LoopEnd]=='\n'){//�ҵ�����ͷ��
						U1RxCmdFlag--;	//ÿ����һ�������������������Լ�
						U1RxPindex = LoopEnd + 1;
					break;
					}
				}
				comnum = Hash(U1RxBuf+LoopStart+1 , UCMDHASHLEN);	//��������Hashͷ
				switch (comnum){	//����ɢת
					
					case (UCMD_NETCNT):	//��λ�����͵�����������մ�ģ���ַ  "#NETCNT\r\n";
						WorkSta1 = STA_NETCONNECT;
					break;
					case (UCMD_PSWCTL):	//��λ���Ŀ��ؿ�������	"#PSWCTL,00000,0,0\r\n";
						CmdApply(U1RxBuf + LoopStart ,LoopEnd - LoopStart);		//������浽����������		
					break;
					
					default:
					//	Usart_SendString_End(USART1 ,StrError);		//�������������޷�����
					break;
							
				}
				
			//��ջ�����
			if((0 == U1RxCmdFlag)||(U1RxIndex >= U1PARSEBUFLEN))
			for (Loopi = 0; Loopi < U1PARSEBUFLEN; Loopi++){
	 			U1RxBuf[Loopi] = 0;	
			}
	  		U1RxIndex   = 0;
			U1RxPindex = 0;
			U1RxFullFlag = 0;
		//	U0Pindex  = 0;		
			}
		} 
	//	if(0 != SPI1OkFlag){	
	//		SPI1OkFlag--;	
	//	}
	}

}

/*********************ken********************************** 
*   ����˵���� ����������������                                
*   ���룺  Uint16 *pCmdPos Ϊ����������ĵ�ǰ���ڽ��յ������Ӧ��������
*                  
*   �����  �������������ɹ��������������������������׵�ַ������NULL��ʾ�������ɹ�                            
*   ���ú�����void                                       
***********************************************************/ 
u8 CmdApply(u8 *pCmdPos , u8 CmdLen)	//ken:����������������
{
	u8	loopi,loopj;
//	CMD_BUF_TypeDef *pRxBuf = NULL;
	if((pCmdBuf->CmdListNum < CMD_NUMLMT)&&(CmdLen < CMD_BUF_LEN)) {
		// ѭ���б� Ѱ�ҿ�Buffer CmdIndex����ָ��յ�buffer
		for(loopi = 0 ; loopi < CMD_NUMLMT ;loopi++){	//Ѱ�ҿյ������ռ�
			if(0 == pCmdBuf->CmdListFlag[loopi]){
		 		pCmdBuf->CmdListFlag[loopi] = 0x10;		//�ҵ��յ������ռ�
				pCmdBuf->CmdListNum++;
				break;
			}			
		}

		pCmdBuf->pCmd_Body = & (Cmd_Body[loopi]);	//ָ��յĴ�ģ���ַ�ռ�

		
		for(loopj = 0 ; loopj < CmdLen ; loopj++){
			pCmdBuf->pCmd_Body->all[loopj] = * (pCmdPos + loopj);	//���½��յ�������浽�յĽ�������ռ���
		}
		
		return 1;
	}
	else{
		return 0;
	}
//	return pRxBuf;		//ken:�����������������׵�ַ
}



//====================================================================================//

