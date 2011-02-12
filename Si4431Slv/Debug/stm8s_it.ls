   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  43                     ; 63 @far @interrupt void TRAP_IRQHandler(void)
  43                     ; 64 {
  44                     	switch	.text
  45  0000               f_TRAP_IRQHandler:
  49                     ; 68 }
  52  0000 80            	iret
  74                     ; 94 @far @interrupt void TLI_IRQHandler(void)
  74                     ; 95 #else /* _RAISONANCE_ */
  74                     ; 96 void TLI_IRQHandler(void) interrupt 0
  74                     ; 97 #endif /* _COSMIC_ */
  74                     ; 98 {
  75                     	switch	.text
  76  0001               f_TLI_IRQHandler:
  80                     ; 102 }
  83  0001 80            	iret
 105                     ; 112 @far @interrupt void AWU_IRQHandler(void)
 105                     ; 113 #else /* _RAISONANCE_ */
 105                     ; 114 void AWU_IRQHandler(void) interrupt 1
 105                     ; 115 #endif /* _COSMIC_ */
 105                     ; 116 {
 106                     	switch	.text
 107  0002               f_AWU_IRQHandler:
 111                     ; 120 }
 114  0002 80            	iret
 136                     ; 130 @far @interrupt void CLK_IRQHandler(void)
 136                     ; 131 #else /* _RAISONANCE_ */
 136                     ; 132 void CLK_IRQHandler(void) interrupt 2
 136                     ; 133 #endif /* _COSMIC_ */
 136                     ; 134 {
 137                     	switch	.text
 138  0003               f_CLK_IRQHandler:
 142                     ; 138 }
 145  0003 80            	iret
 168                     ; 148 @far @interrupt void EXTI_PORTA_IRQHandler(void)
 168                     ; 149 #else /* _RAISONANCE_ */
 168                     ; 150 void EXTI_PORTA_IRQHandler(void) interrupt 3
 168                     ; 151 #endif /* _COSMIC_ */
 168                     ; 152 {
 169                     	switch	.text
 170  0004               f_EXTI_PORTA_IRQHandler:
 174                     ; 156 }
 177  0004 80            	iret
 200                     ; 166 @far @interrupt void EXTI_PORTB_IRQHandler(void)
 200                     ; 167 #else /* _RAISONANCE_ */
 200                     ; 168 void EXTI_PORTB_IRQHandler(void) interrupt 4
 200                     ; 169 #endif /* _COSMIC_ */
 200                     ; 170 {
 201                     	switch	.text
 202  0005               f_EXTI_PORTB_IRQHandler:
 206                     ; 174 }
 209  0005 80            	iret
 232                     ; 184 @far @interrupt void EXTI_PORTC_IRQHandler(void)
 232                     ; 185 #else /* _RAISONANCE_ */
 232                     ; 186 void EXTI_PORTC_IRQHandler(void) interrupt 5
 232                     ; 187 #endif /* _COSMIC_ */
 232                     ; 188 {	
 233                     	switch	.text
 234  0006               f_EXTI_PORTC_IRQHandler:
 238                     ; 190 }
 241  0006 80            	iret
 286                     ; 200 @far @interrupt void EXTI_PORTD_IRQHandler(void)
 286                     ; 201 #else /* _RAISONANCE_ */
 286                     ; 202 void EXTI_PORTD_IRQHandler(void) interrupt 6
 286                     ; 203 #endif /* _COSMIC_ */
 286                     ; 204 {
 287                     	switch	.text
 288  0007               f_EXTI_PORTD_IRQHandler:
 290       00000001      OFST:	set	1
 291  0007 3b0002        	push	c_x+2
 292  000a be00          	ldw	x,c_x
 293  000c 89            	pushw	x
 294  000d 3b0002        	push	c_y+2
 295  0010 be00          	ldw	x,c_y
 296  0012 89            	pushw	x
 297  0013 88            	push	a
 300                     ; 206   ButtonState ^= 0xFF;
 302  0014 b600          	ld	a,_ButtonState
 303  0016 a8ff          	xor	a,	#255
 304  0018 b700          	ld	_ButtonState,a
 305                     ; 215 	SPI1Sta = SPI1_Read(STATUS_24L01);	// 读取状态寄存其来判断数据接收状况	
 307  001a a607          	ld	a,#7
 308  001c cd0000        	call	_SPI1_Read
 310  001f b700          	ld	_SPI1Sta,a
 311                     ; 216 	SPI1_CE_L;	//StandBy I模式
 313  0021 7213500a      	bres	20490,#1
 314                     ; 217 	if(SPI1Sta & TX_DS){			//正常发送接收到ACK后的中断
 316  0025 b600          	ld	a,_SPI1Sta
 317  0027 a520          	bcp	a,#32
 318  0029 2707          	jreq	L711
 319                     ; 219 		SPI1_RW_Reg(FLUSH_TX_24L01 , 0);
 321  002b 5f            	clrw	x
 322  002c a6e1          	ld	a,#225
 323  002e 95            	ld	xh,a
 324  002f cd0000        	call	_SPI1_RW_Reg
 326  0032               L711:
 327                     ; 222 	if(SPI1Sta & MAX_RT){				// 判断是否超过重发最大数
 329  0032 b600          	ld	a,_SPI1Sta
 330  0034 a510          	bcp	a,#16
 331  0036 2707          	jreq	L121
 332                     ; 224 		SPI1_RW_Reg(FLUSH_TX_24L01 , 0);	//不知道是否要清空FIFO，还是读取FIFO值后自动清空
 334  0038 5f            	clrw	x
 335  0039 a6e1          	ld	a,#225
 336  003b 95            	ld	xh,a
 337  003c cd0000        	call	_SPI1_RW_Reg
 339  003f               L121:
 340                     ; 228 	if(SPI1Sta & RX_DR){				// 判断是否接收到数据
 342  003f b600          	ld	a,_SPI1Sta
 343  0041 a540          	bcp	a,#64
 344  0043 2772          	jreq	L321
 345                     ; 229 	  SPI1NewFlg = 1;
 347  0045 35010000      	mov	_SPI1NewFlg,#1
 348                     ; 231 		SPI1_CE_L;	//StandBy I模式
 350  0049 7213500a      	bres	20490,#1
 351                     ; 232 		SPI1_Read_Buf(RD_RX_PLOAD_24L01,SPI1_RxBuf,TX_PLOAD_WIDTH_24L01);// read receive payload from RX_FIFO buffer
 353  004d 4b20          	push	#32
 354  004f ae0000        	ldw	x,#_SPI1_RxBuf
 355  0052 89            	pushw	x
 356  0053 a661          	ld	a,#97
 357  0055 cd0000        	call	_SPI1_Read_Buf
 359  0058 5b03          	addw	sp,#3
 360                     ; 234 	  SPI1_RW_Reg(FLUSH_RX_24L01 , 0);
 362  005a 5f            	clrw	x
 363  005b a6e2          	ld	a,#226
 364  005d 95            	ld	xh,a
 365  005e cd0000        	call	_SPI1_RW_Reg
 367                     ; 237 		if(!SPI1FullFlag){
 369  0061 725d0000      	tnz	_SPI1FullFlag
 370  0065 2648          	jrne	L521
 371                     ; 238 			for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
 373  0067 0f01          	clr	(OFST+0,sp)
 374  0069               L721:
 375                     ; 239 				SPI1_ParseBuf[SPI1index] = SPI1_RxBuf[i];	//将接收缓冲区SPI1_RxBuf数据转移到处理数据缓冲区SPI1_ParseBuf
 377  0069 c60000        	ld	a,_SPI1index
 378  006c 5f            	clrw	x
 379  006d 97            	ld	xl,a
 380  006e 7b01          	ld	a,(OFST+0,sp)
 381  0070 905f          	clrw	y
 382  0072 9097          	ld	yl,a
 383  0074 90d60000      	ld	a,(_SPI1_RxBuf,y)
 384  0078 d70000        	ld	(_SPI1_ParseBuf,x),a
 385                     ; 240 				if(0x0A == SPI1_ParseBuf[SPI1index] ){		
 387  007b c60000        	ld	a,_SPI1index
 388  007e 5f            	clrw	x
 389  007f 97            	ld	xl,a
 390  0080 d60000        	ld	a,(_SPI1_ParseBuf,x)
 391  0083 a10a          	cp	a,#10
 392  0085 2611          	jrne	L531
 393                     ; 241 					if(0x0D == SPI1_ParseBuf[SPI1index-1] ){
 395  0087 c60000        	ld	a,_SPI1index
 396  008a 5f            	clrw	x
 397  008b 97            	ld	xl,a
 398  008c 5a            	decw	x
 399  008d d60000        	ld	a,(_SPI1_ParseBuf,x)
 400  0090 a10d          	cp	a,#13
 401  0092 2604          	jrne	L531
 402                     ; 242 						SPI1OkFlag ++;		//收到0x0D 0x0A认为是一条完整的命令			
 404  0094 725c0000      	inc	_SPI1OkFlag
 405  0098               L531:
 406                     ; 245 				SPI1index++;
 408  0098 725c0000      	inc	_SPI1index
 409                     ; 246 				if(SPI1index >= SPI1PARSEBUFLEN){
 411  009c c60000        	ld	a,_SPI1index
 412  009f a1a0          	cp	a,#160
 413  00a1 2504          	jrult	L141
 414                     ; 247 					SPI1FullFlag = 1;	//接收缓冲区满，未来得及处理数据
 416  00a3 35010000      	mov	_SPI1FullFlag,#1
 417  00a7               L141:
 418                     ; 238 			for(i=0 ; i<RX_PLOAD_WIDTH_24L01 ; i++){
 420  00a7 0c01          	inc	(OFST+0,sp)
 423  00a9 7b01          	ld	a,(OFST+0,sp)
 424  00ab a120          	cp	a,#32
 425  00ad 25ba          	jrult	L721
 426  00af               L521:
 427                     ; 251 		SPI1NewFlg = 0;
 429  00af 725f0000      	clr	_SPI1NewFlg
 430                     ; 252 		SPI1_CE_H;	//置高CE，保持接收模式
 432  00b3 7212500a      	bset	20490,#1
 433  00b7               L321:
 434                     ; 254 	SPI1_RW_Reg(WRITE_REG_24L01 + STATUS_24L01,0xff);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
 436  00b7 ae00ff        	ldw	x,#255
 437  00ba a627          	ld	a,#39
 438  00bc 95            	ld	xh,a
 439  00bd cd0000        	call	_SPI1_RW_Reg
 441                     ; 255 }
 444  00c0 84            	pop	a
 445  00c1 85            	popw	x
 446  00c2 bf00          	ldw	c_y,x
 447  00c4 320002        	pop	c_y+2
 448  00c7 85            	popw	x
 449  00c8 bf00          	ldw	c_x,x
 450  00ca 320002        	pop	c_x+2
 451  00cd 80            	iret
 474                     ; 265 @far @interrupt void EXTI_PORTE_IRQHandler(void)
 474                     ; 266 #else /* _RAISONANCE_ */
 474                     ; 267 void EXTI_PORTE_IRQHandler(void) interrupt 7
 474                     ; 268 #endif /* _COSMIC_ */
 474                     ; 269 {
 475                     	switch	.text
 476  00ce               f_EXTI_PORTE_IRQHandler:
 480                     ; 273 }
 483  00ce 80            	iret
 505                     ; 303 @far @interrupt void CAN_RX_IRQHandler(void)
 505                     ; 304 #else /* _RAISONANCE_ */
 505                     ; 305 void CAN_RX_IRQHandler(void) interrupt 8
 505                     ; 306 #endif /* _COSMIC_ */
 505                     ; 307 {
 506                     	switch	.text
 507  00cf               f_CAN_RX_IRQHandler:
 511                     ; 311 }
 514  00cf 80            	iret
 536                     ; 321 @far @interrupt void CAN_TX_IRQHandler(void)
 536                     ; 322 #else /* _RAISONANCE_ */
 536                     ; 323 void CAN_TX_IRQHandler(void) interrupt 9
 536                     ; 324 #endif /* _COSMIC_ */
 536                     ; 325 {
 537                     	switch	.text
 538  00d0               f_CAN_TX_IRQHandler:
 542                     ; 329 }
 545  00d0 80            	iret
 567                     ; 340 @far @interrupt void SPI_IRQHandler(void)
 567                     ; 341 #else /* _RAISONANCE_ */
 567                     ; 342 void SPI_IRQHandler(void) interrupt 10
 567                     ; 343 #endif /* _COSMIC_ */
 567                     ; 344 {
 568                     	switch	.text
 569  00d1               f_SPI_IRQHandler:
 573                     ; 348 }
 576  00d1 80            	iret
 599                     ; 358 @far @interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
 599                     ; 359 #else /* _RAISONANCE_ */
 599                     ; 360 void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) interrupt 11
 599                     ; 361 #endif /* _COSMIC_ */
 599                     ; 362 {
 600                     	switch	.text
 601  00d2               f_TIM1_UPD_OVF_TRG_BRK_IRQHandler:
 605                     ; 366 }
 608  00d2 80            	iret
 631                     ; 376 @far @interrupt void TIM1_CAP_COM_IRQHandler(void)
 631                     ; 377 #else /* _RAISONANCE_ */
 631                     ; 378 void TIM1_CAP_COM_IRQHandler(void) interrupt 12
 631                     ; 379 #endif /* _COSMIC_ */
 631                     ; 380 {
 632                     	switch	.text
 633  00d3               f_TIM1_CAP_COM_IRQHandler:
 637                     ; 384 }
 640  00d3 80            	iret
 669                     ; 431 @far @interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
 669                     ; 432 #else /* _RAISONANCE_ */
 669                     ; 433 void TIM2_UPD_OVF_BRK_IRQHandler(void) interrupt 13
 669                     ; 434 #endif /* _COSMIC_ */
 669                     ; 435 {
 670                     	switch	.text
 671  00d4               f_TIM2_UPD_OVF_BRK_IRQHandler:
 673  00d4 3b0002        	push	c_x+2
 674  00d7 be00          	ldw	x,c_x
 675  00d9 89            	pushw	x
 676  00da 3b0002        	push	c_y+2
 677  00dd be00          	ldw	x,c_y
 678  00df 89            	pushw	x
 681                     ; 437 	if(TIM2_GetITStatus(TIM2_IT_UPDATE) != RESET){		//待机状态	  
 683  00e0 a601          	ld	a,#1
 684  00e2 cd0000        	call	_TIM2_GetITStatus
 686  00e5 4d            	tnz	a
 687  00e6 272c          	jreq	L332
 688                     ; 446 		TIM2_ClearITPendingBit(TIM2_IT_UPDATE);	//清除 TIMx 的中断待处理位TIM_IT_Update 
 690  00e8 a601          	ld	a,#1
 691  00ea cd0000        	call	_TIM2_ClearITPendingBit
 693                     ; 447 		TIM2_ClearFlag(TIM2_FLAG_UPDATE );		
 695  00ed ae0001        	ldw	x,#1
 696  00f0 cd0000        	call	_TIM2_ClearFlag
 698                     ; 448 		if(GPIO_ReadInputPin(LEDS_PORT, LED0_PIN)){
 700  00f3 4b01          	push	#1
 701  00f5 ae5005        	ldw	x,#20485
 702  00f8 cd0000        	call	_GPIO_ReadInputPin
 704  00fb 5b01          	addw	sp,#1
 705  00fd 4d            	tnz	a
 706  00fe 270b          	jreq	L532
 707                     ; 449 			GPIO_WriteLow(LEDS_PORT, LED0_PIN);
 709  0100 4b01          	push	#1
 710  0102 ae5005        	ldw	x,#20485
 711  0105 cd0000        	call	_GPIO_WriteLow
 713  0108 84            	pop	a
 715  0109 2009          	jra	L332
 716  010b               L532:
 717                     ; 452 			GPIO_WriteHigh(LEDS_PORT, LED0_PIN);
 719  010b 4b01          	push	#1
 720  010d ae5005        	ldw	x,#20485
 721  0110 cd0000        	call	_GPIO_WriteHigh
 723  0113 84            	pop	a
 724  0114               L332:
 725                     ; 455 }
 728  0114 85            	popw	x
 729  0115 bf00          	ldw	c_y,x
 730  0117 320002        	pop	c_y+2
 731  011a 85            	popw	x
 732  011b bf00          	ldw	c_x,x
 733  011d 320002        	pop	c_x+2
 734  0120 80            	iret
 761                     ; 465 @far @interrupt void TIM2_CAP_COM_IRQHandler(void)
 761                     ; 466 #else /* _RAISONANCE_ */
 761                     ; 467 void TIM2_CAP_COM_IRQHandler(void) interrupt 14
 761                     ; 468 #endif /* _COSMIC_ */
 761                     ; 469 {
 762                     	switch	.text
 763  0121               f_TIM2_CAP_COM_IRQHandler:
 765  0121 3b0002        	push	c_x+2
 766  0124 be00          	ldw	x,c_x
 767  0126 89            	pushw	x
 768  0127 3b0002        	push	c_y+2
 769  012a be00          	ldw	x,c_y
 770  012c 89            	pushw	x
 773                     ; 470 	if(TIM2_GetITStatus(TIM2_IT_CC1) != RESET){	//同步工作状态。接收
 775  012d a602          	ld	a,#2
 776  012f cd0000        	call	_TIM2_GetITStatus
 778  0132 4d            	tnz	a
 779  0133 2718          	jreq	L152
 780                     ; 471 		TIM2_ClearITPendingBit(TIM2_IT_CC1);	//清除 TIMx 的中断待处理位TIM_IT_Update 
 782  0135 a602          	ld	a,#2
 783  0137 cd0000        	call	_TIM2_ClearITPendingBit
 785                     ; 473 		if((TRUE == InNetFlag)&&(STA_STANDBY == WorkSta1)){	//只有从STA_STANDBY模式才能转入
 787  013a b600          	ld	a,_InNetFlag
 788  013c a101          	cp	a,#1
 789  013e 264b          	jrne	L552
 791  0140 c60000        	ld	a,_WorkSta1
 792  0143 a106          	cp	a,#6
 793  0145 2644          	jrne	L552
 794                     ; 474 			WorkSta1 = STA_SYNCHRONIZE;	//同步工作状态。
 796  0147 35020000      	mov	_WorkSta1,#2
 797  014b 203e          	jra	L552
 798  014d               L152:
 799                     ; 478 	else if(TIM2_GetITStatus(TIM2_IT_CC2) != RESET){	//广播阶段，接收来自主模块的命令与数据 接收
 801  014d a604          	ld	a,#4
 802  014f cd0000        	call	_TIM2_GetITStatus
 804  0152 4d            	tnz	a
 805  0153 2718          	jreq	L752
 806                     ; 479 		TIM2_ClearITPendingBit(TIM2_IT_CC2);	//清除 TIMx 的中断待处理位TIM_IT_Update
 808  0155 a604          	ld	a,#4
 809  0157 cd0000        	call	_TIM2_ClearITPendingBit
 811                     ; 481 		if((TRUE == InNetFlag)&&(STA_SYNCHRONIZE == WorkSta1)){	//只有从STA_SYNCHRONIZE模式才能转入
 813  015a b600          	ld	a,_InNetFlag
 814  015c a101          	cp	a,#1
 815  015e 262b          	jrne	L552
 817  0160 c60000        	ld	a,_WorkSta1
 818  0163 a102          	cp	a,#2
 819  0165 2624          	jrne	L552
 820                     ; 482 			WorkSta1 = STA_BROADCAST;		//广播阶段
 822  0167 35030000      	mov	_WorkSta1,#3
 823  016b 201e          	jra	L552
 824  016d               L752:
 825                     ; 486 	else if(TIM2_GetITStatus(TIM2_IT_CC3) != RESET){	//数据阶段，发送回复命令及心跳包到主模块 发送
 827  016d a608          	ld	a,#8
 828  016f cd0000        	call	_TIM2_GetITStatus
 830  0172 4d            	tnz	a
 831  0173 2716          	jreq	L552
 832                     ; 487 		TIM2_ClearITPendingBit(TIM2_IT_CC3);	//清除 TIMx 的中断待处理位TIM_IT_Update 
 834  0175 a608          	ld	a,#8
 835  0177 cd0000        	call	_TIM2_ClearITPendingBit
 837                     ; 489 		if((TRUE == InNetFlag)&&(STA_BROADCAST == WorkSta1)){	//只有从STA_SYNCHRONIZE模式才能转入{
 839  017a b600          	ld	a,_InNetFlag
 840  017c a101          	cp	a,#1
 841  017e 260b          	jrne	L552
 843  0180 c60000        	ld	a,_WorkSta1
 844  0183 a103          	cp	a,#3
 845  0185 2604          	jrne	L552
 846                     ; 490 			WorkSta1 = STA_DATA ;		//维持心跳普通数据传输阶段
 848  0187 35040000      	mov	_WorkSta1,#4
 849  018b               L552:
 850                     ; 494 }
 853  018b 85            	popw	x
 854  018c bf00          	ldw	c_y,x
 855  018e 320002        	pop	c_y+2
 856  0191 85            	popw	x
 857  0192 bf00          	ldw	c_x,x
 858  0194 320002        	pop	c_x+2
 859  0197 80            	iret
 886                     ; 506 @far @interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
 886                     ; 507 #else /* _RAISONANCE_ */
 886                     ; 508 void TIM3_UPD_OVF_BRK_IRQHandler(void) interrupt 15
 886                     ; 509 #endif /* _COSMIC_ */
 886                     ; 510 {	//1秒中断一次， 作为系统的整体时基，用于同步网络各模块时基
 887                     	switch	.text
 888  0198               f_TIM3_UPD_OVF_BRK_IRQHandler:
 890  0198 3b0002        	push	c_x+2
 891  019b be00          	ldw	x,c_x
 892  019d 89            	pushw	x
 893  019e 3b0002        	push	c_y+2
 894  01a1 be00          	ldw	x,c_y
 895  01a3 89            	pushw	x
 898                     ; 511 	if(TIM3_GetITStatus(TIM3_IT_UPDATE) != RESET){	  
 900  01a4 a601          	ld	a,#1
 901  01a6 cd0000        	call	_TIM3_GetITStatus
 903  01a9 4d            	tnz	a
 904  01aa 2713          	jreq	L103
 905                     ; 515 		TIM3_ClearITPendingBit(TIM3_IT_UPDATE);	//清除 TIMx 的中断待处理位TIM_IT_Update 
 907  01ac a601          	ld	a,#1
 908  01ae cd0000        	call	_TIM3_ClearITPendingBit
 910                     ; 516 		TIM3_ClearFlag(TIM3_FLAG_UPDATE );
 912  01b1 ae0001        	ldw	x,#1
 913  01b4 cd0000        	call	_TIM3_ClearFlag
 915                     ; 517 		GlobalRunTime.Second++;
 917  01b7 ae0000        	ldw	x,#_GlobalRunTime
 918  01ba a601          	ld	a,#1
 919  01bc cd0000        	call	c_lgadc
 921  01bf               L103:
 922                     ; 520 }
 925  01bf 85            	popw	x
 926  01c0 bf00          	ldw	c_y,x
 927  01c2 320002        	pop	c_y+2
 928  01c5 85            	popw	x
 929  01c6 bf00          	ldw	c_x,x
 930  01c8 320002        	pop	c_x+2
 931  01cb 80            	iret
 954                     ; 530 @far @interrupt void TIM3_CAP_COM_IRQHandler(void)
 954                     ; 531 #else /* _RAISONANCE_ */
 954                     ; 532 void TIM3_CAP_COM_IRQHandler(void) interrupt 16
 954                     ; 533 #endif /* _COSMIC_ */
 954                     ; 534 {
 955                     	switch	.text
 956  01cc               f_TIM3_CAP_COM_IRQHandler:
 960                     ; 538 }
 963  01cc 80            	iret
 986                     ; 550 @far @interrupt void UART1_TX_IRQHandler(void)
 986                     ; 551 #else /* _RAISONANCE_ */
 986                     ; 552 void UART1_TX_IRQHandler(void) interrupt 17
 986                     ; 553 #endif /* _COSMIC_ */
 986                     ; 554 {
 987                     	switch	.text
 988  01cd               f_UART1_TX_IRQHandler:
 992                     ; 558 }
 995  01cd 80            	iret
1023                     ; 568 @far @interrupt void UART1_RX_IRQHandler(void)
1023                     ; 569 #else /* _RAISONANCE_ */
1023                     ; 570 void UART1_RX_IRQHandler(void) interrupt 18
1023                     ; 571 #endif /* _COSMIC_ */
1023                     ; 572 {
1024                     	switch	.text
1025  01ce               f_UART1_RX_IRQHandler:
1027  01ce 3b0002        	push	c_x+2
1028  01d1 be00          	ldw	x,c_x
1029  01d3 89            	pushw	x
1030  01d4 3b0002        	push	c_y+2
1031  01d7 be00          	ldw	x,c_y
1032  01d9 89            	pushw	x
1035                     ; 577     if(!U1RxFullFlag){
1037  01da 725d0000      	tnz	_U1RxFullFlag
1038  01de 2639          	jrne	L333
1039                     ; 578 		U1RxBuf[U1RxIndex] = UART1_ReceiveData8();
1041  01e0 c60000        	ld	a,_U1RxIndex
1042  01e3 5f            	clrw	x
1043  01e4 97            	ld	xl,a
1044  01e5 89            	pushw	x
1045  01e6 cd0000        	call	_UART1_ReceiveData8
1047  01e9 85            	popw	x
1048  01ea d70000        	ld	(_U1RxBuf,x),a
1049                     ; 579 			if(0x0A == U1RxBuf[U1RxIndex] ){		
1051  01ed c60000        	ld	a,_U1RxIndex
1052  01f0 5f            	clrw	x
1053  01f1 97            	ld	xl,a
1054  01f2 d60000        	ld	a,(_U1RxBuf,x)
1055  01f5 a10a          	cp	a,#10
1056  01f7 2611          	jrne	L533
1057                     ; 580 				if(0x0D == U1RxBuf[U1RxIndex-1] ){
1059  01f9 c60000        	ld	a,_U1RxIndex
1060  01fc 5f            	clrw	x
1061  01fd 97            	ld	xl,a
1062  01fe 5a            	decw	x
1063  01ff d60000        	ld	a,(_U1RxBuf,x)
1064  0202 a10d          	cp	a,#13
1065  0204 2604          	jrne	L533
1066                     ; 581 					U1RxCmdFlag ++;		//收到0x0D 0x0A认为是一条完整的命令		
1068  0206 725c0000      	inc	_U1RxCmdFlag
1069  020a               L533:
1070                     ; 584 			U1RxIndex++;
1072  020a 725c0000      	inc	_U1RxIndex
1073                     ; 585 			if(U1RxIndex >= U1PARSEBUFLEN){
1075  020e c60000        	ld	a,_U1RxIndex
1076  0211 a132          	cp	a,#50
1077  0213 2504          	jrult	L333
1078                     ; 586 				U1RxFullFlag = 1;	//接收缓冲区满，未来得及处理数据
1080  0215 35010000      	mov	_U1RxFullFlag,#1
1081  0219               L333:
1082                     ; 591 }
1085  0219 85            	popw	x
1086  021a bf00          	ldw	c_y,x
1087  021c 320002        	pop	c_y+2
1088  021f 85            	popw	x
1089  0220 bf00          	ldw	c_x,x
1090  0222 320002        	pop	c_x+2
1091  0225 80            	iret
1113                     ; 602 @far @interrupt void I2C_IRQHandler(void)
1113                     ; 603 #else /* _RAISONANCE_ */
1113                     ; 604 void I2C_IRQHandler(void) interrupt 19
1113                     ; 605 #endif /* _COSMIC_ */
1113                     ; 606 {
1114                     	switch	.text
1115  0226               f_I2C_IRQHandler:
1119                     ; 610 }
1122  0226 80            	iret
1145                     ; 659 @far @interrupt void UART3_TX_IRQHandler(void)
1145                     ; 660 #else /* _RAISONANCE_ */
1145                     ; 661 void UART3_TX_IRQHandler(void) interrupt 20
1145                     ; 662 #endif /* _COSMIC_ */
1145                     ; 663 {
1146                     	switch	.text
1147  0227               f_UART3_TX_IRQHandler:
1151                     ; 667   }
1154  0227 80            	iret
1177                     ; 677 @far @interrupt void UART3_RX_IRQHandler(void)
1177                     ; 678 #else /* _RAISONANCE_ */
1177                     ; 679 void UART3_RX_IRQHandler(void) interrupt 21
1177                     ; 680 #endif /* _COSMIC_ */
1177                     ; 681 {
1178                     	switch	.text
1179  0228               f_UART3_RX_IRQHandler:
1183                     ; 685   }
1186  0228 80            	iret
1208                     ; 697 @far @interrupt void ADC2_IRQHandler(void)
1208                     ; 698 #else /* _RAISONANCE_ */
1208                     ; 699 void ADC2_IRQHandler(void) interrupt 22
1208                     ; 700 #endif /* _COSMIC_ */
1208                     ; 701 {
1209                     	switch	.text
1210  0229               f_ADC2_IRQHandler:
1214                     ; 706     return;
1217  0229 80            	iret
1240                     ; 759 @far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
1240                     ; 760 #else /* _RAISONANCE_ */
1240                     ; 761 void TIM4_UPD_OVF_IRQHandler(void) interrupt 23
1240                     ; 762 #endif /* _COSMIC_ */
1240                     ; 763 {
1241                     	switch	.text
1242  022a               f_TIM4_UPD_OVF_IRQHandler:
1246                     ; 767 }
1249  022a 80            	iret
1272                     ; 778 @far @interrupt void EEPROM_EEC_IRQHandler(void)
1272                     ; 779 #else /* _RAISONANCE_ */
1272                     ; 780 void EEPROM_EEC_IRQHandler(void) interrupt 24
1272                     ; 781 #endif /* _COSMIC_ */
1272                     ; 782 {
1273                     	switch	.text
1274  022b               f_EEPROM_EEC_IRQHandler:
1278                     ; 786 }
1281  022b 80            	iret
1293                     	xref.b	_ButtonState
1294                     	xref.b	_InNetFlag
1295                     	xref	_WorkSta1
1296                     	xref.b	_GlobalRunTime
1297                     	xref	_SPI1_RxBuf
1298                     	xref	_SPI1_ParseBuf
1299                     	xref	_SPI1index
1300                     	xref	_SPI1FullFlag
1301                     	xref	_SPI1NewFlg
1302                     	xref	_SPI1OkFlag
1303                     	xref	_SPI1_Read_Buf
1304                     	xref	_SPI1_RW_Reg
1305                     	xref	_SPI1_Read
1306                     	xref.b	_SPI1Sta
1307                     	xref	_U1RxBuf
1308                     	xref	_U1RxIndex
1309                     	xref	_U1RxFullFlag
1310                     	xref	_U1RxCmdFlag
1311                     	xdef	f_EEPROM_EEC_IRQHandler
1312                     	xdef	f_TIM4_UPD_OVF_IRQHandler
1313                     	xdef	f_ADC2_IRQHandler
1314                     	xdef	f_UART3_TX_IRQHandler
1315                     	xdef	f_UART3_RX_IRQHandler
1316                     	xdef	f_I2C_IRQHandler
1317                     	xdef	f_UART1_RX_IRQHandler
1318                     	xdef	f_UART1_TX_IRQHandler
1319                     	xdef	f_TIM3_CAP_COM_IRQHandler
1320                     	xdef	f_TIM3_UPD_OVF_BRK_IRQHandler
1321                     	xdef	f_TIM2_CAP_COM_IRQHandler
1322                     	xdef	f_TIM2_UPD_OVF_BRK_IRQHandler
1323                     	xdef	f_TIM1_UPD_OVF_TRG_BRK_IRQHandler
1324                     	xdef	f_TIM1_CAP_COM_IRQHandler
1325                     	xdef	f_SPI_IRQHandler
1326                     	xdef	f_CAN_TX_IRQHandler
1327                     	xdef	f_CAN_RX_IRQHandler
1328                     	xdef	f_EXTI_PORTE_IRQHandler
1329                     	xdef	f_EXTI_PORTD_IRQHandler
1330                     	xdef	f_EXTI_PORTC_IRQHandler
1331                     	xdef	f_EXTI_PORTB_IRQHandler
1332                     	xdef	f_EXTI_PORTA_IRQHandler
1333                     	xdef	f_CLK_IRQHandler
1334                     	xdef	f_AWU_IRQHandler
1335                     	xdef	f_TLI_IRQHandler
1336                     	xdef	f_TRAP_IRQHandler
1337                     	xref	_UART1_ReceiveData8
1338                     	xref	_TIM3_ClearITPendingBit
1339                     	xref	_TIM3_GetITStatus
1340                     	xref	_TIM3_ClearFlag
1341                     	xref	_TIM2_ClearITPendingBit
1342                     	xref	_TIM2_GetITStatus
1343                     	xref	_TIM2_ClearFlag
1344                     	xref	_GPIO_ReadInputPin
1345                     	xref	_GPIO_WriteLow
1346                     	xref	_GPIO_WriteHigh
1347                     	xref.b	c_x
1348                     	xref.b	c_y
1367                     	xref	c_lgadc
1368                     	end
