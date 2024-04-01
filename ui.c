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
    //初始化
	TFTLCD_CLEAR(WHITE);

    //日期显示
    TFTLCD_ShowString(10,10,"2022/12/21",BLACK,WHITE);
    TFTLCD_ShowChinese(95,10,"周三",BLACK,WHITE);
    TFTLCD_ShowChinese(10,30,"壬寅年冬月廿八",BLACK,WHITE);
	Number_Show_one(90,70,2,64,BLACK, WHITE);//日期数字1
	Number_Show_one(120,70,1,64,BLACK, WHITE);//日期数字1
	//TFTLCD_ShowChinese(95,125,"宜答辩",BLACK,WHITE);
	TFTLCD_ShowChinese(95,125,"宜康复",BLACK,WHITE);

	//气温显示
	TFTLCD_ShowChinese(20,170,"温度",BLACK,WHITE);
	//Number_Show_one(10,190,1,32,BLACK, WHITE);//气温数字1
	//Number_Show_one(25,190,0,32,BLACK, WHITE);//气温数字2
	Chinese_Show_one(40,190,0,32,BLACK, WHITE);//气温单位
	//天气显示
	TFTLCD_ShowChinese(100,170,"天气",BLACK,WHITE);
	//Chinese_Show_one(100,190,1,32,BLACK, WHITE);//多云图标
	Chinese_Show_one(100,190,8,32,BLACK, WHITE);//晴天图标
	//心情显示
	TFTLCD_ShowChinese(180,170,"心情",BLACK,WHITE);
	//Chinese_Show_one(180,190,7,32,BLACK, WHITE);//happy图标
	Chinese_Show_one(180,190,5,32,BLACK, WHITE);//unhappy图标
	//日程显示（UART输入）
	TFTLCD_ShowChinese(10,245,"今日日程",BLACK,WHITE);
	TFTLCD_ShowChinese(10,265,"单片机答辩",BLACK,WHITE);
	TFTLCD_ShowChinese(10,285,"吃红烧肉",BLACK,WHITE);
	TFTLCD_ShowChinese(10,305,"戴好口罩，做好防护",BLACK,WHITE);

	//功能图标
	Chinese_Show_one(20,350,2,32,BLACK, WHITE);//随心记图标
	Chinese_Show_one(190,350,3,32,BLACK, WHITE);//吃药提醒图标
	Chinese_Show_one(105,350,4,32,BLACK, WHITE);//番茄钟图标


}
void Show_ClockMenu(){
	TFTLCD_CLEAR(WHITE);
	Number_Show_one(45,70,2,64,BLACK, WHITE);
	Number_Show_one(75,70,5,64,BLACK, WHITE);
	Number_Show_one(110,65,10,64,BLACK, WHITE);
	Number_Show_one(135,70,0,64,BLACK, WHITE);
	Number_Show_one(165,70,0,64,BLACK, WHITE);
	TFTLCD_ShowChinese(95,30,"番茄钟",BLACK,WHITE);
	Chinese_Show_one(200,40,6,32,BLACK, WHITE);//返回图标
}


void Show_MedicineMenu(){
	TFTLCD_CLEAR(WHITE);
	Number_Show_one(90,70,0,64,BLACK, WHITE);//日期数字1
	Number_Show_one(120,70,0,64,BLACK, WHITE);//日期数字1
	TFTLCD_ShowChinese(95,30,"吃药数量",BLACK,WHITE);
	Chinese_Show_one(200,40,6,32,BLACK, WHITE);//返回图标
}
