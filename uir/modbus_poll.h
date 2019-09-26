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

#define  MAIN                             1       /* callback function: mb_mainPanelCB */
#define  MAIN_SLAVE                       2       /* control type: command, callback function: OpenSlaveCallback */
#define  MAIN_E2000                       3       /* control type: command, callback function: OpenE2000Callback */
#define  MAIN_M2001                       4       /* control type: command, callback function: OpenM2001Callback */
#define  MAIN_POLL                        5       /* control type: command, callback function: OpenPollCallback */
#define  MAIN_COMCONFIG_2                 6       /* control type: command, callback function: OpenCom2Callback */
#define  MAIN_COMCONFIG                   7       /* control type: command, callback function: OpenCom1Callback */
#define  MAIN_MAIN_TIMER                  8       /* control type: timer, callback function: MainTimerCallback */
#define  MAIN_DECORATION_5                9       /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_4                10      /* control type: deco, callback function: (none) */
#define  MAIN_TEXTMSG_5                   11      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_4                   12      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG                     13      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_UNNAMEDM                 2

#define  MENUBAR_2                        2
#define  MENUBAR_2_UNNAMEDM               2


     /* Callback Prototypes: */

int  CVICALLBACK MainTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mb_mainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenE2000Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenM2001Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenPollCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSlaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
