   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  57                     ; 9 u8 SPI1_RW(u8 Data)
  57                     ; 10 {
  59                     	switch	.text
  60  0000               _SPI1_RW:
  62  0000 88            	push	a
  63       00000000      OFST:	set	0
  66                     ; 11 	SPI_SendData(Data);
  68  0001 cd0000        	call	_SPI_SendData
  71  0004               L13:
  72                     ; 12 	while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
  74  0004 a601          	ld	a,#1
  75  0006 cd0000        	call	_SPI_GetFlagStatus
  77  0009 4d            	tnz	a
  78  000a 27f8          	jreq	L13
  79                     ; 13 	Data = SPI_ReceiveData();
  81  000c cd0000        	call	_SPI_ReceiveData
  83  000f 6b01          	ld	(OFST+1,sp),a
  84                     ; 14   return(Data);           		  // return read uchar
  86  0011 7b01          	ld	a,(OFST+1,sp)
  89  0013 5b01          	addw	sp,#1
  90  0015 81            	ret
 143                     ; 18 u8 SPI1_RWReg(u8 Reg, u8 Data)
 143                     ; 19 {
 144                     	switch	.text
 145  0016               _SPI1_RWReg:
 147  0016 89            	pushw	x
 148  0017 88            	push	a
 149       00000001      OFST:	set	1
 152                     ; 21 	SPI1_CSN_L;			//NSS拉低		// CSN low, init SPI transaction                  
 154  0018 7219500a      	bres	20490,#4
 155                     ; 22 	status = SPI1_RW(Reg);      // select register
 157  001c 9e            	ld	a,xh
 158  001d ade1          	call	_SPI1_RW
 160  001f 6b01          	ld	(OFST+0,sp),a
 161                     ; 23 	SPI1_RW(Data);             // ..and write value to it..                  
 163  0021 7b03          	ld	a,(OFST+2,sp)
 164  0023 addb          	call	_SPI1_RW
 166                     ; 24 	SPI1_CSN_H;			//NSS拉高，关闭SPI	 // CSN high again
 168  0025 7218500a      	bset	20490,#4
 169                     ; 25 	return(status);            // return nRF24L01 status uchar
 171  0029 7b01          	ld	a,(OFST+0,sp)
 174  002b 5b03          	addw	sp,#3
 175  002d 81            	ret
 219                     ; 28 u8 SPI1_Read(u8 Reg)
 219                     ; 29 {
 220                     	switch	.text
 221  002e               _SPI1_Read:
 223  002e 88            	push	a
 224       00000001      OFST:	set	1
 227                     ; 31 	SPI1_CSN_L;			//NSS拉低
 229  002f 7219500a      	bres	20490,#4
 230                     ; 32 	SPI1_RW(Reg);            // Select register to read from..
 232  0033 adcb          	call	_SPI1_RW
 234                     ; 33 	Reg_val = SPI1_RW(0);    // ..then read registervalue
 236  0035 4f            	clr	a
 237  0036 adc8          	call	_SPI1_RW
 239  0038 6b01          	ld	(OFST+0,sp),a
 240                     ; 34 	SPI1_CSN_H;			//NSS拉高，关闭SPI
 242  003a 7218500a      	bset	20490,#4
 243                     ; 35 	return(Reg_val);        // return register value
 245  003e 7b01          	ld	a,(OFST+0,sp)
 248  0040 5b01          	addw	sp,#1
 249  0042 81            	ret
 293                     ; 38 u16 SPI1_RWWord(u16 Reg)
 293                     ; 39 {
 294                     	switch	.text
 295  0043               _SPI1_RWWord:
 297  0043 89            	pushw	x
 298  0044 89            	pushw	x
 299       00000002      OFST:	set	2
 302                     ; 41 	SPI1_CSN_L;			//NSS拉低	// Set CSN low, init SPI tranaction = 0;						
 304  0045 7219500a      	bres	20490,#4
 305                     ; 42 	temp16  = (u16) (SPI1_RW( (u8)((Reg & 0xFF00) >> 8) ));
 307  0049 01            	rrwa	x,a
 308  004a 9f            	ld	a,xl
 309  004b a4ff          	and	a,#255
 310  004d 97            	ld	xl,a
 311  004e 4f            	clr	a
 312  004f 02            	rlwa	x,a
 313  0050 4f            	clr	a
 314  0051 01            	rrwa	x,a
 315  0052 9f            	ld	a,xl
 316  0053 adab          	call	_SPI1_RW
 318  0055 5f            	clrw	x
 319  0056 97            	ld	xl,a
 320  0057 1f01          	ldw	(OFST-1,sp),x
 321                     ; 43 	temp16 <<= 8;
 323  0059 7b02          	ld	a,(OFST+0,sp)
 324  005b 6b01          	ld	(OFST-1,sp),a
 325  005d 0f02          	clr	(OFST+0,sp)
 326                     ; 44 	temp16 += (u16) (SPI1_RW( (u8)(Reg & 0x00FF) ));
 328  005f 7b04          	ld	a,(OFST+2,sp)
 329  0061 a4ff          	and	a,#255
 330  0063 ad9b          	call	_SPI1_RW
 332  0065 5f            	clrw	x
 333  0066 97            	ld	xl,a
 334  0067 72fb01        	addw	x,(OFST-1,sp)
 335  006a 1f01          	ldw	(OFST-1,sp),x
 336                     ; 45 	SPI1_CSN_H;			//NSS拉高，关闭SPI	// Set CSN high again;
 338  006c 7218500a      	bset	20490,#4
 339                     ; 46 	return temp16;
 341  0070 1e01          	ldw	x,(OFST-1,sp)
 344  0072 5b04          	addw	sp,#4
 345  0074 81            	ret
 382                     ; 59 void Si4431TX_Init(void)
 382                     ; 60 { u8 TmpRegVal;                  
 383                     	switch	.text
 384  0075               _Si4431TX_Init:
 386  0075 88            	push	a
 387       00000001      OFST:	set	1
 390                     ; 61 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x80);	//寄存器软复位
 392  0076 ae0080        	ldw	x,#128
 393  0079 a687          	ld	a,#135
 394  007b 95            	ld	xh,a
 395  007c ad98          	call	_SPI1_RWReg
 398  007e               L741:
 399                     ; 63 	while ( GPIO_ReadInputPin(SPI1_CTL_GPIO, SPI1_PIN_IRQ) == Bit_SET);	//wait for chip ready interrupt from the radio (while the nIRQ pin is high) 
 401  007e 4b01          	push	#1
 402  0080 ae500f        	ldw	x,#20495
 403  0083 cd0000        	call	_GPIO_ReadInputPin
 405  0086 5b01          	addw	sp,#1
 406  0088 a101          	cp	a,#1
 407  008a 27f2          	jreq	L741
 408                     ; 65 	SPI1_Read(InterruptStatus1);	//清中断
 410  008c a603          	ld	a,#3
 411  008e ad9e          	call	_SPI1_Read
 413                     ; 66 	SPI1_Read(InterruptStatus2);
 415  0090 a604          	ld	a,#4
 416  0092 ad9a          	call	_SPI1_Read
 418                     ; 68 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);		//关闭所有中断
 420  0094 5f            	clrw	x
 421  0095 a686          	ld	a,#134
 422  0097 95            	ld	xh,a
 423  0098 cd0016        	call	_SPI1_RWReg
 425                     ; 70 	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x7F);		//30M晶振的调谐电容为12.5P
 427  009b ae007f        	ldw	x,#127
 428  009e a689          	ld	a,#137
 429  00a0 95            	ld	xh,a
 430  00a1 cd0016        	call	_SPI1_RWReg
 432                     ; 71 	TmpRegVal = SPI1_Read(CrystalOscillatorLoadCapacitance);						//读寄存器，检查是否设置正确
 434  00a4 a609          	ld	a,#9
 435  00a6 ad86          	call	_SPI1_Read
 437                     ; 74 	SPI1_RWReg((REG_WRITE | GPIO0Configuration), 0x12);									//GPIO_0 发射模式
 439  00a8 ae0012        	ldw	x,#18
 440  00ab a68b          	ld	a,#139
 441  00ad 95            	ld	xh,a
 442  00ae cd0016        	call	_SPI1_RWReg
 444                     ; 75 	SPI1_RWReg((REG_WRITE | GPIO1Configuration), 0x14); 								//GPIO_1 接收数据
 446  00b1 ae0014        	ldw	x,#20
 447  00b4 a68c          	ld	a,#140
 448  00b6 95            	ld	xh,a
 449  00b7 cd0016        	call	_SPI1_RWReg
 451                     ; 76 	SPI1_RWReg((REG_WRITE | GPIO2Configuration), 0x15); 								//GPIO_2 接收模式	
 453  00ba ae0015        	ldw	x,#21
 454  00bd a68d          	ld	a,#141
 455  00bf 95            	ld	xh,a
 456  00c0 cd0016        	call	_SPI1_RWReg
 458                     ; 77 	SPI1_RWReg((REG_WRITE | IOPortConfiguration), 0x00); 							  // gpio    0, 1,2 NO OTHER FUNCTION. 
 460  00c3 5f            	clrw	x
 461  00c4 a68e          	ld	a,#142
 462  00c6 95            	ld	xh,a
 463  00c7 cd0016        	call	_SPI1_RWReg
 465                     ; 78 	SPI1_RWReg((REG_WRITE | ModulationModeControl1),0x20);							//不使用曼彻斯特编码 没有白化 
 467  00ca ae0020        	ldw	x,#32
 468  00cd a6f0          	ld	a,#240
 469  00cf 95            	ld	xh,a
 470  00d0 cd0016        	call	_SPI1_RWReg
 472                     ; 81 	SPI1_RWReg((REG_WRITE | AFCLoopGearshiftOverride), 0x00);						//(1Dh)禁止AFC
 474  00d3 5f            	clrw	x
 475  00d4 a69d          	ld	a,#157
 476  00d6 95            	ld	xh,a
 477  00d7 cd0016        	call	_SPI1_RWReg
 479                     ; 83 	SPI1_RWReg((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);			//(20h)
 481  00da ae00a1        	ldw	x,#161
 482  00dd a6a0          	ld	a,#160
 483  00df 95            	ld	xh,a
 484  00e0 cd0016        	call	_SPI1_RWReg
 486                     ; 84 	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset2), 0x20);								//(21h)
 488  00e3 ae0020        	ldw	x,#32
 489  00e6 a6a1          	ld	a,#161
 490  00e8 95            	ld	xh,a
 491  00e9 cd0016        	call	_SPI1_RWReg
 493                     ; 85 	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset1), 0x4e);								//(22h)
 495  00ec ae004e        	ldw	x,#78
 496  00ef a6a2          	ld	a,#162
 497  00f1 95            	ld	xh,a
 498  00f2 cd0016        	call	_SPI1_RWReg
 500                     ; 86 	SPI1_RWReg((REG_WRITE | ClockRecoveryOffset0), 0xa5);								//(23h)
 502  00f5 ae00a5        	ldw	x,#165
 503  00f8 a6a3          	ld	a,#163
 504  00fa 95            	ld	xh,a
 505  00fb cd0016        	call	_SPI1_RWReg
 507                     ; 87 	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);				//(24h)
 509  00fe 5f            	clrw	x
 510  00ff a6a4          	ld	a,#164
 511  0101 95            	ld	xh,a
 512  0102 cd0016        	call	_SPI1_RWReg
 514                     ; 88 	SPI1_RWReg((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);				//(25h)0x0a
 516  0105 ae0036        	ldw	x,#54
 517  0108 a6a5          	ld	a,#165
 518  010a 95            	ld	xh,a
 519  010b cd0016        	call	_SPI1_RWReg
 521                     ; 94 	SPI1_RWReg((REG_WRITE | TXDataRate1), 0x02); 												//(6EH)9600BPS
 523  010e ae0002        	ldw	x,#2
 524  0111 a6ee          	ld	a,#238
 525  0113 95            	ld	xh,a
 526  0114 cd0016        	call	_SPI1_RWReg
 528                     ; 95 	SPI1_RWReg((REG_WRITE | TXDataRate0), 0x75);												//(6FH)
 530  0117 ae0075        	ldw	x,#117
 531  011a a6ef          	ld	a,#239
 532  011c 95            	ld	xh,a
 533  011d cd0016        	call	_SPI1_RWReg
 535                     ; 97 	SPI1_RWReg((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
 537  0120 ae007f        	ldw	x,#127
 538  0123 a6d2          	ld	a,#210
 539  0125 95            	ld	xh,a
 540  0126 cd0016        	call	_SPI1_RWReg
 542                     ; 100 	SPI1_RWReg((REG_WRITE | FrequencyBandSelect), 0x53);    						//(75H)边带选择，低频段240-479.9M 430Mhz
 544  0129 ae0053        	ldw	x,#83
 545  012c a6f5          	ld	a,#245
 546  012e 95            	ld	xh,a
 547  012f cd0016        	call	_SPI1_RWReg
 549                     ; 101 	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency1), 0x4b);  					//(76H)fc  正好433HZ
 551  0132 ae004b        	ldw	x,#75
 552  0135 a6f6          	ld	a,#246
 553  0137 95            	ld	xh,a
 554  0138 cd0016        	call	_SPI1_RWReg
 556                     ; 102 	SPI1_RWReg((REG_WRITE | NominalCarrierFrequency0), 0x00);						//(77H)fc
 558  013b 5f            	clrw	x
 559  013c a6f7          	ld	a,#247
 560  013e 95            	ld	xh,a
 561  013f cd0016        	call	_SPI1_RWReg
 563                     ; 105 	SPI1_RWReg((REG_WRITE | FrequencyDeviation), 0x20);                 //(72h)频率偏差20k                            
 565  0142 ae0020        	ldw	x,#32
 566  0145 a6f2          	ld	a,#242
 567  0147 95            	ld	xh,a
 568  0148 cd0016        	call	_SPI1_RWReg
 570                     ; 106 	SPI1_RWReg((REG_WRITE | FrequencyOffset),0x00); 										//(73h)
 572  014b 5f            	clrw	x
 573  014c a6f3          	ld	a,#243
 574  014e 95            	ld	xh,a
 575  014f cd0016        	call	_SPI1_RWReg
 577                     ; 108 	SPI1_RWReg((REG_WRITE | ModulationModeControl1), 0x00); 						//(70H)
 579  0152 5f            	clrw	x
 580  0153 a6f0          	ld	a,#240
 581  0155 95            	ld	xh,a
 582  0156 cd0016        	call	_SPI1_RWReg
 584                     ; 109 	SPI1_RWReg((REG_WRITE | ModulationModeControl2), 0x22); 						//(71H)直接模式 FSK调制
 586  0159 ae0022        	ldw	x,#34
 587  015c a6f1          	ld	a,#241
 588  015e 95            	ld	xh,a
 589  015f cd0016        	call	_SPI1_RWReg
 591                     ; 111 	SPI1_RWReg((REG_WRITE | HeaderControl1), 0x0F);											//(32h)校验checkhead3-0 4位接收地址
 593  0162 ae000f        	ldw	x,#15
 594  0165 a6b2          	ld	a,#178
 595  0167 95            	ld	xh,a
 596  0168 cd0016        	call	_SPI1_RWReg
 598                     ; 112 	SPI1_RWReg((REG_WRITE | HeaderControl2), 0x42); 										//(33h)no head; sync word 3 and 2
 600  016b ae0042        	ldw	x,#66
 601  016e a6b3          	ld	a,#179
 602  0170 95            	ld	xh,a
 603  0171 cd0016        	call	_SPI1_RWReg
 605                     ; 113 	SPI1_RWReg((REG_WRITE | PreambleLength), 0x08);   									//(34h)引导头长度 32 byte
 607  0174 ae0008        	ldw	x,#8
 608  0177 a6b4          	ld	a,#180
 609  0179 95            	ld	xh,a
 610  017a cd0016        	call	_SPI1_RWReg
 612                     ; 115 	SPI1_RWReg((REG_WRITE | SyncWord3), 0x2d);													//(36h)同步头
 614  017d ae002d        	ldw	x,#45
 615  0180 a6b6          	ld	a,#182
 616  0182 95            	ld	xh,a
 617  0183 cd0016        	call	_SPI1_RWReg
 619                     ; 116 	SPI1_RWReg((REG_WRITE | SyncWord2), 0xa4);													//(37h)
 621  0186 ae00a4        	ldw	x,#164
 622  0189 a6b7          	ld	a,#183
 623  018b 95            	ld	xh,a
 624  018c cd0016        	call	_SPI1_RWReg
 626                     ; 120 	SPI1_RWReg((REG_WRITE | DataAccessControl), 0x8D); 									//(30h)enable TX handling	CRC16
 628  018f ae008d        	ldw	x,#141
 629  0192 a6b0          	ld	a,#176
 630  0194 95            	ld	xh,a
 631  0195 cd0016        	call	_SPI1_RWReg
 633                     ; 122 	SPI1_RWReg((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);			//(1Fh)
 635  0198 ae0013        	ldw	x,#19
 636  019b a69f          	ld	a,#159
 637  019d 95            	ld	xh,a
 638  019e cd0016        	call	_SPI1_RWReg
 640                     ; 124 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x03);					//(08h)
 642  01a1 ae0003        	ldw	x,#3
 643  01a4 a688          	ld	a,#136
 644  01a6 95            	ld	xh,a
 645  01a7 cd0016        	call	_SPI1_RWReg
 647                     ; 125 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00);					//(08h)
 649  01aa 5f            	clrw	x
 650  01ab a688          	ld	a,#136
 651  01ad 95            	ld	xh,a
 652  01ae cd0016        	call	_SPI1_RWReg
 654                     ; 126 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);					//(09h)ready模式，Xtal
 656  01b1 ae0001        	ldw	x,#1
 657  01b4 a687          	ld	a,#135
 658  01b6 95            	ld	xh,a
 659  01b7 cd0016        	call	_SPI1_RWReg
 661                     ; 127 	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x60);										//(50h)使能发射FIFO几乎满，几乎空中断
 663  01ba ae0060        	ldw	x,#96
 664  01bd a685          	ld	a,#133
 665  01bf 95            	ld	xh,a
 666  01c0 cd0016        	call	_SPI1_RWReg
 668                     ; 128 	SPI1_RWReg((REG_WRITE | TXPower), 0x07);
 670  01c3 ae0007        	ldw	x,#7
 671  01c6 a6ed          	ld	a,#237
 672  01c8 95            	ld	xh,a
 673  01c9 cd0016        	call	_SPI1_RWReg
 675                     ; 130 	SPI1_RWReg((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x3f);
 677  01cc ae003f        	ldw	x,#63
 678  01cf a689          	ld	a,#137
 679  01d1 95            	ld	xh,a
 680  01d2 cd0016        	call	_SPI1_RWReg
 682                     ; 131 }
 685  01d5 84            	pop	a
 686  01d6 81            	ret
 711                     ; 140 void Si4431TX_IdleMod(void)
 711                     ; 141 {
 712                     	switch	.text
 713  01d7               _Si4431TX_IdleMod:
 717                     ; 142 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x01);		// 
 719  01d7 ae0001        	ldw	x,#1
 720  01da a687          	ld	a,#135
 721  01dc 95            	ld	xh,a
 722  01dd cd0016        	call	_SPI1_RWReg
 724                     ; 144 	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x00);
 726  01e0 5f            	clrw	x
 727  01e1 a685          	ld	a,#133
 728  01e3 95            	ld	xh,a
 729  01e4 cd0016        	call	_SPI1_RWReg
 731                     ; 145 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
 733  01e7 5f            	clrw	x
 734  01e8 a686          	ld	a,#134
 735  01ea 95            	ld	xh,a
 736  01eb cd0016        	call	_SPI1_RWReg
 738                     ; 147 	SPI1_Read(InterruptStatus1);
 740  01ee a603          	ld	a,#3
 741  01f0 cd002e        	call	_SPI1_Read
 743                     ; 148 	SPI1_Read(InterruptStatus2);
 745  01f3 a604          	ld	a,#4
 746  01f5 cd002e        	call	_SPI1_Read
 748                     ; 149 }
 751  01f8 81            	ret
 817                     ; 158 void Si4431TX_TransmitMod(u8 * pTxHeader)
 817                     ; 159 {
 818                     	switch	.text
 819  01f9               _Si4431TX_TransmitMod:
 821  01f9 89            	pushw	x
 822  01fa 5203          	subw	sp,#3
 823       00000003      OFST:	set	3
 826                     ; 161 	Si4431TX_IdleMod();        
 828  01fc add9          	call	_Si4431TX_IdleMod
 830                     ; 162 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
 832  01fe ae0001        	ldw	x,#1
 833  0201 a688          	ld	a,#136
 834  0203 95            	ld	xh,a
 835  0204 cd0016        	call	_SPI1_RWReg
 837                     ; 163 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
 839  0207 5f            	clrw	x
 840  0208 a688          	ld	a,#136
 841  020a 95            	ld	xh,a
 842  020b cd0016        	call	_SPI1_RWReg
 844                     ; 164 	TxHeaderAdr = TransmitHeader3;			//发送帧头
 846  020e a63a          	ld	a,#58
 847  0210 6b02          	ld	(OFST-1,sp),a
 848                     ; 166 	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头，高位对齐	
 850  0212 0f03          	clr	(OFST+0,sp)
 851  0214               L512:
 852                     ; 167 		SPI1_RWReg((REG_WRITE | TxHeaderAdr + iLoop),* (pTxHeader+iLoop));		
 854  0214 7b04          	ld	a,(OFST+1,sp)
 855  0216 97            	ld	xl,a
 856  0217 7b05          	ld	a,(OFST+2,sp)
 857  0219 1b03          	add	a,(OFST+0,sp)
 858  021b 2401          	jrnc	L22
 859  021d 5c            	incw	x
 860  021e               L22:
 861  021e 02            	rlwa	x,a
 862  021f f6            	ld	a,(x)
 863  0220 97            	ld	xl,a
 864  0221 7b02          	ld	a,(OFST-1,sp)
 865  0223 1b03          	add	a,(OFST+0,sp)
 866  0225 aa80          	or	a,#128
 867  0227 95            	ld	xh,a
 868  0228 cd0016        	call	_SPI1_RWReg
 870                     ; 166 	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){		//设置发送地址头，高位对齐	
 872  022b 0c03          	inc	(OFST+0,sp)
 875  022d 7b03          	ld	a,(OFST+0,sp)
 876  022f a104          	cp	a,#4
 877  0231 25e1          	jrult	L512
 878                     ; 170   TmpVal = SPI1_Read(TransmitHeader3);
 880  0233 a63a          	ld	a,#58
 881  0235 cd002e        	call	_SPI1_Read
 883                     ; 171 	TmpVal = SPI1_Read(TransmitHeader0);
 885  0238 a63d          	ld	a,#61
 886  023a cd002e        	call	_SPI1_Read
 888                     ; 173 	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);							  //中断使能包发送
 890  023d ae0004        	ldw	x,#4
 891  0240 a685          	ld	a,#133
 892  0242 95            	ld	xh,a
 893  0243 cd0016        	call	_SPI1_RWReg
 895                     ; 174 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
 897  0246 5f            	clrw	x
 898  0247 a686          	ld	a,#134
 899  0249 95            	ld	xh,a
 900  024a cd0016        	call	_SPI1_RWReg
 902                     ; 175 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);			//TX人工接收模式，预备模式
 904  024d ae0009        	ldw	x,#9
 905  0250 a687          	ld	a,#135
 906  0252 95            	ld	xh,a
 907  0253 cd0016        	call	_SPI1_RWReg
 909                     ; 176 }
 912  0256 5b05          	addw	sp,#5
 913  0258 81            	ret
 978                     ; 185 void Si4431TX_ReceiveMod(u8 * pRxCheckHeader)
 978                     ; 186 {	u8 iLoop,RxCheckHeaderAdr,TmpVal;
 979                     	switch	.text
 980  0259               _Si4431TX_ReceiveMod:
 982  0259 89            	pushw	x
 983  025a 5203          	subw	sp,#3
 984       00000003      OFST:	set	3
 987                     ; 187 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x02); 			 //清接收FIFO
 989  025c ae0002        	ldw	x,#2
 990  025f a688          	ld	a,#136
 991  0261 95            	ld	xh,a
 992  0262 cd0016        	call	_SPI1_RWReg
 994                     ; 188  	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2), 0x00); 
 996  0265 5f            	clrw	x
 997  0266 a688          	ld	a,#136
 998  0268 95            	ld	xh,a
 999  0269 cd0016        	call	_SPI1_RWReg
