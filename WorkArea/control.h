#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
int TIM1_UP_IRQHandler(void); 
void Set_Pwm1(int moto1);
void Set_Pwm2(int moto2);
void Xianfu_Pwm1(void);
void Xianfu_Pwm2(void);
int myabs(int a);
int Incremental_PI1 (int Encoder1,int Target1);
int Incremental_PI2 (int Encoder2,int Target2);
#endif
