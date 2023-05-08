#include "exti.h"
#include "timer.h"
#include "sys.h"
#include "st178.h"
#include "moto.h"
#include "ui.h"

char cunchu[4] = {0, 0, 0, 0};
char z_cha = 0, y_cha = 0, q_cha = 0, h_cha = 0;
u16 count_fz = 0;
u8 fz_flag = 0;

u16 bb12 = 70;
u16 bb13 = 70;
u16 bb14 = 150;

u16 b12 = 0;
u16 b13 = 0;
u16 b14 = 0;

//�ư��� b12С->��->��ʱ��
//�ư��� b13С->��->˳ʱ��

u16 dongzuo[][3] =
	{
		{350, 100, 295}, //��λ0
		
		{252, 395, 200}, //����ץ��1
		
		{252, 395, 295}, //����ץ��2
		{250, 310, 295}, //����3
		{350, 100, 295}, //���4
		
		{380, 460, 295}, //���ַŽ�5
		{380, 460, 295}, //���ַŽ�56
		{380, 460, 295}, //���ַŽ�57
		{380, 460, 200}, //���ַ���68
		{350, 100, 200}, //��λ79
		
		{163, 310, 200}, //����ץǰ��8
		
		{163, 310, 295}, //����ץ��9
		{350, 100, 295}, //���10
		
		{380, 520, 295}, //���ַŽ�11
		{380, 520, 295}, //���ַŽ�11
		{380, 520, 295}, //���ַŽ�11
		{380, 520, 200}, //���ַ���12
		{350, 100, 200}//��λ13
};
u16 dongshuzu[][2] = {{0, 0},{1,1}, {2, 4}, {5, 9}, {10,10},{11, 12}, {13, 17}}; // 0��λ0 1��1��3-4����ץ(9cm)2 5-7���ַ�3 8-8��4��10-11����ץ(11.5cm)5 12-15���ַ�6
void fzopen()
{
	cunchu[0] = zuo_sum;
	cunchu[1] = you_sum;
	cunchu[2] = qian_sum;
	cunchu[3] = hou_sum;

	Init_TIM6(99, 7199);
}

void fzclose()
{
	TIM_Cmd(TIM6, DISABLE);
}

void Init_TIM6(u16 arr, u16 psc)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);				//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;			  // TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);							  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM6, ENABLE);
}

void TIM6_IRQHandler(void)
{
	// 10usһ��
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		b12 %= 2000;
		b12++;
		if (b12 <= bb12)
			PBout(12) = 1;
		else
			PBout(12) = 0;

		b13 %= 2000;
		b13++;
		if (b13 <= bb13)
			PBout(13) = 1;
		else
			PBout(13) = 0;

		b14 %= 2000;
		b14++;
		if (b14 <= bb14)
			PBout(14) = 1;
		else
			PBout(14) = 0;
	}

	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	//	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	//	{
	//		z_cha=zuo_sum-cunchu[0];
	//		if(z_cha<0)
	//			z_cha=-z_cha;
	//		y_cha=you_sum-cunchu[1];
	//		if(y_cha<0)
	//			y_cha=-y_cha;
	//		q_cha=qian_sum-cunchu[2];
	//		if(q_cha<0)
	//			q_cha=-q_cha;
	//		h_cha=hou_sum-cunchu[3];
	//		if(h_cha<0)
	//			h_cha=-h_cha;
	//		if(q_cha>0||h_cha>0 ||z_cha>0||y_cha>0)
	//		{
	//			count_fz=0;
	//			cunchu[0]=zuo_sum;
	//			cunchu[1]=you_sum;
	//			cunchu[2]=qian_sum;
	//			cunchu[3]=hou_sum;
	//		}
	//		else
	//		{
	//			count_fz++;
	//		}
	//		if(count_fz>=300)
	//		{
	//			fz_flag=1;
	//			stop();
	//			count_fz=0;
	//		}
	//
	//		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	//	}
}
void zuodongzuo(u8 xuhao, u8 yanshi)
{
	int iii;
	int iiii;
	if (xuhao < 100)
	{
		TIM_Cmd(TIM6, ENABLE);
		for (iii = dongshuzu[xuhao][0]; iii <= dongshuzu[xuhao][1]; iii++)
		{
			delay_ms(10);
			bb12 = dongzuo[iii][0];
			delay_ms(10);
			bb13 = dongzuo[iii][1];
			delay_ms(10);
			bb14 = dongzuo[iii][2];
			for (iiii = 0; iiii < yanshi*4; iiii++)
				delay_ms(100);
		}
		delay_ms(600);
//		TIM_Cmd(TIM6, DISABLE);
	}
	else
	{
		TIM_Cmd(TIM1, ENABLE);
		if (xuhao == 100) //�ر�
		{
				TIM_SetCompare2(TIM1, 1660); //����PE11   20000Ϊ��pwm   ��1����߶��  ��С->���
				delay_ms(15);	
				TIM_SetCompare3(TIM1, 1320); //�Ҷ��PE13               ��3���ұ߶��1530  ��С->��С
				delay_ms(10);
//			TIM_SetCompare2(TIM1, 1560); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(5);
//			TIM_SetCompare3(TIM1, 1530); //�Ҷ��PE13               ��3���ұ߶��1530
//			delay_ms(10);
		}
		else if (xuhao == 101) //������1��
		{
//			  TIM_SetCompare2(TIM1, 1550); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//				delay_ms(5);	
//				TIM_SetCompare3(TIM1, 1530); //�Ҷ��PE13               ��3���ұ߶��1530
//				delay_ms(10);
			TIM_SetCompare2(TIM1, 1170); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 1790); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
		}
		else if (xuhao == 102) //����
		{
				TIM_SetCompare2(TIM1, 800);
				delay_ms(2);
				TIM_SetCompare3(TIM1, 2100); 
				delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 103) //��2���
		{
				TIM_SetCompare2(TIM1, 500);
				delay_ms(2);
				TIM_SetCompare3(TIM1, 2500); 
				delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 104) //ֱ��
		{
			TIM_SetCompare2(TIM1, 870); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2000); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 105) //�뿪
		{
			TIM_SetCompare2(TIM1, 500); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2100); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 106) //�Ҵ�ֱ
		{
			TIM_SetCompare2(TIM1, 500); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2000); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 107) //�뿪
		{
			TIM_SetCompare2(TIM1, 870); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2500); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 108) //��ֱ
		{
			TIM_SetCompare2(TIM1, 1000); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2500); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		else if (xuhao == 109) //�򿪽���
		{
			TIM_SetCompare2(TIM1, 650); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
			delay_ms(5);
			TIM_SetCompare3(TIM1, 2300); //�Ҷ��PE13               ��3���ұ߶��1530
			delay_ms(10);
//			TIM_SetCompare2(TIM1, 850); //����PE11   20000Ϊ��pwm   ��1����߶��  1560
//			delay_ms(10);
//			TIM_SetCompare3(TIM1, 2250); //�Ҷ��PE13               ��3���ұ߶��
		}
		for (iiii = 0; iiii < yanshi*4; iiii++)
		{
			delay_ms(100);
		}
		delay_ms(600);
//		TIM_Cmd(TIM1, DISABLE);
	}
}