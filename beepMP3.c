#include <string.h>
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
#include "beepMP3.h"
#include "Music.h"

#define   ulong  unsigned long
#define   uchar  unsigned char
#define   ushort unsigned short

extern uint32_t g_ui32SysClock;
//发声频率，取值(系统时钟/65535UL)+1～12000，单位：Hz
#define   BUZZER_FREQUENCY     (SysCtlClockGet()/65535UL)||(usFreq>12000)
//GPIO端口初始化
void Yifan_Buzzer_Music_Play_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);  //  使能PM5所在的GPIO端口
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);                        //  使能TIMER4模块

	GPIOPinConfigure(GPIO_PM5_T4CCP1);
    GPIOPinTypeTimer(GPIO_PORTM_BASE,GPIO_PIN_5);                     //  配置PM5所在管脚为Timer功能

    TimerConfigure(TIMER4_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PWM); //  配置Timer1B为16位PWM

    GPIODirModeSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_DIR_MODE_OUT);	////设置为输出模式
	//GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
	GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, 0);//PM5输出高电平

	IntEnable(INT_TIMER4B);
	TimerEnable(TIMER4_BASE , TIMER_B);
}
//蜂鸣器停止发声
void Yifan_Buzzer_Quiet()
{
    TimerDisable(TIMER4_BASE , TIMER_B);                        				//  禁止TimerB计数，PWM停止输出
    GPIODirModeSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_DIR_MODE_OUT);               //  配置PM5所在管脚为GPIO输出
    //GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD);
    GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, 0x00);
}
//蜂鸣器发出指定频率的声音
//usFreq是发声频率，
void Yifan_Buzzer_Sound(ushort usFreq)
{
  ulong ulVal;
  if (usFreq<=BUZZER_FREQUENCY)
  {
    //蜂鸣器停止发声
    Yifan_Buzzer_Quiet();
  }
  else
  {
    //设置相关管脚为Timer功能
	GPIOPinTypeTimer(GPIO_PORTM_BASE,GPIO_PIN_5);
    ulVal=(SysCtlClockGet())/usFreq;
    TimerLoadSet(TIMER4_BASE , TIMER_B , ulVal);            //  设置TimerB初值，决定PWM周期
    TimerMatchSet(TIMER4_BASE , TIMER_B , ulVal / 2);       //  设置TimerB匹配值，决定PWM占空比
    TimerEnable(TIMER4_BASE , TIMER_B);
  }
}
//  演奏乐曲
void Yifan_Buzzer_Music_Play(tMusic_hy *Yifan_Play_music)
{
  int i;
  for (i=0;;i++)
  {
    //如果是结束符则退出
    if(Yifan_Play_music[i].Music_Time == 0)
    	break;
    //蜂鸣器发出不同声音
    Yifan_Buzzer_Sound(Yifan_Play_music[i].Music_Name);
    //定义时值单位，决定演奏速度（数值单位：ms）
    SysCtlDelay(Yifan_Play_music[i].Music_Time*(g_ui32SysClock/3000));
    //蜂鸣器停止发声
    Yifan_Buzzer_Quiet();
    //延时10ms
    SysCtlDelay(10*(g_ui32SysClock/3000));
  }
}
void MusicRun(void)
{
	int i;
	while(1)
	{
	    //奏乐（看月亮爬上来【张杰】）
	    for (i=0;i<1;i++)//循环控制演奏次数
	    {
	       Yifan_Buzzer_Music_Play(my_music_kanyueliangpashanglai);
	       SysCtlDelay(2000*(g_ui32SysClock/3000));
	    }
	    //奏乐（化蝶【梁祝】）
//	    for (i=0;i<1;i++)//循环控制演奏次数
//	    {
//	       Yifan_Buzzer_Music_Play(my_music_huadie);
//	       SysCtlDelay(5000*(g_ui32SysClock/3000));
//	    }
	}
}
