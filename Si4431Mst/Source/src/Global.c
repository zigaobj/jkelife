#include "stm32f10x.h"
#include "Global.h"


/* Private variables ---------------------------------------------------------*/ 
volatile RUN_TIME_TYPE GlobalRunTime;	//��¼ϵͳ�ϵ�������ʱ��
volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2,StartTimeMs3,EndTimeMs3;

//uint8_t SPI1_ParseBuf[SPI1PARSEBUFLEN];				//SPIy_Buffer_Rx

uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;
volatile SysWorkStatus WorkSta1 = STA_SLEEP;			//����ϵͳ�Ĺ���״̬
volatile SysWorkStatus WorkStaPre1 = STA_SLEEP;		//����ϵͳ��ǰһ������״̬
volatile SysWorkStatus WorkSta2 = STA_SLEEP;		//����ϵͳ�Ĺ���״̬
volatile SysWorkStatus WorkStaPre2 = STA_SLEEP;		//����ϵͳ��ǰһ������״̬

//volatile STA24L01 Mst24L01Sta = TXSTATUS,Slv24L01Sta = RXSTATUS;

__IO uint32_t TimingDelay;

uint8_t TestStr[] = "USART1TEST\r\n";
uint8_t TxNoReply[] = "TxNoReply\r\n";
uint8_t RxNotMatch[] = "RxNotMatch\r\n";
uint8_t RxMatch[] = "RxMatch\r\n";

uint8_t TestWord[] = "A";

uint8_t StrError[] = "Error!";

uint8_t MSGRP_OK[] = "OK\0";
uint8_t MSGRP_ERR[] = "ER\0";
/* Private functions ---------------------------------------------------------*/





/**
  * @brief  Inserts a delay time.
  * @param nTime: specifies the delay time length, in us.  ������TimingDelayΪȫ�ֱ�������������ͬʱ����DelayUs�������
  * @retval : None
  */
void DelayUs(__IO uint32_t usTime)
{ 
 SysTick->CTRL |=0x07; // ʹ��SysTick������
//   SysTick_CounterCmd(SysTick_Counter_Enable);	// ʹ��SysTick������
  TimingDelay = usTime;

  while(TimingDelay != 0);
  SysTick->CTRL &=0xFD;	// ֹͣSysTick��������������SysTick�쳣�жϣ������ڼ���
//  SysTick_CounterCmd(SysTick_Counter_Disable );	// �ر�SysTick������

}

void DelayCom(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

//=============================================================================================
//˵��:�����ʱ//ϵͳʱ��72M �����
//����:time��ʱʱ�䣬��λus
//���:void
//����:void
//�޸�:2011-01-20			KEN			����
//=============================================================================================
void DelayUs_Soft(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //�����õ�17 
      while(i--) ;    
   }
}
//=============================================================================================
//˵��:�����ʱ//ϵͳʱ��72M �����
//����:time��ʱʱ�䣬��λms
//���:void
//����:void
//�޸�:2011-01-20			KEN			����
//=============================================================================================
void DelayMs_Soft(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //�����õ�18000
      while(i--) ;    
   }
}



/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}
//---------------------------------------------------------------------------
// ������������ֵ��������ɢת����	
// 
//---------------------------------------------------------------------------
uint16_t Hash(uint8_t *pStr, uint8_t len)  	
{  
	uint16_t result = 0,i;  
	for (i=0;i<len; i++) { 
		result += (pStr[i])*(i+1);
	}
	return result;  
}

///---------------------------------------------------------------------------
//˵�����������ݲ��뺯��	
//������pTargetĿ���ַ��pSourceԴ��ַ��MsgLen�����ַ����ȣ�AddDotFg�Ƿ����','�ż���'\0'��ʼ����
//���أ�void	
//---------------------------------------------------------------------------
void MsgInsrt(uint8_t * pTarget, uint8_t * pSource, uint16_t MsgLen ,u8 AddDotFg)
{
	u16 i=0, j=0;
	
	if(TRUE == AddDotFg){
		while(pTarget[i]){i++;}				// Ѱ���νӴ���'\0'
		if (i) pTarget[i++] = ',';		// �����ǿ�ͷ�� �����','
	}
	for( ;j<MsgLen; ) {
		pTarget[i++] = pSource[j++];
	}
	pTarget[i] = '\0';
}
//---------------------------------------------------------------------------
// �Զ����strlen������strlen���������� 	
// �ظ�������Ϻ���:�νӴ��ĵ�һλ����Ϊ'\0'
//---------------------------------------------------------------------------
uint16_t MyStrLen(uint8_t str[])
{
    uint16_t nlen = 0;
    uint8_t *p = str;
    while (p && *p++)
        nlen++;

    return nlen;
}


