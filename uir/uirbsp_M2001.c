#include 	<ansi_c.h>
#include 	<userint.h>
#include 	"M2001.h"
#include 	"includes.h"
#include 	"stringstr.h"
#include	"sensor_switch.h"


//定义面板名称
#define		UIR_M2001_NAME	"M2001.uir"

//全局变量
int	    		gM2001Handle = 0;
extern	 	int gmainPanel;							//主面板


//打开M2001面板，关闭主面板。
int CVICALLBACK OpenM2001Callback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gM2001Handle	= LoadPanel (0,UIR_M2001_NAME, M2001PANEL);
				DisplayPanel (gM2001Handle);						//显示从机面板	
				HidePanel	 (gmainPanel);								//隐藏设置面板			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.关闭M2001面板，显示主面板。						    */
/********************************************************************************************/
int CVICALLBACK M2001PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gM2001Handle);								//退出窗口
			gM2001Handle = 0;										//
			
			DisplayPanel(gmainPanel);

			break;
		}
	return 0;
}

//在时间回调函数中调用，进行常规任务查询、执行处理。
void CVI_M2001PanelHandle(int panel)
{
	if(gM2001Handle == 0)														// 面板打开状态下，才执行函数处理
		return;
	
	//GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// 取设备ID
	//GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// 取数据
	
	//int	led;																	   
	//GetCtrlVal(panel,M2001PANEL_LED,		&led) ;								// 取数据
	
	//if(led)
	//	SetCtrlVal(panel,M2001PANEL_LED,0	) ;
	//else
	//	SetCtrlVal(panel,M2001PANEL_LED,1	) ;
}


// 。
int CVICALLBACK M2001NodeCallback  (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// 取设备ID
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
				GetCtrlVal(panel,M2001PANEL_M2001SENSOR,&l_SensorNum) ;		// 取设备ID
			break;
	}
	return 0;		
}

// 。
int CVICALLBACK M2001ValCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// 取数据
			break;
	}
	return 0;	
}

//面板时钟回调函数
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

//手动操作回调函数
int CVICALLBACK M2001RUNCallback (int panel, int control, int event,
					 		 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//MB_PollOperate();						//
			
			GetCtrlVal(panel,M2001PANEL_NODE,		&g_SensorChangeCtl.SensorNum) ;		// 取设备ID
			GetCtrlVal(panel,M2001PANEL_VAL,		&g_SensorChangeCtl.ChangeVal) ;		// 取数据
			M2001CoidChange(g_SensorChangeCtl.SensorNum,g_SensorChangeCtl.ChangeVal);
			break;
	}
	return 0;
}


//传感器切换回调函数
int CVICALLBACK M2001ChangeCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,M2001PANEL_M2001SENSOR,&l_SensorNum) ;		// 取设备ID
			SensorChange(l_SensorNum);
			break;
	}
	return 0;
}
