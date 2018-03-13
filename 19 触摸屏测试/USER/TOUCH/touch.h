#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "common.h"
   
//////////////////////////////////////////////////////////////////////////////////	 
extern u8  CMD_RDX;
extern u8  CMD_RDY;

//������оƬ��������	   
#define PEN  		PFin(11)  	//T_PEN
#define DOUT 		PBin(2)   	//T_MISO
#define TDIN 		PBout(1)  	//T_MOSI
#define TCLK 		PAout(5)  	//T_CLK
#define TCS  		PBout(0)  	//T_CS 
 
//����������������

extern	u8 touchtype;  //���������� 0Ϊ������  1Ϊ������ �������Ƴ�������
	
extern	u16 Xdown; 		 
extern	u16 Ydown;	   //�����������¾ͷ��صĵ�����ֵ
extern  u16 Xup;
extern  u16 Yup;       //������������֮��̧�𷵻صĵ�����ֵ  


extern float xFactor;	 //������У׼����(����������ҪУ׼) 
extern float yFactor;
extern short xOffset;  
extern short yOffset;

   
//����������
/*********������SPIͨ�����ȡ������ADֵ*********************/
void SPI_Write_Byte(u8 num);				  //�����оƬд��һ������
u16 SPI_Read_AD(u8 CMD);							//��ȡADת��ֵ
u16 RTouch_Read_XorY(u8 xy);							//���˲��������ȡ(X/Y)
u8 RTouch_Read_XY(u16 *x,u16 *y);				//˫�����ȡ(X+Y)
u8 RTouch_Read_XY2(u16 *x,u16 *y);			//���ζ�ȡ��˫���������ȡ

/*********��������ʼ������*********************/
void Touch_Init(void);						 	//��ʼ��

/*********������ɨ�谴������*********************/
void RTouch_Scan(u8 tp);	        //tp:0,��Ļ����;1,��������(У׼�����ⳡ����)

void Draw_Point(u16 x,u16 y,u16 color);	//�ڰ��´���һ��2*2��				

#endif

















