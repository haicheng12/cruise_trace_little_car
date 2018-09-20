#include "control.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
extern PS_TYPE PS_DEF;													//��紫��������

int Target_velocity1;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms
int Target_velocity2;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms

u16 last_led;
						
int TIM3_IRQHandler(void)  
{    
	if(TIM3->SR&0X0001)//10ms��ʱ�ж�
	{   
		  TIM3->SR&=~(1<<0);                              //===�����ʱ��1�жϱ�־λ		 
		  Encoder1=Read_Encoder(2);                       //===��ȡ��������ֵ��M�����٣����Ϊÿ10ms��������
		  Encoder2=Read_Encoder(4);                       //===��ȡ��������ֵ��M�����٣����Ϊÿ10ms��������
		  //����˼�룺1���ƣ�2���ƣ�3���Ƶ����Ѳ�ߣ�4���ƣ�5���Ƶ������������ת������������������ж�
		  switch(PS_DEF.Front.DATA_16)
			{
				//1����
				case 0x0001://1 
						Moto1=Incremental_PI1(Encoder1,-20);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,20);          //===�ٶ�PI������
				  break;
				case 0x0040://7
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				case 0x0080://8
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				case 0x0100://9
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				case 0x4000://15
					  Moto1=Incremental_PI1(Encoder1,20);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,-20);          //===�ٶ�PI������
				  break;
				//2����
				case 0x003://1 2
					  Moto1=Incremental_PI1(Encoder1,-20);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,20);          //===�ٶ�PI������
				  break;
				case 0x0030://5 6
					  Moto1=Incremental_PI1(Encoder1,-17);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,17);          //===�ٶ�PI������
				  break;
				case 0x0060://6 7
					  Moto1=Incremental_PI1(Encoder1,-15);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,15);          //===�ٶ�PI������
				  break;
				case 0x00C0://7 8
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				case 0x0180://8 9
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				case 0x0300://9 10
					  Moto1=Incremental_PI1(Encoder1,15);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,-15);          //===�ٶ�PI������
				  break;
				case 0x0600://10 11
					  Moto1=Incremental_PI1(Encoder1,17);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,-17);          //===�ٶ�PI������
				  break;
				case 0x6000://14 15
					  Moto1=Incremental_PI1(Encoder1,20);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,-20);          //===�ٶ�PI������
				  break;
				//3����
				case 0x01C0://7 8 9
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
				
				case 0x0000://��������
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,-10);          //===�ٶ�PI������
				    if(last_led==0x0001)//�ұ߳���
						{
						   Moto1=Incremental_PI1(Encoder1,-15);         //===�ٶ�PI������
  		         Moto2=Incremental_PI2(Encoder2,15);          //===�ٶ�PI������
						}
						if(last_led==0x4000)//��߳���
						{
						   Moto1=Incremental_PI1(Encoder1,15);         //===�ٶ�PI������
  		         Moto2=Incremental_PI2(Encoder2,-15);          //===�ٶ�PI������
						}
				  break;
				default://��������
					  Moto1=Incremental_PI1(Encoder1,10);         //===�ٶ�PI������
  		      Moto2=Incremental_PI2(Encoder2,10);          //===�ٶ�PI������
				  break;
			}	
//		  Moto1=Incremental_PI1(Encoder1,Target_velocity1);         //===�ٶ�PI������
//		  Moto2=Incremental_PI2(Encoder2,Target_velocity2);         //===�ٶ�PI������
	  	Xianfu_Pwm1();                                            //===PWM�޷�
		  Xianfu_Pwm2();                                            //===PWM�޷�
    	Set_Pwm1(Moto1);                                          //===��ֵ��PWM�Ĵ���  
		  Set_Pwm2(Moto2);                                          //===��ֵ��PWM�Ĵ���  
	}       	
	 return 0;	  
} 

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
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
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm1(void)
{	
	  int Amplitude=7100;    //===PWM������7200 ������7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

void Xianfu_Pwm2(void)
{	
	  int Amplitude=7100;    //===PWM������7200 ������7100
    if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI1 (int Encoder1,int Target1)
{ 	
   float Kp1=20,Ki1=30;	
	 static int Bias1,Pwm1,Last_bias1;
	 Bias1=Encoder1-Target1;                //����ƫ��
	 Pwm1+=Kp1*(Bias1-Last_bias1)+Ki1*Bias1;//����ʽPI������
	 Last_bias1=Bias1;	                    //������һ��ƫ�� 
	 return Pwm1;                           //�������
}

int Incremental_PI2 (int Encoder2,int Target2)
{ 	
   float Kp2=20,Ki2=30;	
	 static int Bias2,Pwm2,Last_bias2;
	 Bias2=Encoder2-Target2;                //����ƫ��
	 Pwm2+=Kp2*(Bias2-Last_bias2)+Ki2*Bias2;//����ʽPI������
	 Last_bias2=Bias2;	                    //������һ��ƫ�� 
	 return Pwm2;                           //�������
}
