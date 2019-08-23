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
#include  	"sensor_switch.h"
#include  	"uirbsp_mb_poll.h"
#include  	"global.h"
#include  	"E2000Motor.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//
sSensorSwitchTable	g_SensorSwitchTable[ MAX_SENSOR_NUM ];		   	// 传感器切换表

stcSensorChangeCtl	g_SensorChangeCtl;								// 传感器通道切换控制字

/********************************************************************************************/
//local
/********************************************************************************************/

/********************************************************************************************/
/* 切换传感器通道*/  				
//redmorningcn  190817
//通过节点号和值，M2001控制对应的继电器组
/********************************************************************************************/
short	M2001CoidChange(short node,short val) 
{
	short 	len = 0;

	if(node)  {
		//初始化 modbus主结构
		gsMBPoll.codeflg  = CODE_COIL_OP;	// 线圈操作；
		gsMBPoll.writeflg = 1;				// 写操作；
	
		gsMBPoll.node	= node; 			 
		gsMBPoll.addr	= 0;
	
		val =SW_INT16U(val);						// 高低位互换
		memcpy(gsMBPoll.buf,&val,sizeof(val)); 	
		gsMBPoll.len	= 16;	

		len = MB_PollOperate();	
	}
	return len;
}

/********************************************************************************************/
/* 传感器切换初始化化，主要为初始化化切换表*/  				
//redmorningcn  190817
/********************************************************************************************/
void	InitSensorSwitch(void)
{
	short	i,j;
	short	m;
	
	short	sensor_ch = 6;
	short	m2001_io  = 16;
	short	tmp = 1;
	short	mod = 0;
	short	motornum =  E2000_START_NODE;		// E2000开始地址

	for(i = 0; i<MAX_SENSOR_NUM ;i++)
	{
		g_SensorSwitchTable[i].num 				= (char)(i + 1);
		
		m 	= (i + 1) * sensor_ch / m2001_io;						// 按每个传感器6个通道，每个控制器16个通道，计算控制地址
		mod = (i + 1) * sensor_ch % m2001_io; 
		if(mod > (sensor_ch -1) ){									// 只需要单个控制器就可以完成操作
			g_SensorSwitchTable[i].M2001[0].node	= m + 1;
			
			tmp = (short)(0x01 << (mod - sensor_ch));
			g_SensorSwitchTable[i].M2001[0].val     = 0;			// 计算值
			for(j = 0;j < sensor_ch;j++){
				g_SensorSwitchTable[i].M2001[0].val+= tmp;
				tmp = (short)(tmp << 1);
			}
			
			g_SensorSwitchTable[i].M2001[1].node	= 0;			// 无需操作，数据为0
			g_SensorSwitchTable[i].M2001[1].val		= 0;  
		}else{
			g_SensorSwitchTable[i].M2001[0].node	= m;
			
			tmp =(short)( 1 << ( mod + m2001_io - sensor_ch ));
			g_SensorSwitchTable[i].M2001[0].val     = 0;			// 计算值
			for(j = ( mod + m2001_io - sensor_ch );j < m2001_io ; j++){
				g_SensorSwitchTable[i].M2001[0].val += tmp;
				tmp = (short)(tmp << 1);
			}			
			
			if(mod){
				g_SensorSwitchTable[i].M2001[1].node	= m + 1;
			}else{
				g_SensorSwitchTable[i].M2001[1].node	= 0;
			}
				
			tmp = 1 << 0;
			g_SensorSwitchTable[i].M2001[1].val     = 0;			// 计算值
			for(j = 0;j < mod ; j++){
				g_SensorSwitchTable[i].M2001[1].val += tmp;
				tmp = (short)(tmp << 1);
			}
		}
		
		g_SensorSwitchTable[i].motor = motornum;

		if(i%4 == 0) {												// 每4台传感器电机编号
			motornum++;
		}
		
		//M2001CoidChange( i + 1 , 0 );								// 传感器通道切换状态清零	
	}
	
	g_SensorChangeCtl.SensorNum 	= 0;							// 初始化传感器控制字
	g_SensorChangeCtl.lstSensorNum  = 0;
}


/********************************************************************************************/
/* 切换传感器通道*/  				
//redmorningcn  190817
//根据传感器的编号，在切换表查出对应控制器的地址和值，
//通过串口，并将上次操作的传感器地址清零，将此次传感器选通。
/********************************************************************************************/
short	SensorChange(short sensornum)
{
	short 	Num;
	short 	len = 0;
	short	node;
	short  	val;

	
	if(sensornum == g_SensorChangeCtl.SensorNum )  //传感器通道相同，不切换
		return len;
	
	g_SensorChangeCtl.SensorNum = sensornum;
	if(sensornum > MAX_SENSOR_NUM ) //传感器编号非法
	{
		return len;
	}
	//将上次编号的传感器通道切换状态取消
	Num 	= g_SensorChangeCtl.lstSensorNum;
	node	= g_SensorSwitchTable[Num].M2001[0].node;
	val		= 0;									//将通道值清零
	
	len 	= M2001CoidChange( node , val );		//通道切换
	if(	len	== 0) {	   //通道切换失败
		return len;
	}
	
	node	= g_SensorSwitchTable[Num].M2001[1].node;
	val		= 0;
	len 	= M2001CoidChange( node , val );		//通道切换
	
	//切换到本次编号的传感器
	Num 	= g_SensorChangeCtl.SensorNum;
	node	= g_SensorSwitchTable[Num].M2001[0].node;	
	val  	= g_SensorSwitchTable[Num].M2001[0].val;
	len 	= M2001CoidChange( node , val );		//通道切换
	if(	len	 == 0) {	   //通道切换失败
		return len;
	}
	
	node	= g_SensorSwitchTable[Num].M2001[1].node;	
	val  	= g_SensorSwitchTable[Num].M2001[1].val;
	len 	= M2001CoidChange( node , val );		//通道切换
	
	//改变切换状态
	g_SensorChangeCtl.lstSensorNum = g_SensorChangeCtl.SensorNum; 
	
	return len;
}



