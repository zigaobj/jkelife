#ifndef  _SI4431API_H_
#define  _SI4431API_H_


#define BOARDCLK   		(24500000/16)
#define BAUDRATE  		9600
#define SPI_CLK  		(BOARDCLK/4)
// SPI(Si4431) commands
#define	REG_READ		0x00
#define	REG_WRITE		0x80

#define TXHEADERLEN	 32
#define TXHEADERRATE (TXHEADERLEN/8)
//sbit RF_NSEL_PIN = P0^7;

//sbit SCLK = P3^4;
//sbit SDA  = P3^3;
//sbit LCDRS = P2^0;
//sbit LCDE  = P2^1;

void SYSCLK_Init (void);
void PORT_Init (void);
void delay(u16 n);
////////////////////////lcd.h///////////////////////                                
extern u8 dis_buf[32];  

extern unsigned char rxdata[20];	//16,接收数据存储器组
extern unsigned char txdata[20];
#define RECKEY    1
#define UPKEY    2
#define DOWNKEY  4
#define ENTKEY   8


# define LSB 1
# define MSB 0


#define RF22_PWRSTATE_READY		1
#define RF22_PWRSTATE_TX		0x09
#define RF22_PWRSTATE_RX		5
#define RF22_PWRSTATE_POWERDOWN		0

#define RF22_PACKET_SENT_INTERRUPT	4
#define RF22_Tx_almost_empty_interrupt	0x20
#define RF22_Rx_almost_full_interrupt   0x10
#define RF22_Rx_packet_received_interrupt   0x02


typedef union _uni_u16_
{
   u16 part_u16;
   s16 part_s16;
   u8 part_u8[2];
   s8 part_S8[2];
} uni_u16;

typedef union _uni_u32_
{
   u32 part_u32;
   s32 part_S32;
   uni_u16 part_uni_u16[2];
   u16 part_u16[2];
   s16 part_s16[2];
   u8 part_u8[4];
   s8 part_s8[4];
} uni_u32;
                                                            
//-----------------------------------------------------------------------------
// 函数定义
//-----------------------------------------------------------------------------

//uni_u16 SpiRfReadWriteAddressData(u16 address, u16 d);

//void send();
void si4432_init(void);
void recv_data(void);
void recv(void);//接收节点地址函数
void send_init(void);
void recv_init(void);
void send_data(unsigned char *seddat,unsigned char leng);

void SpiRfWriteWord(uni_u16 spi_in);
u8 SPI1_RW(u8 Data);
u8 SPI1_RWReg(u8 Reg, u8 Data);
u8 SPI1_Read(u8 Reg);
u8 SPI2_RW(u8 Data);
u8 SPI2_RWReg(u8 Reg, u8 Data);
u8 SPI2_Read(u8 Reg);


uni_u16 SpiRfReadWriteWord(uni_u16 spi_in);
//u16 SpiRfReadRegister(u16 address);
extern void LCD_Init(void);
extern void write_byte(unsigned char wdata);
extern void lcdaddr(u8 DDRAM);
extern void lcdchar (u8 ch);
extern void writedata(u8 sdata);
extern void clrscreen(void);
extern void lcddisplay(void);
extern void display(u8 *pstr);
extern void newdisplay(void);
///////////////////////keyscan.h/////////////////////////////////



extern u8   keyval;
extern u8   keynew;	//判断键值
extern u8   keylast;
extern u8	KEYISNEW;

extern u8 turncount;
extern u8 txcount;
extern u8 rxcount;
extern u8 count0;
extern u8 count1;
extern u8 count2;

extern u8 num0;
extern u8 num1;
extern u8 num2;


extern void key_init(void);
extern void key_scan(void);
extern void keyproc(void);


///////////////////////display.c/////////////////////////////////
enum status {start,phy,trans,channels,powers,baudrates,chs,pows,bauds};//声明
extern enum status workmode;//外部声明，而该变量在键盘文件中定义

extern void new_dis_buf(void);
typedef struct 
	{
	  u8  dischar[16];
	  u8  datalen;
	}testdisplay;

extern testdisplay testdis[28];

///////////////////////si4421SET/////////////////////////////////////////
typedef union STYPE
{
     u16 U16;
     int S16;
     u8 U8[2];
     char S8[2];
} STYPE;

