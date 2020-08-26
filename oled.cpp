#include"oled.h"
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
void oled_print(String string1){
    u8g2.firstPage();
    do {
         u8g2.setCursor(0, 20);
         u8g2.print(string1);
    } while ( u8g2.nextPage() );
}
void oled_print(String string1,String string2){
    u8g2.firstPage();                                                      
    do {
         u8g2.setCursor(0, 20);
         u8g2.print(string1);
         u8g2.setCursor(0, 40);
         u8g2.print(string2);   
    } while ( u8g2.nextPage() );
}
