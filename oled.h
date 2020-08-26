#ifndef OLED_H
#define OLED_H
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
void oled_print(String string1);                                          //oled列印(第一行)
void oled_print(String string1,String string2);                           //oled列(第一行,第二行) 
#endif
