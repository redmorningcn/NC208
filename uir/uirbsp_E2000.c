#include 	<ansi_c.h>
#include 	<userint.h>
#include 	"E2000.h"
#include 	"includes.h"
#include 	"stringstr.h"
#include 	"E2000Motor.h"


//定义面板名称
#define		UIR_E2000_NAME	"E2000.uir"

//全局变量
int	    		gE2000Handle = 0;
extern	 	int gmainPanel;							//主面板
 

//打开E2000面板，关闭主面板。
int CVICALLBACK OpenE2000Callback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gE2000Handle	= LoadPanel (0,UIR_E2000_NAME, E2000PANEL);
				DisplayPanel (gE2000Handle);						//显示从机面板	
				HidePanel	 (gmainPanel);							//隐藏设置面板			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.关闭E2000面板，显示主面板。						    */
/********************************************************************************************/
int CVICALLBACK E2000PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gE2000Handle);								//退出窗口
			gE2000Handle = 0;										//
			
			DisplayPanel(gmainPanel);

			break;
		}
	return 0;
}

//在时间回调函数中调用，进行常规任务查询、执行处理。
void CVI_E2000PanelHandle(int panel)
{
	if(gE2000Handle == 0)														// 面板打开状态下，才执行函数处理
		return;
	
	
	GetCtrlVal(panel,E2000PANEL_NODE,		&gE2000Ctrl.node) ;					// 取设备ID
	GetCtrlVal(panel,E2000PANEL_SPEED,		&gE2000Ctrl.speed) ;				// 速度

}


int CVICALLBACK E2000StartCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetE2000Speed(gE2000Ctrl.node,gE2000Ctrl.speed);
			break;
	}
	return 0;		
}

int CVICALLBACK E2000STOPCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetE2000Speed(gE2000Ctrl.node,0);          
			break;
	}
	return 0;		
}


int CVICALLBACK E2000NodeCallback  (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				GetCtrlVal(panel,E2000PANEL_NODE,		&gE2000Ctrl.node) ;		// 取设备ID
			break;
	}
	return 0;	
}


int CVICALLBACK E2000SPEEDCallback  (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				GetCtrlVal(panel,E2000PANEL_SPEED,		&gE2000Ctrl.speed) ;	// 速度
			break;
	}
	return 0;	
}

//面板时钟回调函数
int CVICALLBACK E2000TimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_E2000PanelHandle(panel); 
			break;
	}
	return 0;
}

