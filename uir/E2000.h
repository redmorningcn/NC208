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

#define  E2000PANEL                       1       /* callback function: E2000PanelCB */
#define  E2000PANEL_SPEED                 2       /* control type: scale, callback function: E2000SPEEDCallback */
#define  E2000PANEL_START                 3       /* control type: command, callback function: E2000StartCallback */
#define  E2000PANEL_STOP                  4       /* control type: command, callback function: E2000STOPCallback */
#define  E2000PANEL_DECORATION            5       /* control type: deco, callback function: (none) */
#define  E2000PANEL_DECORATION_2          6       /* control type: deco, callback function: (none) */
#define  E2000PANEL_E2000_TIMER           7       /* control type: timer, callback function: E2000TimerCallback */
#define  E2000PANEL_STRING_2              8       /* control type: textMsg, callback function: (none) */
#define  E2000PANEL_STRING                9       /* control type: textMsg, callback function: (none) */
#define  E2000PANEL_NODE                  10      /* control type: numeric, callback function: E2000NodeCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK E2000NodeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E2000PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E2000SPEEDCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E2000StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E2000STOPCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E2000TimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
