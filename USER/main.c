#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "oled2.h"
#include "timer.h"
#include "gpio.h"
#include "ADC_Config.h"
#include "moto.h"
#include "move.h"
#include "st178.h"
#include "ui.h"
#include "exti.h"
#include "stmflash.h"


u16 TLHXBCS=0;
int main(void)
{
	delay_init(); //��ʱ��ʼ��
	OLED_Init();  // OLED��ʼ��
	LCD_CLS();	  // OLED����
	// TZXH_LOGO();//̨��ѧԺlogo��ʾ
	All_GPIO_Init();  //�õ���IO�ڳ�ʼ��
	uart1_init(115200); //����1
	uart2_init(115200); //����2
	uart3_init(9600); //����3

	Init_BMQ(); //��������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ADC_DMA_Configuration(); // ADC1��ʼ��(��֪����û���õ����ϳ�����)
	ADKey_Init();			 // ACD3��ʼ��(�õ�)

	Init_TIM8_PWM(899, 7); //���PWM��

	Init_TIM1_PWM(19999, 71); // pe11 pe13���(Ԥ��)(����20ms)
	// Init_TIM6_PWM(4, 71);	  //��е�۶��10msһ��

	
	// zuodongzuo(100, 0);
	
	read_from_flash();		  //��flash�ж�ȡ����							
	LCD_CLS();

//printf("%s","TLCDB!");
//		zuodongzuo(100, 1);
	delay_ms(10);
	printf("%s\r\n","TLCDB!");	//ʵ���Ҿ������ֳԸ������ܽ��˫������ͨ������
	delay_ms(10);
	angle_cs=angle_6;
	while (1)
	{		
		// sprintf(OLED_BUF,"%d 	",ADKey_Deal(Get_Key_Adc_Average(ADC_Channel_4,1)));//��ʾ
		// LCD_16_HanZi_ASCII(0,6,OLED_BUF);	

	    MenuOperate();
//		delay_ms(1000);
//		delay_ms(1000);
//		zuodongzuo(2, 1);
//		delay_ms(1000);
	}
}
