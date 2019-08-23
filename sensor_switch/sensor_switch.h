/**************************************************************************
通道切換控制：   redmorningcn 190815
1、根据需测试传感器的编号，确认好控制器编号及控制器的值。采用结构体对照表：
{传感器编号、控制器编号1、控制器编号1值、控制器编号2、控制器编号2值}
**************************************************************************/

#include <userint.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define	MAX_SENSOR_NUM		100  /* 传感器编号最大值 */		

/********************************************************************************************/
/* M-2001控制值，由地址和值组成。															 */
/********************************************************************************************/
typedef struct	_stcM2001   
{
	short 	node;		//数值量输出模块地址
	short 	val;		//模块输出值，每位代表1个线圈
}sM2001;


/********************************************************************************************/
/* 传感器切换逻辑。
   对应编号的传感器由那个地址的M2001控制，控制值是多少。
   如果只由1个控制控制，则第二个控制器的值全为0；
*/
/********************************************************************************************/
typedef struct	_stcSensorSwitchTable_   
{
	char	num;		// 传感器编号
	char	motor;		// 电机编号
	char	tmp[2];		// 缓冲
	sM2001	M2001[2];	// 模块对应值
}sSensorSwitchTable;


/********************************************************************************************/
/* 传感器通道切换控制。

*/
/********************************************************************************************/
typedef struct	_stcSensorChangeCtl_   
{
	short	lstSensorNum;		//传感器编号
	short	lstChangeVal;
	short	SensorNum;			//缓冲
	short   ChangeVal;
	
	
}stcSensorChangeCtl;

extern	sSensorSwitchTable	g_SensorSwitchTable[ MAX_SENSOR_NUM ];		   	// 传感器切换表
extern	stcSensorChangeCtl	g_SensorChangeCtl;								// 传感器通道切换控制字

extern	void	InitSensorSwitch (void);				// 传感器切换表初始化
extern	short	SensorChange     (short sensornum);		// 传感器切换
extern	short	M2001CoidChange	 (short node,short val) ; // M2001控制对应通道开关



#ifdef __cplusplus
    }
#endif
