#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epi.h"
#include "inc/hw_ints.h"
#include "driverlib/epi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"
#include "driverlib/fpu.h"
#include "utils/uartstdio.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
#include "TOUCHinit/TOUCH_TSC2046.h"
#include "EPIinit/EPIinit.h"
#include "touchTFT.h"
#include "led.h"
#include "bmp.h"
#include "ui.h"
#include "adcTest.h"
#include "ds18b20.h"
#include "PWMbreathingLED.h"
#include "IICmiziguan.h"
#include "IICaccelermeter.h"
#include "beepMP3.h"
#include "Music.h"
#include "Button.h"
//#include "inc/tm4c1294ncpdt.h"
uint32_t TouchXData[10];
uint32_t TouchYData[10];
volatile uint8_t rec_cmd=0,fuwei=0;
extern uint32_t g_ui32SysClock;
int m;
int s;
#define CMD_BUF_SIZE            64
static char g_cCmdBuf[CMD_BUF_SIZE];

void draw_run(){
	while(fuwei==0){

		uint16_t ui32Loop = 0;
		for(ui32Loop=0;ui32Loop<9;ui32Loop++)
		{
			SSIDataPut(SSI0_BASE,0x90);//读取y方向转换数据，写入0x90
			SysCtlDelay(3);
			SSIDataGet(SSI0_BASE,&TouchYData[ui32Loop]);//TouchYData接受数据
			SysCtlDelay(3);
			SSIDataPut(SSI0_BASE,0xd0);//读取x方向转换数据，写入0xd0
			SysCtlDelay(3);
			SSIDataGet(SSI0_BASE,&TouchXData[ui32Loop]);//TouchXData接受数据
			SysCtlDelay(3);
		}
		if(TOUCH_PointAdjust()==1)
		{
			if((TouchXData[9]<=240)&&(TouchYData[9]<=400))
			{
				TFTLCD_DrawPoint(TouchXData[9],TouchYData[9],BLACK);

			}else if(TouchYData[9]>20&&TouchYData[9]<80){
				if(TouchXData[9]>180&&TouchXData[9]<230)
				{
					fuwei=1;
					SysCtlReset();
					IntMasterDisable();
					rec_cmd=0;
				}
			}
		}
	}
}

void  myCloc1k_run(){
	while(fuwei==0){

		uint16_t ui32Loop = 0;
		for(ui32Loop=0;ui32Loop<9;ui32Loop++)
		{
			SSIDataPut(SSI0_BASE,0x90);//读取y方向转换数据，写入0x90
			SysCtlDelay(3);
			SSIDataGet(SSI0_BASE,&TouchYData[ui32Loop]);//TouchYData接受数据
			SysCtlDelay(3);
			SSIDataPut(SSI0_BASE,0xd0);//读取x方向转换数据，写入0xd0
			SysCtlDelay(3);
			SSIDataGet(SSI0_BASE,&TouchXData[ui32Loop]);//TouchXData接受数据
			SysCtlDelay(3);
		}
		if(TOUCH_PointAdjust()==1)
		{
			if((TouchXData[9]<=240)&&(TouchYData[9]<=400))
			{
				if(m!=0){
					if(--s<0){
						s=59;
						m--;
					}
					myCloc1k_Show(m,s);
				}else{
					myCloc1k_Show(0,0);
				}
				SysCtlDelay(18000000/3);

			}else if(TouchYData[9]>20&&TouchYData[9]<80){
				if(TouchXData[9]>180&&TouchXData[9]<230)
				{
					fuwei=1;
					SysCtlReset();
					IntMasterDisable();
					rec_cmd=0;
				}
			}
		}
	}
}

void myCloc1k_Timer(int m,int s){
	if(--s<0){s=59;}
	--m;
}

