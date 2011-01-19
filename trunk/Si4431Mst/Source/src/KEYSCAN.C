#include <si4421.h>

uchar xdata keyval;
uchar xdata keynew=0;	//判断键值
uchar xdata keylast=0;
uchar xdata turncount;
uchar xdata txcount;
uchar xdata rxcount;
uchar xdata count0;
uchar xdata count1;
uchar xdata count2;

uchar xdata keynum;

uchar xdata num1;
uchar xdata num2;

bit KEYISNEW;

uchar xdata baud[8][12] =	
{
//	 IFBW, COSR, CRO2, CRO1, CRO0, CTG1, CTG0, TDR1, TDR0, MMC1, FDEV, B_TIME
	{0x01, 0x83, 0xc0, 0x13, 0xa9, 0x00, 0x05, 0x13, 0xa9, 0x20, 0x3a, 209},  		//DR: 2.4kbps, DEV: +-36kHz, BBBW: 75.2kHz
	{0x04, 0x41, 0x60, 0x27, 0x52, 0x00, 0x0a, 0x27, 0x52, 0x20, 0x48, 105},		//DR: 4.8kbps, DEV: +-45kHz, BBBW: 95.3kHz
	{0x91, 0x71, 0x40, 0x34, 0x6e, 0x00, 0x18, 0x4e, 0xa5, 0x20, 0x48, 53 },		//DR: 9.6kbps, DEV: +-45kHz, BBBW: 112.8kHz
	{0x12, 0xc8, 0x00, 0xa3, 0xd7, 0x01, 0x13, 0x51, 0xec, 0x20, 0x13, 50 },		//DR: 10kbps, DEV: +-12kHz, BBBW: 41.7kHz
	{0x02, 0x64, 0x01, 0x47, 0xae, 0x05, 0x21, 0x0A, 0x3D, 0x00, 0x20, 13 },		//DR: 40kbps, DEV: +-20kHz, BBBW: 83.2kHz
	{0x05, 0x50, 0x01, 0x99, 0x9A, 0x06, 0x68, 0x0C, 0xCD, 0x00, 0x28, 10 },		//DR: 50kbps, DEV: +-25kHz, BBBW: 112.8kHz
	{0x9A, 0x3C, 0x02, 0x22, 0x22, 0x07, 0xFF, 0x19, 0x9A, 0x00, 0x50, 5  },		//DR: 100kbps, DEV: +-50kHz, BBBW: 225.1kHz
	{0x83, 0x5e, 0x01, 0x5d, 0x86, 0x05, 0x74, 0x20, 0xc5, 0x00, 0x66, 4  },		//DR: 128kbps, DEV: +-64kHz, BBBW: 269.3kHz
};
/*
uchar xdata freq[4][4] =
{
//  fb  , fc_h, fc_l, fhch_h ，fhch_l   
   {0x73, 0x57, 0x80, 0x3c,},// 867.60MHz
   {0x73, 0x64, 0x00, 0x05,},// 868.05MHz
   {0x73, 0x64, 0x00, 0x32,},// 868.50MHz
   {0x73, 0x64, 0x00, 0x5f,} // 868.95MHz
};
*/

uchar xdata power[4] = { 0x00, 0x01, 0x02 ,0x03 };
extern unsigned char send_flag;//进入接收状态标志

void key_init(void)
{
 	keyval=0;
 	keynew=0;				//判断键值
 	keylast=0;		
 	KEYISNEW=0;
	turncount = 0;
	txcount =0;
	rxcount = 0;
	count1 = 3;
	count2 = 1;
	num1 = 3;
	num2 = 1;
	workmode=start;		//初始工作模式为正常模式		
}

void key_scan(void)
	{
	uchar xdata tt,Temp;
	tt=P1&0x0f;
	
	if(tt!=0x0f)
	{
	delay(20);
	Temp = P1;
	Temp &=0x0f;
	if(Temp==tt)
	{
    while(Temp!=0x0f)
	{
	  Temp = P1&0x0f;
      delay(10);
      Temp = P1&0x0f;
	}
	tt =~tt;
	tt &=0x0f;
	keyval = tt;
	KEYISNEW=1;
	}
	else
     KEYISNEW=0;
	  
	}

	}

void keyproc(void)
{

	if(KEYISNEW==1)
		{
		     
		     switch(keyval)
			 {

			      case RECKEY:
				  {   
				       if(workmode == phy)
					   {
                           workmode = trans;}
                         
					   else if(workmode == trans)
					   {
                           workmode = phy;}

                       else if(workmode ==powers)
					   {
                           workmode = phy;}
                       else if(workmode == pows)
					   {
                           workmode = powers;}


                       else if(workmode ==baudrates)
					   {
                           workmode = phy;}
                       else if(workmode == bauds)
					   {
                           workmode = baudrates;}

					}break;
					
					
				case UPKEY:
				  {   
				         if(workmode == powers)
						 {
						      workmode = baudrates; }
                         else if(workmode == baudrates)
						 {
						      workmode = powers; }
                         else if(workmode == pows)
						 {    
						      if(count1 == 0)
							      count1 = 3;  
							  else 
							      count1--;
						 }
                         else if(workmode == bauds)
						 {
                           if(count2 == 0)
						      count2 = 7;
                           else 

						       count2--;
                         }
					} break;		
              
			  
			  	case DOWNKEY:
				  {   
                         if(workmode == powers)
						 {
						      workmode = baudrates; }
                         else if(workmode == baudrates)
						 {
						      workmode = powers; }
                         
				         else if(workmode == pows)
						 {    
						      if(count1 == 3)
							      count1 = 0;  
							  else 
							      count1++;
						 }
                         else if(workmode == bauds)
						 {
                           if(count2 == 7)
						          count2 = 0;
                           else 
						          count2++;
                         }

					} break;
			  
			  
			  	case ENTKEY:
				  {   
                      
					  if(workmode ==phy)
					   {
                           workmode = powers;}

                      else if(workmode ==trans)
					   {
					        txcount++;
							if(txcount== 100)
							txcount =0;
							send_init();
							send_data(&(txdata[2]),12);
							delay(100);

                       }
					   else if(workmode == powers)
					   {
					        workmode = pows ;}

                       else if(workmode == pows)
					   {
					      workmode = powers;
					      num1 = count1;     
						  SpiRfWriteAddressData(0xed,power[count1]);  // 选择发射功率
						}

                       	else if(workmode ==baudrates)
					   {
                            workmode = bauds;}

					   else if(workmode == bauds)
					   {
					        workmode = baudrates;
							num2 = count2;   
							send_flag = 1;
                        }
					} break;
			       
			}	       
     }
}














