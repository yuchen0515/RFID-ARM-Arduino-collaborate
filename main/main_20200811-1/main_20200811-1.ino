#include <Bounce2.h>
#include "Command.h"       //自訂的標頭檔，放在同個資料夾

Bounce button_delete = Bounce(2, 60);      //按鈕(Pin,delay time)
Bounce button_exe = Bounce(3, 60);
Bounce button_store= Bounce(8,60);

command cmd(servo_a,servo_b,servo_c,servo_d);     // command 物件 

void setup(){
    Serial.begin(9600);
    SPI.begin();               // 初始化SPI介面
    mfrc522.PCD_Init();        // 初始化MFRC522卡片
    servo_init();              // 伺服馬達設定(在servo_setting.h中)

    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT);
    pinMode(8, INPUT);

    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_unifont_t_chinese1);   //設定字形

    oled_print(F("開始!!"),F("請掃描卡片..."));
    Serial.println(F("Please scan MIFARE Classic card..."));

    // 準備金鑰（用於key A和key B），出廠預設為6組 0xFF。
    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xFF;

}

void loop(){
    //  u8g2.firstPage();                     //oled列印
    //  do {
    //    u8g2.setCursor(0, 20);
    //    u8g2.print("scan card");
    //  } while ( u8g2.nextPage() );
    if (button_delete.update() == true && button_delete.read() == LOW) {     //刪除按鈕觸發
        Serial.println(F("刪除"));                                                     
        oled_print(F("刪除指令:"),cmd.command_transfer(cmd.command_return_last()));

        cmd.command_delete();
        cmd.command_print();
    }

    if (button_exe.update() == true && button_exe.read() == LOW){ 
    //執行按鈕觸發
        Serial.println(F("exe"));
        cmd.command_print();
        u8g2.clearDisplay();

        oled_print(F("執行中..."));
        cmd.command_exe(cmd.command_return());         //指令執行

        oled_print(F("執行完成"));
        cmd.reset_exe();

        cmd.command_clean();
        Serial.println("-----------------------------");
    }

    if (button_store.update() == true && button_store.read() == LOW) {       //儲存按鈕觸發
        Serial.println(F("儲存"));
        cmd.command_print();
        u8g2.clearDisplay();
        oled_print(F("儲存"));

        while (1){
            if (  mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial())
                break;
        }

        writeBlock(sector, block, cmd.command_return());
        Serial.println(F("-----------------------------"));

        mfrc522.PICC_HaltA();//令卡片進入停止狀態
        mfrc522.PCD_StopCrypto1();
        u8g2.clearDisplay();

        oled_print(F("儲存完成"));
    }

    // 查看是否感應到卡片
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;  
        // 退回loop迴圈的開頭
    }

    // 選取一張卡片
    if ( ! mfrc522.PICC_ReadCardSerial()) {  // 若傳回1，代表已讀取到卡片的ID
        return;
    }

    readBlock(sector, block, buffer);    // 區段編號、區塊編號、存放讀取資料的陣列
    Serial.print(F("Read block: "));        // 顯示儲存讀取資料的陣列元素值

    for (byte i = 0 ; i < 16 ; i++)
        Serial.write (buffer[i]);



    cmd.check_and_set_commandline(buffer); //如果讀到不正確的資料，就不將指令放入command_line
    Serial.println();
    u8g2.firstPage();                     //oled列印


    oled_print(F("讀取指令"),cmd.command_transfer(buffer[0]));   //印出第一個讀到的指令

    mfrc522.PICC_HaltA();//令卡片進入停止狀態
    mfrc522.PCD_StopCrypto1();
}