/*
#define		DeviceType 								 0x00
#define		DeviceVersion								 0x01
#define  DeviceStatus 								 0x02
#define  InterruptStatus1 							 0x03
#define  InterruptStatus2 							 0x04
#define  InterruptEnable1 							 0x05          
#define  InterruptEnable2 							 0x06         
#define  OperatingFunctionControl1 				 0x07
#define  OperatingFunctionControl2 				 0x08	 
#define  CrystalOscillatorLoadCapacitance 			 0x09
#define  MicrocontrollerOutputClock 				 0x0A
#define  GPIO0Configuration 						 0x0B
#define  GPIO1Configuration 						 0x0C         
#define  GPIO2Configuration						     0x0D
#define  IOPortConfiguration						 0x0E
#define  ADCConfiguration							 0x0F
#define  ADCSensorAmplifierOffset					 0x10
#define  ADCValue									 					0x11
#define  TemperatureSensorControl					 0x12
#define  TemperatureValueOffset					 0x13	 
#define  WakeUpTimerPeriod1 						 0x14          
#define  WakeUpTimerPeriod2 						 0x15         
#define  WakeUpTimerPeriod3 						 0x16         
#define  WakeUpTimerValue1							 0x17
#define  WakeUpTimerValue2							 0x18
#define  LowDutyCycleModeDuration 					 0x19       
#define  LowBatteryDetectorThreshold  				 0x1A
#define  BatteryVoltageLevel 						 0x1B                          
#define  IFFilterBandwidth  						 0x1C                           
#define  AFCLoopGearshiftOverride					 0x1D
#define  AFCTimingControl 							 0x1E                              
#define  ClockRecoveryGearshiftOverride 			 0x1F              
#define  ClockRecoveryOversamplingRatio 			 0x20              
#define  ClockRecoveryOffset2 						 0x21                       
#define  ClockRecoveryOffset1 						 0x22                       
#define  ClockRecoveryOffset0 						 0x23                     
#define  ClockRecoveryTimingLoopGain1 				 0x24              
#define  ClockRecoveryTimingLoopGain0 				 0x25             
#define  ReceivedSignalStrengthIndicator 			 0x26          
#define  RSSIThresholdForClearChannelIndicator 	     0x27   
#define  AntennaDiversityRegister1					 0x28
#define  AntennaDiversityRegister2					 0x29
#define  DataAccessControl 						     0x30                          
#define  EZmacStatus 								 		0x31                                  
#define  HeaderControl1 							 0x32                               
#define  HeaderControl2 							 0x33                              
#define  PreambleLength 							 0x34                               
#define  PreambleDetectionControl 					 0x35                    
#define  SyncWord3 								 0x36                                   
#define  SyncWord2 								 0x37                                   
#define  SyncWord1 								 0x38                               
#define  SyncWord0 								 0x39                                
#define  TransmitHeader3							 0x3A                       
#define  TransmitHeader2 							 0x3B                             
#define  TransmitHeader1 							 0x3C                              
#define  TransmitHeader0 							 0x3D                             
#define  TransmitPacketLength 						 0x3E                         
#define  CheckHeader3 								 0x3F                                
#define  CheckHeader2 								 0x40                              
#define  CheckHeader1 								 0x41                             
#define  CheckHeader0 								 0x42                            
#define  HeaderEnable3 							 0x43                               
#define  HeaderEnable2 							 0x44                                 
#define  HeaderEnable1 							 0x45                                
#define  HeaderEnable0 							 0x46                              
#define  ReceivedHeader3 							 0x47                          
#define  ReceivedHeader2 							 0x48                         
#define  ReceivedHeader1 							 0x49                           
#define  ReceivedHeader0 							 0x4A                             
#define  ReceivedPacketLength						 0x4B
#define  AnalogTestBus 							 0x50                              
#define  DigitalTestBus 							 0x51                          
#define  TXRampControl 							 0x52                             
#define  PLLTuneTime 								 0x53                            
#define  CalibrationControl 						 0x55                     
#define  ModemTest 								 0x56                               
#define  ChargepumpTest 							 0x57                    
#define  ChargepumpCurrentTrimming_Override 		 0x58         
#define  DividerCurrentTrimming				 	 0x59    
#define  VCOCurrentTrimming 						 0x5A                           
#define  VCOCalibration_Override 					 0x5B                    
#define  SynthesizerTest 							 0x5C                              
#define  BlockEnableOverride1 						 0x5D                        
#define  BlockEnableOverride2 						 0x5E                      
#define  BlockEnableOverride3 						 0x5F                       
#define  ChannelFilterCoefficientAddress 			 0x60             
#define  ChannelFilterCoefficientValue 			 0x61            
#define  CrystalOscillator_ControlTest 			 0x62               
#define  RCOscillatorCoarseCalibration_Override 	 0x63    
#define  RCOscillatorFineCalibration_Override 		 0x64      
#define  LDOControlOverride 						 0x65                          
#define  DeltasigmaADCTuning1			 			 0x67
#define  DeltasigmaADCTuning2			 			 0x68
#define  AGCOverride1					 			 0x69
#define  AGCOverride2 								 0x6A
#define  GFSKFIRFilterCoefficientAddress 			 0x6B            
#define  GFSKFIRFilterCoefficientValue 			     0x6C              
#define  TXPower 									 0x6D                                   
#define  TXDataRate1 								 0x6E                            
#define  TXDataRate0 								 0x6F                              
#define  ModulationModeControl1 					 0x70                   
#define  ModulationModeControl2 					 0x71                   
#define  FrequencyDeviation 						 0x72                            
#define  FrequencyOffset 							 0x73                            
#define  FrequencyChannelControl					 0x74
#define  FrequencyBandSelect 						 0x75                        
#define  NominalCarrierFrequency1	 				 0x76                    
#define  NominalCarrierFrequency0 					 0x77                    
#define  FrequencyHoppingChannelSelect 			    0x79               
#define  FrequencyHoppingStepSize 					 0x7A                     
#define  TXFIFOControl1 							 0x7C                        
#define  TXFIFOControl2 							 0x7D    
#define  RXFIFOControl 							 0x7E                               
#define  FIFOAccess								 0x7F
*/



