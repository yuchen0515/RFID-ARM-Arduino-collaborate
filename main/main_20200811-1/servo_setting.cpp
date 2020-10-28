#include"servo_setting.h"

Servo servo_a;
Servo servo_b;
Servo servo_c;
Servo servo_d;

void servo_rotation(Servo s, int32_t servo_angle){
    int32_t angle = s.read();
    int32_t temp = servo_angle - angle;

    if (!temp) //servo angle == angle
        s.write(servo_angle);
    else{ //servo angle != angle => rise or down the servo
        int32_t check = temp > 0 ? 1 : -1;
        for (; angle != servo_angle; angle += check){
            s.write(angle);
            delay(30);
        }
    }
}

/*
void servo_rotation(Servo s, int servo_angle){
    int angle = 0;
    angle = s.read();

    if(servo_angle-angle>0){
        while (1){ 
            angle++;
            s.write(angle);

            if(angle==servo_angle) break;
            delay(30);
        }
    }else if (servo_angle-angle==0)
        s.write(servo_angle);

    else if(servo_angle-angle<0){
        while (1){ 
            angle--;
            s.write(angle);

            if(angle==servo_angle) break;
            delay(30);
        }
    }
}
*/

void servo_init(){
    servo_a.attach(4);
    servo_b.attach(5);
    servo_c.attach(6);
    servo_d.attach(7);
    servo_a.write(151);
    servo_b.write(128);
    servo_c.write(126);
    servo_d.write(70);
}

void move_cube(String ps, String pd){               //移動方塊("L1","R1")//L位置高度1移到R位置高度1
    //servo_rotation(servo_c,cube_height[3][1]);     //直立版
    //servo_rotation(servo_b,cube_height[3][0]);
    servo_rotation(servo_b,80);                      //平放版
    delay(500);

    if(ps[0]=='L'){
        servo_rotation(servo_a,cube_position[0]);
        delay(500);
    }
    else if(ps[0]=='M'){
        servo_rotation(servo_a,cube_position[1]);
        delay(500);
    }
    else if(ps[0]=='R'){
        servo_rotation(servo_a,cube_position[2]);
        delay(500);
    }

    if(ps[1] >= '1' && ps[1] <= '3'){
        servo_rotation(servo_c,cube_height[ps[1]-'1'][1]);
        servo_rotation(servo_b,cube_height[ps[1]-'1'][0]);
        delay(500);
    }
    /*
    if(ps[1]=='1'){
        servo_rotation(servo_c,cube_height[0][1]);
        servo_rotation(servo_b,cube_height[0][0]);
        delay(500);
    }
    else if(ps[1]=='2'){
        servo_rotation(servo_c,cube_height[1][1]); 
        servo_rotation(servo_b,cube_height[1][0]);
        delay(500);
    }
    else if(ps[1]=='3'){
        servo_rotation(servo_c,cube_height[2][1]); 
        servo_rotation(servo_b,cube_height[2][0]);
        delay(500);
    }
    */

    servo_rotation(servo_d,claw[1]);
    delay(500);
    //servo_rotation(servo_c,cube_height[3][1]);       //直立版
    //servo_rotation(servo_b,cube_height[3][0]);
    servo_rotation(servo_b,80);                        //平放版
    delay(500);

    if(pd[0]=='L'){
        servo_rotation(servo_a,cube_position[0]);
        delay(500);
    }
    else if(pd[0]=='M'){
        servo_rotation(servo_a,cube_position[1]);
        delay(500);
    }
    else if(pd[0]=='R'){
        servo_rotation(servo_a,cube_position[2]);
        delay(500);
    }

    if(ps[1] >= '1' && ps[1] <= '3'){
        servo_rotation(servo_c,cube_height[ps[1]-'1'][1]);
        servo_rotation(servo_b,cube_height[ps[1]-'1'][0]);
        delay(500);
    }

    servo_rotation(servo_d, claw[0]);
    delay(500);
}