1001                     ; 189 	RxCheckHeaderAdr = CheckHeader3;			//接收校对地址头
1003  026c a63f          	ld	a,#63
1004  026e 6b02          	ld	(OFST-1,sp),a
1005                     ; 191 	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //设置接收校对地址头	
1007  0270 0f03          	clr	(OFST+0,sp)
1008  0272               L552:
1009                     ; 192 		SPI1_RWReg((REG_WRITE | RxCheckHeaderAdr + iLoop),* (pRxCheckHeader+iLoop));		
1011  0272 7b04          	ld	a,(OFST+1,sp)
1012  0274 97            	ld	xl,a
1013  0275 7b05          	ld	a,(OFST+2,sp)
1014  0277 1b03          	add	a,(OFST+0,sp)
1015  0279 2401          	jrnc	L62
1016  027b 5c            	incw	x
1017  027c               L62:
1018  027c 02            	rlwa	x,a
1019  027d f6            	ld	a,(x)
1020  027e 97            	ld	xl,a
1021  027f 7b02          	ld	a,(OFST-1,sp)
1022  0281 1b03          	add	a,(OFST+0,sp)
1023  0283 aa80          	or	a,#128
1024  0285 95            	ld	xh,a
1025  0286 cd0016        	call	_SPI1_RWReg
1027                     ; 191 	for(iLoop=0; iLoop < TXHEADERRATE; iLoop++){										 //设置接收校对地址头	
1029  0289 0c03          	inc	(OFST+0,sp)
1032  028b 7b03          	ld	a,(OFST+0,sp)
1033  028d a104          	cp	a,#4
1034  028f 25e1          	jrult	L552
1035                     ; 194   TmpVal = SPI1_Read(CheckHeader3);
1037  0291 a63f          	ld	a,#63
1038  0293 cd002e        	call	_SPI1_Read
1040                     ; 195 	TmpVal = SPI1_Read(CheckHeader0);
1042  0296 a642          	ld	a,#66
1043  0298 cd002e        	call	_SPI1_Read
1045                     ; 197 	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x02); 							 //中断使能接收到有效包
1047  029b ae0002        	ldw	x,#2
1048  029e a685          	ld	a,#133
1049  02a0 95            	ld	xh,a
1050  02a1 cd0016        	call	_SPI1_RWReg
1052                     ; 198  	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00); 
1054  02a4 5f            	clrw	x
1055  02a5 a686          	ld	a,#134
1056  02a7 95            	ld	xh,a
1057  02a8 cd0016        	call	_SPI1_RWReg
1059                     ; 200 	SPI1_Read(InterruptStatus1);
1061  02ab a603          	ld	a,#3
1062  02ad cd002e        	call	_SPI1_Read
1064                     ; 201 	SPI1_Read(InterruptStatus2);
1066  02b0 a604          	ld	a,#4
1067  02b2 cd002e        	call	_SPI1_Read
1069                     ; 203 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x05);			 //RX人工接收模式，预备模式
1071  02b5 ae0005        	ldw	x,#5
1072  02b8 a687          	ld	a,#135
1073  02ba 95            	ld	xh,a
1074  02bb cd0016        	call	_SPI1_RWReg
1076                     ; 205 }
1079  02be 5b05          	addw	sp,#5
1080  02c0 81            	ret
1115                     ; 214 u8 Si4431TX_BusyCheck(void)
1115                     ; 215 {
1116                     	switch	.text
1117  02c1               _Si4431TX_BusyCheck:
1119  02c1 88            	push	a
1120       00000001      OFST:	set	1
1123                     ; 217 	value =  (unsigned char)(SPI1_Read(ReceivedSignalStrengthIndicator)) ;//读信号强度寄存器
1125  02c2 a626          	ld	a,#38
1126  02c4 cd002e        	call	_SPI1_Read
1128  02c7 6b01          	ld	(OFST+0,sp),a
1129                     ; 218 	if(value>40)
1131  02c9 7b01          	ld	a,(OFST+0,sp)
1132  02cb a129          	cp	a,#41
1133  02cd 2504          	jrult	L103
1134                     ; 219 		return 0;
1136  02cf 4f            	clr	a
1139  02d0 5b01          	addw	sp,#1
1140  02d2 81            	ret
1141  02d3               L103:
1142                     ; 221 		return 1;
1144  02d3 a601          	ld	a,#1
1147  02d5 5b01          	addw	sp,#1
1148  02d7 81            	ret
1203                     ; 231 void Si4431TX_TxPacket(unsigned char * packet, unsigned char length)
1203                     ; 232 {
1204                     	switch	.text
1205  02d8               _Si4431TX_TxPacket:
1207  02d8 89            	pushw	x
1208  02d9 88            	push	a
1209       00000001      OFST:	set	1
1212                     ; 234 	Si4431TX_IdleMod();        
1214  02da cd01d7        	call	_Si4431TX_IdleMod
1216                     ; 235 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
1218  02dd ae0001        	ldw	x,#1
1219  02e0 a688          	ld	a,#136
1220  02e2 95            	ld	xh,a
1221  02e3 cd0016        	call	_SPI1_RWReg
1223                     ; 236 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl2),0x00);         
1225  02e6 5f            	clrw	x
1226  02e7 a688          	ld	a,#136
1227  02e9 95            	ld	xh,a
1228  02ea cd0016        	call	_SPI1_RWReg
1230                     ; 237 	SPI1_RWReg((REG_WRITE | TransmitPacketLength), length);	 
1232  02ed 7b06          	ld	a,(OFST+5,sp)
1233  02ef 97            	ld	xl,a
1234  02f0 a6be          	ld	a,#190
1235  02f2 95            	ld	xh,a
1236  02f3 cd0016        	call	_SPI1_RWReg
1238                     ; 238   for(temp8=0;temp8<length;temp8++){	
1240  02f6 0f01          	clr	(OFST+0,sp)
1242  02f8 2015          	jra	L733
1243  02fa               L333:
1244                     ; 239 		SPI1_RWReg((REG_WRITE | FIFOAccess),packet[temp8]);		
1246  02fa 7b02          	ld	a,(OFST+1,sp)
1247  02fc 97            	ld	xl,a
1248  02fd 7b03          	ld	a,(OFST+2,sp)
1249  02ff 1b01          	add	a,(OFST+0,sp)
1250  0301 2401          	jrnc	L43
1251  0303 5c            	incw	x
1252  0304               L43:
1253  0304 02            	rlwa	x,a
1254  0305 f6            	ld	a,(x)
1255  0306 97            	ld	xl,a
1256  0307 a6ff          	ld	a,#255
1257  0309 95            	ld	xh,a
1258  030a cd0016        	call	_SPI1_RWReg
1260                     ; 238   for(temp8=0;temp8<length;temp8++){	
1262  030d 0c01          	inc	(OFST+0,sp)
1263  030f               L733:
1266  030f 7b01          	ld	a,(OFST+0,sp)
1267  0311 1106          	cp	a,(OFST+5,sp)
1268  0313 25e5          	jrult	L333
1269                     ; 241 	SPI1_RWReg((REG_WRITE | InterruptEnable1), 0x04);
1271  0315 ae0004        	ldw	x,#4
1272  0318 a685          	ld	a,#133
1273  031a 95            	ld	xh,a
1274  031b cd0016        	call	_SPI1_RWReg
1276                     ; 242 	SPI1_RWReg((REG_WRITE | InterruptEnable2), 0x00);
1278  031e 5f            	clrw	x
1279  031f a686          	ld	a,#134
1280  0321 95            	ld	xh,a
1281  0322 cd0016        	call	_SPI1_RWReg
1283                     ; 243 	SPI1_RWReg((REG_WRITE | OperatingFunctionControl1), 0x09);		
1285  0325 ae0009        	ldw	x,#9
1286  0328 a687          	ld	a,#135
1287  032a 95            	ld	xh,a
1288  032b cd0016        	call	_SPI1_RWReg
1290                     ; 244 }
1293  032e 5b03          	addw	sp,#3
1294  0330 81            	ret
1307                     	xdef	_Si4431TX_TxPacket
1308                     	xdef	_Si4431TX_BusyCheck
1309                     	xdef	_Si4431TX_ReceiveMod
1310                     	xdef	_Si4431TX_TransmitMod
1311                     	xdef	_Si4431TX_IdleMod
1312                     	xdef	_Si4431TX_Init
1313                     	xdef	_SPI1_RWWord
1314                     	xdef	_SPI1_Read
1315                     	xdef	_SPI1_RWReg
1316                     	xdef	_SPI1_RW
1317                     	xref	_SPI_GetFlagStatus
1318                     	xref	_SPI_ReceiveData
1319                     	xref	_SPI_SendData
1320                     	xref	_GPIO_ReadInputPin
1339                     	end
