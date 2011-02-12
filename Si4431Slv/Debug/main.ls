   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     	bsct
  16  0000               _ButtonState:
  17  0000 00            	dc.b	0
  53                     ; 54 void main(void)
  53                     ; 55 {
  55                     	switch	.text
  56  0000               _main:
  60                     ; 59 	SysInit_Config();	//系统配置
  62  0000 cd0000        	call	_SysInit_Config
  64                     ; 61 	Si4431TX_Init();
  66  0003 cd0000        	call	_Si4431TX_Init
  68                     ; 69   enableInterrupts();		//开全局中断
  71  0006 9a            rim
  73                     ; 71 	WorkSta1 = STA_NETCONNECT;	//上电组网
  76  0007 35010000      	mov	_WorkSta1,#1
  77                     ; 76 	GPIO_WriteHigh(LEDS_PORT, LED0_PIN);
  79  000b 4b01          	push	#1
  80  000d ae5005        	ldw	x,#20485
  81  0010 cd0000        	call	_GPIO_WriteHigh
  83  0013 84            	pop	a
  84  0014               L12:
  85                     ; 80 		SysRun();
  87  0014 cd0000        	call	_SysRun
  89                     ; 81 		SPI1Rx_Parse();
  91  0017 cd0000        	call	_SPI1Rx_Parse
  94  001a 20f8          	jra	L12
 118                     	xdef	_main
 119                     	xdef	_ButtonState
 120                     	xref	_WorkSta1
 121                     	xref	_SPI1Rx_Parse
 122                     	xref	_SysRun
 123                     	xref	_Si4431TX_Init
 124                     	xref	_SysInit_Config
 125                     	xref	_GPIO_WriteHigh
 144                     	end
