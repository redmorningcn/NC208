# 轨道交通通信信号传感器试验平台通道切换装置

## 功能描述

* 串口接收控制软件发送指令，并反馈；
* 通过串口发送指令控制切换装置选择通道；
* 通过串口发送指令控制电机启动、停止、速度变化；
* 通过界面配置串口；
* 启动后自动运行；

---

## 系统架构

* 通道切户和电机控制，软件采用cvi_modbus框架，应用异步定时器和多线程技术，自动完成modbus_poll功能；
* 和检测软件（测试台软件）通讯，通过自定义协议实现。接收到发送的 速度和传感器编号；
* M-2001模块的地址范围1-63；电机的控制器E2000地址范围64-128；
* 



  



