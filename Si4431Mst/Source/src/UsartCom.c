/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Global.h"



//���ݳ����򴮿ڷ����ַ���
void Usart_SendString(USART_TypeDef* USARTx , uint8_t *string , uint16_t len)
{	uint8_t *tstr;
	uint16_t iLoop;
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	tstr = string;	
	for (iLoop=0; iLoop<len; iLoop++)
	{
		USARTx->DR = *tstr;
		while(0 ==(USARTx->SR & USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
		tstr++;
	}
}
//�򴮿ڷ����ַ�����ֱ��'\0'Ϊֹ	
//====================================================================================//
void Usart_SendString_End(USART_TypeDef* USARTx , uint8_t *string)
{	uint8_t *tstr;	
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
  
	tstr = string;
	while(*tstr != '\0')
	{
		if(*tstr == '\0'){
			DelayUs(1);
		
		}
		
		USARTx->DR = *tstr;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
		while(0 ==(USARTx->SR & USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
		tstr++;	
	}
}

//�򴮿ڷ���һ�ֽڣ�	
//====================================================================================//
void Usart_SendByte(USART_TypeDef* USARTx , uint8_t byte)
{		
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));		
	USARTx->DR = byte;
	//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USART_ClearFlag(USARTx, USART_FLAG_TC);
	while(0 ==(USARTx->SR & USART_FLAG_TC));	//�ȴ�������ɱ�־λ
	//	USARTx->SR = (uint16_t)~USART_FLAG_TC;		//�巢����ɱ�־λ
}


//****************************************************************************************************
//*���ܣ�Usart1���մ�����	
//*������
//****************************************************************************************************/
void Usart1_Rx_Parse(void)
{
  uint8_t LoopStart,LoopEnd,Loopi;
  uint16_t comnum;	

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
uint8_t CmdApply(uint8_t *pCmdPos , uint8_t CmdLen)	//ken:����������������
{
	uint8_t	loopi,loopj;
//	CMD_BUF_TypeDef *pRxBuf = NULL;
	if((pCmdBuf->CmdListNum < CMD_NUMLMT)&&(CmdLen <= CMD_BUF_LEN)) {
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

