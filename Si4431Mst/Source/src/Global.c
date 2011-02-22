#include "stm32f10x.h"
#include "Global.h"


/* Private variables ---------------------------------------------------------*/ 
volatile RUN_TIME_TYPE GlobalRunTime;	//记录系统上电后的运行时间
volatile timems_t StartTimeMs1,EndTimeMs1,StartTimeMs2,EndTimeMs2,StartTimeMs3,EndTimeMs3;

//uint8_t SPI1_ParseBuf[SPI1PARSEBUFLEN];				//SPIy_Buffer_Rx

uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;
volatile SysWorkStatus WorkSta1 = STA_SLEEP;			//整个系统的工作状态
volatile SysWorkStatus WorkStaPre1 = STA_SLEEP;		//整个系统的前一个工作状态
volatile SysWorkStatus WorkSta2 = STA_SLEEP;		//整个系统的工作状态
volatile SysWorkStatus WorkStaPre2 = STA_SLEEP;		//整个系统的前一个工作状态

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
  * @param nTime: specifies the delay time length, in us.  但由于TimingDelay为全局变量，两个程序同时调用DelayUs会出问题
  * @retval : None
  */
void DelayUs(__IO uint32_t usTime)
{ 
 SysTick->CTRL |=0x07; // 使能SysTick计数器
//   SysTick_CounterCmd(SysTick_Counter_Enable);	// 使能SysTick计数器
  TimingDelay = usTime;

  while(TimingDelay != 0);
  SysTick->CTRL &=0xFD;	// 停止SysTick计数器，不进入SysTick异常中断，但仍在计数
//  SysTick_CounterCmd(SysTick_Counter_Disable );	// 关闭SysTick计数器

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
      i=10;  //尹工用的17 
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
      i=12000;  //尹工用的18000
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
// 计算命令特征值函数用于散转命令	
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
//说明：命令数据插入函数	
//参数：pTarget目标地址，pSource源地址，MsgLen插入字符长度，AddDotFg是否插入','号及从'\0'开始插入
//返回：void	
//---------------------------------------------------------------------------
void MsgInsrt(uint8_t * pTarget, uint8_t * pSource, uint16_t MsgLen ,u8 AddDotFg)
{
	u16 i=0, j=0;
	
	if(TRUE == AddDotFg){
		while(pTarget[i]){i++;}				// 寻找衔接处的'\0'
		if (i) pTarget[i++] = ',';		// 若不是开头， 则添加','
	}
	for( ;j<MsgLen; ) {
		pTarget[i++] = pSource[j++];
	}
	pTarget[i] = '\0';
}
//---------------------------------------------------------------------------
// 自定义的strlen函数，strlen函数不好用 	
// 回复内容组合函数:衔接处的第一位必须为'\0'
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
//说明:读取当前的运行时间
//参数:输入两次运行时间
//=============================================================================================
timems_t ReadRunTime(void)
{/*	RUN_TIME_TYPE TmpRunTime;
	RUN_TIME_TYPE * pTmpRunTime;
	pTmpRunTime = &TmpRunTime; */
//	pTmpRunTime->MilliSecond = TIM3->ARR / 10 ;		//获得当前TIM4计数值，单位是0.1ms所以要除以10
//	pTmpRunTime->Second = GlobalRunTime->Second;	//		
	return (GlobalRunTime.Second * 1000) + (TIM3->CNT / 10);	//转为毫秒级时间
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
//---------------------------------------------------------------------------
//说明：数据复制拷贝函数	
//参数：pTarget目标地址，pSource源地址，MsgLen要复制的字符长度
//返回：void	
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
//// 回复内容组合函数
//// ken:会算出发送字符串长度	
//u16 ReplyAppend(CMD_BODY_TypeDef *pRplyStr)
//{	u16		nCheckNum = 0 ,nRplyStrLen = 0;
//	u8		nCheckChar[2];
//	u8 		i;
//
//	while(pRplyStr->all[nRplyStrLen] != '\0'){nRplyStrLen++;}	//寻找结尾
//	//插入长度					
//	MyNumToStr(pRplyStr->part.CmdTotalLen,(nRplyStrLen + CMD_TAIL_LEN) , 3);	//加上 *xor\r\n 5个字节长度
//	
//	for(i=0;i < nRplyStrLen;i++) {
//		nCheckNum ^= pRplyStr->all[i];		//ken:计算CheckSum值
//	}								
//	//ken:把CheckSum值分为两个字节
//	nCheckChar[0] = nCheckNum >> 4;		//ken:保存CheckSum高位
//	nCheckChar[1] = nCheckNum & 0xF;	//ken:保存CheckSum低位
//	for (i=0;i<2;i++) {
//		if (nCheckChar[i]<=9)		{nCheckChar[i] += 48;}	//ken:将16进制转换为ASCII码
//		else						{nCheckChar[i] += 55;}
//	}
//	
//	pRplyStr->all[nRplyStrLen++] = '*';
//	pRplyStr->all[nRplyStrLen++] = nCheckChar[0];		//异或校验高位
//	pRplyStr->all[nRplyStrLen++] = nCheckChar[1];		//异或校验低位	
//	pRplyStr->all[nRplyStrLen++] = '\r';
//	pRplyStr->all[nRplyStrLen++] = '\n';
//	 
//	MyNumToStr(pRplyStr->part.CmdTotalLen, nRplyStrLen , CMD_TOTAL_LEN);	//将长度转为ASCII码，添加至
//	return nRplyStrLen;
//}
	


/*********************ken********************************** 
*   函数说明： 将接收命令中的字符长度转换成数据                               
*   输入：  pStr - 字符串首地址, DataLen - 数值位数       				
*   输出：  函数名为转换后的数值 长度为32 long型                            
*   调用函数：void                                      
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
*   函数说明： 将知道位数的数字转为字符                               
*   输入：  pStr - 字符串首地址,Num - 要转化的数字， NumLen - 数字的位数       				
*   输出：  函数名为转换后的数值 长度为32 long型                            
*   调用函数：void                                      
***********************************************************/ 

u8 MyNumToStr(u8 *pStr,u32 Num , u16 NumLen)
{	u16	i;
	u32 TmpNum;
	u8 *pStrEnd = pStr+NumLen;
	if(NumLen>10) {return 0;}
	for(i=1;NumLen>=i;i++) {
		TmpNum = Num % 10; //ken:取最低位
		Num /=10;	
		*(pStrEnd-i) = TmpNum +'0';
	}
	//*pStrEnd = '\0';
	return 	1;
}

/*********************ken********************************** 
*   函数说明： 将知道位数的数字转为字符                               
*   输入：  pTarget - 字符串首地址,pLSource - 要转化的32位数据首地址， NumLen - 数字的位数       				
*   输出：  函数名                            
*   调用函数：void                                      
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
//	for(iLoop=0; iLoop<cLen; iLoop++) //检查数据格式是否合格，如果不合格返回999999
//	{
//		if(iLoop==0)
//		{
//			if(*(cString+iLoop)=='+')                                 sign = 0;//确定为正数
//		 	else if(*(cString+iLoop)=='-')	                          sign = 1;//确定为负数
//			else if((*(cString+iLoop)<=0x39)&&(*(cString+iLoop)>=0x30)) sign = 0;//确定为正数		
//		}
//	    if(*(cString+iLoop)=='.')               digit= iLoop;//确定小数点位 
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
//			value = value*10.+(*(cString+iLoop)-0x30);//转换整数部分；
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
//			value1 = (value1+(*(cString+iLoop)-0x30))/10.;//转换小数部分；
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

