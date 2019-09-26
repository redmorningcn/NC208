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
#include  	"MonitorCom.h"
#include  	"global.h"

#include 	"MonitorCom.h"
#include 	"cpu.h"
#include 	"NO_MB_OS.h"

#include	"CrcCheck.h"
#include	"sensor_switch.h"

#include	"main.h"

extern		sMonitorInfo	gMonitorInfo; 			// 测试台主要信息
sSendMonitor				gSendMonitor;			// 应答帧格式		


extern	void NMB_Tx(MODBUS_CH    *pch,        
	            CPU_INT08U   *p_reg_tbl,      
	            CPU_INT16U   nbr_bytes);      
                                              
void	MonitorComOperate(void)
{
	
	if(gMonitorInfo.MonitorRecFlg)					//接收成功
	{
		//printf("\r\n 传感器编号：%d,速度：%d，电机编号：%d",gMonitorInfo.sensorNum,gMonitorInfo.rotate,gMonitorInfo.motorNum);
		//启动设置电机转速通讯 （E2000）
		if(gMonitorInfo.sensorNum >  MAX_SENSOR_NUM -1 &&  gMonitorInfo.sensorNum != 255 ) {
			
			gMonitorInfo.MonitorRecFlg = 0;				//  清接收标识
			return;
		}

	
		//启动设置传感器通讯   （M2001）
		SensorChange(gMonitorInfo.sensorNum);		// 切换传感器
		
	  	if(gMonitorInfo.sensorNum != 255) {
		                                                                                     
			short motornum = g_SensorSwitchTable[gMonitorInfo.sensorNum].motor;                  			
			short speed	   = gMonitorInfo.rotate;                                                			
		                                                                                     			
			if(g_SensorSwitchTable[gMonitorInfo.sensorNum].flg !=1)  //传感器未配置，不处理      			
			{                                                                                    			
				return;                                                                          			
			}                                                                                    			
	
			SetE2000Speed(motornum,speed);			// 调整速度
		}
		
		//应答发送成功给测试台
		gSendMonitor.head  			= 	MONITOR_COMM_HEAD;
		gSendMonitor.head 			= 	SW_INT16U(gSendMonitor.head );
		
		gSendMonitor.flg			= 	MONITOR_REPLY_FLG;
		gSendMonitor.sta			= 	0x01;
		unsigned char sum; 
		sum	= GetCheckSum((char *)&gSendMonitor,MONITOR_SEND_LEN - 1);
		gSendMonitor.sumcheck		= 	sum;
		
		sCtrl.pch2->TxBufByteCtr 	= 	MONITOR_SEND_LEN;
		memcpy(sCtrl.pch2->TxBuf,(char *)&gSendMonitor,MONITOR_SEND_LEN);
		


		gMonitorInfo.MonitorRecFlg = 0;				//  清接收标识    
		// 启动发送
		NMB_Tx(sCtrl.pch2,
			   sCtrl.pch2->TxBuf,
			   sCtrl.pch2->TxBufByteCtr);
		
		Delay_Nus(100);
	}
}

/********************************************************************************************
 

********************************************************************************************/
