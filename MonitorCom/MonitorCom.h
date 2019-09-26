#ifndef  _MonitorCom_h_
#define  _MonitorCom_h_

/**************************************************************************
������ͨѶ���ơ�
monitor���ͣ���ʼ 55DD  + �����ţ� 1byte + ��������� 1byte + ת�� 4byte  + У��� 1byte
���ճɹ�   ����ʼ 55DD  + FF + ״̬ 1byte + У��� 1byte��
redmorningcn 190820
**************************************************************************/
#include <userint.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define		MONITOR_COMM_HEAD		0x55DD    		/* ����ͨѶ��ʼ */
#define		MONITOR_REPLY_FLG		0xFF			/* ͨѶӦ���ʶ */	
#define		MONITOR_REPLY_OK		0x01			/* ͨѶӦ���ʶ */	
#define		MONITOR_REC_LEN			9				/* ���յ�֡��   */	
#define		MONITOR_SEND_LEN		5				/* ���յ�֡��   */	
		
#define		ADDR_MOTOR_NUM			2				/* ������λ�� 	*/
#define		ADDR_SENSOR_NUM			3				/* ���������λ��	*/
#define		ADDR_ROTATE				4				/* ת��λ��			*/	
		
/********************************************************************************************/
/* �Ͳ���̨����ͨѶ��֡��ʽ															 */
/********************************************************************************************/
typedef struct	_stcRecMonitor   
{
	short 	head;		//����֡ͷ��
	char	motorNum;	//������
	char	sensorNum;	//���������
	int		rotate;		//��ת�ٶ�
	char	sumcheck;	//У���
}sRecMonitor;

/********************************************************************************************/
/* �Ͳ���̨����ͨѶ��֡��ʽ															 */
/********************************************************************************************/
typedef struct	_stcSendMonitor   
{
	short 	head;		//����֡ͷ��
	char	flg	;		//�ָ���ʶ
	char	sta;		//������
	char	sumcheck;	//У���
}sSendMonitor;


/********************************************************************************************/
/*  ���ݽṹ														 */
/********************************************************************************************/
typedef struct	_stcMonitorInfo
{
	unsigned char	sensorNum;			// ���������
	unsigned char	motorNum;			// ������
	unsigned char	tmp;
	unsigned char	MonitorRecFlg:1;	// ����̨���ճɹ���ʶ
	unsigned char	MonitorSendEnFlg:1;	// ����̨���ͳɹ���ʶ
	unsigned char	E2000SetFlg:1;		// ������óɹ�ָ��
	unsigned char	M2001SetFlg:1;		// �������ģ��
	unsigned char	tmpFlg:4;			// ����
	unsigned int    rotate;				// ת��
}sMonitorInfo;


extern	void	MonitorComOperate(void);
extern	void	SetE2000Speed(short node,short speed);  

#ifdef __cplusplus
    }
#endif

#endif
