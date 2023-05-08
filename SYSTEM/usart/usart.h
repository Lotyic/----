#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "moto.h" 

#define USART1_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define USART2_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���	

extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���	

extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	
extern float angle_6;
extern int USART_PRINTF_FLAG;
extern u8 x_c;
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 bound);
void USART1_Putc(unsigned char c);
void USART1_Puts(char * str);
void uart2_init(u32 bound);
void USART2_Putc(unsigned char c);
void USART2_Puts(char * str);
void uart3_init(u32 bound);
void USART3_Putc(unsigned char c);
void USART3_Puts(char * str);
#endif


