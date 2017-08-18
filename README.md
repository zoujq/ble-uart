蓝牙串口透传 NORDIC KEIL 
=======================
ble-uart 是基于nordic蓝牙芯片，keil开发环境的低功耗蓝牙串口源码，希望帮助蓝牙爱好者！

基本功能
---------------------
* 蓝牙串口
* AT指令
* 低功耗模式（广播模式下功耗0.1-0.2mA）

# 1 串口管脚定义
>文件：pca10001.h
```c
      #define RX_PIN_NUMBER  12
      #define TX_PIN_NUMBER  11
      #define CTS_PIN_NUMBER 10
      #define RTS_PIN_NUMBER 8
      #define HWFC           false
```
# 2 控制管脚定义

>文件：user_ble_control.h
```c
      #define DISCONNECT_BLE_SWITCH 13
      #define WAKEUP_BLE_SWITCH     23
      #define BLE_STATUS            29
```

      * DISCONNECT_BLE_SWITCH
      * 下降沿有效，断开当前已建立的蓝牙连接，广播并重新等待被连接
*WAKEUP_BLE_SWITCH
*降沿唤醒system off 中的蓝牙芯片
