#ifndef RFID_H
#define RFID_H
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include "oled.h"
#define RST_PIN    A0     // Reset腳
#define SS_PIN     10     // 晶片選擇腳
extern MFRC522::StatusCode status;
extern MFRC522 mfrc522;    // 建立MFRC522物件
extern MFRC522::MIFARE_Key key;  // 儲存金鑰
extern byte buffer[18]; //
extern byte sector ;    // 指定讀寫的「區段」，可能值:0~15
extern byte block ;     // 指定讀寫的「區塊」，可能值:0~3
void readBlock(byte _sector, byte _block, byte _blockData[]);           
void writeBlock(byte _sector, byte _block, byte _blockData[]);

#endif
