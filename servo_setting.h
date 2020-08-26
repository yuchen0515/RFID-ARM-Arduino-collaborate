#ifndef SERVO_SETTING_H
#define SERVO_SETTING_H

#include <Servo.h>
#include <Arduino.h>

extern Servo servo_a;
extern Servo servo_b;
extern Servo servo_c;
extern Servo servo_d;

const int cube_position[3]={125,75,25};                           //A,B,C位置
//const int cube_height[4][2]={{149,124},{140,122},{128,126},{110,122}};          //方塊高度{B馬達度數,C馬達度數}[直立版]
//const int cube_height[4][2]={{145,173},{143,143},{165,105},{110,122}};            //方塊高度{B馬達度數,C馬達度數}[平放版]
const int cube_height[4][2]={{132,173},{143,148},{160,115},{110,122}};            //方塊高度{B馬達度數,C馬達度數}[平放版]
const int claw[2]={50,10};  

void servo_rotation(Servo s,int servo_angle);                 
void servo_init();
void move_cube(char ps[2],char pd[2]);                                 ////移動方塊從X位置高度m移動到Y位置高度n

#endif
