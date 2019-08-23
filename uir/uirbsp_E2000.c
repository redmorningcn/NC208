#include 	<ansi_c.h>
#include 	<userint.h>
#include 	"E2000.h"
#include 	"includes.h"
#include 	"stringstr.h"
#include 	"E2000Motor.h"


//�����������
#define		UIR_E2000_NAME	"E2000.uir"

//ȫ�ֱ���
int	    		gE2000Handle = 0;
extern	 	int gmainPanel;							//�����
 

//��E2000��壬�ر�����塣
int CVICALLBACK OpenE2000Callback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gE2000Handle	= LoadPanel (0,UIR_E2000_NAME, E2000PANEL);
				DisplayPanel (gE2000Handle);						//��ʾ�ӻ����	
				HidePanel	 (gmainPanel);							//�����������			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.�ر�E2000��壬��ʾ����塣						    */
/********************************************************************************************/
int CVICALLBACK E2000PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gE2000Handle);								//�˳�����
			gE2000Handle = 0;										//
			
			DisplayPanel(gmainPanel);

			break;
		}
	return 0;
}

//��ʱ��ص������е��ã����г��������ѯ��ִ�д���
void CVI_E2000PanelHandle(int panel)
{
	if(gE2000Handle == 0)														// ����״̬�£���ִ�к�������
		return;
	
	
	GetCtrlVal(panel,E2000PANEL_NODE,		&gE2000Ctrl.node) ;					// ȡ�豸ID
	GetCtrlVal(panel,E2000PANEL_SPEED,		&gE2000Ctrl.speed) ;				// �ٶ�

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
				GetCtrlVal(panel,E2000PANEL_NODE,		&gE2000Ctrl.node) ;		// ȡ�豸ID
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
				GetCtrlVal(panel,E2000PANEL_SPEED,		&gE2000Ctrl.speed) ;	// �ٶ�
			break;
	}
	return 0;	
}

//���ʱ�ӻص�����
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

