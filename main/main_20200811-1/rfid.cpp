#include"rfid.h"
MFRC522::StatusCode status;
MFRC522 mfrc522(SS_PIN, RST_PIN);    // 建立MFRC522物件
MFRC522::MIFARE_Key key;  // 儲存金鑰

byte buffer[18]; 
byte sector = 15, block = 1;   // 指定讀寫的「區段」，可能值:0~15

void readBlock(byte _sector, byte _block, byte _blockData[]){            //讀取RFID
    if (_sector < 0 || _sector > 15 || _block < 0 || _block > 3) {
        // 顯示「區段或區塊碼錯誤」，然後結束函式。
        Serial.println(F("Wrong sector or block number."));
        return;
    }

    byte blockNum = _sector * 4 + _block;  // 計算區塊的實際編號（0~63）
    byte trailerBlock = _sector * 4 + 3;   // 控制區塊編號

    // 驗證金鑰
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

    // 若未通過驗證…
    if (status != MFRC522::STATUS_OK) {
        // 顯示錯誤訊息
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    byte buffersize = 18;
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockNum, _blockData, &buffersize);

    // 若讀取不成功…
    if (status != MFRC522::STATUS_OK) {
        // 顯示錯誤訊息
        Serial.print(F("MIFARE_read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        u8g2.firstPage();                             //顯示錯誤訊息，提醒使用者再掃一次

        do { 
            u8g2.setCursor(0, 20);
            u8g2.print("scan failed");
            u8g2.setCursor(0,40);
            u8g2.print("scan again");
        }while ( u8g2.nextPage() );

        delay(1000);
        
        return;
    }

    // 顯示「讀取成功！」
    Serial.println(F("Data was read."));
}

void writeBlock(byte _sector, byte _block, byte _blockData[]){
    if (_sector < 0 || _sector > 15 || _block < 0 || _block > 3){
        // 顯示「區段或區塊碼錯誤」，然後結束函式。
        Serial.println(F("Wrong sector or block number."));
        return;
    }

    if (_sector == 0 && _block == 0) {
        // 顯示「第一個區塊只能讀取」，然後結束函式。
        Serial.println(F("First block is read-only."));
        return;
    }

    byte blockNum = _sector * 4 + _block;  // 計算區塊的實際編號（0~63）
    byte trailerBlock = _sector * 4 + 3;   // 控制區塊編號

    // 驗證金鑰
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    // 若未通過驗證…
    if (status != MFRC522::STATUS_OK) {
        // 顯示錯誤訊息
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // 在指定區塊寫入16位元組資料
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockNum, _blockData, 16);
    // 若寫入不成功…
    if (status != MFRC522::STATUS_OK) {
        // 顯示錯誤訊息
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    // 顯示「寫入成功！」
    Serial.println(F("Data was written."));
}
