#include  <hw_types.h>
#include  "nrf2401.h"
#include  <hw_memmap.h>
#include  <hw_gpio.h>
#include  <sysctl.h>
#include  <gpio.h>


//  延时
void  delay(unsigned long  ulVal)
{
    while ( --ulVal  !=  0 );
}

void delay_ms(unsigned char data){
    unsigned int i,j,k;
      data=data*2;
      for(i=0;i<data;i++)
        for(j=0;j<4;j++)
          for(k=0;k<500;k++);      
}

//**********************IO口初始化*****************//
void init_io(void)
{	
 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                               //  使能SPI所在的GPIO端口
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);                              //使能LED所在的GPIO端口
    
    IO_Output_PWRDN();                        //CE output
    IO_Clear_PWRDN();                         //CE=0,chip enable	
    IO_Output_CSN();
    IO_Set_CSN();                          //CSN=1;	 Spi disable		
    IO_Output_SCK();
    IO_Clear_SCK();                       //SCK=0;	Spi clock line init high	
    IO_Output_MOSI();                     //P3DIR |= MOSI
    IO_Input_MISO() ;                     //P3DIR &=~ MISO
    LEDS_Output();
    LEDR_Output();
    LEDS_ON;
    LEDR_ON;
}
/**************************************************
Function: SpiReadWrite();
Description:
  Writes one byte to nRF24L01, and return the byte read
  from nRF24L01 during write, according to SPI protocol
**************************************************/
unsigned char SpiReadWrite(unsigned char byte)
{
    unsigned char bit_ctr;
    for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // output 8-bit
    {
            if(0X80 == (byte & 0x80))
              IO_Set_MOSI();
            else
              {
              IO_Clear_MOSI();
              }
            byte = (byte << 1);           // shift next bit into MSB..
            IO_Set_SCK(); 
            //DDRS=0X00;                // Set SCK high..
            if((0X01 & GPIOPinRead(GPIO_PORTA_BASE , 0XFF))==0X01)
              byte |=1;
            else
              byte&=~1;
           // DDRS=0XFF;
            IO_Clear_SCK();              // ..then set SCK low again
    }
  return(byte);           		     // return read byte
}

