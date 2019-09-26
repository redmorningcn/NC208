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
#include  	"CrcCheck.h"


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
	
		val =(short)SW_INT16U(val);						// �ߵ�λ����
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
		
		g_SensorSwitchTable[i].motor = (char)motornum;

		if(i%4 == 0) {												// ÿ4̨������������
			motornum++;
		}
		
		//M2001CoidChange( i + 1 , 0 );								// ������ͨ���л�״̬����	
	}
	
	g_SensorChangeCtl.SensorNum 	= 0;							// ��ʼ��������������
	g_SensorChangeCtl.lstSensorNum  = 0;
}

#define		DELAY_US_E2000   	(2000000)
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

//	if(sensornum == g_SensorChangeCtl.SensorNum )  // ������ͨ����ͬ�����л�
//		return len;
	
	//���������Ϊ255�����д�����ͨ���л���ɣ����ٽ����л���
	if( sensornum  == 255){
		val = 0;
		for(node = 1;node < 18;node++){
			len 	= M2001CoidChange( node , val );		//ͨ���л�
			if(	len	== 0) {	   //ͨ���л�ʧ��
				Delay_Nus(DELAY_US_E2000);
			}			
		}
		return len;
	}
	Delay_Nus(DELAY_US_E2000);
	
	if(g_SensorSwitchTable[sensornum].flg != 1 )   // ������δ���ã����л�
		return len;
	
	g_SensorChangeCtl.SensorNum = sensornum;
	if(sensornum > MAX_SENSOR_NUM ) //��������ŷǷ�
	{
		return len;
	}
	
//	for(short tmp = 1; tmp < 20;tmp++){
//		val = 0;
//		M2001CoidChange( tmp , val );		//ͨ���л�
//		Delay_Nus(10);
//	}
	
	//���ϴα�ŵĴ�����ͨ���л�״̬ȡ��
	
	
	Num 	= g_SensorChangeCtl.lstSensorNum;
	if( Num != g_SensorChangeCtl.SensorNum)				//�����ͬ�����л�
	{
		node	= g_SensorSwitchTable[Num].M2001[0].node;
		val		= 0;									//��ͨ��ֵ����
	
		len 	= M2001CoidChange( node , val );		//ͨ���л�
		if(	len	== 0) {	   //ͨ���л�ʧ��
			Delay_Nus(DELAY_US_E2000);
		}
		len 	= M2001CoidChange( node , val );		//ͨ���л����ٴιر�	190926
		Delay_Nus(DELAY_US_E2000);
		//
		node	= g_SensorSwitchTable[Num].M2001[1].node;
		val		= 0;
		if(g_SensorSwitchTable[Num].M2001[1].val && node) {
			len 	= M2001CoidChange( node , val );	//ͨ���л�
			if(	len	== 0) {	   //ͨ���л�ʧ��
				Delay_Nus(DELAY_US_E2000);
			}
			len 	= M2001CoidChange( node , val );	//ͨ���л��� �ٴιر�   190926       
		}
		Delay_Nus(DELAY_US_E2000);
	}
	
	Delay_Nus(DELAY_US_E2000);

	//�л������α�ŵĴ�����
	Num 	= g_SensorChangeCtl.SensorNum;

	if( Num )
	{
		node	= g_SensorSwitchTable[Num].M2001[0].node;	          
		val  	= g_SensorSwitchTable[Num].M2001[0].val;
		
		len 	= M2001CoidChange( node , val );		//ͨ���л�    	Delay_Nus(DELAY_US_E2000);
		
		if(	len	== 0) {	   //ͨ���л�ʧ��
			//return len;
			Delay_Nus(DELAY_US_E2000);
		}
		Delay_Nus(DELAY_US_E2000);
		len 	= M2001CoidChange( node , val );		//ͨ���л����ٴδ� 190926
		
		node	= g_SensorSwitchTable[Num].M2001[1].node;	
		val  	= g_SensorSwitchTable[Num].M2001[1].val;
		
		if( val && node ) {
			len 	= M2001CoidChange( node , val );		//ͨ���л�

			if(	len	== 0) {	   //ͨ���л�ʧ��
				Delay_Nus(DELAY_US_E2000);
				//return len;
			}	
			Delay_Nus(DELAY_US_E2000);
			len 	= M2001CoidChange( node , val );		//ͨ���л�
		}
	}
	//�ı��л�״̬
	g_SensorChangeCtl.lstSensorNum = g_SensorChangeCtl.SensorNum; 
	
	return len;
}