//=============================================================================================
//˵��:��ȡ��ǰ������ʱ��
//����:������������ʱ��
//=============================================================================================
timems_t ReadRunTime(void)
{/*	RUN_TIME_TYPE TmpRunTime;
	RUN_TIME_TYPE * pTmpRunTime;
	pTmpRunTime = &TmpRunTime; */
//	pTmpRunTime->MilliSecond = TIM3->ARR / 10 ;		//��õ�ǰTIM4����ֵ����λ��0.1ms����Ҫ����10
//	pTmpRunTime->Second = GlobalRunTime->Second;	//		
	return (GlobalRunTime.Second * 1000) + (TIM3->CNT / 10);	//תΪ���뼶ʱ��
}

//=============================================================================================
//˵��:����������е�ʱ���
//����:������������ʱ�䣬���������غ���Ϊ��λ��ʱ���
//=============================================================================================
timems_t CheckTimeInterval(timems_t StartTime,timems_t EndTime)
{
	if(EndTime < StartTime){
		return 0;
	}
	else{
		return (EndTime - StartTime);
	}
}
//---------------------------------------------------------------------------
//˵�������ݸ��ƿ�������	
//������pTargetĿ���ַ��pSourceԴ��ַ��MsgLenҪ���Ƶ��ַ�����
//���أ�void	
//---------------------------------------------------------------------------
void MsgCopy(u8 * pTarget, u8 * pSource, u16 MsgLen)
{
	u16 j;	
	for(j = 0 ;j<MsgLen; j++) {
		pTarget[j] = pSource[j];
	}
//	pTarget[i] = '\0';
}

////--------------------------------------------------------------------------- 	
//// �ظ�������Ϻ���
//// ken:����������ַ�������	
//u16 ReplyAppend(CMD_BODY_TypeDef *pRplyStr)
//{	u16		nCheckNum = 0 ,nRplyStrLen = 0;
//	u8		nCheckChar[2];
//	u8 		i;
//
//	while(pRplyStr->all[nRplyStrLen] != '\0'){nRplyStrLen++;}	//Ѱ�ҽ�β
//	//���볤��					
//	MyNumToStr(pRplyStr->part.CmdTotalLen,(nRplyStrLen + CMD_TAIL_LEN) , 3);	//���� *xor\r\n 5���ֽڳ���
//	
//	for(i=0;i < nRplyStrLen;i++) {
//		nCheckNum ^= pRplyStr->all[i];		//ken:����CheckSumֵ
//	}								
//	//ken:��CheckSumֵ��Ϊ�����ֽ�
//	nCheckChar[0] = nCheckNum >> 4;		//ken:����CheckSum��λ
//	nCheckChar[1] = nCheckNum & 0xF;	//ken:����CheckSum��λ
//	for (i=0;i<2;i++) {
//		if (nCheckChar[i]<=9)		{nCheckChar[i] += 48;}	//ken:��16����ת��ΪASCII��
//		else						{nCheckChar[i] += 55;}
//	}
//	
//	pRplyStr->all[nRplyStrLen++] = '*';
//	pRplyStr->all[nRplyStrLen++] = nCheckChar[0];		//���У���λ
//	pRplyStr->all[nRplyStrLen++] = nCheckChar[1];		//���У���λ	
//	pRplyStr->all[nRplyStrLen++] = '\r';
//	pRplyStr->all[nRplyStrLen++] = '\n';
//	 
//	MyNumToStr(pRplyStr->part.CmdTotalLen, nRplyStrLen , CMD_TOTAL_LEN);	//������תΪASCII�룬�����
//	return nRplyStrLen;
//}
	


/*********************ken********************************** 
*   ����˵���� �����������е��ַ�����ת��������                               
*   ���룺  pStr - �ַ����׵�ַ, DataLen - ��ֵλ��       				
*   �����  ������Ϊת�������ֵ ����Ϊ32 long��                            
*   ���ú�����void                                      
***********************************************************/ 
u32 MyStrToNum(u8 *pStr, u8	NumLen)		
{	u32	result = 0;
	u8 i;
	if(NumLen>10) {return result;}
	for(i=0;i<NumLen;i++) {
		if((pStr[i]>='0')&&(pStr[i]<='9')){
			result *= 10;
			result += (pStr[i] - '0');
		}
		else{
			return 	0;
		}
	}
	return 	result;
}

