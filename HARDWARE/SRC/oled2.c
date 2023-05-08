//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB13��SCL��
//              D1   ��PB15��SDA��
//              RES  ��PB11
//              DC   ��PB10
//              CS   ��P12               
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#include "oled2.h"
#include "stdlib.h"
#include "oledfont1.h"  	 
#include "delay.h"
#include "oledfont2.h" 
//#include "oledfont.h" 

#define uint16 u16 
#define uint8 u8 
#define int16 s16 
#define int8 s8 

#define byte u8
#define word u16

char OLED2_BUF[100];

uint8 OLED_GRAM[128][8]     = {0};
uint8 OLED_BCK_GRAM[128][8] = {0};
//uint8 OLED_2[128][8] = {0};
//uint8 OLED_4[128][8] = {0};

//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//CLK
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)//DIN
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_1)

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//RES
//#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

//#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//DC
//#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)
// 		     
//#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_7)//CS
//#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_7)

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

#if OLED_MODE==1
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 cmd)
{
	DATAOUT(dat);	    
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		   
	OLED_CS_Clr();
	OLED_WR_Clr();	 
	OLED_WR_Set();
	OLED_CS_Set();	  
	OLED_DC_Set();	 
} 	    	    
#else
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
#endif
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F88X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F88X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x88[c][i],OLED_DATA);
				
			}
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char *BMP)
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
//  if(y1%8==0) y=y1/8;      
//  else y=y1/8+1;
	for(y=y0;y<=y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 


////��ʼ��SSD1306					    
//void OLED_Init(void)
//{ 	
// 
// 	 
// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��A�˿�ʱ��

//	GPIO_InitStructure.GPIO_Pin = oled_cs|oled_d0|oled_d1|oled_res|oled_dc;
// 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
// 	GPIO_Init(oled_gpio, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6

//  OLED_RST_Set();
//	delay_ms(100);
//	OLED_RST_Clr();
//	delay_ms(200);
//	OLED_RST_Set(); 
//					  
//	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
//	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
//	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
//	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
//	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
//	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
//	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
//	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
//	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
//	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
//	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
//	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
//	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
//	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
//	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
//	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
//	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
//	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
//	OLED_WR_Byte(0x12,OLED_CMD);
//	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
//	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
//	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
//	OLED_WR_Byte(0x02,OLED_CMD);//
//	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
//	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
//	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
//	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
//	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
//	
//	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
//	OLED_Clear();
//	OLED_Set_Pos(0,0); 	
//}  






void OLED_CLS(u8 mode)//1������������� 0�����OLED_GRAM
{
  uint8 i,j;
  if(!mode)
  {
    for(i=0;i<128;i++)
    for(j=2;j<8;j++) 
    {
      OLED_GRAM[i][j]=0;
    }
  }
  else
  {
    for(i=0;i<128;i++)
    for(j=2;j<8;j++) 
    {
      OLED_GRAM[i][j]=0;
      OLED_BCK_GRAM[i][j]=0;
    }
        
  }

}	 
void OLED_CLS_67(u8 mode)//1������������� 0�����OLED_GRAM
{
  uint8 i,j;
  if(!mode)
  {
    for(i=0;i<128;i++)
    for(j=6;j<8;j++) 
    {
      OLED_GRAM[i][j]=0;
    }
  }
  else
  {
    for(i=0;i<128;i++)
    for(j=6;j<8;j++) 
    {
      OLED_GRAM[i][j]=0;
      OLED_BCK_GRAM[i][j]=0;
    }
        
  }

}	

void OLED_Refresh(void)
{

  uint8 y,x;
  
  for(y=2;y<8;y++)
    for(x=0;x<X_WIDTH;x++)
      OLED_GRAM[x][y]=OLED_GRAM[x][y]|OLED_BCK_GRAM[x][y];
//     diandao();
  for(y=2;y<8;y++)
  {


		OLED_WR_Byte(0xb0+y,OLED_CMD);
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
    for(x=0;x<X_WIDTH;x++)
    {
			OLED_WR_Byte(OLED_GRAM[x][y],OLED_DATA);
    }
  }

 
}

void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)
		return;//������Χ��.     
        pos = y/8;       
	bx = y%8;
       	temp = 1<<bx;       
	
	if(!t)
			OLED_GRAM[x][pos]|=temp;//��ʾ
	  else 
			OLED_GRAM[x][pos]&=~temp;
	
}

