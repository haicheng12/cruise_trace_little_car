#include "sys.h"

  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
轮子1：（左）
PWMA-->PA8
AIN1-->PB14
AIN2-->PB15
A相-->PA1
B相-->PA0

轮子2：（右）
PWMB--PA11
BIN1-->PB12
BIN2-->PB13
A相-->PB6
B相-->PB7

**************************************************************************/
u8 Flag_Stop=1;            //停止标志位
int Encoder1;               //编码器的脉冲计数
int Encoder2;               //编码器的脉冲计数
int Moto1;                 //电机PWM变量 应是Motor的 向Moto致敬	
int Moto2;

//u8 delay_50,delay_flag;

int main(void)
{
	
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);                 //延时初始化
	uart_init(72,115200);           //初始化串口1
	MiniBalance_PWM_Init(7199,0);   //初始化PWM 10KHZ 高频可以防止电机低频时的尖叫声
	Encoder_Init_TIM2();            //初始化编码器1
	Encoder_Init_TIM4();            //初始化编码器2 
  Timer3_Init(99,7199);           //10MS进一次中断服务函数，中断服务函数在control.c
	NVIC_Configuration();																//优先级配置
	CAN1_Configuration();                               //CAN1初始化

	while(1)
	{
			printf("轮子1的速度为%d，轮子2的速度为%d\r\n",Encoder1,Encoder2);	
	}
	
	
}




