/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/

#include 	<ansi_c.h>
#include  	"E2000Motor.h"
#include  	"uirbsp_mb_poll.h"
#include  	"global.h"
#include  	"CrcCheck.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//
sE2000Ctrl		gE2000Ctrl;				//E2000控制字
/********************************************************************************************/
/* 切换传感器通道*/  				
//redmorningcn  190817
//通过节点号和值，M2001控制对应的继电器组
/********************************************************************************************/
short	E2000RegChangeOne(short node,short addr,short val) 
{
	short 	len = 0;

	if(node)  {
		//初始化 modbus主结构
		gsMBPoll.codeflg  = CODE_REG_OP;		// 线圈操作；
		gsMBPoll.writeflg = 1;					// 写操作；
	
		gsMBPoll.node	= node; 			 
		gsMBPoll.addr	= addr;
	
		//val =SW_INT16U(val);						// 高低位互换
		memcpy(gsMBPoll.buf,&val,sizeof(val)); 	
		gsMBPoll.len	= 1;	

		len = MB_PollOperate();	
	}
	return len;
}

/********************************************************************************************/
/* 初始化E2000控制方式*/  				
//redmorningcn  190819
//主频X，选择modbus；启动方式，选择modbus+panel；减速停机。
/********************************************************************************************/
void	InitE2000Modbus(void)
{
	short	len;
	
	for(short i = E2000_START_NODE; i < E2000_MAX_NUM ;i++)
	{
		//设置主频X ：
		len = E2000RegChangeOne(i,ADDR_X_FRQ_SOUREC,CODE_X_MODBUS);

		//设置启动来源
		len = E2000RegChangeOne(i,ADDR_START_SOUREC,CODE_START_MODBUS_PANEL);
		
		//减速停机
		len = E2000RegChangeOne(i,ADDR_MOTOR_CTRL,CODE_MOTOR_STOP);	
	}
}

/********************************************************************************************/
/* 设置指定电机速度*/  				
//redmorningcn  190819
//设定指定电机速度值
/********************************************************************************************/
void	SetE2000Speed(short node,short speed)
{
	short	len;
	
	if(speed == 0){  		//关闭电机
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_MOTOR_STOP);
	}else{
		
		//锁定设定速度
		len = E2000RegChangeOne(node,ADDR_FRQ_TARGET,speed);
		Delay_Nus(100);
		//锁定正转
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_TURN_CLOCKWISE);
		Delay_Nus(100);

		//设定正转
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_START_CLOCKWISE);
		Delay_Nus(100);
	}
}

