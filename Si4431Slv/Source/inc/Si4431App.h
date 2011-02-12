
#ifndef _SI4431APP_H_
#define _SI4431APP_H_



u8 HeartBeat(u8 * pHeartBeatAdr);
u8 NewConnect(u8 * pNewAdr);
void CheckConnect(void);
void FreHopping(u8 SPIx , u8 Fre);
void RandomDelayUs(void);
void NetConnect(bool Sta);
void SysRun(void);
void SPI2_CMDCNT(u8 stacnt);
void Synchronize(void);
void DataReceive(void);
void DataSend(void);
void Broadcast(u8 * TxStr);

#endif
