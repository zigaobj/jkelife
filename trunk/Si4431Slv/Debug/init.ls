   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  52                     ; 5 void SysInit_Config(void)
  52                     ; 6 {
  54                     	switch	.text
  55  0000               _SysInit_Config:
  59                     ; 14   CLK_Configuration();
  61  0000 ad1b          	call	_CLK_Configuration
  63                     ; 17   GPIO_Configuration();
  65  0002 ad58          	call	_GPIO_Configuration
  67                     ; 23 	SPI_Config();
  69  0004 cd0192        	call	_SPI_Config
  71                     ; 26   ITC_Configuration();
  73  0007 cd025c        	call	_ITC_Configuration
  75                     ; 28   USART_Config();	//串口初始化
  77  000a cd0096        	call	_USART_Config
  79                     ; 30   TIM3_Config();	//系统时钟，提供10us的最小计时单元
  81  000d cd01b1        	call	_TIM3_Config
  83                     ; 32 	Delay(100);
  85  0010 ae0064        	ldw	x,#100
  86  0013 cd0000        	call	_Delay
  88                     ; 33   TIM2_Config();
  90  0016 cd01db        	call	_TIM2_Config
  92                     ; 35   VarInit();	//系统变量，状态初始化
  94  0019 cd00bf        	call	_VarInit
  96                     ; 38 }
  99  001c 81            	ret
 127                     ; 45 void CLK_Configuration(void)
 127                     ; 46 {
 128                     	switch	.text
 129  001d               _CLK_Configuration:
 133                     ; 47   CLK_DeInit();
 135  001d cd0000        	call	_CLK_DeInit
 137                     ; 50 	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
 139  0020 4f            	clr	a
 140  0021 cd0000        	call	_CLK_HSIPrescalerConfig
 142                     ; 52 	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, DISABLE);	//选择内部高速时钟
 144  0024 4b00          	push	#0
 145  0026 4b00          	push	#0
 146  0028 ae00e1        	ldw	x,#225
 147  002b a601          	ld	a,#1
 148  002d 95            	ld	xh,a
 149  002e cd0000        	call	_CLK_ClockSwitchConfig
 151  0031 85            	popw	x
 152                     ; 55 	CLK_HSICmd(ENABLE);	//使能内部高速时钟
 154  0032 a601          	ld	a,#1
 155  0034 cd0000        	call	_CLK_HSICmd
 157                     ; 57 	CLK_PeripheralClockConfig( CLK_PERIPHERAL_UART1 , ENABLE);	//打开UART时钟
 159  0037 ae0001        	ldw	x,#1
 160  003a a602          	ld	a,#2
 161  003c 95            	ld	xh,a
 162  003d cd0000        	call	_CLK_PeripheralClockConfig
 164                     ; 58 	CLK_PeripheralClockConfig( CLK_PERIPHERAL_SPI, ENABLE);
 166  0040 ae0001        	ldw	x,#1
 167  0043 a601          	ld	a,#1
 168  0045 95            	ld	xh,a
 169  0046 cd0000        	call	_CLK_PeripheralClockConfig
 171                     ; 59 	CLK_PeripheralClockConfig( CLK_PERIPHERAL_TIMER2, ENABLE);
 173  0049 ae0001        	ldw	x,#1
 174  004c a605          	ld	a,#5
 175  004e 95            	ld	xh,a
 176  004f cd0000        	call	_CLK_PeripheralClockConfig
 178                     ; 60 	CLK_PeripheralClockConfig( CLK_PERIPHERAL_TIMER3 , ENABLE);
 180  0052 ae0001        	ldw	x,#1
 181  0055 a606          	ld	a,#6
 182  0057 95            	ld	xh,a
 183  0058 cd0000        	call	_CLK_PeripheralClockConfig
 185                     ; 63 }
 188  005b 81            	ret
 213                     ; 70 void GPIO_Configuration(void)
 213                     ; 71 {
 214                     	switch	.text
 215  005c               _GPIO_Configuration:
 219                     ; 74   GPIO_Init(LEDS_PORT, (LED0_PIN | Q1_PIN | Q2_PIN), GPIO_MODE_OUT_PP_LOW_FAST);		//推挽输出
 221  005c 4be0          	push	#224
 222  005e 4b19          	push	#25
 223  0060 ae5005        	ldw	x,#20485
 224  0063 cd0000        	call	_GPIO_Init
 226  0066 85            	popw	x
 227                     ; 75 	GPIO_Init(SPI1_PIN_GPIO, (SPI1_PIN_CSN | SPI1_PIN_CE ), GPIO_MODE_OUT_PP_HIGH_FAST);		//推挽输出
 229  0067 4bf0          	push	#240
 230  0069 4b12          	push	#18
 231  006b ae500a        	ldw	x,#20490
 232  006e cd0000        	call	_GPIO_Init
 234  0071 85            	popw	x
 235                     ; 76 	GPIO_Init(SPI1_CTL_GPIO, SPI1_PIN_PWR , GPIO_MODE_OUT_PP_HIGH_FAST);		//推挽输出
 237  0072 4bf0          	push	#240
 238  0074 4b04          	push	#4
 239  0076 ae500f        	ldw	x,#20495
 240  0079 cd0000        	call	_GPIO_Init
 242  007c 85            	popw	x
 243                     ; 80 	GPIO_Init(SPI1_CTL_GPIO , SPI1_PIN_IRQ , GPIO_MODE_IN_FL_IT );
 245  007d 4b20          	push	#32
 246  007f 4b01          	push	#1
 247  0081 ae500f        	ldw	x,#20495
 248  0084 cd0000        	call	_GPIO_Init
 250  0087 85            	popw	x
 251                     ; 83   EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);	//设置输入线路下降沿为中断请求
 253  0088 ae0002        	ldw	x,#2
 254  008b a603          	ld	a,#3
 255  008d 95            	ld	xh,a
 256  008e cd0000        	call	_EXTI_SetExtIntSensitivity
 258                     ; 85 	SPI1_PWR_OFF();	//断电重启24L01模块
 260  0091 7215500f      	bres	20495,#2
 261                     ; 86 }
 264  0095 81            	ret
 291                     ; 89  void USART_Config(void)
 291                     ; 90 {
 292                     	switch	.text
 293  0096               _USART_Config:
 297                     ; 92 	UART1_DeInit();
 299  0096 cd0000        	call	_UART1_DeInit
 301                     ; 95   UART1_Init((u32)15200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
 303  0099 4b0c          	push	#12
 304  009b 4b80          	push	#128
 305  009d 4b00          	push	#0
 306  009f 4b00          	push	#0
 307  00a1 4b00          	push	#0
 308  00a3 ae3b60        	ldw	x,#15200
 309  00a6 89            	pushw	x
 310  00a7 ae0000        	ldw	x,#0
 311  00aa 89            	pushw	x
 312  00ab cd0000        	call	_UART1_Init
 314  00ae 5b09          	addw	sp,#9
 315                     ; 98   UART1_Cmd(ENABLE);
 317  00b0 a601          	ld	a,#1
 318  00b2 cd0000        	call	_UART1_Cmd
 320                     ; 103   UART1_ITConfig(UART1_IT_RXNE, ENABLE);
 322  00b5 4b01          	push	#1
 323  00b7 ae0255        	ldw	x,#597
 324  00ba cd0000        	call	_UART1_ITConfig
 326  00bd 84            	pop	a
 327                     ; 109 }
 330  00be 81            	ret
 375                     ; 113 void VarInit(void)
 375                     ; 114 {	u8 i;
 376                     	switch	.text
 377  00bf               _VarInit:
 379  00bf 88            	push	a
 380       00000001      OFST:	set	1
 383                     ; 116 	WorkStaPre1 = STA_SLEEP;
 385  00c0 725f0000      	clr	_WorkStaPre1
 386                     ; 117 	WorkSta1	= STA_SLEEP;	
 388  00c4 725f0000      	clr	_WorkSta1
 389                     ; 120 	pCmdBuf =&CmdBuf;	//指向命理处理缓冲区
 391  00c8 ae0000        	ldw	x,#_CmdBuf
 392  00cb bf00          	ldw	_pCmdBuf,x
 393                     ; 121 	pRxAdr_Tab = &RxAdr_Tab;
 395  00cd ae0000        	ldw	x,#_RxAdr_Tab
 396  00d0 bf00          	ldw	_pRxAdr_Tab,x
 397                     ; 122 	for(i = 0;i < SPIBUFLEN ;i++){
 399  00d2 0f01          	clr	(OFST+0,sp)
 400  00d4               L76:
 401                     ; 123 		SPI1_RxBuf[i] = 0;
 403  00d4 7b01          	ld	a,(OFST+0,sp)
 404  00d6 5f            	clrw	x
 405  00d7 97            	ld	xl,a
 406  00d8 724f0000      	clr	(_SPI1_RxBuf,x)
 407                     ; 125 		SPI1_TxBuf[i] = i;
 409  00dc 7b01          	ld	a,(OFST+0,sp)
 410  00de 5f            	clrw	x
 411  00df 97            	ld	xl,a
 412  00e0 7b01          	ld	a,(OFST+0,sp)
 413  00e2 d70000        	ld	(_SPI1_TxBuf,x),a
 414                     ; 122 	for(i = 0;i < SPIBUFLEN ;i++){
 416  00e5 0c01          	inc	(OFST+0,sp)
 419  00e7 7b01          	ld	a,(OFST+0,sp)
 420  00e9 a120          	cp	a,#32
 421  00eb 25e7          	jrult	L76
 422                     ; 128 	sta = 0;   //状态标志
 424  00ed 3f00          	clr	_sta
 425                     ; 137 	pRxAdr_Tab->RxAdrTabCnt = 0;
 427  00ef 923f00        	clr	[_pRxAdr_Tab.w]
 428                     ; 140 	pRxAdr_Tab->pRxAdrTabCnt = pRxAdr_Tab->RxAdrTab0;	//将pRxAdrTabCnt指向空的接收地址表格空间。
 430  00f2 be00          	ldw	x,_pRxAdr_Tab
 431  00f4 1c001d        	addw	x,#29
 432  00f7 90be00        	ldw	y,_pRxAdr_Tab
 433  00fa 90ef01        	ldw	(1,y),x
 434                     ; 142 	for(i = 0; i < RXADRTABLEN; i++){
 436  00fd 0f01          	clr	(OFST+0,sp)
 437  00ff               L57:
 438                     ; 149 		pRxAdr_Tab->TabFlag[i] = 0;
 440  00ff b600          	ld	a,_pRxAdr_Tab
 441  0101 97            	ld	xl,a
 442  0102 b601          	ld	a,_pRxAdr_Tab+1
 443  0104 1b01          	add	a,(OFST+0,sp)
 444  0106 2401          	jrnc	L61
 445  0108 5c            	incw	x
 446  0109               L61:
 447  0109 02            	rlwa	x,a
 448  010a 6f04          	clr	(4,x)
 449                     ; 150 		pCmdBuf->CmdListFlag[i] = 0;
 451  010c b600          	ld	a,_pCmdBuf
 452  010e 97            	ld	xl,a
 453  010f b601          	ld	a,_pCmdBuf+1
 454  0111 1b01          	add	a,(OFST+0,sp)
 455  0113 2401          	jrnc	L02
 456  0115 5c            	incw	x
 457  0116               L02:
 458  0116 02            	rlwa	x,a
 459  0117 6f0a          	clr	(10,x)
 460                     ; 142 	for(i = 0; i < RXADRTABLEN; i++){
 462  0119 0c01          	inc	(OFST+0,sp)
 465  011b 7b01          	ld	a,(OFST+0,sp)
 466  011d a106          	cp	a,#6
 467  011f 25de          	jrult	L57
 468                     ; 153 	pRxAdr_Tab->TabFlag[5] = 0;
 470  0121 be00          	ldw	x,_pRxAdr_Tab
 471  0123 6f09          	clr	(9,x)
 472                     ; 158 	for(i = 0;i < RX_ADR_WIDTH;i++){
 474  0125 0f01          	clr	(OFST+0,sp)
 475  0127               L301:
 476                     ; 159 		pRxAdr_Tab->RxAdrTab0[i] = i;
 478  0127 b600          	ld	a,_pRxAdr_Tab
 479  0129 97            	ld	xl,a
 480  012a b601          	ld	a,_pRxAdr_Tab+1
 481  012c 1b01          	add	a,(OFST+0,sp)
 482  012e 2401          	jrnc	L22
 483  0130 5c            	incw	x
 484  0131               L22:
 485  0131 02            	rlwa	x,a
 486  0132 7b01          	ld	a,(OFST+0,sp)
 487  0134 e71d          	ld	(29,x),a
 488                     ; 160 		pRxAdr_Tab->RxAdrTab1[i] = i;
 490  0136 b600          	ld	a,_pRxAdr_Tab
 491  0138 97            	ld	xl,a
 492  0139 b601          	ld	a,_pRxAdr_Tab+1
 493  013b 1b01          	add	a,(OFST+0,sp)
 494  013d 2401          	jrnc	L42
 495  013f 5c            	incw	x
 496  0140               L42:
 497  0140 02            	rlwa	x,a
 498  0141 7b01          	ld	a,(OFST+0,sp)
 499  0143 e721          	ld	(33,x),a
 500                     ; 161 		pRxAdr_Tab->RxAdrTab2[i] = i;
 502  0145 b600          	ld	a,_pRxAdr_Tab
 503  0147 97            	ld	xl,a
 504  0148 b601          	ld	a,_pRxAdr_Tab+1
 505  014a 1b01          	add	a,(OFST+0,sp)
 506  014c 2401          	jrnc	L62
 507  014e 5c            	incw	x
 508  014f               L62:
 509  014f 02            	rlwa	x,a
 510  0150 7b01          	ld	a,(OFST+0,sp)
 511  0152 e725          	ld	(37,x),a
 512                     ; 162 		pRxAdr_Tab->RxAdrTab3[i] = i;
 514  0154 b600          	ld	a,_pRxAdr_Tab
 515  0156 97            	ld	xl,a
 516  0157 b601          	ld	a,_pRxAdr_Tab+1
 517  0159 1b01          	add	a,(OFST+0,sp)
 518  015b 2401          	jrnc	L03
 519  015d 5c            	incw	x
 520  015e               L03:
 521  015e 02            	rlwa	x,a
 522  015f 7b01          	ld	a,(OFST+0,sp)
 523  0161 e729          	ld	(41,x),a
 524                     ; 163 		pRxAdr_Tab->RxAdrTab4[i] = i;
 526  0163 b600          	ld	a,_pRxAdr_Tab
 527  0165 97            	ld	xl,a
 528  0166 b601          	ld	a,_pRxAdr_Tab+1
 529  0168 1b01          	add	a,(OFST+0,sp)
 530  016a 2401          	jrnc	L23
 531  016c 5c            	incw	x
 532  016d               L23:
 533  016d 02            	rlwa	x,a
 534  016e 7b01          	ld	a,(OFST+0,sp)
 535  0170 e72d          	ld	(45,x),a
 536                     ; 164 		pRxAdr_Tab->RxAdrTab5[i] = i;	
 538  0172 b600          	ld	a,_pRxAdr_Tab
 539  0174 97            	ld	xl,a
 540  0175 b601          	ld	a,_pRxAdr_Tab+1
 541  0177 1b01          	add	a,(OFST+0,sp)
 542  0179 2401          	jrnc	L43
 543  017b 5c            	incw	x
 544  017c               L43:
 545  017c 02            	rlwa	x,a
 546  017d 7b01          	ld	a,(OFST+0,sp)
 547  017f e731          	ld	(49,x),a
 548                     ; 158 	for(i = 0;i < RX_ADR_WIDTH;i++){
 550  0181 0c01          	inc	(OFST+0,sp)
 553  0183 7b01          	ld	a,(OFST+0,sp)
 554  0185 a104          	cp	a,#4
 555  0187 259e          	jrult	L301
 556                     ; 167 	srand((unsigned) MOD3_TXADR[4]);	//随机函数的种子函数，可以在变值的地方调用，提高随机性
 558  0189 b604          	ld	a,_MOD3_TXADR+4
 559  018b 5f            	clrw	x
 560  018c 97            	ld	xl,a
 561  018d cd0000        	call	_srand
 563                     ; 168 }
 566  0190 84            	pop	a
 567  0191 81            	ret
 593                     ; 174 void SPI_Config(void)
 593                     ; 175 {
 594                     	switch	.text
 595  0192               _SPI_Config:
 599                     ; 185   SPI_DeInit();
 601  0192 cd0000        	call	_SPI_DeInit
 603                     ; 186 	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_16, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00);
 605  0195 4b00          	push	#0
 606  0197 4b02          	push	#2
 607  0199 4b00          	push	#0
 608  019b 4b00          	push	#0
 609  019d 4b00          	push	#0
 610  019f 4b04          	push	#4
 611  01a1 ae0018        	ldw	x,#24
 612  01a4 4f            	clr	a
 613  01a5 95            	ld	xh,a
 614  01a6 cd0000        	call	_SPI_Init
 616  01a9 5b06          	addw	sp,#6
 617                     ; 187 	SPI_Cmd(ENABLE);
 619  01ab a601          	ld	a,#1
 620  01ad cd0000        	call	_SPI_Cmd
 622                     ; 189 }
 625  01b0 81            	ret
 654                     ; 197 void TIM3_Config(void)
 654                     ; 198 {
 655                     	switch	.text
 656  01b1               _TIM3_Config:
 660                     ; 199   TIM3_DeInit(); 
 662  01b1 cd0000        	call	_TIM3_DeInit
 664                     ; 203   TIM3_TimeBaseInit(TIM3_PRESCALER_1024, 15625);	//正好一秒
 666  01b4 ae3d09        	ldw	x,#15625
 667  01b7 89            	pushw	x
 668  01b8 a60a          	ld	a,#10
 669  01ba cd0000        	call	_TIM3_TimeBaseInit
 671  01bd 85            	popw	x
 672                     ; 206   TIM3_PrescalerConfig(TIM3_PRESCALER_1024, TIM3_PSCRELOADMODE_IMMEDIATE);	
 674  01be ae0001        	ldw	x,#1
 675  01c1 a60a          	ld	a,#10
 676  01c3 95            	ld	xh,a
 677  01c4 cd0000        	call	_TIM3_PrescalerConfig
 679                     ; 209   TIM3_ARRPreloadConfig(ENABLE);
 681  01c7 a601          	ld	a,#1
 682  01c9 cd0000        	call	_TIM3_ARRPreloadConfig
 684                     ; 210 	TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);	//启动TIM3更新中断
 686  01cc ae0001        	ldw	x,#1
 687  01cf a601          	ld	a,#1
 688  01d1 95            	ld	xh,a
 689  01d2 cd0000        	call	_TIM3_ITConfig
 691                     ; 213   TIM3_Cmd(ENABLE);
 693  01d5 a601          	ld	a,#1
 694  01d7 cd0000        	call	_TIM3_Cmd
 696                     ; 215 }
 699  01da 81            	ret
 734                     ; 217 void TIM2_Config(void)
 734                     ; 218 {
 735                     	switch	.text
 736  01db               _TIM2_Config:
 740                     ; 219   TIM2_DeInit();
 742  01db cd0000        	call	_TIM2_DeInit
 744                     ; 223   TIM2_TimeBaseInit(TIM2_PRESCALER_1024, TIM2_PERIOD);	//正好两秒
 746  01de ae7a12        	ldw	x,#31250
 747  01e1 89            	pushw	x
 748  01e2 a60a          	ld	a,#10
 749  01e4 cd0000        	call	_TIM2_TimeBaseInit
 751  01e7 85            	popw	x
 752                     ; 226   TIM2_PrescalerConfig(TIM2_PRESCALER_1024, TIM2_PSCRELOADMODE_IMMEDIATE);	
 754  01e8 ae0001        	ldw	x,#1
 755  01eb a60a          	ld	a,#10
 756  01ed 95            	ld	xh,a
 757  01ee cd0000        	call	_TIM2_PrescalerConfig
 759                     ; 239 	TIM2_OC1Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR1, TIM2_OCPOLARITY_HIGH);
 761  01f1 4b00          	push	#0
 762  01f3 ae061a        	ldw	x,#1562
 763  01f6 89            	pushw	x
 764  01f7 ae0011        	ldw	x,#17
 765  01fa 4f            	clr	a
 766  01fb 95            	ld	xh,a
 767  01fc cd0000        	call	_TIM2_OC1Init
 769  01ff 5b03          	addw	sp,#3
 770                     ; 241   TIM2_OC1PreloadConfig(DISABLE);
 772  0201 4f            	clr	a
 773  0202 cd0000        	call	_TIM2_OC1PreloadConfig
 775                     ; 247   TIM2_OC2Init(TIM2_OCMODE_TIMING,TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR2,TIM2_OCPOLARITY_HIGH); 
 777  0205 4b00          	push	#0
 778  0207 ae249f        	ldw	x,#9375
 779  020a 89            	pushw	x
 780  020b ae0011        	ldw	x,#17
 781  020e 4f            	clr	a
 782  020f 95            	ld	xh,a
 783  0210 cd0000        	call	_TIM2_OC2Init
 785  0213 5b03          	addw	sp,#3
 786                     ; 248   TIM2_OC2PreloadConfig(DISABLE);
 788  0215 4f            	clr	a
 789  0216 cd0000        	call	_TIM2_OC2PreloadConfig
 791                     ; 254   TIM2_OC3Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_ENABLE,TIM2_CCR3, TIM2_OCPOLARITY_HIGH);
 793  0219 4b00          	push	#0
 794  021b ae3d09        	ldw	x,#15625
 795  021e 89            	pushw	x
 796  021f ae0011        	ldw	x,#17
 797  0222 4f            	clr	a
 798  0223 95            	ld	xh,a
 799  0224 cd0000        	call	_TIM2_OC3Init
 801  0227 5b03          	addw	sp,#3
 802                     ; 255   TIM2_OC3PreloadConfig(DISABLE);
 804  0229 4f            	clr	a
 805  022a cd0000        	call	_TIM2_OC3PreloadConfig
 807                     ; 257   TIM2_ARRPreloadConfig(ENABLE);
 809  022d a601          	ld	a,#1
 810  022f cd0000        	call	_TIM2_ARRPreloadConfig
 812                     ; 259   TIM2_ITConfig(TIM2_IT_CC1, ENABLE);
 814  0232 ae0001        	ldw	x,#1
 815  0235 a602          	ld	a,#2
 816  0237 95            	ld	xh,a
 817  0238 cd0000        	call	_TIM2_ITConfig
 819                     ; 260   TIM2_ITConfig(TIM2_IT_CC2, ENABLE);
 821  023b ae0001        	ldw	x,#1
 822  023e a604          	ld	a,#4
 823  0240 95            	ld	xh,a
 824  0241 cd0000        	call	_TIM2_ITConfig
 826                     ; 261   TIM2_ITConfig(TIM2_IT_CC3, ENABLE);
 828  0244 ae0001        	ldw	x,#1
 829  0247 a608          	ld	a,#8
 830  0249 95            	ld	xh,a
 831  024a cd0000        	call	_TIM2_ITConfig
 833                     ; 262 	TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);	//启动TIM2中断 
 835  024d ae0001        	ldw	x,#1
 836  0250 a601          	ld	a,#1
 837  0252 95            	ld	xh,a
 838  0253 cd0000        	call	_TIM2_ITConfig
 840                     ; 266   TIM2_Cmd(ENABLE);
 842  0256 a601          	ld	a,#1
 843  0258 cd0000        	call	_TIM2_Cmd
 845                     ; 268 }
 848  025b 81            	ret
 872                     ; 288 void ITC_Configuration(void)
 872                     ; 289 {
 873                     	switch	.text
 874  025c               _ITC_Configuration:
 878                     ; 290 	ITC_SetSoftwarePriority(ITC_IRQ_UART1_RX , ITC_PRIORITYLEVEL_1);	//将UART1_RX中断优先级设置为1级
 880  025c ae0001        	ldw	x,#1
 881  025f a612          	ld	a,#18
 882  0261 95            	ld	xh,a
 883  0262 cd0000        	call	_ITC_SetSoftwarePriority
 885                     ; 291 	ITC_SetSoftwarePriority(ITC_IRQ_TIM2_OVF , ITC_PRIORITYLEVEL_2);	//将TIM2_OVF中断优先级设置为3级
 887  0265 5f            	clrw	x
 888  0266 a60d          	ld	a,#13
 889  0268 95            	ld	xh,a
 890  0269 cd0000        	call	_ITC_SetSoftwarePriority
 892                     ; 292 }
 895  026c 81            	ret
 908                     	xref	_Delay
 909                     	xref	_WorkStaPre1
 910                     	xref	_WorkSta1
 911                     	xref	_srand
 912                     	xref.b	_RxAdr_Tab
 913                     	xref.b	_pRxAdr_Tab
 914                     	xref.b	_pCmdBuf
 915                     	xref.b	_CmdBuf
 916                     	xref.b	_MOD3_TXADR
 917                     	xref.b	_sta
 918                     	xref	_SPI1_RxBuf
 919                     	xref	_SPI1_TxBuf
 920                     	xdef	_ITC_Configuration
 921                     	xdef	_SysInit_Config
 922                     	xdef	_GPIO_Configuration
 923                     	xdef	_CLK_Configuration
 924                     	xdef	_TIM2_Config
 925                     	xdef	_TIM3_Config
 926                     	xdef	_USART_Config
 927                     	xdef	_VarInit
 928                     	xdef	_SPI_Config
 929                     	xref	_UART1_ITConfig
 930                     	xref	_UART1_Cmd
 931                     	xref	_UART1_Init
 932                     	xref	_UART1_DeInit
 933                     	xref	_TIM3_ARRPreloadConfig
 934                     	xref	_TIM3_PrescalerConfig
 935                     	xref	_TIM3_ITConfig
 936                     	xref	_TIM3_Cmd
 937                     	xref	_TIM3_TimeBaseInit
 938                     	xref	_TIM3_DeInit
 939                     	xref	_TIM2_OC3PreloadConfig
 940                     	xref	_TIM2_OC2PreloadConfig
 941                     	xref	_TIM2_OC1PreloadConfig
 942                     	xref	_TIM2_ARRPreloadConfig
 943                     	xref	_TIM2_PrescalerConfig
 944                     	xref	_TIM2_ITConfig
 945                     	xref	_TIM2_Cmd
 946                     	xref	_TIM2_OC3Init
 947                     	xref	_TIM2_OC2Init
 948                     	xref	_TIM2_OC1Init
 949                     	xref	_TIM2_TimeBaseInit
 950                     	xref	_TIM2_DeInit
 951                     	xref	_SPI_Cmd
 952                     	xref	_SPI_Init
 953                     	xref	_SPI_DeInit
 954                     	xref	_ITC_SetSoftwarePriority
 955                     	xref	_GPIO_Init
 956                     	xref	_EXTI_SetExtIntSensitivity
 957                     	xref	_CLK_HSIPrescalerConfig
 958                     	xref	_CLK_ClockSwitchConfig
 959                     	xref	_CLK_PeripheralClockConfig
 960                     	xref	_CLK_HSICmd
 961                     	xref	_CLK_DeInit
 980                     	end