//register name and addresses for Si4432 revV2
typedef enum _RF_REG_MAP					
{
  DeviceType 						        = 0x00,
  DeviceVersion						        = 0x01,
  DeviceStatus 							= 0x02,
  InterruptStatus1 						= 0x03,
  InterruptStatus2 						= 0x04,
  InterruptEnable1 						= 0x05,
  InterruptEnable2 						= 0x06,
  OperatingFunctionControl1 				        = 0x07,
  OperatingFunctionControl2 				        = 0x08,
  CrystalOscillatorLoadCapacitance 			        = 0x09,
  MicrocontrollerOutputClock 				        = 0x0A,
  GPIO0Configuration 						= 0x0B,
  GPIO1Configuration 						= 0x0C,      
  GPIO2Configuration						= 0x0D,
  IOPortConfiguration						= 0x0E,
  ADCConfiguration						= 0x0F,
  ADCSensorAmplifierOffset					= 0x10,
  ADCValue							= 0x11,
  TemperatureSensorControl					= 0x12,
  TemperatureValueOffset					= 0x13,
  WakeUpTimerPeriod1 						= 0x14,
  WakeUpTimerPeriod2 						= 0x15,
  WakeUpTimerPeriod3 						= 0x16,
  WakeUpTimerValue1						= 0x17,
  WakeUpTimerValue2						= 0x18,
  LowDutyCycleModeDuration 					= 0x19,
  LowBatteryDetectorThreshold  				        = 0x1A,
  BatteryVoltageLevel 						= 0x1B,
  IFFilterBandwidth  						= 0x1C,
  AFCLoopGearshiftOverride					= 0x1D,
  AFCTimingControl 						= 0x1E,
  ClockRecoveryGearshiftOverride 			        = 0x1F,
  ClockRecoveryOversamplingRatio 			        = 0x20,
  ClockRecoveryOffset2 						= 0x21,
  ClockRecoveryOffset1 						= 0x22,
  ClockRecoveryOffset0 						= 0x23,
  ClockRecoveryTimingLoopGain1 				        = 0x24,
  ClockRecoveryTimingLoopGain0 				        = 0x25,
  ReceivedSignalStrengthIndicator 			        = 0x26,
  RSSIThresholdForClearChannelIndicator 	                = 0x27,
  AntennaDiversityRegister1					= 0x28,
  AntennaDiversityRegister2					= 0x29,
  DataAccessControl 						= 0x30,
  EZmacStatus 							= 0x31,
  HeaderControl1 						= 0x32,
  HeaderControl2 						= 0x33,
  PreambleLength 						= 0x34,
  PreambleDetectionControl 					= 0x35,
  SyncWord3 							= 0x36,
  SyncWord2 							= 0x37,
  SyncWord1 							= 0x38,
  SyncWord0 							= 0x39,
  TransmitHeader3						= 0x3A,
  TransmitHeader2 						= 0x3B,
  TransmitHeader1 						= 0x3C,
  TransmitHeader0 						= 0x3D,
  TransmitPacketLength 						= 0x3E,                         
  CheckHeader3 							= 0x3F,                                
  CheckHeader2 							= 0x40,                              
  CheckHeader1 							= 0x41,                             
  CheckHeader0 							= 0x42,                           
  HeaderEnable3 						= 0x43,                               
  HeaderEnable2 						= 0x44,                                 
  HeaderEnable1 						= 0x45,                                
  HeaderEnable0 						= 0x46,                              
  ReceivedHeader3 						= 0x47,                          
  ReceivedHeader2 						= 0x48,                         
  ReceivedHeader1 						= 0x49,                          
  ReceivedHeader0 						= 0x4A,                             
  ReceivedPacketLength						= 0x4B,
  AnalogTestBus 						= 0x50,                              
  DigitalTestBus 						= 0x51,                          
  TXRampControl 						= 0x52,                            
  PLLTuneTime 							= 0x53,                            
  CalibrationControl 						= 0x55,                     
  ModemTest 							= 0x56,                              
  ChargepumpTest 						= 0x57,                    
  ChargepumpCurrentTrimming_Override 		                = 0x58,         
  DividerCurrentTrimming				 	= 0x59,    
  VCOCurrentTrimming 						= 0x5A,                        
  VCOCalibration_Override 					= 0x5B,                    
  SynthesizerTest 						= 0x5C,                
  BlockEnableOverride1 					= 0x5D,               
  BlockEnableOverride2 					= 0x5E,              
  BlockEnableOverride3 					= 0x5F,              
  ChannelFilterCoefficientAddress 			        = 0x60,             
  ChannelFilterCoefficientValue 			        = 0x61,            
  CrystalOscillator_ControlTest 			        = 0x62,               
  RCOscillatorCoarseCalibration_Override 	                = 0x63,    
  RCOscillatorFineCalibration_Override 		                = 0x64,      
  LDOControlOverride 						= 0x65,                       
  DeltasigmaADCTuning1			 		= 0x67,
  DeltasigmaADCTuning2			 			= 0x68,
  AGCOverride1					 		= 0x69,
 
  AGCOverride2 							= 0x6A,

  GFSKFIRFilterCoefficientAddress 			        = 0x6B,            
  
  GFSKFIRFilterCoefficientValue 			        = 0x6C,              
 
  TXPower 							= 0x6D,              
  
  TXDataRate1 						= 0x6E,                   
  
  TXDataRate0 						= 0x6F,                    
  
  ModulationModeControl1 					= 0x70,                   
  
  ModulationModeControl2 					= 0x71,                   
  
  FrequencyDeviation 					= 0x72,             
  
  FrequencyOffset 						= 0x73,            
  
  FrequencyChannelControl					= 0x74,
  FrequencyBandSelect 						= 0x75,                   
  
  NominalCarrierFrequency1	 				= 0x76,                  
  
  NominalCarrierFrequency0 					= 0x77,                  
  
  FrequencyHoppingChannelSelect 			        = 0x79,               
 
  FrequencyHoppingStepSize 					= 0x7A,            
  
  TXFIFOControl1 						= 0x7C,          
  
  TXFIFOControl2 						= 0x7D,    
 
  RXFIFOControl 						= 0x7E,           
  
  FIFOAccess							= 0x7F, 
} RF_REG_MAP;

