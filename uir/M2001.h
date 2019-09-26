/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  M2001PANEL                       1       /* callback function: M2001PanelCB */
#define  M2001PANEL_M2001SENSOR           2       /* control type: numeric, callback function: M2001SensorCallback */
#define  M2001PANEL_CHANGE                3       /* control type: command, callback function: M2001ChangeCallback */
#define  M2001PANEL_VAL                   4       /* control type: numeric, callback function: M2001ValCallback */
#define  M2001PANEL_DECORATION_2          5       /* control type: deco, callback function: (none) */
#define  M2001PANEL_TEXTMSG_2             6       /* control type: textMsg, callback function: (none) */
#define  M2001PANEL_NODE                  7       /* control type: numeric, callback function: M2001NodeCallback */
#define  M2001PANEL_RUN                   8       /* control type: command, callback function: M2001RUNCallback */
#define  M2001PANEL_M2001_TIMER           9       /* control type: timer, callback function: M2001TimerCallback */
#define  M2001PANEL_DECORATION            10      /* control type: deco, callback function: (none) */
#define  M2001PANEL_TEXTMSG               11      /* control type: textMsg, callback function: (none) */
#define  M2001PANEL_TEXTMSG_3             12      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK M2001ChangeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001NodeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001RUNCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001SensorCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001TimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M2001ValCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
