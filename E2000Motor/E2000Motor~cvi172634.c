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
#include  	"E2000Motor.h"
#include  	"uirbsp_mb_poll.h"
#include  	"global.h"
#include  	"CrcCheck.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//
sE2000Ctrl		gE2000Ctrl;				//E2000������
/********************************************************************************************/
/* �л�������ͨ��*/  				
//redmorningcn  190817
//ͨ���ڵ�ź�ֵ��M2001���ƶ�Ӧ�ļ̵�����
/********************************************************************************************/
short	E2000RegChangeOne(short node,short addr,short val) 
{
	short 	len = 0;

	if(node)  {
		//��ʼ�� modbus���ṹ
		gsMBPoll.codeflg  = CODE_REG_OP;		// ��Ȧ������
		gsMBPoll.writeflg = 1;					// д������
	
		gsMBPoll.node	= node; 			 
		gsMBPoll.addr	= addr;
	
		//val =SW_INT16U(val);						// �ߵ�λ����
		memcpy(gsMBPoll.buf,&val,sizeof(val)); 	
		gsMBPoll.len	= 1;	

		len = MB_PollOperate();	
	}
	return len;
}

/********************************************************************************************/
/* ��ʼ��E2000���Ʒ�ʽ*/  				
//redmorningcn  190819
//��ƵX��ѡ��modbus��������ʽ��ѡ��modbus+panel������ͣ����
/********************************************************************************************/
void	InitE2000Modbus(void)
{
	short	len;
	
	for(short i = E2000_START_NODE; i < E2000_MAX_NUM ;i++)
	{
		//������ƵX ��
		len = E2000RegChangeOne(i,ADDR_X_FRQ_SOUREC,CODE_X_MODBUS);

		//����������Դ
		len = E2000RegChangeOne(i,ADDR_START_SOUREC,CODE_START_MODBUS_PANEL);
		
		//����ͣ��
		len = E2000RegChangeOne(i,ADDR_MOTOR_CTRL,CODE_MOTOR_STOP);	
	}
}

/********************************************************************************************/
/* ����ָ������ٶ�*/  				
//redmorningcn  190819
//�趨ָ������ٶ�ֵ
/********************************************************************************************/
void	SetE2000Speed(short node,short speed)
{
	short	len;
	
	if(speed == 0){  		//�رյ��
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_MOTOR_STOP);
	}else{
		
		//�����趨�ٶ�
		len = E2000RegChangeOne(node,ADDR_FRQ_TARGET,speed);
		Delay_Nus(100);
		//������ת
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_TURN_CLOCKWISE);
		Delay_Nus(100);

		//�趨��ת
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_START_CLOCKWISE);
		Delay_Nus(100);
	}
}

