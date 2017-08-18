# 蓝牙串口透传 NORDIC KEIL 

ble-uart 是基于nordic蓝牙芯片，keil开发环境的低功耗蓝牙串口源码，希望帮助蓝牙爱好者！

# 基本功能

* 蓝牙串口
* AT指令
* 低功耗模式（广播模式下功耗0.1-0.2mA）

## 1 串口管脚定义

>文件：pca10001.h

```c
      #define RX_PIN_NUMBER  12
      #define TX_PIN_NUMBER  11
      #define CTS_PIN_NUMBER 10
      #define RTS_PIN_NUMBER 8
      #define HWFC           false
```

## 2 控制管脚定义

>文件：user_ble_control.h

```c
      #define DISCONNECT_BLE_SWITCH 13
      #define WAKEUP_BLE_SWITCH     23
      #define BLE_STATUS            29
```

* `DISCONNECT_BLE_SWITCH`: `[in]` 下降沿有效，断开当前已建立的蓝牙连接，广播并重新等待被连接
* `WAKEUP_BLE_SWITCH`: [`in`]降沿唤醒system off 中的蓝牙芯片,低电平串口正常工作，高电平串口电源关闭
* `BLE_STATUS`:[`out`] 高电平表示蓝牙已连接，低电平表示蓝牙等待被连接

## 3 AT指令

* `AT+ADVEN`: 决定蓝牙是否进入`system off`,蓝牙进入`system off`步骤，`a 发送AT+ADVEN0` , `b WAKEUP_BLE_SWITCH 输入高电平` <br> `AT+ADVEN1`,关闭`system off`
