#ifndef  _E2000Motor_h_
#define  _E2000Motor_h_

/**************************************************************************
变频控制器E2000简单控制： redmorningcn 190819
欧瑞变频器，控制传感器
**************************************************************************/
#include <userint.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define		E2000_START_NODE		64
#define		E2000_MAX_NUM			8

		
#define		ADDR_START_SOUREC		0x0200		/* 地址：启动指令来源 	 	*/
#define		ADDR_X_FRQ_SOUREC		0x0203		/* 地址：X频率来源    		*/
#define		ADDR_FRQ_TARGET			0x010D		/* 地址：目标频率（转速） 	*/	
#define		ADDR_TURN_CHOOSE		0x0102		/* 地址：正转锁定			*/	
#define		ADDR_MOTOR_CTRL			0x2000		/* 地址：电机启动、停止转动 */

#define		CODE_START_CLOCKWISE	0x0001		/* 指令：启动正转			*/
#define		CODE_START_UNCLOCKWISE	0x0002		/* 指令：启动反转			*/  
		
#define		CODE_START_CLOCKWISE	0x0001		/* 指令：启动正转			*/
#define		CODE_START_UNCLOCKWISE	0x0002		/* 指令：启动反转			*/  
#define		CODE_X_MODBUS			0x000A		/* 指令：主频来源modbus		*/
#define		CODE_START_MODBUS_PANEL 0x0004		/* 指令：启动指令来源面板+modbus */
#define		CODE_TURN_CLOCKWISE		0x0000		/* 指令：正向锁定			*/
#define		CODE_TURN_UNCLOCKWISE	0x0001		/* 指令：反向锁定  			*/
#define		CODE_MOTOR_STOP			0x0003		/* 指令：减速停机			*/
#define		CODE_MOTOR_STOP_FREE	0x0004		/* 指令：自由停机			*/		


/********************************************************************************************/
/*E2000控制值 控制参数。															 */
/********************************************************************************************/
typedef struct	_stcE2000Ctrl   
{
	short 			node;		// E2000通讯地址
	unsigned short	speed;	   	// 电机速度
}sE2000Ctrl;		
		

extern	sE2000Ctrl		gE2000Ctrl;						// 电机控制字

extern	void	InitE2000Modbus(void)  ;				// 初始化电机
extern	short	SetE2000Speed(short node,short speed);	// 设定电机转速


		
#ifdef __cplusplus
    }
#endif

#endif
