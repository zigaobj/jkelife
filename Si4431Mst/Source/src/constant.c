#include "stm32f10x.h"
#include "Global.h"

u8 const baud[8][12] =	
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
u8 const freq[4][5] =
{
//  fb  , fc_h, fc_l, fhch_h ��fhch_l   
   {0x73, 0x57, 0x80, 0x00,0x3c,},
   {0x73, 0x64, 0x00, 0x00,0x05,},
   {0x73, 0x64, 0x00, 0x00,0x32,},
   {0x73, 0x64, 0x00, 0x00,0x5f,}
};

u8 const power[4] = { 0x00, 0x01, 0x02 ,0x03 };

     