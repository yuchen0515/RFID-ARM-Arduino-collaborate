#include"Command.h"
unsigned long timestamp =0 ;
command::command(Servo a,Servo b,Servo c,Servo d){
  servo_a=a;
  servo_b=b;
  servo_c=c;
  servo_d=d;
}
void command::command_clean(){
    for(int i=0;i<=16;i++)
        command_line[i]=0;
    command_num=0;              //索引值歸0
}
byte* command::command_return(){
    return command_line;
}
void command::set_command_line(byte a[]){
    for(int i =0;i<16;i++)
    { 
      if(a[i]==0)
         break;    
      command_line[command_num]=a[i];
      command_num++;
    }            
}
String command::command_transfer(byte c){
  String command;
  //byte num = c ;
  //Serial.println(c);
  //Serial.println(num);
  if(c-'A'>=0)
  {   
      //Serial.println("IF");
      command = short_command_string[c];
      if(c=='A')
          command = "移至L位置";
  }
  else
  {    
      //Serial.println("ELSE");
      command = long_command_string(c);
  }
  return command;                          
}

void command::command_print(){
   Serial.println(F("command print:"));
   for (int i=0;i<=16;i++)
   {   
       if(command_line[i]==0)
           break;
      // Serial.print(command_transfer(command_line[i]));
       Serial.print(F("指令"));
       Serial.print(i+1);
       Serial.print(F(": "));
      //Serial.print(command_line[i]);
       Serial.print(command_transfer(command_line[i]));
       Serial.print("\n");
   }       
   Serial.println();
}
void command::command_delete(){
  
  if(command_num>0)
  {
     command_num--;
     command_line[command_num]=0;
  }
  else
  {
     command_num=0;
     command_line[command_num]=0;
  }
}
int command::command_index(){
  return command_num;
}
void command::command_exe(byte _command_line[]){
  for(int i=0;i<16;i++)
  { 
    if (exe_break)
    {   delay(500);
        break;
    }
    else if(_command_line[i]==0)
         break;
    else if(_command_line[i]==1)
         move_cube("L1","R3");
    else if(_command_line[i]==2)
         move_cube("L3","R1");
    else if(_command_line[i]==3)
         move_cube("L2","R1");
    else if(_command_line[i]==4)
         move_cube("L1","R2");
    else if(_command_line[i]==5)
         move_cube("L1","R1");
    else if(_command_line[i]==6)
         move_cube("L2","R2");
    else if(_command_line[i]==7)
         move_cube("L1","M3");
    else if(_command_line[i]==8)
         move_cube("L3","M1");
    else if(_command_line[i]==9)
         move_cube("L2","M1");
    else if(_command_line[i]==10)
         move_cube("L1","M2");
    else if(_command_line[i]==11)
         move_cube("L1","M1");
    else if(_command_line[i]==12)
         move_cube("L2","M2");
    else if(_command_line[i]==13)
         move_cube("R1","M3");
    else if(_command_line[i]==14)
         move_cube("R3","M1");
    else if(_command_line[i]==15)
         move_cube("R2","M1");
    else if(_command_line[i]==16)
         move_cube("R1","M2");
    else if(_command_line[i]==17)
         move_cube("R1","M1");
    else if(_command_line[i]==18)
         move_cube("R2","M2");
    else if(_command_line[i]==19)
         move_cube("R1","L3");
    else if(_command_line[i]==20)
         move_cube("R3","L1");
    else if(_command_line[i]==21)
         move_cube("R2","L1");
    else if(_command_line[i]==22)
         move_cube("R1","L2");
    else if(_command_line[i]==23)
         move_cube("R1","L1");
    else if(_command_line[i]==24)
         move_cube("R2","L2");
    else if(_command_line[i]==25)
         move_cube("M1","L3");
    else if(_command_line[i]==26)
         move_cube("M3","L1");
    else if(_command_line[i]==27)
         move_cube("M2","L1");
    else if(_command_line[i]==28)
         move_cube("M1","L2");
    else if(_command_line[i]==29)
         move_cube("M1","L1");
    else if(_command_line[i]==30)
         move_cube("M2","L2");
    else if(_command_line[i]==31)
         move_cube("M1","R3");
    else if(_command_line[i]==32)
         move_cube("M3","R1");
    else if(_command_line[i]==33)
         move_cube("M2","R1");
    else if(_command_line[i]==34)
         move_cube("M1","R2");
    else if(_command_line[i]==35)
         move_cube("M1","R1");
    else if(_command_line[i]==36)
         move_cube("M2","R2");
    else if(_command_line[i]=='A')      //L位置
    {
        servo_rotation(servo_a,cube_position[0]);
        is_card_read();
    }
    else if(_command_line[i]=='B')         //M位置
    {
        servo_rotation(servo_a,cube_position[1]);
        is_card_read();
    }
    else if(_command_line[i]=='C')         //R位置
    {
        servo_rotation(servo_a,cube_position[2]);
        is_card_read();
    }
     else if(_command_line[i]=='D')        //高度1
    {
        servo_rotation(servo_c,cube_height[0][1]);
        servo_rotation(servo_b,cube_height[0][0]);
        is_card_read();
    }
    else if(_command_line[i]=='E')        //高度2
    {     
        servo_rotation(servo_c,cube_height[1][1]); 
        servo_rotation(servo_b,cube_height[1][0]);
        is_card_read();
    }
    else if(_command_line[i]=='F')         //高度3
    {
        servo_rotation(servo_c,cube_height[2][1]); 
        servo_rotation(servo_b,cube_height[2][0]);
        is_card_read();
    }
    else if(_command_line[i]=='G')        //高度4
    {    
        servo_rotation(servo_c,cube_height[3][1]); 
        servo_rotation(servo_b,cube_height[3][0]);
        is_card_read();
    }
    else if(_command_line[i]=='H')        //開爪
    {   
        servo_rotation(servo_d,claw[0]);
        is_card_read();
    }
    else if(_command_line[i]=='I')        //閉爪
    {   
        servo_rotation(servo_d,claw[1]);
        is_card_read();

    }
    else if(_command_line[i]=='J')    //while迴圈執行
    {
        for(int j=i+1;j<=16;j++)
        {
          command_while[j-i-1]=_command_line[j];
        }
//        Serial.println(command_while[0]);
//        Serial.println(command_while[1]);
        while(true)
        { 
          command_exe(command_while);
          if (exe_break)
              break;
        }
    }
  }
}
byte command::command_return_last(){
    return command_line[command_num-1];
    
}
void command::is_card_read(){         //在的同時讀卡
    timestamp = millis() + 500;       //delay(500)
    exe_break = false;
    bool card_break = false;
    while(true)
    {  
       Serial.print(F("t:"));
       Serial.println(timestamp);
       Serial.println(millis());
       if (timestamp <= millis())    
            break;
       if (mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial()) {
            card_break = true;
            break;
       }
    }
    if (card_break)
    {
      readBlock(sector, block, buffer);
      mfrc522.PICC_HaltA();//令卡片進入停止狀態
      mfrc522.PCD_StopCrypto1();
      if(buffer[0]=='Z')
      {  
          exe_break = true;
          //Serial.println("ZZZZ");
          u8g2.firstPage();                     //oled列印
          do {
             u8g2.setCursor(0, 20);
             u8g2.print(F("Break"));//列印讀取到的指令
          } while ( u8g2.nextPage() );
      } 
    }
    
}

