

///////////////////////////////////////////////////////////////////////////
//          显示程序
////////////////////////////////////////////////////////////////////////
#include <SI4421.h>

extern bit revframe;
uchar xdata sendlength;
uchar xdata receivelength;

testdisplay code testdis[28]=
{ 
    {"SI4432_DEMO",11},
    {"SI4432_DEMO",11},

    {"SI4432_MENU",11},
    {"1.Channel Select",16},

    {"SI4432_MENU",11},
    {"1.Channel Select",16},

    {"SI4432_MENU",11},
    {"2.Power Select",14},

    {"TX: TESTING",11},
    {"RX: ",4},

	{"SI4432_MENU",11},
    {"1.Pow Select",12},

    {"Pow Set",7},
	{"1.+11 DBm",9},
	{"2.+13 DBm",9},
	{"3.+17 DBm",9},
	{"4.+20 DBm",9},

    {"SI4432_MENU",11},
    {"2.Baud Select",13},

    {"Baudrate Set",12},
    {"1.2400 ",7},
    {"2.4800 ",7},
    {"3.9600 ",7},
    {"4.10000 ",8},
    {"5.40000 ",8},
    {"6.50000 ",8},
    {"7.100000 ",9},
    {"8.128000 ",9},

};

void depart_buf(uchar offset)  // 数据缓冲区
	{
	uchar xdata i,tt;
	uchar xdata val[10];
	uchar xdata txtemp,rxtemp;
	for(i=0;i<testdis[turncount].datalen;i++)
		dis_buf[i+offset]=testdis[turncount].dischar[i];
	tt=i;
    
	txtemp = txcount;
	rxtemp = rxcount;
   if(turncount ==8)   // 发送数据缓冲区
	{
	  if(txtemp==0)
		{  
		  val[0]=0;
	    }		
	  for(i=0;i<4;i++)  // 发送数据次数处理
	    {
			val[i]=txtemp%10;	//顺序放置小数位、个位、十位.....
			txtemp/=10;
			if(txtemp==0) break;
			}
			
	  for(;i>0;i--)  
	  dis_buf[offset+tt++]=val[i];
	  dis_buf[offset+tt++]=val[0];

	  sendlength = tt+1;
	  txdata[0] = 0x20;//sendlength;
      for(i = 0;i<sendlength;i++)
	  {
	     txdata[i+1] = dis_buf[i+3];}

    }

    if(turncount ==9)  //////接收数据缓冲区
	{	
	    if(rlength == 0xff)   //处理接收长度；
		{
		      rlength = 0; }

	     if(rlength > 12)     
	           rlength = 12;

         if(rlength != 0)
		 {
	          for(i = 0;i < rlength; i++) 
	          { 
	              dis_buf[offset+tt++]=rxdata[i];} //处理接收数据；
              
		      for(i=0;i<20;i++)
		             rxdata[i]=0x00;
         }

     }	
}


void new_dis_buf(void)  // 显示方式
{
    if(workmode ==start)
	{
	   	 turncount = 0;
		 depart_buf(0);
    }

    else if(workmode == phy)
	{
	     turncount = 1;
		 depart_buf(0);
    }

	else if(workmode==trans)
	{
          turncount = 8;
		  depart_buf(0);
		  turncount = 9;
		  depart_buf(16);
	}

   else if(workmode == powers)
   {
          turncount = 10;
		  depart_buf(0);
		  turncount = 11;
		  depart_buf(16);
    }

   else if(workmode == baudrates)
   {
          turncount = 17;
		  depart_buf(0);
		  turncount = 18;
		  depart_buf(16);
    }

	else if(workmode == pows)
   {
         switch(count1)
		 {
		     case 0:
			 {
		         turncount = 12;
		         depart_buf(0);
		         turncount = 13;
		         depart_buf(16);
              }break;
             case 1:
			 {
		         turncount = 12;
		         depart_buf(0);
		         turncount = 14;
		         depart_buf(16);
             }break;

             case 2:
			 {
		         turncount = 12;
		         depart_buf(0);
		         turncount = 15 ;
		         depart_buf(16);
              }break;
             case 3:
			 {
		         turncount = 12;
		         depart_buf(0);
		         turncount = 16;
		         depart_buf(16);
             }break;

			 default:
			      break;
		 }
   
   }
   else if(workmode == bauds)
   {
         switch(count2)
		 {
		     case 0:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 20;
		         depart_buf(16);
              }break;
             case 1:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 21;
		         depart_buf(16);
             }break;

             case 2:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 22 ;
		         depart_buf(16);
              }break;
             case 3:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 23;
		         depart_buf(16);
             }break;


			  case 4:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 24;
		         depart_buf(16);
              }break;
             case 5:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 25;
		         depart_buf(16);
             }break;

			 case 6:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 26;
		         depart_buf(16);
              }break;
             case 7:
			 {
		         turncount = 19;
		         depart_buf(0);
		         turncount = 27;
		         depart_buf(16);
             }break;

			 default:
			      break;
		 }
     }
}


void clrscreen(void)
{
	uchar xdata i;

	for(i=0;i<32;i++)
	{
		dis_buf[i]=' ';
	}
}

void lcddisplay(void)   //  显示程序
{
	uchar xdata i;
	if((KEYISNEW==1)||revframe)
	{
	KEYISNEW=0;
	revframe = 0;
	clrscreen();
	new_dis_buf();
	lcdaddr(1);
	for(i=0;i<16;i++) lcdchar(dis_buf[i]); //第一行显示发送数据
	lcdaddr(17);
	for(i=16;i<32;i++) lcdchar(dis_buf[i]); //第二行显示接收数据；
	}
}
