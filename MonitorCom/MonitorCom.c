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

extern		sMonitorInfo	gMonitorInfo; 			// ����̨��Ҫ��Ϣ
sSendMonitor				gSendMonitor;			// Ӧ��֡��ʽ		

void	MonitorComOperate(void)
{
	if(gMonitorInfo.MonitorRecFlg)					//���ճɹ�
	{
		
		//printf("\r\n ��������ţ�%d,�ٶȣ�%d�������ţ�%d",gMonitorInfo.sensorNum,gMonitorInfo.rotate,gMonitorInfo.motorNum);
		//�������õ��ת��ͨѶ ��E2000��
		if(gMonitorInfo.sensorNum >  MAX_SENSOR_NUM -1) {
			gMonitorInfo.MonitorRecFlg = 0;				//  ����ձ�ʶ
			return;
		}
		
		short motornum = g_SensorSwitchTable[gMonitorInfo.sensorNum].motor;
		short speed	   = gMonitorInfo.rotate;	
		SetE2000Speed(motornum,speed);
		
		//�������ô�����ͨѶ   ��M2001��
		SensorChange(gMonitorInfo.sensorNum);		//�л�������
		
		//Ӧ���ͳɹ�������̨
		gSendMonitor.head  			= 	MONITOR_COMM_HEAD;
		gSendMonitor.head 			= 	SW_INT16U(gSendMonitor.head );
		
		gSendMonitor.flg			= 	MONITOR_REPLY_FLG;
		gSendMonitor.sta			= 	0x01;
		unsigned char sum; 
		sum	= GetCheckSum((char *)&gSendMonitor,MONITOR_SEND_LEN - 1);
		gSendMonitor.sumcheck		= 	sum;
		
		sCtrl.pch2->TxBufByteCtr 	= 	MONITOR_SEND_LEN;
		memcpy(sCtrl.pch2->TxBuf,(char *)&gSendMonitor,MONITOR_SEND_LEN);
		
		extern	void NMB_Tx(MODBUS_CH    *pch,
			            CPU_INT08U   *p_reg_tbl,
			            CPU_INT16U   nbr_bytes);
		// ��������
		NMB_Tx(sCtrl.pch2,
			   sCtrl.pch2->TxBuf,
			   sCtrl.pch2->TxBufByteCtr);
		
		gMonitorInfo.MonitorRecFlg = 0;				//  ����ձ�ʶ
	}
}

/********************************************************************************************
 

********************************************************************************************/