//register name and addresses for Si4432 revV2
typedef enum _SI4431_ITSTATUS1_MAP					
{
	icrcerror		=	0x01,
	ipkvalid 		=	0x02,
	ipksent 		=	0x04,
	iext 				=	0x08,
	irxffafull 	=	0x10,
	itxffaem 		=	0x20,
	itxffafull 	=	0x40,
	ifferr 			=	0x80,
			
} SI4431_ITSTATUS1_MAP;

typedef enum _SI4431_ITSTATUS2_MAP					
{	       
	ipor				=	0x01,
	ichiprdy 		=	0x02,
	ilbd		 		=	0x04,
	iwut 				=	0x08,
	irssi			 	=	0x10,
	ipreainval	=	0x20,
	ipreaval	 	=	0x40,
	iswdet 			=	0x80,		
} SI4431_ITSTATUS2_MAP;



u8 SPI1_RW(u8 Data);
u8 SPI1_RWReg(u8 Reg, u8 Data);
u8 SPI1_Read(u8 Reg);
u16 SPI1_RWWord(u16 Reg);
u8 SPI2_RW(u8 Data);
u8 SPI2_RWReg(u8 Reg, u8 Data);
u8 SPI2_Read(u8 Reg);
u16 SPI2_RWWord(u16 Reg);

void Si4431TX_Init(void);
void Si4431TX_IdleMod(void);
void Si4431TX_TransmitMod(u8 * pTxHeader);
void Si4431TX_ReceiveMod(u8 * pRxCheckHeader);
u8 Si4431TX_BusyCheck(void);
void Si4431TX_TxPacket(unsigned char * packet, unsigned char length);
void Si4431RX_Init(void);
void Si4431RX_IdleMod(void);
void Si4431RX_TransmitMod(u8 * pTxHeader);
void Si4431RX_ReceiveMod(u8 * pRxCheckHeader);
u8 Si4431RX_BusyCheck(void);
void Si4431RX_TxPacket(unsigned char * packet, unsigned char length);




#endif

