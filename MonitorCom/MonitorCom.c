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


extern	void NMB_Tx(MODBUS_CH    *pch,        
	            CPU_INT08U   *p_reg_tbl,      
	            CPU_INT16U   nbr_bytes);      
                                              
void	MonitorComOperate(void)
{
	
	if(gMonitorInfo.MonitorRecFlg)					//���ճɹ�
	{
		//printf("\r\n ��������ţ�%d,�ٶȣ�%d�������ţ�%d",gMonitorInfo.sensorNum,gMonitorInfo.rotate,gMonitorInfo.motorNum);
		//�������õ��ת��ͨѶ ��E2000��
		if(gMonitorInfo.sensorNum >  MAX_SENSOR_NUM -1 &&  gMonitorInfo.sensorNum != 255 ) {
			
			gMonitorInfo.MonitorRecFlg = 0;				//  ����ձ�ʶ
			return;
		}

	
		//�������ô�����ͨѶ   ��M2001��
		SensorChange(gMonitorInfo.sensorNum);		// �л�������
		
	  	if(gMonitorInfo.sensorNum != 255) {
		                                                                                     
			short motornum = g_SensorSwitchTable[gMonitorInfo.sensorNum].motor;                  			
			short speed	   = gMonitorInfo.rotate;                                                			
		                                                                                     			
			if(g_SensorSwitchTable[gMonitorInfo.sensorNum].flg !=1)  //������δ���ã�������      			
			{                                                                                    			
				return;                                                                          			
			}                                                                                    			
	
			SetE2000Speed(motornum,speed);			// �����ٶ�
		}
		
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
		


		gMonitorInfo.MonitorRecFlg = 0;				//  ����ձ�ʶ    
		// ��������
		NMB_Tx(sCtrl.pch2,
			   sCtrl.pch2->TxBuf,
			   sCtrl.pch2->TxBufByteCtr);
		
		Delay_Nus(100);
	}
}

/********************************************************************************************
 

********************************************************************************************/