/*********************ken********************************** 
*   ����˵���� ��֪��λ��������תΪ�ַ�                               
*   ���룺  pStr - �ַ����׵�ַ,Num - Ҫת�������֣� NumLen - ���ֵ�λ��       				
*   �����  ������Ϊת�������ֵ ����Ϊ32 long��                            
*   ���ú�����void                                      
***********************************************************/ 

u8 MyNumToStr(u8 *pStr,u32 Num , u16 NumLen)
{	u16	i;
	u32 TmpNum;
	u8 *pStrEnd = pStr+NumLen;
	if(NumLen>10) {return 0;}
	for(i=1;NumLen>=i;i++) {
		TmpNum = Num % 10; //ken:ȡ���λ
		Num /=10;	
		*(pStrEnd-i) = TmpNum +'0';
	}
	//*pStrEnd = '\0';
	return 	1;
}

/*********************ken********************************** 
*   ����˵���� ��֪��λ��������תΪ�ַ�                               
*   ���룺  pTarget - �ַ����׵�ַ,pLSource - Ҫת����32λ�����׵�ַ�� NumLen - ���ֵ�λ��       				
*   �����  ������                            
*   ���ú�����void                                      
***********************************************************/ 
u8 MyLongToStr(u8 *pTarget ,u32 * pLSource , u16 NumLen)
{	u16	i,j,segment,temp;
	longWord32 Temp32;
	
	if(NumLen % 4 == 0){
		segment = NumLen / 4;	//
	}
	else{
		segment = NumLen / 4 + 1;
	}

	for(i = 0; i < segment; i++){
		Temp32.All32 = *(pLSource + i);
//	Serial[iLoop] = *(cSerialNumber+iLoop);
		for(j = 0; j<4; j++){
			temp = i*4+j;
			if(temp >= NumLen) break;
			pTarget[temp] = Temp32.Bit8[j];		
		}
	}
	//*pStrEnd = '\0';
	return 	1;
}

////===============================================================================//
//float ASC_Float(u8 *cString, u8 cLen)
//{
//	u8 iLoop;
//	u8 sign;
//	u8 digit;
//	float value  = 0.;
//	float value1 = .0;
//	sign  = 0;
//	digit = cLen;
//	
//	for(iLoop=0; iLoop<cLen; iLoop++) //������ݸ�ʽ�Ƿ�ϸ�������ϸ񷵻�999999
//	{
//		if(iLoop==0)
//		{
//			if(*(cString+iLoop)=='+')                                 sign = 0;//ȷ��Ϊ����
//		 	else if(*(cString+iLoop)=='-')	                          sign = 1;//ȷ��Ϊ����
//			else if((*(cString+iLoop)<=0x39)&&(*(cString+iLoop)>=0x30)) sign = 0;//ȷ��Ϊ����		
//		}
//	    if(*(cString+iLoop)=='.')               digit= iLoop;//ȷ��С����λ 
//		if(*(cString+iLoop)>0x39 || *(cString+iLoop)<0x30)
//		{
//			if((*(cString+iLoop)!='+')&&(*(cString+iLoop)!='-')&&(*(cString+iLoop)!='.'))
//			return(-999999);			
//		}	
//	}
//	
//	for(iLoop=0; iLoop<digit; iLoop++)
//	{     	
//		if((*(cString+iLoop)>=0x30) && (*(cString+iLoop)<=0x39))
//		{	
//			value = value*10.+(*(cString+iLoop)-0x30);//ת���������֣�
//		}
//		else
//		{
//			return(-999999);	
//		}
//	}
//
//	for(iLoop=cLen-1; iLoop>digit; iLoop--) 
//	{
//		if((*(cString+iLoop)>=0x30) && (*(cString+iLoop)<=0x39))
//		{
//			value1 = (value1+(*(cString+iLoop)-0x30))/10.;//ת��С�����֣�
//		}
//		else
//		{
//			return(-999999);	
//		}	
//	}	
//	value += value1;
//	
//	
//	     if(sign==0) return(value);
//	else if(sign==1) return(-value);
//	return(1);	
//}

