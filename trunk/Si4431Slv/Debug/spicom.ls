   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  91                     ; 48 void SPI1Rx_Parse(void)
  91                     ; 49 { //u8 i,j,k;
  93                     	switch	.text
  94  0000               _SPI1Rx_Parse:
  96  0000 5204          	subw	sp,#4
  97       00000004      OFST:	set	4
 100                     ; 68 	if(0 != SPI1OkFlag ){								
 102  0002 725d0186      	tnz	_SPI1OkFlag
 103  0006 2603          	jrne	L6
 104  0008 cc00ca        	jp	L35
 105  000b               L6:
 106                     ; 69 		for(LoopStart = SPI1Pindex; LoopStart < SPI1index; LoopStart++){
 108  000b c60181        	ld	a,_SPI1Pindex
 109  000e 6b03          	ld	(OFST-1,sp),a
 111  0010 acc000c0      	jpf	L16
 112  0014               L55:
 113                     ; 70 			if(SPI1_ParseBuf[LoopStart]=='#'){//找到命令头了	
 115  0014 7b03          	ld	a,(OFST-1,sp)
 116  0016 5f            	clrw	x
 117  0017 97            	ld	xl,a
 118  0018 d600e1        	ld	a,(_SPI1_ParseBuf,x)
 119  001b a123          	cp	a,#35
 120  001d 2703          	jreq	L01
 121  001f cc00be        	jp	L56
 122  0022               L01:
 123                     ; 71 				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//找结尾
 125  0022 7b03          	ld	a,(OFST-1,sp)
 126  0024 6b04          	ld	(OFST+0,sp),a
 128  0026 2039          	jra	L37
 129  0028               L76:
 130                     ; 72 					if(SPI1_ParseBuf[LoopEnd]=='\n'){//找到命令头了
 132  0028 7b04          	ld	a,(OFST+0,sp)
 133  002a 5f            	clrw	x
 134  002b 97            	ld	xl,a
 135  002c d600e1        	ld	a,(_SPI1_ParseBuf,x)
 136  002f a10a          	cp	a,#10
 137  0031 262c          	jrne	L77
 138                     ; 73 						SPI1OkFlag--;	//每处理一条命令，接收命令计数器自减
 140  0033 725a0186      	dec	_SPI1OkFlag
 141                     ; 74 						SPI1Pindex = LoopEnd + 1;
 143  0037 7b04          	ld	a,(OFST+0,sp)
 144  0039 4c            	inc	a
 145  003a c70181        	ld	_SPI1Pindex,a
 146                     ; 75 						break;
 147  003d               L57:
 148                     ; 79 				comnum = Hash(SPI1_ParseBuf+LoopStart+1 , RFCMDHASHLEN);	//计算命令Hash头
 150  003d 4b03          	push	#3
 151  003f 7b04          	ld	a,(OFST+0,sp)
 152  0041 5f            	clrw	x
 153  0042 97            	ld	xl,a
 154  0043 1c00e2        	addw	x,#_SPI1_ParseBuf+1
 155  0046 cd0000        	call	_Hash
 157  0049 84            	pop	a
 158  004a 1f01          	ldw	(OFST-3,sp),x
 159                     ; 80 				switch (comnum){	//命令散转
 161  004c 1e01          	ldw	x,(OFST-3,sp)
 163                     ; 117 					default:
 163                     ; 118 					//	Uart1_SendString_End(StrError);		//接收命令有误，无法解析
 163                     ; 119 					break;
 164  004e 1d0144        	subw	x,#324
 165  0051 2723          	jreq	L5
 166  0053 1d0075        	subw	x,#117
 167  0056 2712          	jreq	L3
 168  0058 1d015c        	subw	x,#348
 169  005b 272c          	jreq	L7
 170  005d 2034          	jra	L301
 171  005f               L77:
 172                     ; 71 				for(LoopEnd = LoopStart; LoopEnd < SPI1index; LoopEnd++){	//找结尾
 174  005f 0c04          	inc	(OFST+0,sp)
 175  0061               L37:
 178  0061 7b04          	ld	a,(OFST+0,sp)
 179  0063 c10182        	cp	a,_SPI1index
 180  0066 25c0          	jrult	L76
 181  0068 20d3          	jra	L57
 182  006a               L3:
 183                     ; 81 					case (RFCMD_NTA):	//NTA握手命令，接收从模块地址  "#NTA,00000\r\n";
 183                     ; 82 				
 183                     ; 83 						NetApply(SPI1_ParseBuf+LoopStart+5 );
 185  006a 7b03          	ld	a,(OFST-1,sp)
 186  006c 5f            	clrw	x
 187  006d 97            	ld	xl,a
 188  006e 1c00e6        	addw	x,#_SPI1_ParseBuf+5
 189  0071 cd0000        	call	_NetApply
 191                     ; 99 					break;
 193  0074 201d          	jra	L301
 194  0076               L5:
 195                     ; 101 					case (RFCMD_SYN):	//收到同步命令	"#SYN,00\r\n";	//16位TIM3->CNT高位在前
 195                     ; 102 						if(STA_SYNCHRONIZE == WorkSta1){	//只有当系统在同步阶段才执行							
 197  0076 c60000        	ld	a,_WorkSta1
 198  0079 a102          	cp	a,#2
 199  007b 2616          	jrne	L301
 200                     ; 103 							Synchronize(SPI1_ParseBuf + LoopStart);
 202  007d 7b03          	ld	a,(OFST-1,sp)
 203  007f 5f            	clrw	x
 204  0080 97            	ld	xl,a
 205  0081 1c00e1        	addw	x,#_SPI1_ParseBuf
 206  0084 cd0000        	call	_Synchronize
 208  0087 200a          	jra	L301
 209  0089               L7:
 210                     ; 108 					case (RFCMD_TMP):	//温度采集	"#TMP,0,00000\r\n";
 210                     ; 109 						if(STA_DATA == WorkSta1){	//只有当系统在数据接收阶段才执行							
 212  0089 c60000        	ld	a,_WorkSta1
 213  008c a104          	cp	a,#4
 214  008e 2603          	jrne	L301
 215                     ; 110 							SPI1_CMDTMP();
 217  0090 cd0000        	call	_SPI1_CMDTMP
 219  0093               L11:
 220                     ; 117 					default:
 220                     ; 118 					//	Uart1_SendString_End(StrError);		//接收命令有误，无法解析
 220                     ; 119 					break;
 222  0093               L301:
 223                     ; 124 			if((0 == SPI1OkFlag)||(SPI1index >= SPI1PARSEBUFLEN))
 225  0093 725d0186      	tnz	_SPI1OkFlag
 226  0097 2707          	jreq	L311
 228  0099 c60182        	ld	a,_SPI1index
 229  009c a1a0          	cp	a,#160
 230  009e 2512          	jrult	L111
 231  00a0               L311:
 232                     ; 125 			for (Loopi = 0; Loopi < SPI1PARSEBUFLEN; Loopi++){
 234  00a0 0f04          	clr	(OFST+0,sp)
 235  00a2               L511:
 236                     ; 126 	 			SPI1_ParseBuf[Loopi] = 0;	
 238  00a2 7b04          	ld	a,(OFST+0,sp)
 239  00a4 5f            	clrw	x
 240  00a5 97            	ld	xl,a
 241  00a6 724f00e1      	clr	(_SPI1_ParseBuf,x)
 242                     ; 125 			for (Loopi = 0; Loopi < SPI1PARSEBUFLEN; Loopi++){
 244  00aa 0c04          	inc	(OFST+0,sp)
 247  00ac 7b04          	ld	a,(OFST+0,sp)
 248  00ae a1a0          	cp	a,#160
 249  00b0 25f0          	jrult	L511
 250  00b2               L111:
 251                     ; 128 	  		SPI1index   = 0;
 253  00b2 725f0182      	clr	_SPI1index
 254                     ; 129 			SPI1Pindex = 0;
 256  00b6 725f0181      	clr	_SPI1Pindex
 257                     ; 130 			SPI1FullFlag = 0;
 259  00ba 725f0183      	clr	_SPI1FullFlag
 260  00be               L56:
 261                     ; 69 		for(LoopStart = SPI1Pindex; LoopStart < SPI1index; LoopStart++){
 263  00be 0c03          	inc	(OFST-1,sp)
 264  00c0               L16:
 267  00c0 7b03          	ld	a,(OFST-1,sp)
 268  00c2 c10182        	cp	a,_SPI1index
 269  00c5 2403          	jruge	L21
 270  00c7 cc0014        	jp	L55
 271  00ca               L21:
 272  00ca               L35:
 273                     ; 143 }
 276  00ca 5b04          	addw	sp,#4
 277  00cc 81            	ret
 395                     	switch	.bss
 396  0000               _SPI1_SendBuf:
 397  0000 000000000000  	ds.b	160
 398                     	xdef	_SPI1_SendBuf
 399                     	xref	_Hash
 400                     	xref	_WorkSta1
 401                     	xdef	_SPI1Rx_Parse
 402  00a0               _SPI1_RxBuf:
 403  00a0 000000000000  	ds.b	32
 404                     	xdef	_SPI1_RxBuf
 405  00c0               _SPI1_TxBuf:
 406  00c0 000000000000  	ds.b	32
 407                     	xdef	_SPI1_TxBuf
 408  00e0               _SPI1ByteNum:
 409  00e0 00            	ds.b	1
 410                     	xdef	_SPI1ByteNum
 411  00e1               _SPI1_ParseBuf:
 412  00e1 000000000000  	ds.b	160
 413                     	xdef	_SPI1_ParseBuf
 414  0181               _SPI1Pindex:
 415  0181 00            	ds.b	1
 416                     	xdef	_SPI1Pindex
 417  0182               _SPI1index:
 418  0182 00            	ds.b	1
 419                     	xdef	_SPI1index
 420  0183               _SPI1FullFlag:
 421  0183 00            	ds.b	1
 422                     	xdef	_SPI1FullFlag
 423  0184               _SPI1ProtocolFlag:
 424  0184 00            	ds.b	1
 425                     	xdef	_SPI1ProtocolFlag
 426  0185               _SPI1NewFlg:
 427  0185 00            	ds.b	1
 428                     	xdef	_SPI1NewFlg
 429  0186               _SPI1OkFlag:
 430  0186 00            	ds.b	1
 431                     	xdef	_SPI1OkFlag
 432                     	xref	_SPI1_CMDTMP
 433                     	xref	_Synchronize
 434                     	xref	_NetApply
 454                     	end
