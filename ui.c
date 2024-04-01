#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/pin_map.h"
#include "grlib/grlib.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"
#include "driverlib/ssi.h"
#include "driverlib/rom_map.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
#include "TOUCHinit/TOUCH_TSC2046.h"
#include "EPIinit/EPIinit.h"
#include "Init.h"
#include "touchTFT.h"
#include "ui.h"

void Show_MianMenu(){
    //��ʼ��
	TFTLCD_CLEAR(WHITE);

    //������ʾ
    TFTLCD_ShowString(10,10,"2022/12/21",BLACK,WHITE);
    TFTLCD_ShowChinese(95,10,"����",BLACK,WHITE);
    TFTLCD_ShowChinese(10,30,"�����궬��إ��",BLACK,WHITE);
	Number_Show_one(90,70,2,64,BLACK, WHITE);//��������1
	Number_Show_one(120,70,1,64,BLACK, WHITE);//��������1
	//TFTLCD_ShowChinese(95,125,"�˴��",BLACK,WHITE);
	TFTLCD_ShowChinese(95,125,"�˿���",BLACK,WHITE);

	//������ʾ
	TFTLCD_ShowChinese(20,170,"�¶�",BLACK,WHITE);
	//Number_Show_one(10,190,1,32,BLACK, WHITE);//��������1
	//Number_Show_one(25,190,0,32,BLACK, WHITE);//��������2
	Chinese_Show_one(40,190,0,32,BLACK, WHITE);//���µ�λ
	//������ʾ
	TFTLCD_ShowChinese(100,170,"����",BLACK,WHITE);
	//Chinese_Show_one(100,190,1,32,BLACK, WHITE);//����ͼ��
	Chinese_Show_one(100,190,8,32,BLACK, WHITE);//����ͼ��
	//������ʾ
	TFTLCD_ShowChinese(180,170,"����",BLACK,WHITE);
	//Chinese_Show_one(180,190,7,32,BLACK, WHITE);//happyͼ��
	Chinese_Show_one(180,190,5,32,BLACK, WHITE);//unhappyͼ��
	//�ճ���ʾ��UART���룩
	TFTLCD_ShowChinese(10,245,"�����ճ�",BLACK,WHITE);
	TFTLCD_ShowChinese(10,265,"��Ƭ�����",BLACK,WHITE);
	TFTLCD_ShowChinese(10,285,"�Ժ�����",BLACK,WHITE);
	TFTLCD_ShowChinese(10,305,"���ÿ��֣����÷���",BLACK,WHITE);

	//����ͼ��
	Chinese_Show_one(20,350,2,32,BLACK, WHITE);//���ļ�ͼ��
	Chinese_Show_one(190,350,3,32,BLACK, WHITE);//��ҩ����ͼ��
	Chinese_Show_one(105,350,4,32,BLACK, WHITE);//������ͼ��


}
void Show_ClockMenu(){
	TFTLCD_CLEAR(WHITE);
	Number_Show_one(45,70,2,64,BLACK, WHITE);
	Number_Show_one(75,70,5,64,BLACK, WHITE);
	Number_Show_one(110,65,10,64,BLACK, WHITE);
	Number_Show_one(135,70,0,64,BLACK, WHITE);
	Number_Show_one(165,70,0,64,BLACK, WHITE);
	TFTLCD_ShowChinese(95,30,"������",BLACK,WHITE);
	Chinese_Show_one(200,40,6,32,BLACK, WHITE);//����ͼ��
}


void Show_MedicineMenu(){
	TFTLCD_CLEAR(WHITE);
	Number_Show_one(90,70,0,64,BLACK, WHITE);//��������1
	Number_Show_one(120,70,0,64,BLACK, WHITE);//��������1
	TFTLCD_ShowChinese(95,30,"��ҩ����",BLACK,WHITE);
	Chinese_Show_one(200,40,6,32,BLACK, WHITE);//����ͼ��
}