void command::reset_exe(){
    exe_break = false;
}
void command::check_and_set_commandline(byte buffer[]){
    bool flag;                     //如果讀到不正確的資料，就不將指令放入command_line
    flag =true;
    for (int i =0;i<16;i++)
    {
       if(buffer[i]=='d')
           flag=false;
    }
    if (flag)    
       set_command_line(buffer);
}
String command::long_command_string(byte c)       //回傳long_command的字串()
{   
    char command[6];
    command[2]='-';
    command[3]='>';
    if(c>=1&&c<=12)
        command[0]='L';
    else if(c>12&&c<=24)
        command[0]='R';
    else
        command[0]='M';
    if(c%6==1||c%6==4)
        command[1]='1';
    else if(c%6==3||c%6==0)
        command[1]='2';
    else 
        command[1]='3';
    if((1<=c&&c<=6)||(c>30&&c<=36))
        command[4]='R';
    else if(c>6&&c<=18)
        command[4]='M';
    else
        command[4]='L';
    if(c%6==1)
        command[5]='3';
    else if(c%6==2||c%6==3||c%6==5)
        command[5]='1';
    else
        command[5]='2';
    return command;
}
//void command::move_cube(char ps[2],char pd[2]){
//    servo_rotation(servo_c,cube_height[3][1]); 
//    servo_rotation(servo_b,cube_height[3][0]);
//    is_card_read();
//    if(ps[0]=='L')
//    {
//        servo_rotation(servo_a,cube_position[0]);
//        is_card_read();
//    }
//    else if(ps[0]=='M')
//    {
//        servo_rotation(servo_a,cube_position[1]);
//        is_card_read();
//    }
//    else if(ps[0]=='R')
//    {
//        servo_rotation(servo_a,cube_position[2]);
//        is_card_read();
//    }
//    if(ps[1]=='1')
//    {
//        servo_rotation(servo_c,cube_height[0][1]);
//        servo_rotation(servo_b,cube_height[0][0]);
//        is_card_read();
//    }
//    else if(ps[1]=='2')
//    {
//        servo_rotation(servo_c,cube_height[1][1]); 
//        servo_rotation(servo_b,cube_height[1][0]);
//        is_card_read();
//    }
//    else if(ps[1]=='3')
//    {
//        servo_rotation(servo_c,cube_height[2][1]); 
//        servo_rotation(servo_b,cube_height[2][0]);
//        is_card_read();
//    }
//    servo_rotation(servo_d,claw[1]);
//    is_card_read();
//    servo_rotation(servo_c,cube_height[3][1]); 
//    servo_rotation(servo_b,cube_height[3][0]);
//    is_card_read();
//    if(pd[0]=='L')
//    {
//        servo_rotation(servo_a,cube_position[0]);
//        is_card_read();
//    }
//    else if(pd[0]=='M')
//    {
//        servo_rotation(servo_a,cube_position[1]);
//        is_card_read();
//    }
//    else if(pd[0]=='R')
//    {
//        servo_rotation(servo_a,cube_position[2]);
//        is_card_read();
//    }
//    if(pd[1]=='1')
//    {
//        servo_rotation(servo_c,cube_height[0][1]);
//        servo_rotation(servo_b,cube_height[0][0]);
//        is_card_read();
//    }
//    else if(pd[1]=='2')
//    {
//        servo_rotation(servo_c,cube_height[1][1]); 
//        servo_rotation(servo_b,cube_height[1][0]);
//        is_card_read();
//    }
//    else if(pd[1]=='3')
//    {
//        servo_rotation(servo_c,cube_height[2][1]); 
//        servo_rotation(servo_b,cube_height[2][0]);
//        is_card_read();
//    }
//    servo_rotation(servo_d,claw[0]);
//    is_card_read();
//}
