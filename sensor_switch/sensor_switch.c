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
#include  	"sensor_switch.h"
#include  	"uirbsp_mb_poll.h"
#include  	"global.h"
#include  	"E2000Motor.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//
sSensorSwitchTable	g_SensorSwitchTable[ MAX_SENSOR_NUM ];		   	// �������л���

stcSensorChangeCtl	g_SensorChangeCtl;								// ������ͨ���л�������

/********************************************************************************************/
//local
/********************************************************************************************/

/********************************************************************************************/
/* �л�������ͨ��*/  				
//redmorningcn  190817
//ͨ���ڵ�ź�ֵ��M2001���ƶ�Ӧ�ļ̵�����
/********************************************************************************************/
short	M2001CoidChange(short node,short val) 
{
	short 	len = 0;

	if(node)  {
		//��ʼ�� modbus���ṹ
		gsMBPoll.codeflg  = CODE_COIL_OP;	// ��Ȧ������
		gsMBPoll.writeflg = 1;				// д������
	
		gsMBPoll.node	= node; 			 
		gsMBPoll.addr	= 0;
	
		val =SW_INT16U(val);						// �ߵ�λ����
		memcpy(gsMBPoll.buf,&val,sizeof(val)); 	
		gsMBPoll.len	= 16;	

		len = MB_PollOperate();	
	}
	return len;
}

/********************************************************************************************/
/* �������л���ʼ��������ҪΪ��ʼ�����л���*/  				
//redmorningcn  190817
/********************************************************************************************/
void	InitSensorSwitch(void)
{
	short	i,j;
	short	m;
	
	short	sensor_ch = 6;
	short	m2001_io  = 16;
	short	tmp = 1;
	short	mod = 0;
	short	motornum =  E2000_START_NODE;		// E2000��ʼ��ַ

	for(i = 0; i<MAX_SENSOR_NUM ;i++)
	{
		g_SensorSwitchTable[i].num 				= (char)(i + 1);
		
		m 	= (i + 1) * sensor_ch / m2001_io;						// ��ÿ��������6��ͨ����ÿ��������16��ͨ����������Ƶ�ַ
		mod = (i + 1) * sensor_ch % m2001_io; 
		if(mod > (sensor_ch -1) ){									// ֻ��Ҫ�����������Ϳ�����ɲ���
			g_SensorSwitchTable[i].M2001[0].node	= m + 1;
			
			tmp = (short)(0x01 << (mod - sensor_ch));
			g_SensorSwitchTable[i].M2001[0].val     = 0;			// ����ֵ
			for(j = 0;j < sensor_ch;j++){
				g_SensorSwitchTable[i].M2001[0].val+= tmp;
				tmp = (short)(tmp << 1);
			}
			
			g_SensorSwitchTable[i].M2001[1].node	= 0;			// �������������Ϊ0
			g_SensorSwitchTable[i].M2001[1].val		= 0;  
		}else{
			g_SensorSwitchTable[i].M2001[0].node	= m;
			
			tmp =(short)( 1 << ( mod + m2001_io - sensor_ch ));
			g_SensorSwitchTable[i].M2001[0].val     = 0;			// ����ֵ
			for(j = ( mod + m2001_io - sensor_ch );j < m2001_io ; j++){
				g_SensorSwitchTable[i].M2001[0].val += tmp;
				tmp = (short)(tmp << 1);
			}			
			
			if(mod){
				g_SensorSwitchTable[i].M2001[1].node	= m + 1;
			}else{
				g_SensorSwitchTable[i].M2001[1].node	= 0;
			}
				
			tmp = 1 << 0;
			g_SensorSwitchTable[i].M2001[1].val     = 0;			// ����ֵ
			for(j = 0;j < mod ; j++){
				g_SensorSwitchTable[i].M2001[1].val += tmp;
				tmp = (short)(tmp << 1);
			}
		}
		
		g_SensorSwitchTable[i].motor = motornum;

		if(i%4 == 0) {												// ÿ4̨������������
			motornum++;
		}
		
		//M2001CoidChange( i + 1 , 0 );								// ������ͨ���л�״̬����	
	}
	
	g_SensorChangeCtl.SensorNum 	= 0;							// ��ʼ��������������
	g_SensorChangeCtl.lstSensorNum  = 0;
}


/********************************************************************************************/
/* �л�������ͨ��*/  				
//redmorningcn  190817
//���ݴ������ı�ţ����л�������Ӧ�������ĵ�ַ��ֵ��
//ͨ�����ڣ������ϴβ����Ĵ�������ַ���㣬���˴δ�����ѡͨ��
/********************************************************************************************/
short	SensorChange(short sensornum)
{
	short 	Num;
	short 	len = 0;
	short	node;
	short  	val;

	
	if(sensornum == g_SensorChangeCtl.SensorNum )  //������ͨ����ͬ�����л�
		return len;
	
	g_SensorChangeCtl.SensorNum = sensornum;
	if(sensornum > MAX_SENSOR_NUM ) //��������ŷǷ�
	{
		return len;
	}
	//���ϴα�ŵĴ�����ͨ���л�״̬ȡ��
	Num 	= g_SensorChangeCtl.lstSensorNum;
	node	= g_SensorSwitchTable[Num].M2001[0].node;
	val		= 0;									//��ͨ��ֵ����
	
	len 	= M2001CoidChange( node , val );		//ͨ���л�
	if(	len	== 0) {	   //ͨ���л�ʧ��
		return len;
	}
	
	node	= g_SensorSwitchTable[Num].M2001[1].node;
	val		= 0;
	len 	= M2001CoidChange( node , val );		//ͨ���л�
	
	//�л������α�ŵĴ�����
	Num 	= g_SensorChangeCtl.SensorNum;
	node	= g_SensorSwitchTable[Num].M2001[0].node;	
	val  	= g_SensorSwitchTable[Num].M2001[0].val;
	len 	= M2001CoidChange( node , val );		//ͨ���л�
	if(	len	 == 0) {	   //ͨ���л�ʧ��
		return len;
	}
	
	node	= g_SensorSwitchTable[Num].M2001[1].node;	
	val  	= g_SensorSwitchTable[Num].M2001[1].val;
	len 	= M2001CoidChange( node , val );		//ͨ���л�
	
	//�ı��л�״̬
	g_SensorChangeCtl.lstSensorNum = g_SensorChangeCtl.SensorNum; 
	
	return len;
}



