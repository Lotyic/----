
#include "move.h"

#define SEEP1  120
#define SEEP2  120
#define SEEP9  100

#define ys  79
extern u8 shu_h[16];
u8 FLAG=0;
u8 move_BUFF_SET_hang = 0;	
/*
1			����
2			����
*/

u8 move_BUFF_SET[15][2] = {0};
u8 move_BUFF_SET2_hang = 0;	
u8 move_BUFF_SET2[15][2] = {0};
u8 move_BUFF_SET3_hang = 0;	
u8 move_BUFF_SET3[15][2] = {0};

#define ce_move1_BUFF_hang 2	
u8 ce_move1_BUFF[10][11] = {
							5,1,1,0,0, 0,0,0,0,0,0,
							5,0,1,0,0, 0,0,0,0,0,0,
							};
#define ce_move2_BUFF_hang 4	
u8 ce_move2_BUFF[10][11] = {
							5,1,1,3,0, 0,0,0,0,0,0,
							2,1,1,4,0, 0,0,0,0,0,0,
							5,0,1,3,0, 0,0,0,0,0,0,
							2,0,1,4,0, 0,0,0,0,0,0,
							};


#define chu_hang3  6	//һ��һ��	ǰһ��һ		16.07s
u8 chu_3[6][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define chu_hang4  7	//��������			
u8 chu_4[7][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define chu_hang5  3	//��ץ		
u8 chu_5[3][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define sb_hang    4	//��˫��
u8 sb[4][11] = {0,0,0,0,0,0,0,0,0,0,0};	
#define zou_hang1  22	//һ�̶��ƣ��������ƣ�	����ץ ������		35s
u8 zou_1[22][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define zou_hang2  18	//һ�̶��ƣ��������ƣ�	���	25s
u8 zou_2[18][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define zou_hang3  10	//������  ��ץľ��
u8 zou_3[10][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fa_hang1  27	//	ֻ͵
u8 fa_1[27][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fa_hang2  30	//	͵+������
u8 fa_2[30][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fa_hang3  12	//	
u8 fa_3[12][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fangfa_hang  14	
u8 fangfa[14][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fangfa_hang1  13	
u8 fangfa_1[13][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fangfa_hang2  3	
u8 fangfa_2[3][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define fangfa_hang3  17	
u8 fangfa_3[17][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define wujie_hang  12	
u8 wujie[12][11] = {0,0,0,0,0,0,0,0,0,0,0};
#define tou_hang  21	//����ʱ͵	
u8 tou[21][11] = {0,0,0,0,0,0,0,0,0,0,0};	
#define LUXIAN1_hang  26		//��ʤ 25.96��38s
u8 LUXIAN1[26][11] = {0,0,0,0,0,0,0,0,0,0,0};

#define chu_hang1  6	
u8 chu_1[6][11]  = {
					7,1,2,0,0,12,114,26,0,0, 0,
					1,0,1,4,0, 0,  0, 0,0,0,50,
					5,1,3,4,0,25,  0, 0,0,0,50,
					4,1,3,0,0,24,  0, 0,0,0, 0,
					2,0,2,3,0, 0,  0, 0,0,0,52,
					2,1,2,0,0, 0,  0, 0,0,0, 0
					};
#define chu_hang2 2	//	��˫��		18s
u8 chu_2[4][11] = {
					5,1,4,0,0,	0,0,0,0,0,0,
//					1,1,1,4,0,	0,0,0,0,0,0,
					5,0,4,0,0,	0,0,0,0,0,0,
					1,0,1,4,0,	0,0,0,0,0,0,
	
					};

//					1,1,3,0,0,	31,24,0,0,0,0,
//					1,0,3,0,0,	113,35,0,0,0,0,

//case 1 :	Hand_SHENZHI();		break;	// 
//case 2 :	Hand_SANJIAO();		break;	// 
//case 3 :	Hand_BAZI();		break;	// 
//case 4 :	Hand_SHENZHI_0();	break;	// 
//case 5 :	Hand_SHENZHI_1();	break;	//
//case 6 :	Hand_SHOUHUI_0();	break;	// 
//case 7 :	Hand_SHOUHUI_1();	break;	// 
//case 8 :	Hand_SANJIAO_0();	break;	// 
//case 9 :	Hand_SANJIAO_1();	break;	//
//case 10:	Hand_BAZI_0();		break;	//
//case 11:	Hand_BAZI_1();		break;	//	
				  
/*******************

���������

	t  	������					   ���߾�=0
	f  	����1ǰ��0��
	sp 	�ٶȣ�
	r  	ת����3��ת��4��ת��   ��ת��=0
	tim	��ʱ��ת��60��ǰ��һ��67   ���þ�=0
	dj_1�������      ʮλ����    ��λ����		������ʮλ0
	dj_2�������      ʮλ����    ��λ����
	dj_3�������      ʮλ����    ��λ����
	dj_4�������      ʮλ����    ��λ����
	YS  ��ö������
		  
********************/
void DJ_MOVE_ZONG(u8 t,u8 f,u8 sp,u8 r,u16 tim,u8 dj_1,u8 dj_2,u8 dj_3,u8 dj_4,u8 YS)
{
	if(tim < 5&&t !=0)
	{
		DJ_MOVE(t,f,sp,dj_1,dj_2,dj_3,dj_4,YS);
//		DJ_MOVE(t,f,sp);
		delay_ms(100);
	}
	
	else if(tim>=5)
	{
		DJ_MOVE_YS(t,f,sp,tim);
		delay_ms(100);
	}
	
	if(r == 3||r == 4)
	{
		DJ_MOVE_ZHUAN(r,f);
		delay_ms(100);
	}
}

void DJ_MOVE_BUFF_SET(u8 t,u8 f)        //ֻ��Ҫ����������������ƶ�ȫ���������
{
	u8 sp;

	if(t == 9)       //����
	{
//		Hand_SHENZHI();
//		delay_ms(100);
//		DJ_MOVE(1,1,1,0,0,0,0,0);
//		delay_ms(100);
//		DJ_MOVE(1,0,1,0,0,0,0,0);
//		Hand_SANJIAO_xiao();
//		delay_ms(100);
//		DJ_MOVE(1,1,1,0,0,0,0,0);
//		delay_ms(100);
//		DJ_MOVE(1,0,1,0,0,0,0,0);
	}
	else             
	{
		sp = 3;        //�ٶ�4��
		if(sp >= 3)
		{
			sp = 3;
		}
		if(f>2)//�Ƚ�������ת
		{
//			Hand_SANJIAO();
			delay_ms(50);
			DJ_MOVE_ZHUAN(f,0);
			f = 1;
		}
		
		DJ_MOVE(t,f,sp,0,0,0,0,0);    //ǰ������

//		Hand_SANJIAO();
		delay_ms(50);
		
	}
	
}
void DJ_MOVE_BUFF_shuzu(u8 a[12][2],u8 hang)
{
	u8 i = 0;
		for(i = 0;i<hang;i++)
		{

			if(a[i][0]==9)
			{
				TIM_Cmd(TIM1, ENABLE);
				if(FLAG==0)
				{
					
					TIM_SetCompare2(TIM1, 500);
					delay_ms(50);
					TIM_SetCompare3(TIM1, 2500);
					delay_ms(500);
					a[i][0]=0;
					FLAG++;
				}
				else
				{
					TIM_SetCompare2(TIM1, 1170);//����???��
					delay_ms(50);
					TIM_SetCompare3(TIM1,1790);
					a[i][0]=0;
					FLAG=0;
					delay_ms(200);
				}
			}
			if(i==0)
			{
				zuodongzuo(0, 1);
				if(a[i][1]==1)
				{
				BMQ_MOVE(1,40,0);
				DJ_MOVE_BUFF_SET(a[i][0]-1,a[i][1]);
				}
				else
				{
				  DJ_MOVE_BUFF_SET(a[i][0],a[i][1]);
				}
			}
			else
				DJ_MOVE_BUFF_SET(a[i][0],a[i][1]);
		}
}



void HAND_FUWEI(void)//��е�۸�λ
{	
	
}
void HAND_ZHUA(void)//��е��ץ
{	
	
}

void HAND_FANG(void)//��е�۷�
{
	
}

void HAND_ZHUAMUKUAI(void)
{

}


void shuzu(u8 a[50][11],u8 hang)
{
	u8 i = 0;
	u8 n,m;
		
	for(i = 0;i<hang;i++)
	{
		DJ_MOVE_ZONG(a[i][0],a[i][1],a[i][2],a[i][3],a[i][4],a[i][5],a[i][6],a[i][7],a[i][8],a[i][9]);
		if(a[i][10] != 0)
		{
			n = a[i][10]/10;		//ʮλ
			m = a[i][10]%10;		//��λ
				
//			if(n == 5)			//ǰ���
//			{
//				if(m == 0)			//��ֱ
//					Hand_SHENZHI();
//				else if(m == 1)		//����
//					Hand_SANJIAO();
//				else if(m == 2)		//����
//					Hand_BAZI();
//			}
		}
	}	
}


void ce(void)
{
//	shuzu(chu_1,chu_hang1);
	shuzu(chu_2,chu_hang2);
}
void ce_1(void)
{
	shuzu(ce_move1_BUFF,ce_move1_BUFF_hang);
}
void ce_2(void)
{
	shuzu(ce_move2_BUFF,ce_move2_BUFF_hang);
}

void WJ(void)
{
	shuzu(wujie,wujie_hang);
}

void chu_1_1(void)		//	����	1.35ץ��
{
	shuzu(chu_1,chu_hang1);
	shuzu(sb,sb_hang);
	shuzu(zou_1,zou_hang1);
	shuzu(fa_1,fa_hang1);
}
void chu_2_1(void)		//41s��ʤ		��˫��
{
	shuzu(chu_2,chu_hang2);
	shuzu(fa_3,fa_hang3);
}
void chu_3_1(void)		//46s��ʤ		1.33ץ��
{
	shuzu(chu_3,chu_hang3);
	shuzu(sb,sb_hang);
	shuzu(zou_1,zou_hang1);
	shuzu(fa_1,fa_hang1);
}
void chu_4_1(void)		//����ץ�� 
{
	shuzu(chu_4,chu_hang4);
	shuzu(sb,sb_hang);
	shuzu(zou_1,zou_hang1);
//	shuzu(zou_3,zou_hang3);
	shuzu(fa_1,fa_hang1);
}

void chong_1(void)		
{
	shuzu(chu_4,chu_hang4);
	shuzu(zou_1,zou_hang1);
	shuzu(fa_1,fa_hang1);
}
void chong_2(void)		
{
	shuzu(chu_5,chu_hang5);	
	shuzu(zou_1,zou_hang1);
	shuzu(fa_1,fa_hang1);
	
}
void chong_3(void)		
{
	shuzu(tou,tou_hang);	
	shuzu(zou_1,zou_hang1);
	shuzu(fa_1,fa_hang1);
	
}
void chong_4(void)		
{
	shuzu(tou,tou_hang);	
	shuzu(zou_3,zou_hang3);
	shuzu(fa_1,fa_hang1);
}

void xian(void)		
{
	shuzu(fangfa,fangfa_hang);	
}
void xian2(void)		
{
	shuzu(fangfa_1,fangfa_hang1);	
}
void xian3(void)		
{
	shuzu(fangfa_2,fangfa_hang2);	
}
void xian4(void)		
{
	shuzu(fangfa_3,fangfa_hang3);	
}

void WanSheng(void)		//30s  �ȶ�
{
	
}	

void LUXIAN_1(void)
{
	

}
		
void LUXIAN_2(void)
{
	
}	


