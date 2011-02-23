
#ifndef _SI4431APP_H_
#define _SI4431APP_H_


u32 Si4431AdrCover(u8 *pStrAdr, u32 NumAdr ,bool sta );
uint8_t HeartBeat(uint8_t * pHeartBeatAdr);
uint8_t NewConnect(uint8_t * pNewAdr);
void CheckConnect(void);
void FreHopping(uint8_t SPIx , uint8_t Fre);
void RandomDelayUs(void);
void NetConnect(bool Sta);
void SysRun(void);
void SPI2_CMDCNT(uint8_t stacnt);
void Synchronize(void);
void DataReceive(void);
void DataSend(void);
void Broadcast(uint8_t * TxStr);

#endif
