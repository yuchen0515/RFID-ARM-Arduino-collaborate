# 機械手臂&RFID 教具

> 目前code我還沒整體修整過

## 聲明

原始code非 yuchen0515 所寫\
為 Prof. Yu-Liang Ting 學生所製作\
本人 yuchen0515 協助code，更改結構、改善以及發展新功能\
未經同意不得擅自使用，亦不得作為商業用途，特此聲明。


## 教具運行方式

利用RFID教具卡，讀取並匯入一連串指令，其中可刪除、新增、儲存等等，執行即可讓機械手臂執行一連串相對應之指令，此外指令對應代碼由0-36, A-J等字母所組成，L,M,R以及1,2,3亦有相對應之涵義。

* L => Left
* M => Mid
* R => Right
* number => move __ distance / box


## 程式碼主要用途

> 此部份待補

* main_20200811-1.ino
* Command.cpp
* oled.cpp
* rfid.cpp
* servo_setting.cpp
