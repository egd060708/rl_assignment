#include "can1.h"
#include "led.h"
#include "interface.h"


/*********************************************************************************
*********************�������� STM32F407Ӧ�ÿ�����(���ݰ�)*************************
**********************************************************************************
* �ļ�����: can1.c                                                               *
* �ļ�������can�����ļ�                                                          *
* �������ڣ�2018.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����                                                                     * 
**********************************************************************************�B
*********************************************************************************/


/****************************************************************************
* ��    ��: u8 CAN1_Mode_Init(u8 mode)
* ��    �ܣ�CAN��ʼ��
* ��ڲ�����mode:CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
* ���ز�����0,�ɹ�;
           	����,ʧ��;
* ˵    ����       
****************************************************************************/	
u8 CAN1_Mode_Init(u8 mode)
{
  	GPIO_InitTypeDef GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
#if CAN1_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif
    //ʹ�����ʱ��
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��PORTBʱ��	                   											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	  //���Ÿ���ӳ������
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART=ENABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ����
	 
/***************************************************************************************/		
    //����can����ģʽ	
  	CAN_InitStructure.CAN_Mode= mode;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq; //ʱ���1��ʱ�䵥Ԫ.  Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=CAN_BS2_6tq; //ʱ���2��ʱ�䵥Ԫ.  Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=3;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
/***************************************************************************************/			
  	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��

//		uint32_t StdId1 =0x0101;                       //�������4����׼CAN ID��Ϊ����  
//    uint32_t StdId2 =0x0102;  
//    uint32_t StdId3 =0x0103;  
//    uint32_t StdId4 =0x0104; 

//		//���ù�����
// 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
//  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList; 
//  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; //32λ 
//  	CAN_FilterInitStructure.CAN_FilterIdHigh=StdId1<<5;
//  	CAN_FilterInitStructure.CAN_FilterIdLow=StdId2<<5;
//  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=StdId3<<5;
//  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=StdId4<<5;
//   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
//  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
//  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
#if CAN1_RX0_INT_ENABLE
	
	  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
  
  	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
}   
 
#if CAN1_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����			    
void CAN1_RX0_IRQHandler(void)
{
  	CanRxMsg RxMessage;
	  CAN1_IRQ_CallBack();
    CAN_Receive(CAN1, 0, &RxMessage);
}
#endif

/****************************************************************************
* ��    ��: u8 CAN1_Send_Msg(u8* msg,u8 len)
* ��    �ܣ�can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)
* ��ڲ�����len:���ݳ���(���Ϊ8)				     
            msg:����ָ��,���Ϊ8���ֽ�.
* ���ز�����0,�ɹ�;
           	����,ʧ��;
* ˵    ����       
****************************************************************************/		
u8 CAN1_Send_Msg(u16 id,u8* msg,u8 len)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		   // ʹ����չ��ʶ��
  TxMessage.RTR=0;		   // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=len;	   // ������֡��Ϣ
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];				 // ��һ֡��Ϣ          
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;		
}

/****************************************************************************
* ��    ��: u8 CAN1_Receive_Msg(u8 *buf)
* ��    �ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;	 			     
* ���ز�����0,�����ݱ��յ�;
    		    ����,���յ����ݳ���;
* ˵    ����       
****************************************************************************/	
u8 CAN1_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<RxMessage.DLC;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}






/****************************************************************************
* ��    ��: u8 CAN1_Receive_Msg(u8 *buf)
* ��    �ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;	 			     
* ���ز�����0,�����ݱ��յ�;
    		    ����,���յ����ݳ���;
* ˵    ����       
****************************************************************************/	
u16 CAN1_ReceiveOnMsg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<RxMessage.DLC;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.StdId;	
}







