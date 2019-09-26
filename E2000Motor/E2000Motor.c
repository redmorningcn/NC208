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
		gsMBPoll.codeflg  	= CODE_REG_OP_06;		// ��Ȧ������
		gsMBPoll.writeflg 	= 1;					// д������
	
		gsMBPoll.node		= node; 			 
		gsMBPoll.addr		= addr;
	
		//val =SW_INT16U(val);						// �ߵ�λ����
		memcpy(gsMBPoll.buf,&val,sizeof(val)); 	
		gsMBPoll.len		= 1;	

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

#define	DELAY_US_MOTOR	(1500000)
/********************************************************************************************/
/* ����ָ������ٶ�*/  				
//redmorningcn  190819
//�趨ָ������ٶ�ֵ
/********************************************************************************************/
short	SetE2000Speed(short node,short speed)
{
	short	len = 0;
	unsigned int	tmp32;
	tmp32	=  speed * 5;
	speed	=  (short)(tmp32 / 3);  
	
	if(speed == 0){  		//�رյ��
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_MOTOR_STOP);
	}else{
		
		//������ƵX ��
		len = E2000RegChangeOne(node,ADDR_X_FRQ_SOUREC,CODE_X_MODBUS);
		Delay_Nus(DELAY_US_MOTOR);

		//����������Դ
		len = E2000RegChangeOne(node,ADDR_START_SOUREC,CODE_START_MODBUS_PANEL);
		Delay_Nus(DELAY_US_MOTOR);

		//�����趨�ٶ�
		len = E2000RegChangeOne(node,ADDR_FRQ_TARGET,speed);
		if(len == 0)
			return len;
		
//		Delay_Nus(100);
		//������ת
//		len = E2000RegChangeOne(node,ADDR_MOTOR_WISE,CODE_TURN_CLOCKWISE);
//		if(len == 0)
//			return len;
		
		Delay_Nus(DELAY_US_MOTOR);

		//�趨��ת
		len = E2000RegChangeOne(node,ADDR_MOTOR_CTRL,CODE_START_CLOCKWISE);
		if(len == 0)
			return len;
		
		Delay_Nus(DELAY_US_MOTOR);
	}
	return len;
}

