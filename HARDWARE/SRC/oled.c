/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            OLED�ĳ�ʼ������������μ�IO_config.h
  * @ʹ��            ��ʾ������ASCII�����LCD_16_HanZi_ASCII����
                     ������ʾ�ĺ�����ST16x16_Idx[]�����ж��壬��ST16x16[]�����д�������ֿ�
  ******************************************************************************
*/

#include "oled.h"
#include "oledfont.h"


char OLED_BUF[64];//OLED��ʾ������ÿ��16���ַ�����4�С�

	#define XLevelL		0x00
	#define XLevelH		0x10
	#define XLevel		((XLevelH&0x0F)*16+XLevelL)
	#define Max_Column	128
	#define Max_Row		  64
	#define	Brightness	0xCF
	
	
	
	//#define D0 GPIO_Pin_2	  //�Ѿ���IO_config.h�ж������
	//#define D1 GPIO_Pin_1
	//#define RST GPIO_Pin_11
	//#define DC GPIO_Pin_10
	//#define OLED_GPIO GPIOB
	
	
	/*
	4��SPIʹ��˵����
	VBT ���ڲ�DC-DC��ѹ��3.3~4.3V�����ʹ��5V��ѹ��Ϊ���������һ��100~500ŷ�ĵ���
	VCC ���ڲ��߼���ѹ 1.8~6V
	GND ��
	
	BS0 �͵�ƽ
	BS1 �͵�ƽ
	BS2 �͵�ƽ
	
	CS  Ƭѡ�ܽ�
	DC  ��������ѡ��ܽ�
	RES ģ�鸴λ�ܽ�
	D0��SCLK�� ��ʱ�ӽţ���MCU����
	D1��MOSI�� ����������������ݽţ���MCU����
	
	D2 ����
	D3-D7 �� �͵�ƽ �� Ҳ�����գ��������Ϊ�͵�ƽ
	RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
	RW  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
	RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
	C7---D0��SCLK��ʱ�ӽţ���MCU����
	C6---D1��MOSI����������������ݽţ���MCU����
	C0---RST ģ�鸴λ�ܽ�
	C4---DC  ��������ѡ��ܽ�*/
	
	/**************************** ���Ŷ��� ***********************************
															PE2    RST
															PE2    DC
															PE3    D1
															PE4    D0
	*************************************************************************/ 
	#define X_WIDTH 128
	#define Y_WIDTH 64
	//======================================
	
	/*
	A13---D0��SCLK��ʱ�ӽţ���MCU����    13
	A12---D1��MOSI����������������ݽţ���MCU����   12
	A15---RST ģ�鸴λ�ܽ�  15
	A14---DC  ��������ѡ��ܽ�     14*/  
	void OLED_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin  = DC|D0|D1|RST|CS|GPIO_Pin_0|GPIO_Pin_1;
		
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
		
		
		GPIO_Init(OLED_GPIO, &GPIO_InitStructure);
		
		CSLOW();
		DCHIGH();
		CLKHIGH();

		RESLOW();
		LCD_DLY_ms(50);
		RESHIGH();
	
		LCD_WrCmd(0xae);//--turn off oled panel
		LCD_WrCmd(0x00);//---set low column address
		LCD_WrCmd(0x10);//---set high column address
		LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
		LCD_WrCmd(0x81);//--set contrast control register
		LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
		LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
		LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
		//   LCD_WrCmd(0xa0);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
		//   LCD_WrCmd(0xc0);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
		LCD_WrCmd(0xa6);//--set normal display
		LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
		LCD_WrCmd(0x3f);//--1/64 duty
		LCD_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
		LCD_WrCmd(0x00);//-not offset
		LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
		LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
		LCD_WrCmd(0xd9);//--set pre-charge period
		LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
		LCD_WrCmd(0xda);//--set com pins hardware configuration
		LCD_WrCmd(0x12);
		LCD_WrCmd(0xdb);//--set vcomh
		LCD_WrCmd(0x40);//Set VCOM Deselect Level
		LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
		LCD_WrCmd(0x02);//
		LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
		LCD_WrCmd(0x14);//--set(0x10) disable
		LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
		LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
		LCD_WrCmd(0xaf);//--turn on oled panel
		OLCD_Fill(0x00);  //��ʼ����
		LCD_Set_Pos(0,0);
	//	TZXH_LOGO();
	//	DZXH_LOGO();
	}
	/*
	A26---D0��SCLK��ʱ�ӽţ���MCU����    13
	A27---D1��MOSI����������������ݽţ���MCU����   12
	A24---RST ģ�鸴λ�ܽ�  15
	A25---DC  ��������ѡ��ܽ�     14*/  
	void LCD_WrDat(byte data)
	{
		byte i=8;
		CSLOW();
		//LCD_CS=0;;
		DCHIGH();;;;//DC=1
		  __NOP();
		 CLKLOW();;;;//D0=0
		 __NOP();
	  while(i--)
	  {
		if(data&0x80)
			{MISOHIGH();;;;}//D1=1
		else
			{MISOLOW();;;;}//D1==0
	   CLKHIGH();//D0=1
	   __NOP();;;;
			//asm("nop");
	   CLKLOW();;;;;//D0==0
		data<<=1;
	  }
		//LCD_CS=1;
	}
	
	/*
	A26---D0��SCLK��ʱ�ӽţ���MCU���� E4
	A27---D1��MOSI����������������ݽţ���MCU���� E3
	A24---RST ģ�鸴λ�ܽ� E6
	A25---DC  ��������ѡ��ܽ�  E5 */
	void LCD_WrCmd(byte cmd)
	{
		byte i=8;
		CSLOW();
		//LCD_CS=0;;
	DCLOW();;;;;
	 CLKLOW();;;;;
	  //asm("nop");
	  
	  while(i--)
	  {
		if(cmd&0x80)
			{MISOHIGH();;;;;}
		else
			{MISOLOW();;;;;;}
		CLKHIGH();;;;;
		__NOP();;;;
			//asm("nop");
	   CLKLOW();;;;;
		cmd<<=1;;;;;
	  } 	
		//LCD_CS=1;
	}
	
	
	void LCD_Set_Pos(byte x, byte y)
	{
	  LCD_WrCmd(0xb0+y);
	  LCD_WrCmd(((x&0xf0)>>4)|0x10);
	  LCD_WrCmd(x&0x0f);//|0x01);ԭ���İ汾ͼ����������һ�У����µ�128���Ƶ���һ����ʾ����֪����ô����Ϊʲô����ʱ�ȸĻ���
	}
	void OLCD_Fill(byte bmp_data)
	{
		byte y,x;
		
		for(y=0;y<8;y++)
		{
			LCD_WrCmd(0xb0+y);
			LCD_WrCmd(0x01);
			LCD_WrCmd(0x10);
			for(x=0;x<X_WIDTH;x++)
				LCD_WrDat(bmp_data);
		}
	}
	void LCD_CLS(void)
	{
		byte y,x;	
		for(y=0;y<8;y++)
		{
			LCD_WrCmd(0xb0+y);
			LCD_WrCmd(0x01);
			LCD_WrCmd(0x10);
			for(x=0;x<X_WIDTH;x++)
				LCD_WrDat(0);
		}
	}
	void LCD_CLS_06(void)
	{
		byte y,x;	
		for(y=0;y<2;y++)
		{
			LCD_WrCmd(0xb0+y);
			LCD_WrCmd(0x01);
			LCD_WrCmd(0x10);
			for(x=0;x<X_WIDTH;x++)
				LCD_WrDat(0);
		}
	}
	void LCD_DLY_ms(word ms)
	{
	  word a;
	  while(ms)
	  {
		a=13350;
		while(a--);
		ms--;
	  }
	  return;
	}
	
	//==============================================================
	//�������� void LCD_PutPixel(byte x,byte y)
	//��������������һ���㣨x,y��
	//��������ʵ����ֵ(x,y),x�ķ�Χ0��127��y�ķ�Χ0��64
	//���أ���
	//==============================================================
	void LCD_PutPixel(byte x,byte y)
	{
		byte data1;  //data1��ǰ�������
		
			LCD_Set_Pos(x,y);
		data1 = 0x01<<(y%8); 	
		LCD_WrCmd(0xb0+(y>>3));
		LCD_WrCmd(((x&0xf0)>>4)|0x10);
		LCD_WrCmd((x&0x0f)|0x00);
		LCD_WrDat(data1); 	 	
	}
	void LCD_xian(byte x1,byte y1,byte x2,byte y2)
	{
		byte n,n1;
		for(n = x1;n < x2;n++)
		{
			for(n1 = y1;n1 < y2;n1++)
			{
				LCD_PutPixel(n,n1);
			}
			
		}
	}
	
	//==============================================================
	//�������� void LCD_Rectangle(byte x1,byte y1,
	//                   byte x2,byte y2,byte color,byte gif)
	//��������������һ��ʵ�ľ���
	//���������Ͻ����꣨x1,y1��,���½����꣨x2��y2��,�Ƿ񶯻�
	//      ����x1��x2�ķ�Χ0��127��y1��y2�ķ�Χ0��63������ʵ����ֵ
	//���أ���
	//==============================================================
	void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif)
	{
		byte n;
			
		LCD_Set_Pos(x1,y1>>3);
		for(n=x1;n<=x2;n++)
		{
			LCD_WrDat(0x01<<(y1%8)); 			
			if(gif == 1) 	LCD_DLY_ms(50);
		}
		LCD_Set_Pos(x1,y2>>3);
		for(n=x1;n<=x2;n++)
		{
			LCD_WrDat(0x01<<(y2%8)); 			
			if(gif == 1) 	LCD_DLY_ms(5);
		}
		
	}
	//==============================================================
	//��������LCD_P6x8Str(byte x,byte y,byte *p)
	//����������д��һ���׼ASCII�ַ���
	//��������ʾ��λ�ã�x,y����yΪҳ��Χ0��7��Ҫ��ʾ���ַ���
	//���أ���
	//==============================================================
	void LCD_P6x8Str(byte x,byte y,byte ch[])
	{
	  byte c=0,i=0,j=0;
	  while (ch[j]!='\0')
	  {
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		LCD_Set_Pos(x,y);
		for(i=0;i<6;i++)
		  LCD_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	  }
	}
	//==============================================================
	//��������LCD_P8x16Str(byte x,byte y,byte *p)
	//����������д��һ���׼ASCII�ַ���
	//��������ʾ��λ�ã�x,y����yΪҳ��Χ0��7��Ҫ��ʾ���ַ���
	//���أ���
	//==============================================================
	void LCD_P8x16Str(byte x,byte y,byte ch[])
	{
	  byte c=0,i=0,j=0;
	
	  while (ch[j]!='\0')
	  {
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		LCD_Set_Pos(x,y);
		for(i=0;i<8;i++)
		  LCD_WrDat(F8X16[c*16+i]);
		LCD_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		  LCD_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	  }
	}
	//��������ַ���
	void LCD_P14x16Str(byte x,byte y,byte ch[])
	{
		byte wm=0,ii = 0;
		word adder=1;
		
		while(ch[ii] != '\0')
		{
		wm = 0;
		adder = 1;
		while(F14x16_Idx[wm] > 127)
		{
			if(F14x16_Idx[wm] == ch[ii])
			{
				if(F14x16_Idx[wm + 1] == ch[ii + 1])
				{
					adder = wm * 14;
					break;
				}
			}
			wm += 2;			
		}
		if(x>118){x=0;y++;}
		LCD_Set_Pos(x , y);
		if(adder != 1)// ��ʾ����					
		{
			LCD_Set_Pos(x , y);
			for(wm = 0;wm < 14;wm++)
			{
				LCD_WrDat(F14x16[adder]);	
				adder += 1;
			}
			LCD_Set_Pos(x,y + 1);
			for(wm = 0;wm < 14;wm++)
			{
				LCD_WrDat(F14x16[adder]);
				adder += 1;
			}   		
		}
		else			  //��ʾ�հ��ַ�			
		{
			ii += 1;
		  LCD_Set_Pos(x,y);
			for(wm = 0;wm < 16;wm++)
			{
					LCD_WrDat(0);
			}
			LCD_Set_Pos(x,y + 1);
			for(wm = 0;wm < 16;wm++)
			{   		
					LCD_WrDat(0);	
			}
		}
		x += 14;
		ii += 2;
		}
	}
	//������ֺ��ַ�����ַ���
	void LCD_Print(byte x, byte y, byte ch[])
	{
		byte ch2[3];
		byte ii=0;
		while(ch[ii] != '\0')
		{
			if(ch[ii] > 127)
			{
				ch2[0] = ch[ii];
				ch2[1] = ch[ii + 1];
				ch2[2] = '\0';			//����Ϊ�����ֽ�
				LCD_P14x16Str(x , y, ch2);	//��ʾ����
				x += 14;
				ii += 2;
			}
			else
			{
				ch2[0] = ch[ii];	
				ch2[1] = '\0';			//��ĸռһ���ֽ�
				LCD_P8x16Str(x , y , ch2);	//��ʾ��ĸ
				x += 8;
				ii+= 1;
			}
		}
	}
	
	//==============================================================
	//�������� void Draw_BMP(byte x,byte y)
	//������������ʾBMPͼƬ128��64
	//��������ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7��ֹ�����꣨x1��y1��
	//���أ���
	//==============================================================
	void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte *bmp)
	{ 	
	//  word ii=0;
	  byte x,y;
	
	  if(y1%8==0)
		y=y1/8;
	  else
		y=y1/8+1;
	  for(y=y0;y<=y1;y++)
	  {
		LCD_Set_Pos(x0,y);				
		for(x=x0;x<=x1;x++)
		{
		  LCD_WrDat(*bmp++);	    	
		}
	  }
	}
	
	
	void Draw_BMP2(byte x0,byte y0,byte x1,byte y1,byte *bmp)
	{ 	
	//  word ii=0;
	  byte x,y;
	
	  if(y1%8==0)
		y=y1/8;
	  else
		y=y1/8+1;
	  for(y=y0;y<=y1;y+=2)
	  {
		LCD_Set_Pos(x0,y);				
		for(x=x0;x<=x1;x++)
		{if((*bmp+=3)>0x80)
		  LCD_WrDat(0x01);  
		else
			LCD_WrDat(0x00);  	
		}
	  }
	}
	
	void Dis_Num(byte y, byte x, unsigned int num,byte N)
	{
	  byte j=0;
	  byte n[6]={0};
	  x=x*8;
	  n[0]=(num/10000)%10;
	  n[1]=(num/1000)%10;
	  n[2]=(num/100)%10;
	  n[3]=(num/10)%10;
	  n[4]=num%10;
	  n[5]='\0';
	  for(j=0;j<5;j++)
		n[j]=n[j]+16+32;	 
	  LCD_P8x16Str(x,y,&n[5-N]);//��ACSII����ж�ȡ�ֽڣ�Ȼ��д��Һ��
	}
	
	void DZXH_LOGO()
	{
		Draw_BMP(0,0,127,7,DZXYlogo);
		delay_ms(1400);            //��ʾLOGO��ʱ
		OLCD_Fill(0x00);  //��ʼ����
		
	}
	
	void TZXH_LOGO()
	{
		Draw_BMP(32,0,95,7,TZXYlogo);
		delay_ms(1400);            //��ʾLOGO��ʱ
//		OLCD_Fill(0x00);  //��ʼ����
		
	}
	
	//��ʾ���� 
	//�����������x��y������ ������
	//250��������+02.50
	void Dis_err(byte y, byte x, int16 num)
	{
	  byte n[6]={0};
	  x=x*8;
	  if(num<0)
	  {
		n[0]=45;
		num=-num;
	  }
	  else if(num>=0)
	  {
		n[0]=43;
	  }
	  n[1]=(num/1000)%10+16+32;
	  n[2]=(num/100)%10+16+32;
	  n[3]=46;
	  n[4]=(num/10)%10+16+32;
	  n[5]=num%10+16+32;
	  LCD_P8x16Str(x,y,&n[0]);//��ACSII����ж�ȡ�ֽڣ�Ȼ��д��Һ��
	}
	
	//���Ͻ���ʾ���� 
	//�����������ѹֵ840��������630���¿ո�0ͼƬ��ʾ1������ʾ
	void Draw_Power(uint16 TSC,uint8 qie)		
	{
	  byte is;
	  byte n[5]={0};
	  if(qie==0)
	  {
		if(TSC<=630)
		  TSC=630;
		TSC=TSC-630;
		TSC=TSC/10;
		if(TSC>21)
		   TSC=21;
		for(is=0;is<21;is++)
		{
			dianchi[8+is]=0x04;
			dianchi[40+is]=0x20;
		}	
		for(is=0;is<TSC;is++)
		{
			dianchi[28-is]=0xF4;
			dianchi[60-is]=0x2F;
		}
		Draw_BMP(96,0,127,1,dianchi);  	
	  }
	  if(qie==1)
	  {
		TSC=TSC;
		n[0]=(TSC/100)%10+16+32;
		n[1]=46;
		n[2]=(TSC/10)%10+16+32;
		n[3]=TSC%10+16+32;
	//    n[4]='\n';
		LCD_P8x16Str(96,0,&n[0]);//��ACSII����ж�ȡ�ֽڣ�Ȼ��д��Һ��
		//Dis_Num(0,11,TSC,4) ;//3
	  }
	
	}
	
	void Draw_XH()
	{
		Draw_BMP(0,0,31,1,xinghao);
		Draw_Power(840,0);
		//Draw_WZ(-30);
	}
	
	 void Dis_Num_point(byte y, byte x, float num,byte N)
	{
	  unsigned int temp;
	  byte j=0;
	  byte n[5]={0};
	  temp = (unsigned int)(num*100);
	  x=x*8;
	  n[0]=temp/100;
	//  n[1]='.';
	  n[2]=(temp/10)%10;
	  n[3]=temp%10;
	//  n[5]='/0';
	  for(j=0;j<4;j++)
		n[j]=n[j]+16+32;
	  n[1] = '.';
	  LCD_P8x16Str(x,y,&n[4-N]);//��ACSII����ж�ȡ�ֽڣ�Ȼ��д��Һ��
	
	}
	
	//��������ʾλ��
	//�������+-60
	void Draw_WZ(int16 WEI2)
	{
		byte iss;
		byte WEI;
		WEI=WEI2+63;
		for(iss=0;iss<128;iss++)
		{
		  weizhi[iss]=0x00;
		}	
		weizhi[WEI]=0x7C;
		weizhi[WEI+1]=0x7C;
		Draw_BMP(0,2,127,3,weizhi);
	}
	
	
	/*****************************************************************************
	 �� �� �� : LED_PrintImage
	 �������� : ��ͼ����ʾ����
	 ������� : UCHAR8 *pucTable ��άͼ������ĵ�ַ
				 USHORT16 usRowNum ��άͼ�������1~64
				 USHORT16 usColumnNum ��άͼ�������1~128
	 ������� : none
	 �� �� ֵ : none
	*****************************************************************************/
	void LED_PrintImage(byte *pucTable, word usRowNum, word usColumnNum)
	{
		byte ucData;
		word i,j,k,m,n;
		word usRowTmp;
	
		m = usRowNum >> 3;   //����ͼƬ������8λΪһ������������
		n = usRowNum % 8;    //����������ʣ�µ�����
	
		for(i = 0; i < m; i++) //��������ɨ��
		{
			LCD_Set_Pos(0,i);
			usRowTmp = i << 3;    //���㵱ǰ�����е��±�
			for(j = 0; j < usColumnNum; j++) //��ɨ��
			{
				ucData = 0;
				for(k = 0; k < 8; k++) //��i���ж���8��ɨ��
				{
					ucData = ucData >> 1;
					if((pucTable + (usRowTmp + k) * usColumnNum)[j] == 0)
					{
						ucData = ucData | 0x80;
					}
	
				}
				LCD_WrDat(ucData);
			}
		}
	
		LCD_Set_Pos(0,(u8)i); //����ʣ�µ�����ʾ����ʼ����
		usRowTmp = i << 3;       //���㵱ǰ�����е��±�
		for(j = 0; j < usColumnNum; j++) //��ɨ��
		{
			ucData = 0;
			for(k = 0; k < n; k++) //��ʣ�µ���ɨ��
			{
				ucData = ucData >> 1;
				if((pucTable + (usRowTmp + k) * usColumnNum)[j] == 0)
				{
					ucData = ucData | 0x80;
				}
	
			}
			ucData = ucData >> (8 - n);
			LCD_WrDat(ucData);
		}
	
		return;
	}
	//��������ַ���
	void LCD_P16x16Str(byte x,byte y,byte ch[])
	{
		byte wm=0,ii = 0;
		word adder=1;
		
		while(ch[ii] != '\0')
		{
			wm = 0;	 //16*16���еĺ���ACSII��λ��
			adder = 1;
			while(ST16x16_Idx[wm] > 127)
			{
				if(ST16x16_Idx[wm] == ch[ii]) //���ֵ�һ�������
				{
					if(ST16x16_Idx[wm + 1] == ch[ii + 1])//���ֵڶ��������
					{
						adder = wm * 16; //�õ�16*16�������ʼλ��
						break;
					}
				}
				wm += 2;			
			}	//�õ����ֵ�λ��adder
			
			if(x>118){x=0;y=y+2;}
			LCD_Set_Pos(x , y); 
			if(adder != 1)// ��ʾ����					
			{  
				LCD_Set_Pos(x , y);
				for(wm = 0;wm < 16;wm++)//16�е���һ��һ����ʾ
				{
					LCD_WrDat(ST16x16[adder]);	
					adder += 1;
				}
				LCD_Set_Pos(x,y + 1);
				for(wm = 0;wm < 16;wm++)
				{
					LCD_WrDat(ST16x16[adder]);
					adder += 1;
				}   		
			}
			else			  //��ʾ�հ��ַ�			
			{
				ii += 1;
			  LCD_Set_Pos(x,y);
				for(wm = 0;wm < 16;wm++)
				{
						LCD_WrDat(0);
				}
				LCD_Set_Pos(x,y + 1);
				for(wm = 0;wm < 16;wm++)
				{   		
						LCD_WrDat(0);	
				}
			}
			x += 16;
			ii += 2;
		}
	}
	//������ֺ��ַ�����ַ���
	void LCD_16_HanZi_ASCII(byte x, byte y, char ch[])
	{
		byte ch2[3];
		byte ii=0;
		while(ch[ii] != '\0')
		{
			if(ch[ii] > 127)
			{
				ch2[0] = ch[ii];
				ch2[1] = ch[ii + 1];
				ch2[2] = '\0';			//����Ϊ�����ֽ�
				if(x*8>118){x=0;y=y+2;}
				LCD_P16x16Str(x*8 , y, ch2);	//��ʾ����
//					x += 16;
				 x=x+2;
				ii += 2;
			}
			else
			{
				ch2[0] = ch[ii];	
				ch2[1] = '\0';			//��ĸռһ���ֽ�
				if(x*8>120){x=0;y=y+2;}
				LCD_P8x16Str(x*8 , y , ch2);	//��ʾ��ĸ
//					x += 8;
				x++;
				ii+= 1;
			}
		}
	}

