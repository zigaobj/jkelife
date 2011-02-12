   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     	bsct
  16  0000               _NetConnectRxAdr:
  17  0000 a1            	dc.b	161
  18  0001 5c            	dc.b	92
  19  0002 00            	dc.b	0
  20  0003 01            	dc.b	1
  21  0004               _TX_ADDRESS_Si4431:
  22  0004 18            	dc.b	24
  23  0005 42            	dc.b	66
  24  0006 31            	dc.b	49
  25  0007 10            	dc.b	16
  26  0008               _RX_ADDRESS_Si4431:
  27  0008 33            	dc.b	51
  28  0009 43            	dc.b	67
  29  000a 10            	dc.b	16
  30  000b 28            	dc.b	40
  31  000c               _MOD1_TXADR:
  32  000c 21            	dc.b	33
  33  000d a1            	dc.b	161
  34  000e 0a            	dc.b	10
  35  000f 01            	dc.b	1
  36  0010               _MOD1_RXADR:
  37  0010 21            	dc.b	33
  38  0011 a1            	dc.b	161
  39  0012 0a            	dc.b	10
  40  0013 01            	dc.b	1
  41  0014               _MOD2_TXADR:
  42  0014 31            	dc.b	49
  43  0015 a1            	dc.b	161
  44  0016 0b            	dc.b	11
  45  0017 02            	dc.b	2
  46  0018               _MOD2_RXADR:
  47  0018 31            	dc.b	49
  48  0019 a1            	dc.b	161
  49  001a 0b            	dc.b	11
  50  001b 02            	dc.b	2
  51  001c               _MOD3_TXADR:
  52  001c 32            	dc.b	50
  53  001d a1            	dc.b	161
  54  001e 0c            	dc.b	12
  55  001f a4            	dc.b	164
  56  0020               _MOD3_RXADR:
  57  0020 32            	dc.b	50
  58  0021 a1            	dc.b	161
  59  0022 0c            	dc.b	12
  60  0023 a4            	dc.b	164
  61  0024               _MOD4_TXADR:
  62  0024 33            	dc.b	51
  63  0025 a1            	dc.b	161
  64  0026 0d            	dc.b	13
  65  0027 e8            	dc.b	232
  66  0028               _MOD4_RXADR:
  67  0028 33            	dc.b	51
  68  0029 a1            	dc.b	161
  69  002a 0d            	dc.b	13
  70  002b e8            	dc.b	232
  71  002c               _StrTest:
  72  002c 48            	dc.b	72
  73  002d 65            	dc.b	101
  74  002e 6c            	dc.b	108
  75  002f 6c            	dc.b	108
  76  0030 6f            	dc.b	111
  77  0031 20            	dc.b	32
  78  0032 53            	dc.b	83
  79  0033 69            	dc.b	105
  80  0034 34            	dc.b	52
  81  0035 34            	dc.b	52
  82  0036 33            	dc.b	51
  83  0037 31            	dc.b	49
  84  0038 21            	dc.b	33
 665                     	xdef	_RX_ADDRESS_Si4431
 666                     	xdef	_TX_ADDRESS_Si4431
 667                     	switch	.ubsct
 668  0000               _pCmdBuf:
 669  0000 0000          	ds.b	2
 670                     	xdef	_pCmdBuf
 671  0002               _CmdBuf:
 672  0002 000000000000  	ds.b	15
 673                     	xdef	_CmdBuf
 674  0011               _Cmd_Body:
 675  0011 000000000000  	ds.b	160
 676                     	xdef	_Cmd_Body
 677  00b1               _U2RxBuf:
 678  00b1 000000000000  	ds.b	200
 679                     	xdef	_U2RxBuf
 680  0179               _U1RxBuf:
 681  0179 000000000000  	ds.b	200
 682                     	xdef	_U1RxBuf
 683  0241               _U2TxBuf:
 684  0241 000000000000  	ds.b	200
 685                     	xdef	_U2TxBuf
 686  0309               _U1TxBuf:
 687  0309 000000000000  	ds.b	200
 688                     	xdef	_U1TxBuf
 689  03d1               _U2ParseBuf:
 690  03d1 000000000000  	ds.b	200
 691                     	xdef	_U2ParseBuf
 692  0499               _U1ParseBuf:
 693  0499 000000000000  	ds.b	200
 694                     	xdef	_U1ParseBuf
 695  0561               _U2RxPindex:
 696  0561 00            	ds.b	1
 697                     	xdef	_U2RxPindex
 698  0562               _U2RxIndex:
 699  0562 00            	ds.b	1
 700                     	xdef	_U2RxIndex
 701  0563               _U1RxPindex:
 702  0563 00            	ds.b	1
 703                     	xdef	_U1RxPindex
 704  0564               _U1RxIndex:
 705  0564 00            	ds.b	1
 706                     	xdef	_U1RxIndex
 707  0565               _U2RxFullFlag:
 708  0565 00            	ds.b	1
 709                     	xdef	_U2RxFullFlag
 710  0566               _U1RxFullFlag:
 711  0566 00            	ds.b	1
 712                     	xdef	_U1RxFullFlag
 713  0567               _U2RxCmdFlag:
 714  0567 00            	ds.b	1
 715                     	xdef	_U2RxCmdFlag
 716  0568               _U1RxCmdFlag:
 717  0568 00            	ds.b	1
 718                     	xdef	_U1RxCmdFlag
 719                     	xdef	_StrTest
 720                     	xdef	_MOD4_RXADR
 721                     	xdef	_MOD4_TXADR
 722                     	xdef	_MOD3_RXADR
 723                     	xdef	_MOD3_TXADR
 724                     	xdef	_MOD2_RXADR
 725                     	xdef	_MOD2_TXADR
 726                     	xdef	_MOD1_RXADR
 727                     	xdef	_MOD1_TXADR
 728                     	xdef	_NetConnectRxAdr
 729  0569               _SPI1RxCnt:
 730  0569 0000          	ds.b	2
 731                     	xdef	_SPI1RxCnt
 732  056b               _SPI2RxCnt:
 733  056b 0000          	ds.b	2
 734                     	xdef	_SPI2RxCnt
 735  056d               _RXItSta2:
 736  056d 00            	ds.b	1
 737                     	xdef	_RXItSta2
 738  056e               _RXItSta1:
 739  056e 00            	ds.b	1
 740                     	xdef	_RXItSta1
 741  056f               _TXItSta2:
 742  056f 00            	ds.b	1
 743                     	xdef	_TXItSta2
 744  0570               _TXItSta1:
 745  0570 00            	ds.b	1
 746                     	xdef	_TXItSta1
 747  0571               _SPI2Sta2:
 748  0571 00            	ds.b	1
 749                     	xdef	_SPI2Sta2
 750  0572               _SPI2Sta1:
 751  0572 00            	ds.b	1
 752                     	xdef	_SPI2Sta1
 753  0573               _SPI2FIFOSta:
 754  0573 00            	ds.b	1
 755                     	xdef	_SPI2FIFOSta
 756  0574               _SPI1Sta2:
 757  0574 00            	ds.b	1
 758                     	xdef	_SPI1Sta2
 759  0575               _SPI1Sta1:
 760  0575 00            	ds.b	1
 761                     	xdef	_SPI1Sta1
 762  0576               _SPI1FIFOSta:
 763  0576 00            	ds.b	1
 764                     	xdef	_SPI1FIFOSta
 765  0577               _sta:
 766  0577 00            	ds.b	1
 767                     	xdef	_sta
 787                     	end
