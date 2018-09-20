#include "control.h"	
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
extern PS_TYPE PS_DEF;													//光电传感器变量

int Target_velocity1;  //设定速度控制的目标速度为50个脉冲每10ms
int Target_velocity2;  //设定速度控制的目标速度为50个脉冲每10ms

u16 last_led;
						
int TIM3_IRQHandler(void)  
{    
	if(TIM3->SR&0X0001)//10ms定时中断
	{   
		  TIM3->SR&=~(1<<0);                              //===清除定时器1中断标志位		 
		  Encoder1=Read_Encoder(2);                       //===读取编码器的值，M法测速，输出为每10ms的脉冲数
		  Encoder2=Read_Encoder(4);                       //===读取编码器的值，M法测速，输出为每10ms的脉冲数
		  //整体思想：1个灯，2个灯，3个灯的情况巡线；4个灯，5个灯的情况控制左右转；其他特殊情况另外判断
		  switch(PS_DEF.Front.DATA_16)
			{
				//1个灯
				case 0x0001://1 
						Moto1=Incremental_PI1(Encoder1,-20);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,20);          //===速度PI控制器
				  break;
				case 0x0040://7
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				case 0x0080://8
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				case 0x0100://9
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				case 0x4000://15
					  Moto1=Incremental_PI1(Encoder1,20);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,-20);          //===速度PI控制器
				  break;
				//2个灯
				case 0x003://1 2
					  Moto1=Incremental_PI1(Encoder1,-20);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,20);          //===速度PI控制器
				  break;
				case 0x0030://5 6
					  Moto1=Incremental_PI1(Encoder1,-17);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,17);          //===速度PI控制器
				  break;
				case 0x0060://6 7
					  Moto1=Incremental_PI1(Encoder1,-15);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,15);          //===速度PI控制器
				  break;
				case 0x00C0://7 8
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				case 0x0180://8 9
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				case 0x0300://9 10
					  Moto1=Incremental_PI1(Encoder1,15);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,-15);          //===速度PI控制器
				  break;
				case 0x0600://10 11
					  Moto1=Incremental_PI1(Encoder1,17);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,-17);          //===速度PI控制器
				  break;
				case 0x6000://14 15
					  Moto1=Incremental_PI1(Encoder1,20);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,-20);          //===速度PI控制器
				  break;
				//3个灯
				case 0x01C0://7 8 9
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
				
				case 0x0000://出界的情况
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,-10);          //===速度PI控制器
				    if(last_led==0x0001)//右边出界
						{
						   Moto1=Incremental_PI1(Encoder1,-15);         //===速度PI控制器
  		         Moto2=Incremental_PI2(Encoder2,15);          //===速度PI控制器
						}
						if(last_led==0x4000)//左边出界
						{
						   Moto1=Incremental_PI1(Encoder1,15);         //===速度PI控制器
  		         Moto2=Incremental_PI2(Encoder2,-15);          //===速度PI控制器
						}
				  break;
				default://其余的情况
					  Moto1=Incremental_PI1(Encoder1,10);         //===速度PI控制器
  		      Moto2=Incremental_PI2(Encoder2,10);          //===速度PI控制器
				  break;
			}	
//		  Moto1=Incremental_PI1(Encoder1,Target_velocity1);         //===速度PI控制器
//		  Moto2=Incremental_PI2(Encoder2,Target_velocity2);         //===速度PI控制器
	  	Xianfu_Pwm1();                                            //===PWM限幅
		  Xianfu_Pwm2();                                            //===PWM限幅
    	Set_Pwm1(Moto1);                                          //===赋值给PWM寄存器  
		  Set_Pwm2(Moto2);                                          //===赋值给PWM寄存器  
	}       	
	 return 0;	  
} 

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm1(int moto1)
{
			if(moto1>0)			AIN2=1,			AIN1=0;
			else 	          AIN2=0,			AIN1=1;
			PWMA=myabs(moto1);
}

void Set_Pwm2(int moto2)
{
			if(moto2>0)			BIN2=1,			BIN1=0;
			else 	          BIN2=0,			BIN1=1;
			PWMB=myabs(moto2);
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm1(void)
{	
	  int Amplitude=7100;    //===PWM满幅是7200 限制在7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

void Xianfu_Pwm2(void)
{	
	  int Amplitude=7100;    //===PWM满幅是7200 限制在7100
    if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;	
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI1 (int Encoder1,int Target1)
{ 	
   float Kp1=20,Ki1=30;	
	 static int Bias1,Pwm1,Last_bias1;
	 Bias1=Encoder1-Target1;                //计算偏差
	 Pwm1+=Kp1*(Bias1-Last_bias1)+Ki1*Bias1;//增量式PI控制器
	 Last_bias1=Bias1;	                    //保存上一次偏差 
	 return Pwm1;                           //增量输出
}

int Incremental_PI2 (int Encoder2,int Target2)
{ 	
   float Kp2=20,Ki2=30;	
	 static int Bias2,Pwm2,Last_bias2;
	 Bias2=Encoder2-Target2;                //计算偏差
	 Pwm2+=Kp2*(Bias2-Last_bias2)+Ki2*Bias2;//增量式PI控制器
	 Last_bias2=Bias2;	                    //保存上一次偏差 
	 return Pwm2;                           //增量输出
}
