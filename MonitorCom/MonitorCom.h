#ifndef  _MonitorCom_h_
#define  _MonitorCom_h_

/**************************************************************************
控制器通讯控制。
monitor发送：起始 55DD  + 电机编号： 1byte + 传感器编号 1byte + 转速 4byte  + 校验和 1byte
接收成功   ：起始 55DD  + FF + 状态 1byte + 校验和 1byte。
redmorningcn 190820
**************************************************************************/
#include <userint.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define		MONITOR_COMM_HEAD		0x55DD    		/* 串口通讯开始 */
#define		MONITOR_REPLY_FLG		0xFF			/* 通讯应答标识 */	
#define		MONITOR_REPLY_OK		0x01			/* 通讯应答标识 */	
#define		MONITOR_REC_LEN			9				/* 接收的帧长   */	
#define		MONITOR_SEND_LEN		5				/* 接收的帧长   */	
		
#define		ADDR_MOTOR_NUM			2				/* 电机编号位置 	*/
#define		ADDR_SENSOR_NUM			3				/* 传感器编号位置	*/
#define		ADDR_ROTATE				4				/* 转速位置			*/	
		
/********************************************************************************************/
/* 和测试台接收通讯的帧格式															 */
/********************************************************************************************/
typedef struct	_stcRecMonitor   
{
	short 	head;		//接收帧头部
	char	motorNum;	//电机编号
	char	sensorNum;	//传感器编号
	int		rotate;		//旋转速度
	char	sumcheck;	//校验和
}sRecMonitor;

/********************************************************************************************/
/* 和测试台发送通讯的帧格式															 */
/********************************************************************************************/
typedef struct	_stcSendMonitor   
{
	short 	head;		//接收帧头部
	char	flg	;		//恢复标识
	char	sta;		//电机编号
	char	sumcheck;	//校验和
}sSendMonitor;


/********************************************************************************************/
/*  数据结构														 */
/********************************************************************************************/
typedef struct	_stcMonitorInfo
{
	unsigned char	sensorNum;			// 传感器编号
	unsigned char	motorNum;			// 电机编号
	unsigned char	tmp;
	unsigned char	MonitorRecFlg:1;	// 测试台接收成功标识
	unsigned char	MonitorSendEnFlg:1;	// 测试台发送成功标识
	unsigned char	E2000SetFlg:1;		// 电机设置成功指令
	unsigned char	M2001SetFlg:1;		// 数字输出模块
	unsigned char	tmpFlg:4;			// 备用
	unsigned int    rotate;				// 转速
}sMonitorInfo;


extern	void	MonitorComOperate(void);
extern	void	SetE2000Speed(short node,short speed);  

#ifdef __cplusplus
    }
#endif

#endif
