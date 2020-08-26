#ifndef Command_H
#define Command_H

#include <Arduino.h>
#include "servo_setting.h"
#include "rfid.h"

class command{

    public:
        void command_clean();              //清空指令
        void command_print();              //印出指令
        void set_command_line(byte a[]);     //加入指令
        void command_delete();             //刪除最近的指令
        String command_transfer(byte c);   //將指令轉換成文字 
        int command_index();               // 指令串的索引值
        void command_exe(byte _command_line[]);                // 指令執形
        //     void rotation(Servo s,int servo_angle);       //伺服馬達旋轉
        command(Servo a,Servo b,Servo c,Servo d);     //建構式   
        byte* command_return();            //傳回command_line
        byte command_return_last();        //回傳最後一個指令
        unsigned long timestamp;           //時間變數
        void reset_exe();                  //重置exe_break變數
        void check_and_set_commandline(byte buffer[]);    //檢查是否有成功讀取，若成功則將讀到的指令存入commandline

    private:
        int command_num=0;                //指令的數量
        byte command_line[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    //指令串
        //     const int cube_position[3]={121,89,40};                           //A,B,C位置
        //     const int cube_height[4][2]={{149,124},{140,122},{128,126},{110,122}};          //方塊高度{B馬達度數,C馬達度數}
        //     const int claw[2]={70,10};                                        //開爪角度
        byte command_while[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   //while迴圈的內容
        void is_card_read();                                        //在等待的同時讀卡
        bool exe_break = false;                                     //中斷是否發生(True 發生;False )
        String long_command_string(byte c);                         //回傳long_command的字串
        //     void move_cube(char ps[2],char pd[2]);
        //     const String long_command_string[36]={"L1->R3","L3->R1","L2->R1","L1->R2","L1->R1","L2->R2",
        //                                    "L1->M3","L3->M1","L2->M1","L1->M2","L1->M1","L2->M2",
        //                                    "R1->M3","R3->M1","R2->M1","R1->M2","R1->M1","R2->M2",
        //                                    "R1->L3","R3->L1","R2->L1","R1->L2","R1->L1","R2->L2",
        //                                    "M1->L3","M3->L1","M2->L1","M1->L2","M1->L1","M2->L2",
        //                                    "M1->R3","M3->R1","M2->R1","M1->R2","M1->R1","M2->R2"};
        const String short_command_string[10]={\
            "移至L位置","移至M位置","移至R位置","移至高度1",\
            "移至高度2","移至高度3","移至高度4","開爪",\
            "閉爪","while迴圈"};    //指令串中文

};

#endif
