   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     	bsct
  16  0000               _TxIdx:
  17  0000 00            	dc.b	0
  18  0001               _RxIdx:
  19  0001 00            	dc.b	0
  20  0002               _k:
  21  0002 00            	dc.b	0
  22                     	switch	.data
  23  0000               _WorkSta1:
  24  0000 00            	dc.b	0
  25  0001               _WorkStaPre1:
  26  0001 00            	dc.b	0
  27  0002               _WorkSta2:
  28  0002 00            	dc.b	0
  29  0003               _WorkStaPre2:
  30  0003 00            	dc.b	0
  31                     	bsct
  32  0003               _InNetFlag:
  33  0003 00            	dc.b	0
  34                     .const:	section	.text
  35  0000               _TestStr:
  36  0000 555341525431  	dc.b	"USART1TEST",13
  37  000b 0a00          	dc.b	10,0
  38  000d               _TxNoReply:
  39  000d 54784e6f5265  	dc.b	"TxNoReply",13
  40  0017 0a00          	dc.b	10,0
  41  0019               _RxNotMatch:
  42  0019 52784e6f744d  	dc.b	"RxNotMatch",13
  43  0024 0a00          	dc.b	10,0
  44  0026               _RxMatch:
  45  0026 52784d617463  	dc.b	"RxMatch",13
  46  002e 0a00          	dc.b	10,0
  47  0030               _TestWord:
  48  0030 4100          	dc.b	"A",0
  49  0032               _StrError:
  50  0032 4572726f7221  	dc.b	"Error!",0
  51  0039               _MsgReSendTimeOut:
  52  0039 4d7367526553  	dc.b	"MsgReSendTimeOut",0,0
  53  004b               _MSGRP_OK:
  54  004b 4f4b0000      	dc.b	"OK",0,0
  55  004f               _MSGRP_ERR:
  56  004f 45520000      	dc.b	"ER",0,0
  96                     ; 66 void Delay(u16 nCount)
  96                     ; 67 {
  98                     	switch	.text
  99  0000               _Delay:
 101  0000 89            	pushw	x
 102       00000000      OFST:	set	0
 105  0001 2007          	jra	L13
 106  0003               L72:
 107                     ; 71     nCount--;
 109  0003 1e01          	ldw	x,(OFST+1,sp)
 110  0005 1d0001        	subw	x,#1
 111  0008 1f01          	ldw	(OFST+1,sp),x
 112  000a               L13:
 113                     ; 69   while (nCount != 0)
 115  000a 1e01          	ldw	x,(OFST+1,sp)
 116  000c 26f5          	jrne	L72
 117                     ; 73 }
 120  000e 85            	popw	x
 121  000f 81            	ret
 164                     ; 82 void DelayUs_Soft(u16 time)
 164                     ; 83 {    
 165                     	switch	.text
 166  0010               _DelayUs_Soft:
 168  0010 89            	pushw	x
 169  0011 89            	pushw	x
 170       00000002      OFST:	set	2
 173                     ; 84    u16 i=0;  
 176  0012 2014          	jra	L16
 177  0014               L75:
 178                     ; 87       i=10;  //尹工用的17 
 180  0014 ae000a        	ldw	x,#10
 181  0017 1f01          	ldw	(OFST-1,sp),x
 183  0019               L17:
 184                     ; 88       while(i--) ;    
 186  0019 1e01          	ldw	x,(OFST-1,sp)
 187  001b 1d0001        	subw	x,#1
 188  001e 1f01          	ldw	(OFST-1,sp),x
 189  0020 1c0001        	addw	x,#1
 190  0023 a30000        	cpw	x,#0
 191  0026 26f1          	jrne	L17
 192  0028               L16:
 193                     ; 85    while(time--)
 195  0028 1e03          	ldw	x,(OFST+1,sp)
 196  002a 1d0001        	subw	x,#1
 197  002d 1f03          	ldw	(OFST+1,sp),x
 198  002f 1c0001        	addw	x,#1
 199  0032 a30000        	cpw	x,#0
 200  0035 26dd          	jrne	L75
 201                     ; 90 }
 204  0037 5b04          	addw	sp,#4
 205  0039 81            	ret
 248                     ; 98 void DelayMs_Soft(u16 time)
 248                     ; 99 {    
 249                     	switch	.text
 250  003a               _DelayMs_Soft:
 252  003a 89            	pushw	x
 253  003b 89            	pushw	x
 254       00000002      OFST:	set	2
 257                     ; 100    u16 i=0;  
 260  003c 2014          	jra	L121
 261  003e               L711:
 262                     ; 103       i=12000;  //尹工用的18000
 264  003e ae2ee0        	ldw	x,#12000
 265  0041 1f01          	ldw	(OFST-1,sp),x
 267  0043               L131:
 268                     ; 104       while(i--) ;    
 270  0043 1e01          	ldw	x,(OFST-1,sp)
 271  0045 1d0001        	subw	x,#1
 272  0048 1f01          	ldw	(OFST-1,sp),x
 273  004a 1c0001        	addw	x,#1
 274  004d a30000        	cpw	x,#0
 275  0050 26f1          	jrne	L131
 276  0052               L121:
 277                     ; 101    while(time--)
 279  0052 1e03          	ldw	x,(OFST+1,sp)
 280  0054 1d0001        	subw	x,#1
 281  0057 1f03          	ldw	(OFST+1,sp),x
 282  0059 1c0001        	addw	x,#1
 283  005c a30000        	cpw	x,#0
 284  005f 26dd          	jrne	L711
 285                     ; 106 }
 288  0061 5b04          	addw	sp,#4
 289  0063 81            	ret
 364                     ; 118 TestStatus Buffercmp(u8 * pBuffer1, u8 * pBuffer2, u16 BufferLength)
 364                     ; 119 {
 365                     	switch	.text
 366  0064               _Buffercmp:
 368  0064 89            	pushw	x
 369       00000000      OFST:	set	0
 372  0065 2019          	jra	L571
 373  0067               L371:
 374                     ; 122     if (*pBuffer1 != *pBuffer2)
 376  0067 1e01          	ldw	x,(OFST+1,sp)
 377  0069 f6            	ld	a,(x)
 378  006a 1e05          	ldw	x,(OFST+5,sp)
 379  006c f1            	cp	a,(x)
 380  006d 2703          	jreq	L102
 381                     ; 124       return FAILED;
 383  006f 4f            	clr	a
 385  0070 201f          	jra	L41
 386  0072               L102:
 387                     ; 126     pBuffer1++;
 389  0072 1e01          	ldw	x,(OFST+1,sp)
 390  0074 1c0001        	addw	x,#1
 391  0077 1f01          	ldw	(OFST+1,sp),x
 392                     ; 127     pBuffer2++;
 394  0079 1e05          	ldw	x,(OFST+5,sp)
 395  007b 1c0001        	addw	x,#1
 396  007e 1f05          	ldw	(OFST+5,sp),x
 397  0080               L571:
 398                     ; 120   while (BufferLength--)
 400  0080 1e07          	ldw	x,(OFST+7,sp)
 401  0082 1d0001        	subw	x,#1
 402  0085 1f07          	ldw	(OFST+7,sp),x
 403  0087 1c0001        	addw	x,#1
 404  008a a30000        	cpw	x,#0
 405  008d 26d8          	jrne	L371
 406                     ; 130   return PASSED;
 408  008f a601          	ld	a,#1
 410  0091               L41:
 412  0091 85            	popw	x
 413  0092 81            	ret
 475                     ; 136 u16 Hash(u8 *pStr, u8 len)  	
 475                     ; 137 {  
 476                     	switch	.text
 477  0093               _Hash:
 479  0093 89            	pushw	x
 480  0094 5204          	subw	sp,#4
 481       00000004      OFST:	set	4
 484                     ; 138 	u16 result = 0,i;  
 486  0096 5f            	clrw	x
 487  0097 1f01          	ldw	(OFST-3,sp),x
 488                     ; 139 	for (i=0;i<len; i++) { 
 490  0099 5f            	clrw	x
 491  009a 1f03          	ldw	(OFST-1,sp),x
 493  009c 201b          	jra	L142
 494  009e               L532:
 495                     ; 140 		result += (pStr[i])*(i+1);
 497  009e 1e05          	ldw	x,(OFST+1,sp)
 498  00a0 72fb03        	addw	x,(OFST-1,sp)
 499  00a3 f6            	ld	a,(x)
 500  00a4 5f            	clrw	x
 501  00a5 97            	ld	xl,a
 502  00a6 1603          	ldw	y,(OFST-1,sp)
 503  00a8 905c          	incw	y
 504  00aa cd0000        	call	c_imul
 506  00ad 72fb01        	addw	x,(OFST-3,sp)
 507  00b0 1f01          	ldw	(OFST-3,sp),x
 508                     ; 139 	for (i=0;i<len; i++) { 
 510  00b2 1e03          	ldw	x,(OFST-1,sp)
 511  00b4 1c0001        	addw	x,#1
 512  00b7 1f03          	ldw	(OFST-1,sp),x
 513  00b9               L142:
 516  00b9 7b09          	ld	a,(OFST+5,sp)
 517  00bb 5f            	clrw	x
 518  00bc 97            	ld	xl,a
 519  00bd bf00          	ldw	c_x,x
 520  00bf 1e03          	ldw	x,(OFST-1,sp)
 521  00c1 b300          	cpw	x,c_x
 522  00c3 25d9          	jrult	L532
 523                     ; 142 	return result;  
 525  00c5 1e01          	ldw	x,(OFST-3,sp)
 528  00c7 5b06          	addw	sp,#6
 529  00c9 81            	ret
 601                     ; 150 void MsgInsrt(u8 * pTarget, u8 * pSource, u16 MsgLen)
 601                     ; 151 {
 602                     	switch	.text
 603  00ca               _MsgInsrt:
 605  00ca 89            	pushw	x
 606  00cb 89            	pushw	x
 607       00000002      OFST:	set	2
 610                     ; 152 	u8 i=0, j=0;
 612  00cc 0f02          	clr	(OFST+0,sp)
 615  00ce 0f01          	clr	(OFST-1,sp)
 617  00d0 2002          	jra	L703
 618  00d2               L303:
 619                     ; 154 	while(pTarget[i]){i++;}			// 寻找衔接处的'\0'
 621  00d2 0c02          	inc	(OFST+0,sp)
 622  00d4               L703:
 625  00d4 7b03          	ld	a,(OFST+1,sp)
 626  00d6 97            	ld	xl,a
 627  00d7 7b04          	ld	a,(OFST+2,sp)
 628  00d9 1b02          	add	a,(OFST+0,sp)
 629  00db 2401          	jrnc	L22
 630  00dd 5c            	incw	x
 631  00de               L22:
 632  00de 02            	rlwa	x,a
 633  00df 7d            	tnz	(x)
 634  00e0 26f0          	jrne	L303
 636  00e2 201d          	jra	L713
 637  00e4               L313:
 638                     ; 157 		pTarget[i++] = pSource[j++];
 640  00e4 7b02          	ld	a,(OFST+0,sp)
 641  00e6 97            	ld	xl,a
 642  00e7 0c02          	inc	(OFST+0,sp)
 643  00e9 9f            	ld	a,xl
 644  00ea 5f            	clrw	x
 645  00eb 97            	ld	xl,a
 646  00ec 72fb03        	addw	x,(OFST+1,sp)
 647  00ef 7b01          	ld	a,(OFST-1,sp)
 648  00f1 9097          	ld	yl,a
 649  00f3 0c01          	inc	(OFST-1,sp)
 650  00f5 909f          	ld	a,yl
 651  00f7 905f          	clrw	y
 652  00f9 9097          	ld	yl,a
 653  00fb 72f907        	addw	y,(OFST+5,sp)
 654  00fe 90f6          	ld	a,(y)
 655  0100 f7            	ld	(x),a
 656  0101               L713:
 657                     ; 156 	for( ;j<MsgLen; ) {
 659  0101 7b01          	ld	a,(OFST-1,sp)
 660  0103 5f            	clrw	x
 661  0104 97            	ld	xl,a
 662  0105 1309          	cpw	x,(OFST+7,sp)
 663  0107 25db          	jrult	L313
 664                     ; 159 	pTarget[i] = '\0';
 666  0109 7b03          	ld	a,(OFST+1,sp)
 667  010b 97            	ld	xl,a
 668  010c 7b04          	ld	a,(OFST+2,sp)
 669  010e 1b02          	add	a,(OFST+0,sp)
 670  0110 2401          	jrnc	L42
 671  0112 5c            	incw	x
 672  0113               L42:
 673  0113 02            	rlwa	x,a
 674  0114 7f            	clr	(x)
 675                     ; 160 }
 678  0115 5b04          	addw	sp,#4
 679  0117 81            	ret
 733                     ; 165 u16 MyStrLen(u8 str[])
 733                     ; 166 {
 734                     	switch	.text
 735  0118               _MyStrLen:
 737  0118 89            	pushw	x
 738  0119 5204          	subw	sp,#4
 739       00000004      OFST:	set	4
 742                     ; 167     u16 nlen = 0;
 744  011b 5f            	clrw	x
 745  011c 1f01          	ldw	(OFST-3,sp),x
 746                     ; 168     u8 *p = str;
 748  011e 1e05          	ldw	x,(OFST+1,sp)
 749  0120 1f03          	ldw	(OFST-1,sp),x
 751  0122 2007          	jra	L553
 752  0124               L153:
 753                     ; 173         nlen++;
 755  0124 1e01          	ldw	x,(OFST-3,sp)
 756  0126 1c0001        	addw	x,#1
 757  0129 1f01          	ldw	(OFST-3,sp),x
 758  012b               L553:
 759                     ; 172     while (p && *p++)
 761  012b 1e03          	ldw	x,(OFST-1,sp)
 762  012d 270d          	jreq	L163
 764  012f 1e03          	ldw	x,(OFST-1,sp)
 765  0131 1c0001        	addw	x,#1
 766  0134 1f03          	ldw	(OFST-1,sp),x
 767  0136 1d0001        	subw	x,#1
 768  0139 7d            	tnz	(x)
 769  013a 26e8          	jrne	L153
 770  013c               L163:
 771                     ; 175     return nlen;
 773  013c 1e01          	ldw	x,(OFST-3,sp)
 776  013e 5b06          	addw	sp,#6
 777  0140 81            	ret
 812                     	switch	.const
 813  0053               L23:
 814  0053 000003e8      	dc.l	1000
 815                     ; 183 timems_t ReadRunTime(void)
 815                     ; 184 {/*	RUN_TIME_TYPE TmpRunTime;
 816                     	switch	.text
 817  0141               _ReadRunTime:
 819  0141 5206          	subw	sp,#6
 820       00000006      OFST:	set	6
 823                     ; 190 	TmpCNT = TIM3->CNTRH << 8;
 825  0143 c65328        	ld	a,21288
 826  0146 5f            	clrw	x
 827  0147 97            	ld	xl,a
 828  0148 4f            	clr	a
 829  0149 02            	rlwa	x,a
 830  014a 1f05          	ldw	(OFST-1,sp),x
 831                     ; 191 	TmpCNT = TmpCNT + TIM3->CNTRL;
 833  014c c65329        	ld	a,21289
 834  014f 5f            	clrw	x
 835  0150 97            	ld	xl,a
 836  0151 1f03          	ldw	(OFST-3,sp),x
 837  0153 1e05          	ldw	x,(OFST-1,sp)
 838  0155 72fb03        	addw	x,(OFST-3,sp)
 839  0158 1f05          	ldw	(OFST-1,sp),x
 840                     ; 192 	TmpCNT = TmpCNT / 15.625;
 842  015a 1e05          	ldw	x,(OFST-1,sp)
 843  015c 90ae000f      	ldw	y,#15
 844  0160 65            	divw	x,y
 845  0161 1f05          	ldw	(OFST-1,sp),x
 846                     ; 193 	return (GlobalRunTime.Second * 1000) + TmpCNT;	//转为毫秒级时间
 848  0163 1e05          	ldw	x,(OFST-1,sp)
 849  0165 cd0000        	call	c_uitolx
 851  0168 96            	ldw	x,sp
 852  0169 1c0001        	addw	x,#OFST-5
 853  016c cd0000        	call	c_rtol
 855  016f ae0010        	ldw	x,#_GlobalRunTime
 856  0172 cd0000        	call	c_ltor
 858  0175 ae0053        	ldw	x,#L23
 859  0178 cd0000        	call	c_lmul
 861  017b 96            	ldw	x,sp
 862  017c 1c0001        	addw	x,#OFST-5
 863  017f cd0000        	call	c_ladd
 867  0182 5b06          	addw	sp,#6
 868  0184 81            	ret
 911                     ; 200 timems_t CheckTimeInterval(timems_t StartTime,timems_t EndTime)
 911                     ; 201 {
 912                     	switch	.text
 913  0185               _CheckTimeInterval:
 915       00000000      OFST:	set	0
 918                     ; 202 	if(EndTime < StartTime){
 920  0185 96            	ldw	x,sp
 921  0186 1c0007        	addw	x,#OFST+7
 922  0189 cd0000        	call	c_ltor
 924  018c 96            	ldw	x,sp
 925  018d 1c0003        	addw	x,#OFST+3
 926  0190 cd0000        	call	c_lcmp
 928  0193 240b          	jruge	L324
 929                     ; 203 		return 0;
 931  0195 ae0000        	ldw	x,#0
 932  0198 bf02          	ldw	c_lreg+2,x
 933  019a ae0000        	ldw	x,#0
 934  019d bf00          	ldw	c_lreg,x
 937  019f 81            	ret
 938  01a0               L324:
 939                     ; 206 		return (EndTime - StartTime);
 941  01a0 96            	ldw	x,sp
 942  01a1 1c0007        	addw	x,#OFST+7
 943  01a4 cd0000        	call	c_ltor
 945  01a7 96            	ldw	x,sp
 946  01a8 1c0003        	addw	x,#OFST+3
 947  01ab cd0000        	call	c_lsub
 951  01ae 81            	ret
1284                     	xdef	_DelayMs_Soft
1285                     	xdef	_DelayUs_Soft
1286                     	xdef	_MsgReSendTimeOut
1287                     	switch	.bss
1288  0000               _TimingDelay:
1289  0000 00000000      	ds.b	4
1290                     	xdef	_TimingDelay
1291                     	xdef	_k
1292                     	xdef	_RxIdx
1293                     	xdef	_TxIdx
1294                     	xdef	_CheckTimeInterval
1295                     	xdef	_ReadRunTime
1296                     	xdef	_MyStrLen
1297                     	xdef	_MsgInsrt
1298                     	xdef	_Hash
1299                     	xdef	_Buffercmp
1300                     	xdef	_Delay
1301                     	xdef	_InNetFlag
1302                     	xdef	_WorkStaPre2
1303                     	xdef	_WorkSta2
1304                     	xdef	_WorkStaPre1
1305                     	xdef	_WorkSta1
1306                     	xdef	_MSGRP_ERR
1307                     	xdef	_MSGRP_OK
1308                     	xdef	_TestWord
1309                     	xdef	_TestStr
1310                     	xdef	_StrError
1311                     	xdef	_RxMatch
1312                     	xdef	_RxNotMatch
1313                     	xdef	_TxNoReply
1314                     	switch	.ubsct
1315  0000               _EndTimeMs2:
1316  0000 00000000      	ds.b	4
1317                     	xdef	_EndTimeMs2
1318  0004               _StartTimeMs2:
1319  0004 00000000      	ds.b	4
1320                     	xdef	_StartTimeMs2
1321  0008               _EndTimeMs1:
1322  0008 00000000      	ds.b	4
1323                     	xdef	_EndTimeMs1
1324  000c               _StartTimeMs1:
1325  000c 00000000      	ds.b	4
1326                     	xdef	_StartTimeMs1
1327  0010               _GlobalRunTime:
1328  0010 000000000000  	ds.b	8
1329                     	xdef	_GlobalRunTime
1330                     	xref.b	c_lreg
1331                     	xref.b	c_x
1351                     	xref	c_lsub
1352                     	xref	c_lcmp
1353                     	xref	c_ladd
1354                     	xref	c_rtol
1355                     	xref	c_uitolx
1356                     	xref	c_lmul
1357                     	xref	c_ltor
1358                     	xref	c_imul
1359                     	end
