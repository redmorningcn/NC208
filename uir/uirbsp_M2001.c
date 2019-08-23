#include 	<ansi_c.h>
#include 	<userint.h>
#include 	"M2001.h"
#include 	"includes.h"
#include 	"stringstr.h"
#include	"sensor_switch.h"


//�����������
#define		UIR_M2001_NAME	"M2001.uir"

//ȫ�ֱ���
int	    		gM2001Handle = 0;
extern	 	int gmainPanel;							//�����


//��M2001��壬�ر�����塣
int CVICALLBACK OpenM2001Callback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gM2001Handle	= LoadPanel (0,UIR_M2001_NAME, M2001PANEL);
				DisplayPanel (gM2001Handle);						//��ʾ�ӻ����	
				HidePanel	 (gmainPanel);								//�����������			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.�ر�M2001��壬��ʾ����塣						    */
/********************************************************************************************/
int CVICALLBACK M2001PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gM2001Handle);								//�˳�����
			gM2001Handle = 0;										//
			
			DisplayPanel(gmainPanel);

			break;
		}
	return 0;
}

//��ʱ��ص������е��ã����г��������ѯ��ִ�д���
void CVI_M2001PanelHandle(int panel)
{
	if(gM2001Handle == 0)														// ����״̬�£���ִ�к�������
		return;
	
	//GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// ȡ�豸ID
	//GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// ȡ����
	
	//int	led;																	   
	//GetCtrlVal(panel,M2001PANEL_LED,		&led) ;								// ȡ����
	
	//if(led)
	//	SetCtrlVal(panel,M2001PANEL_LED,0	) ;
	//else
	//	SetCtrlVal(panel,M2001PANEL_LED,1	) ;
}


// ��
int CVICALLBACK M2001NodeCallback  (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// ȡ�豸ID
			break;
	}
	return 0;	
}


short	l_SensorNum;
int CVICALLBACK M2001SensorCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				GetCtrlVal(panel,M2001PANEL_M2001SENSOR,&l_SensorNum) ;		// ȡ�豸ID
			break;
	}
	return 0;		
}

// ��
int CVICALLBACK M2001ValCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// ȡ����
			break;
	}
	return 0;	
}

//���ʱ�ӻص�����
int CVICALLBACK M2001TimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_M2001PanelHandle(panel); 
			break;
	}
	return 0;
}

//�ֶ������ص�����
int CVICALLBACK M2001RUNCallback (int panel, int control, int event,
					 		 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//MB_PollOperate();						//
			
			GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// ȡ�豸ID
			GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// ȡ����
			M2001CoidChange(g_SensorChangeCtl.SensorNum,g_SensorChangeCtl.ChangeVal);
			break;
	}
	return 0;
}


//�������л��ص�����
int CVICALLBACK M2001ChangeCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,M2001PANEL_M2001SENSOR,&l_SensorNum) ;		// ȡ�豸ID
			SensorChange(l_SensorNum);
			break;
	}
	return 0;
}