void myCloc1k_Show(int m,int s){
	int temp;
	if(m<10){
		Number_Show_one(45,70,0,64,BLACK, WHITE);
		Number_Show_one(75,70,m,64,BLACK, WHITE);
	}else{
		temp=m % 10;
		m=m/10;
		Number_Show_one(45,70,m,64,BLACK, WHITE);
		Number_Show_one(75,70,temp,64,BLACK, WHITE);
	}
	Number_Show_one(110,65,10,64,BLACK, WHITE);
	if(s<10){
		Number_Show_one(135,70,0,64,BLACK, WHITE);
		Number_Show_one(165,70,s,64,BLACK, WHITE);
	}else{
		temp=s % 10;
		s=s/10;
		Number_Show_one(135,70,s,64,BLACK, WHITE);
		Number_Show_one(165,70,temp,64,BLACK, WHITE);
	}

}
void Touch_PressKey(void)
{
//	rec_cmd=identify_key();
//	if(rec_cmd==16){
//		fuwei=1;
//	}
	uint16_t ui32Loop = 0;
	for(ui32Loop=0;ui32Loop<9;ui32Loop++)
	{
		SSIDataPut(SSI0_BASE,0x90);//读取y方向转换数据，写入0x90
		SysCtlDelay(3);
		SSIDataGet(SSI0_BASE,&TouchYData[ui32Loop]);//TouchYData接受数据
		SysCtlDelay(3);
		SSIDataPut(SSI0_BASE,0xd0);//读取x方向转换数据，写入0xd0
		SysCtlDelay(3);
		SSIDataGet(SSI0_BASE,&TouchXData[ui32Loop]);//TouchXData接受数据
		SysCtlDelay(3);
	}
	if(TOUCH_PointAdjust()==1)
	{
		if(TouchXData[9]>1000)
			TouchXData[9]=0;
		if(TouchYData[9]>1000||(TouchYData[9]<60&&TouchXData[9]<=2))
			TouchYData[9]=0;
		//UARTprintf("%d\n",TouchXData[9]);
		//UARTprintf("%d\n",TouchYData[9]);
		//TFTLCD_ShowData(90,300,TouchXData[9],BLACK,WHITE);
		//TFTLCD_ShowData(90,320,TouchYData[9],BLACK,WHITE);
		if(rec_cmd==0)
		{
			//diyihna
			if(TouchYData[9]>335&&TouchYData[9]<399)
			{
				//1号区域
				if(TouchXData[9]>0&&TouchXData[9]<70)
				{
					rec_cmd=1;//20,102
					TFTLCD_CLEAR(WHITE);
					Chinese_Show_one(200,40,6,32,BLACK, WHITE);//返回图标
					SysCtlDelay(SysCtlClockGet());
				}
				//2号区域
				else if(TouchXData[9]>100&&TouchXData[9]<120)
				{
					rec_cmd=2;
					Show_ClockMenu();
					m=25;
					s=0;
					SysCtlDelay(SysCtlClockGet());
					//TFTLCD_ShowPicture1(87,103,gImage_2);
				}
				//3号区域
				else if(TouchXData[9]>170&&TouchXData[9]<200)
				{
					rec_cmd=3;

					Show_MedicineMenu();
					SysCtlDelay(SysCtlClockGet());
					//TFTLCD_ShowPicture1(155,103,gImage_3);
				}
			}


		}
		if(TouchYData[9]>20&&TouchYData[9]<80)
		{
			if(TouchXData[9]>180&&TouchXData[9]<230)
			{
				fuwei=1;
				SysCtlReset();
				IntMasterDisable();
				rec_cmd=0;
			}
		}
//		if(TouchXData[9]<150&&TouchXData[9]>90)
//		{
//			if(TouchYData[9]>140&&TouchYData[9]<180)
//			{
//				GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, GPIO_PIN_5);//PM5输出高电平
//			}
//			else if(TouchYData[9]>200&&TouchYData[9]<230)
//			{
//				GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, 0);//PM5输出高电平
//			}
//		}
		//TFTLCD_DrawPoint(TouchXData[9],TouchYData[9],BLUE);
	}

}


void BoardTest(void)
{
	if(fuwei==1)
	{

	}
	else
	{
		switch(rec_cmd)
		{
		    //UARTgets(g_cCmdBuf, sizeof(g_cCmdBuf));//获取用户URUT输入
		    //TFTLCD_ShowChinese(10,265,g_cCmdBuf,BLACK,WHITE);
			case 0:
				ADC_Get();//温度输入
				//TFTLCD_ShowChinese(10,265,g_cCmdBuf,BLACK,WHITE);
				break;
			case 1:

				draw_run();
				fuwei=0;
				break;
			case 2:
				TFTLCD_FillBlock(10, 50, 190, 220, WHITE);
				if(m!=0){
					if(--s<0){
						s=59;
						m--;
					}
					myCloc1k_Show(m,s);
				}else{
					myCloc1k_Show(0,0);
				}
				SysCtlDelay(2000*(10000000/3000));
				fuwei=0;
				break;
			case 3:

				//buttonShow();
				UARTgets(g_cCmdBuf, sizeof(g_cCmdBuf));//获取用户URUT输入
				int i=atoi(g_cCmdBuf);
				while(1){
					int temp;
					if(i<10){
						Number_Show_one(90,70,0,64,BLACK, WHITE);
						Number_Show_one(120,70,i,64,BLACK, WHITE);
						ShowNumber(0,1);
						ShowNumber(i,2);
					}else{
						temp=i % 10;
						m=i/10;
						Number_Show_one(90,70,i,64,BLACK, WHITE);
						Number_Show_one(120,70,temp,64,BLACK, WHITE);
						ShowNumber(i,1);
						ShowNumber(temp,2);
					}

				}
				fuwei=0;
				break;

			default:break;
		}
	}
}

//
//int temp;
//int temp2;
//if(a<10){
//	Number_Show_one(90,70,0,64,BLACK, WHITE);
//	Number_Show_one(120,70,a,64,BLACK, WHITE);
//}else{
//	temp=a % 10;
//	temp2=a/10;
//	Number_Show_one(90,70,temp2,64,BLACK, WHITE);
//	Number_Show_one(120,70,temp,64,BLACK, WHITE);
//}
