#ifndef _GPIO_H
#define _GPIO_H

#include "sys.h"

#define   S_D_LED   PBout(14)

#define   CAR_BL   PDout(1) //�������
#define   CAR_FL   PDout(0) //�������
#define   CAR_FR   PDout(3) //�������
#define   CAR_BR   PDout(2) //�������

#define   Bluetooth2   PFin(11)//����2ʹ��
#define   Bluetooth3   PDin(10)//����3ʹ��

/*ѡ�������õ�ַ*/
#define  St188_A     PEout(4)
#define  St188_B     PEout(5)
#define  St188_C     PEout(6)

/*ѭ��ʹ�ܶ�*/
#define St188_CS1   PFout(1)//ǰ
#define St188_CS2   PFout(4)//��
#define St188_CS3  	PEout(2)//��
#define St188_CS4   PBout(8)//��

/*ѭ�����ض�����ֵ*/
#define St188_Y1_1    PFin(2)
#define St188_Y2_1    PFin(5)
#define St188_Y3_1    PEin(3)
#define St188_Y4_1    PBin(9)


#define PE11     PEout(11) 		//PE11Ԥ����
#define PE13   PEout(13)		//PE13Ԥ����



void All_GPIO_Init(void);


#endif