void OLED_DrawHanzi(u8 x,u8 y,char ch[],u8 mode)//�������֣����ո���GRAM����
{
	u8 i,j,mark,temp;
	u8 y0=y;
	u8 wm=0,ii = 0;
	u16 adder=1;
               
	while(ch[ii] != '\0')
         {
			wm = 0;	 //16*16���еĺ���ACSII��λ��
			adder = 1;
			while(OLED_ST16x16_Idx[wm] > 127)
			{
				if(OLED_ST16x16_Idx[wm] == ch[ii]) //���ֵ�һ�������
				{
					if(OLED_ST16x16_Idx[wm + 1] == ch[ii + 1])//���ֵڶ��������
					{
						adder = wm; //�õ�16*16�������ʼλ��
						break;
					}
				}
				wm += 2;			
			}	//�õ����ֵ�λ��adder
			 
			if(adder != 1)
			{
			   mark=adder/2;
		   
			   for(i=0;i<32;i++)  //16*16/8=32
			   {
				   temp=OLED_ST16x16[mark*32+i];
				   for(j=0;j<8;j++) //дһ���ֽڣ���8����
				   {
					  if(temp&0x80)OLED_DrawPoint(x,y,!mode); 
					  else  OLED_DrawPoint(x,y,mode);
					  temp<<=1;
					  y++;
					  if((y-y0)==16)  //��������Ϊȡģ��ʽΪ����ʽ
					  {
							y=y0;
							x++;
							break;
					  }                  
				   }            
			   }
					
		   }
			else			  //��ʾ�հ��ַ�			
			{
				ii += 1;
			}			
           ii += 2;
         }	 	
}




void OLED_DrawPicture(u8 x,u8 y,u8 high,u8 csize,u8 *p,u8 mode)//mode1 Ϊ���� 0 Ϊ������
{
	u8 temp,t,t1;
	u8 y0=y;
	//u8 csize=32;		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	 
	if(x>127||y>63)
		return;//������Χ��
	
	for(t=0;t<csize;t++)
	{   
		temp = p[t];
	
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,!mode);
			else OLED_DrawPoint(x,y,mode);
			temp<<=1;
			y++;
			if((y-y0)==high)
			{
				y=y0;
				x++;
				break;
			}
		}
	}
}
//��ָ��λ����ʾһ���ַ�
void OLED_ShowxcChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ		 
    for(t=0;t<csize;t++)
    {
		if(size==12)
			temp=asc2_1206[chr][t]; 	 	//����1206����
		else if(size==16)
			temp=asc2_1608[chr][t];	//����1608����
		else if(size==24)
			temp=asc2_2412[chr][t];	//����2412����
		else
			return;								//û�е��ֿ�
    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
				OLED_DrawPoint(x,y,mode);
			else
				OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
void OLED_ShowxcString(u8 x,u8 y,const u8 *p,u8 size,u8 mode)//0Ϊѡ��
{
	while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
	{
			if(x>(128-(size/2)))
			{
				x=0;
				y+=size;
			}
			if(y>(64-size))
			{
				y=x=0;
				OLED_CLS(0);
			}
			OLED_ShowxcChar(x,y,*p,size,!mode);	 
			x+=size/2;
			p++;
	}  
}

//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowxcNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowxcChar(x+(size/2)*t,y,' ',16,!mode);
				continue;
			}else enshow=1; 
		 	 
		}
		
	 	OLED_ShowxcChar(x,y,temp+'0',16,!mode); 
		x+=size/2;
	}
} 

