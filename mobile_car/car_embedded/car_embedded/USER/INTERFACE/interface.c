#include "interface.h"
#include "beep.h" 
#include "can1.h"
#include "can2.h"
#include "led.h"
#include "common.h"
#include "string.h"
#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "usart1.h"
#include "VehicleControl.h"
#include "pstwo.h"

uint16_t ID1 = 0x0585;  //IMU���ٶȼ�������ٶ�
int8_t sensor1_buf[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
extern u16 Handkey;
//Vehicle three-axis target moving speed, unit: m/s
//С������Ŀ���˶��ٶȣ���λ��m/s

/**/

/* '<Root>/v_out' */
static real_T v_out;

/* '<Root>/w_out' */
static real_T w_out;

/* '<Root>/yaw' */
static real_T yaw;

static uint16_T KeyValue = 0U;
/***************************************************����**********************************************************/

/*CAN�жϽ������Գ��ؿ��������͹����ı�������*/ 
uint8_t buf[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint16_t ID;

void CAN1_IRQ_CallBack(void)
{
	LED2 =! LED2;
	ID = CAN1_ReceiveOnMsg(buf);

	if(ID==ID1)
	{
		memcpy(&sensor1_buf,&buf, 8);
	}

}
/**/

/*************************************************����main����*****************************/
u8 txbuf[8];
static short Move_X=0, Move_Y=0, Move_Z=0;


/* '<Root>/v_out' */
static real_T v_out;

/* '<Root>/w_out' */
static real_T w_out;

/* '<Root>/yaw' */
static double yaw;

void MainFCN(void)
{
//	/* Step the model */
	KeyValue = Handkey;
	VehicelControl_step(&v_out, &w_out, sensor1_buf, &yaw, KeyValue);

	//���ײ������巢���ٶ�ָ���λ��mm/s
	Move_X = (short)v_out;
	Move_Y = 0;
	Move_Z = (short)w_out;

	//���͵�������ʮ���Ƶ�
	txbuf[0]=Move_X >> 8;  //X���ٶ�
	txbuf[1]=Move_X;  
	txbuf[2]=Move_Y >> 8;	 //Y���ٶ�
	txbuf[3]=Move_Y;		
	txbuf[4]=Move_Z >> 8;  //Z���ٶ�
	txbuf[5]=Move_Z;  
	txbuf[6]=0;  //Ԥ��λ
	txbuf[7]=0;	 //Ԥ��λ
	CAN1_Send_Msg(0x181,txbuf,8);//CAN����
	

	
//	printf("w_out: %.2f\n",w_out/3.14159*180/1000);//degree/s
//	printf("yaw: %.2lf\n",yaw);//degree
}


/*************************************************��ʱ���жϷ�����*****************************/

void TimerIQR(void)
{

}
/**/

