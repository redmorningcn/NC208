#ifndef  _E2000Motor_h_
#define  _E2000Motor_h_

/**************************************************************************
��Ƶ������E2000�򵥿��ƣ� redmorningcn 190819
ŷ���Ƶ�������ƴ�����
**************************************************************************/
#include <userint.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define		E2000_START_NODE		64
#define		E2000_MAX_NUM			8

		
#define		ADDR_START_SOUREC		0x0200		/* ��ַ������ָ����Դ 	 	*/
#define		ADDR_X_FRQ_SOUREC		0x0203		/* ��ַ��XƵ����Դ    		*/
#define		ADDR_FRQ_TARGET			0x010D		/* ��ַ��Ŀ��Ƶ�ʣ�ת�٣� 	*/	
#define		ADDR_TURN_CHOOSE		0x0102		/* ��ַ����ת����			*/	
#define		ADDR_MOTOR_CTRL			0x2000		/* ��ַ�����������ֹͣת�� */

#define		CODE_START_CLOCKWISE	0x0001		/* ָ�������ת			*/
#define		CODE_START_UNCLOCKWISE	0x0002		/* ָ�������ת			*/  
		
#define		CODE_START_CLOCKWISE	0x0001		/* ָ�������ת			*/
#define		CODE_START_UNCLOCKWISE	0x0002		/* ָ�������ת			*/  
#define		CODE_X_MODBUS			0x000A		/* ָ���Ƶ��Դmodbus		*/
#define		CODE_START_MODBUS_PANEL 0x0004		/* ָ�����ָ����Դ���+modbus */
#define		CODE_TURN_CLOCKWISE		0x0000		/* ָ���������			*/
#define		CODE_TURN_UNCLOCKWISE	0x0001		/* ָ���������  			*/
#define		CODE_MOTOR_STOP			0x0003		/* ָ�����ͣ��			*/
#define		CODE_MOTOR_STOP_FREE	0x0004		/* ָ�����ͣ��			*/		


/********************************************************************************************/
/*E2000����ֵ ���Ʋ�����															 */
/********************************************************************************************/
typedef struct	_stcE2000Ctrl   
{
	short 			node;		// E2000ͨѶ��ַ
	unsigned short	speed;	   	// ����ٶ�
}sE2000Ctrl;		
		

extern	sE2000Ctrl		gE2000Ctrl;						// ���������

extern	void	InitE2000Modbus(void)  ;				// ��ʼ�����
extern	short	SetE2000Speed(short node,short speed);	// �趨���ת��


		
#ifdef __cplusplus
    }
#endif

#endif
