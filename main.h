#ifndef	CVI_MAIN_H
#define	CVI_MAIN_H

#include "mb.h"
#include "MB_BSP.h"


/********************************************************************************************/
/* 串口配置结构体																				    */
/********************************************************************************************/
typedef struct	_strCtrl_
{
	MODBUS_CH   	*pch;
	stcUartConfig	*com1;
	MODBUS_CH   	*pch2;
	stcUartConfig	*com2;		
	
}strCtrl;				//串口配置结构体

extern	strCtrl		sCtrl;
extern	int 	gmainPanel;


#endif
