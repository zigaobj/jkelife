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

volatile STA24L01 Mst24L01Sta = TXSTATUS,Slv24L01Sta = RXSTATUS;

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

//---------------------------------------------------------------------------
// MsgInsrt: 	
// �ظ�������Ϻ���:�νӴ��ĵ�һλ����Ϊ'\0'
//---------------------------------------------------------------------------

void MsgInsrt(uint8_t * pTarget, uint8_t * pSource, uint16_t MsgLen)
{
	uint8_t i=0, j=0;

	while(pTarget[i]){i++;}			// Ѱ���νӴ���'\0'
//	if (i) pTarget[i++] = ',';		// �����ǿ�ͷ�� �����','
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


