#include "sys.h"

  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
����1������
PWMA-->PA8
AIN1-->PB14
AIN2-->PB15
A��-->PA1
B��-->PA0

����2�����ң�
PWMB--PA11
BIN1-->PB12
BIN2-->PB13
A��-->PB6
B��-->PB7

**************************************************************************/
u8 Flag_Stop=1;            //ֹͣ��־λ
int Encoder1;               //���������������
int Encoder2;               //���������������
int Moto1;                 //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Moto2;

//u8 delay_50,delay_flag;

int main(void)
{
	
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ��
	uart_init(72,115200);           //��ʼ������1
	MiniBalance_PWM_Init(7199,0);   //��ʼ��PWM 10KHZ ��Ƶ���Է�ֹ�����Ƶʱ�ļ����
	Encoder_Init_TIM2();            //��ʼ��������1
	Encoder_Init_TIM4();            //��ʼ��������2 
  Timer3_Init(99,7199);           //10MS��һ���жϷ��������жϷ�������control.c
	NVIC_Configuration();																//���ȼ�����
	CAN1_Configuration();                               //CAN1��ʼ��

	while(1)
	{
			printf("����1���ٶ�Ϊ%d������2���ٶ�Ϊ%d\r\n",Encoder1,Encoder2);	
	}
	
	
}




