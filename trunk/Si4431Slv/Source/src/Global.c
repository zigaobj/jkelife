#include "stm8s_conf.h"
#include "Global.h"


/* Private variables ---------------------------------------------------------*/ 
volatile RUN_TIME_TYPE GlobalRunTime;	//��¼ϵͳ�ϵ�������ʱ��
volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2;

//uint8_t SPI1_ParseBuf[SPI1PARSEBUFLEN];				//SPIy_Buffer_Rx

u8 TxIdx = 0, RxIdx = 0, k = 0;
//@near volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//@near volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;
@near volatile SysWorkStatus WorkSta1 = STA_SLEEP;			//����ϵͳ�Ĺ���״̬
@near volatile SysWorkStatus WorkStaPre1 = STA_SLEEP;		//����ϵͳ��ǰһ������״̬
@near volatile SysWorkStatus WorkSta2 = STA_SLEEP;		//����ϵͳ�Ĺ���״̬
@near volatile SysWorkStatus WorkStaPre2 = STA_SLEEP;		//����ϵͳ��ǰһ������״̬

//volatile STA24L01 Mst24L01Sta = TXSTATUS,Slv24L01Sta = RXSTATUS;

@near volatile u32 TimingDelay;

bool InNetFlag = FALSE;

const u8 TestStr[] = "USART1TEST\r\n";
const u8 TxNoReply[] = "TxNoReply\r\n";
const u8 RxNotMatch[] = "RxNotMatch\r\n";
const u8 RxMatch[] = "RxMatch\r\n";

const u8 TestWord[] = "A";

const u8 StrError[] = "Error!";
const u8 MsgReSendTimeOut[] = "MsgReSendTimeOut\0";
const u8 MSGRP_OK[] = "OK\0";
const u8 MSGRP_ERR[] = "ER\0";
/* Private functions ---------------------------------------------------------*/





/**
  * @brief  Inserts a delay time.
  * @param nTime: specifies the delay time length, in us.  ������TimingDelayΪȫ�ֱ�������������ͬʱ����DelayUs�������
  * @retval : None
  */
	/*
void DelayUs(__IO uint32_t usTime)
{ 
 SysTick->CTRL |=0x07; // ʹ��SysTick������
//   SysTick_CounterCmd(SysTick_Counter_Enable);	// ʹ��SysTick������
  TimingDelay = usTime;

  while(TimingDelay != 0);
  SysTick->CTRL &=0xFD;	// ֹͣSysTick��������������SysTick�쳣�жϣ������ڼ���
//  SysTick_CounterCmd(SysTick_Counter_Disable );	// �ر�SysTick������

}
*/

/**
  * @brief Dela+y.
  * @param[in] nCount
  * @retval 
  * None
  */
void Delay(u16 nCount)
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
      i=6;  //�����õ�17 
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
      for(i=0;i<490;i++)	
      _asm("");			
   } 
}




/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(u8 * pBuffer1, u8 * pBuffer2, u16 BufferLength)
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
u16 Hash(u8 *pStr, u8 len)  	
{  
	u16 result = 0,i;  
	for (i=0;i<len; i++) { 
		result += (pStr[i])*(i+1);
	}
	return result;  
}

//---------------------------------------------------------------------------
// MsgInsrt: 	
// �ظ�������Ϻ���:�νӴ��ĵ�һλ����Ϊ'\0'
//---------------------------------------------------------------------------

void MsgInsrt(u8 * pTarget, u8 * pSource, u16 MsgLen)
{
	u8 i=0, j=0;

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
u16 MyStrLen(u8 str[])
{
    u16 nlen = 0;
    u8 *p = str;

 

    while (p && *p++)
        nlen++;

    return nlen;
}


//=============================================================================================
//˵��:��ȡ��ǰ������ʱ��	��ҪתΪms����ʱ��
//����:������������ʱ��
//=============================================================================================
timems_t ReadRunTime(void)
{/*	RUN_TIME_TYPE TmpRunTime;
	RUN_TIME_TYPE * pTmpRunTime;
	pTmpRunTime = &TmpRunTime; */
//	pTmpRunTime->MilliSecond = TIM4->ARR / 10 ;		//��õ�ǰTIM3����ֵ����λ��0.1ms����Ҫ����10
//	pTmpRunTime->Second = GlobalRunTime->Second;	//		
	u16 TmpCNT;
	TmpCNT = TIM3->CNTRH << 8;
	TmpCNT = TmpCNT + TIM3->CNTRL;
	TmpCNT = TmpCNT / 15.625;
	return (GlobalRunTime.Second * 1000) + TmpCNT;	//תΪ���뼶ʱ��
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