/**************************************************
Function: SpiWriteAddressData();
Description:
  Writes value 'value' to register 'reg'
**************************************************/
unsigned char SpiWriteAddressData(unsigned char reg, unsigned char value)
{
    unsigned char status;
    IO_Clear_CSN();                   // CSN low, init SPI transaction
    status = SpiReadWrite(reg);             // select register
    SpiReadWrite(value);                    // ..and write value to it..
    IO_Set_CSN();                     // CSN high again
    return(status);                   // return nRF24L01 status byte
}
/**************************************************
Function: SPI_Read();
Description:
  Read one byte from nRF24L01 register, 'reg'
**************************************************/
unsigned char SpiRfReadRegister(BYTE reg)
{
    BYTE reg_val;
    IO_Clear_CSN();                // CSN low, initialize SPI communication...
    SpiReadWrite(reg);                   // Select register to read from..
    reg_val = SpiReadWrite(0);           // ..then read registervalue
    IO_Set_CSN();                  // CSN high, terminate SPI communication
    return(reg_val);               // return register value
}
/**************************************************
Function: SPI_Read_Buf();
Description:
  Reads 'bytes' #of bytes from register 'reg'
  Typically used to read RX payload, Rx/Tx address
**************************************************/
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,byte_ctr;
    IO_Clear_CSN();             // Set CSN low, init SPI tranaction
    status = SpiReadWrite(reg);       // Select register to write to and read status byte
    for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SpiReadWrite(0);// Perform SpiReadWrite to read byte from nRF24L01
    IO_Set_CSN();              // Set CSN high again
    return(status);            // return nRF24L01 status byte
}
/**************************************************
Function: SPI_Write_Buf();
Description:
  Writes contents of buffer '*pBuf' to nRF24L01
  Typically used to write TX payload, Rx/Tx address
**************************************************/
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,byte_ctr;
    IO_Clear_CSN();                             // Set CSN low, init SPI tranaction
    status = SpiReadWrite(reg);                       // Select register to write to and read status byte
    for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // then write all byte in buffer(*pBuf)
    SpiReadWrite(*pBuf++);
    IO_Set_CSN();                               // Set CSN high again
    return(status);                             // return nRF24L01 status byte
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  unsigned short SpiReadWriteWord(unsigned short spi_in)
  +
  + DESCRIPTION:    sends and read 16 length data through the SPI port
  +
  +	INPUT:			data 
  +
  + RETURN:         received word
  +
  + NOTES:          it controls the nSEL pin
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned short SpiReadWriteWord(unsigned short spi_in)
{
	unsigned short temp16;

	
	IO_Clear_CSN();                             // Set CSN low, init SPI tranaction = 0;						
	temp16 = (unsigned short) (SpiReadWrite( (unsigned char)((spi_in & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (unsigned short) (SpiReadWrite( (unsigned char)(spi_in & 0x00FF) ));
	IO_Set_CSN();                               // Set CSN high again;
	

	return temp16;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void RfInitHw(void)
  +
  + DESCRIPTION:    initializes the used I/O pins, SPI and timer peripherals, 
  +					IT routines needed for the RF stack
  +
  + RETURN:         None
  +
  + NOTES:          1.) has to be called in the power-on routine
  +					2.) it doesn't initialize the RF chip registers
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void RfInitHw(void)
{
 
        IO_Set_CSN();                    //片选
        IO_Clear_PWRDN();                //使能                   

        SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x80);
 	
  	delay_ms(2);
	SpiReadWriteWord(0x03<< 8);
        SpiReadWriteWord(0x04<< 8);
	
        SpiWriteAddressData((REG_WRITE | TXRampControl), 0x7F); 	//Add by T.L.Steve
	SpiWriteAddressData((REG_WRITE | AFCLoopGearshiftOverride), 0x00);
	SpiWriteAddressData((REG_WRITE | FrequencyBandSelect), 0x53);    //set frequency
	SpiWriteAddressData((REG_WRITE | NominalCarrierFrequency1), 0x4b);  //433HZ
	SpiWriteAddressData((REG_WRITE | NominalCarrierFrequency0), 0x00);
	SpiWriteAddressData((REG_WRITE | ModulationModeControl1), 0x00); 
	SpiWriteAddressData((REG_WRITE | ModulationModeControl2), 0x22); //asynchronous mode  FSK
	SpiWriteAddressData((REG_WRITE | HeaderControl2), 0x02); //no head; sync word 3 and 2
	SpiWriteAddressData((REG_WRITE | HeaderControl1), 0x00);
	SpiWriteAddressData((REG_WRITE | PreambleLength), 0x04);   // 2 byte
	SpiWriteAddressData((REG_WRITE | PreambleDetectionControl), 0x10); //8bit
	SpiWriteAddressData((REG_WRITE | SyncWord3), 0x2d);
	SpiWriteAddressData((REG_WRITE | SyncWord2), 0xa4);
	SpiWriteAddressData((REG_WRITE | DataAccessControl), 0x88); //enable TX handling
	SpiWriteAddressData((REG_WRITE | IFFilterBandwidth), 0x03); //BW=90kHZ
	SpiWriteAddressData((REG_WRITE | ClockRecoveryOversamplingRatio), 0xa1);
	SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset2), 0x20);
	SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset1), 0x4e);
	SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset0), 0xa5);
	SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain1), 0x00);
	SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain0), 0x36);
	SpiWriteAddressData((REG_WRITE | TXDataRate1), 0x02); //9600BPS
	SpiWriteAddressData((REG_WRITE | TXDataRate0), 0x75);
	SpiWriteAddressData((REG_WRITE | FrequencyDeviation), 0x20);                  //72h 频率偏差20k
	SpiWriteAddressData((REG_WRITE | ClockRecoveryGearshiftOverride), 0x13);
	SpiWriteAddressData((REG_WRITE | GPIO0Configuration), 0x1f);
	SpiWriteAddressData((REG_WRITE | GPIO1Configuration), 0x12); //GPIO_1 TX state
	SpiWriteAddressData((REG_WRITE | GPIO2Configuration), 0x15); //GPIO_2 RX state
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x03);
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x00);
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x01);
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x02);
        SpiWriteAddressData((REG_WRITE | TXPower), 0x07);
        
        SpiWriteAddressData((REG_WRITE | 0x09), 0x3f);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFIdle(void)
  +
  + DESCRIPTION:    sets the transceiver and the RF stack into IDLE state, 
  +					independently of the actual state of the RF stack.
  +
  + RETURN:         RF_OK: 			the operation was succesfull
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void RFIdle(void)
{
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x01); 
	//diasble all ITs
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x00);
	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00);
         //releaze all IT flags
	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFTransmit(uint8 * packet, uint8 length)
  +
  + DESCRIPTION:    starts packet transmission
  +
  + INPUT:			MESSAGE structure
  +
  + RETURN:         RF_OK: 				the packet sent correctly
  +					RF_ERROR_TIMING: 	timing poblem -> the packet didn't send within timeout
  +					RF_ERROR_PARAMETER: the command is ignored, some of the 
  +										input parameter(s) are
  +										out of the valid range
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void RFTransmit(unsigned char * packet, unsigned char length)
{
	unsigned char temp8,reg;
	
	RFIdle();
        
        SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2),0x01);       //清发送FIFO
        SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2),0x00); 
        
	SpiWriteAddressData((REG_WRITE | TransmitPacketLength), length);	 

        for(temp8=0;temp8<length;temp8++)
	{
            SpiWriteAddressData((REG_WRITE | FIFOAccess),packet[temp8]);		
	}

	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x04);
	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00);

	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x09);
		
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFReceive(void)
  +
  + DESCRIPTION:    starts packet reception
  +
  + INPUT:			None
  +
  + RETURN:         RF_OK: 				the operation was succesfull
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void RFReceive(void)
{
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x02); 
 	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x00); 
  
        SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x02); 
 	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00); 

        SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);
        
        SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x05);

}


//*************************检测信道是否繁忙***********************//
unsigned char Channel_busy()
{
        unsigned char value;
        value =  (unsigned char)(0x00FF & SpiReadWriteWord(ReceivedSignalStrengthIndicator << 8)) ;//读信号强度寄存器
        if(value>40)
          return 0;
        else
          return 1;
}
