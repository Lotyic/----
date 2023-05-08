#include "gpio.h"
#include "delay.h"


void All_GPIO_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	//	  pwm���ʹ�ܹܽŶ��壻����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PD�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;    // PD0 PD1 PD2 PD3��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	//����23ʹ�ܶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;    // PD10��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
//	St188�ܽ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB,ENABLE);//GPIOF GPIOE GPIOB
	//-------------out
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;//PE2 PE4 PE5 PE6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);							//�����趨������ʼ��PE
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;//PF1 PF4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);							//�����趨������ʼ��PF
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;						//PB8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);							//�����趨������ʼ��PB
	
	//--------------in
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  					//PE3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_5;//PF2 PF5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;						//PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//���Ԥ�����ڶ�ʱ��1���õ����ö�ʱ��1ʱ������Ҫע�͡�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13;//PE2 PE4 PE5 PE6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);							//�����趨������ʼ��PE
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);							//�����趨������ʼ��PE


	
}

