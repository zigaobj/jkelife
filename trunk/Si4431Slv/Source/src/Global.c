#include "stm8s_conf.h"
#include "Global.h"


/* Private variables ---------------------------------------------------------*/ 
volatile RUN_TIME_TYPE GlobalRunTime;	//记录系统上电后的运行时间
volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2;

//uint8_t SPI1_ParseBuf[SPI1PARSEBUFLEN];				//SPIy_Buffer_Rx

u8 TxIdx = 0, RxIdx = 0, k = 0;
//@near volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//@near volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;
@near volatile SysWorkStatus WorkSta1 = STA_SLEEP;			//整个系统的工作状态
@near volatile SysWorkStatus WorkStaPre1 = STA_SLEEP;		//整个系统的前一个工作状态
@near volatile SysWorkStatus WorkSta2 = STA_SLEEP;		//整个系统的工作状态
@near volatile SysWorkStatus WorkStaPre2 = STA_SLEEP;		//整个系统的前一个工作状态

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
  * @param nTime: specifies the delay time length, in us.  但由于TimingDelay为全局变量，两个程序同时调用DelayUs会出问题
  * @retval : None
  */
	/*
void DelayUs(__IO uint32_t usTime)
{ 
 SysTick->CTRL |=0x07; // 使能SysTick计数器
//   SysTick_CounterCmd(SysTick_Counter_Enable);	// 使能SysTick计数器
  TimingDelay = usTime;

  while(TimingDelay != 0);
  SysTick->CTRL &=0xFD;	// 停止SysTick计数器，不进入SysTick异常中断，但仍在计数
//  SysTick_CounterCmd(SysTick_Counter_Disable );	// 关闭SysTick计数器

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
//说明:软件延时//系统时钟72M 情况下
//输入:time延时时间，单位us
//输出:void
//调用:void
//修改:2011-01-20			KEN			初定
//=============================================================================================
void DelayUs_Soft(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=6;  //尹工用的17 
      while(i--) ;    
   }
}
//=============================================================================================
//说明:软件延时//系统时钟72M 情况下
//输入:time延时时间，单位ms
//输出:void
//调用:void
//修改:2011-01-20			KEN			初定
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
// 计算命令特征值函数用于散转命令	
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
// 回复内容组合函数:衔接处的第一位必须为'\0'
//---------------------------------------------------------------------------

void MsgInsrt(u8 * pTarget, u8 * pSource, u16 MsgLen)
{
	u8 i=0, j=0;

	while(pTarget[i]){i++;}			// 寻找衔接处的'\0'
//	if (i) pTarget[i++] = ',';		// 若不是开头， 则添加','
	for( ;j<MsgLen; ) {
		pTarget[i++] = pSource[j++];
	}
	pTarget[i] = '\0';
}
//---------------------------------------------------------------------------
// 自定义的strlen函数，strlen函数不好用 	
// 回复内容组合函数:衔接处的第一位必须为'\0'
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
//说明:读取当前的运行时间	需要转为ms级的时间
//参数:输入两次运行时间
//=============================================================================================
timems_t ReadRunTime(void)
{/*	RUN_TIME_TYPE TmpRunTime;
	RUN_TIME_TYPE * pTmpRunTime;
	pTmpRunTime = &TmpRunTime; */
//	pTmpRunTime->MilliSecond = TIM4->ARR / 10 ;		//获得当前TIM3计数值，单位是0.1ms所以要除以10
//	pTmpRunTime->Second = GlobalRunTime->Second;	//		
	u16 TmpCNT;
	TmpCNT = TIM3->CNTRH << 8;
	TmpCNT = TmpCNT + TIM3->CNTRL;
	TmpCNT = TmpCNT / 15.625;
	return (GlobalRunTime.Second * 1000) + TmpCNT;	//转为毫秒级时间
}

//=============================================================================================
//说明:计算程序运行的时间差
//参数:输入两次运行时间，函数名返回毫秒为单位的时间差
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


