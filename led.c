#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include "led.h"

void LED_init(int ledn)
{
	if(ledn<3)
	{
		switch(ledn)
		{
		case 0:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTF_BASE,LED0,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTF_BASE,LED0,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTF_BASE,LED0, 0x00);//PF1输出低电平
			break;
		case 1:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTF_BASE,LED1,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTF_BASE,LED1,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTF_BASE,LED1, 0x00);//PF1输出低电平
			break;
		case 2:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTF_BASE,LED2,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTF_BASE,LED2,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTF_BASE,LED2, 0x00);//PF1输出低电平
			break;
		default:break;
		}
	}
	else if(ledn>=3)
	{
		switch(ledn)
		{
		case 3:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTL_BASE,LED3,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTL_BASE,LED3,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTL_BASE,LED3, 0x00);//PF1输出低电平
			break;
		case 4:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTL_BASE,LED4,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTL_BASE,LED4,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTL_BASE,LED4, 0x00);//PF1输出低电平
			break;
		case 5:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTL_BASE,LED5,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTL_BASE,LED5,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTL_BASE,LED5, 0x00);//PF1输出低电平
			break;
		case 6:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTL_BASE,LED6,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTL_BASE,LED6,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTL_BASE,LED6, 0x00);//PF1输出低电平
			break;
		case 7:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
			GPIODirModeSet(GPIO_PORTL_BASE,LED7,GPIO_DIR_MODE_OUT); ////设置为输出模式
			GPIOPadConfigSet(GPIO_PORTL_BASE,LED7,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
			GPIOPinWrite(GPIO_PORTL_BASE,LED7, 0x00);//PF1输出低电平
			break;
		default:break;
		}
	}
}
void  ledWrite(int ledn,LED_status status)
{
	if(ledn<3)
	{
		switch(ledn)
		{
		case 0:
			GPIOPinWrite(GPIO_PORTF_BASE,LED0, status);//PF1输出低电平
			break;
		case 1:
			GPIOPinWrite(GPIO_PORTF_BASE,LED1, status);//PF1输出低电平
			break;
		case 2:
			GPIOPinWrite(GPIO_PORTF_BASE,LED2, status);//PF1输出低电平
			break;
		default:break;
		}
	}
	else if(ledn>3)
	{
		switch(ledn)
		{
		case 3:
			GPIOPinWrite(GPIO_PORTL_BASE,LED3, status);//PF1输出低电平
			break;
		case 4:
			GPIOPinWrite(GPIO_PORTL_BASE,LED4, status);//PF1输出低电平
			break;
		case 5:
			GPIOPinWrite(GPIO_PORTL_BASE,LED5, status);//PF1输出低电平
			break;
		case 6:
			GPIOPinWrite(GPIO_PORTL_BASE,LED6, status);//PF1输出低电平
			break;
		case 7:
			GPIOPinWrite(GPIO_PORTL_BASE,LED7, status);//PF1输出低电平
			break;
		default:break;
		}
	}
}
void led_initAll()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能GPIOF口
	GPIODirModeSet(GPIO_PORTF_BASE,LED0|LED1|LED2,GPIO_DIR_MODE_OUT); ////设置为输出模式
	GPIOPadConfigSet(GPIO_PORTF_BASE,LED0|LED1|LED2,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
	GPIOPinWrite(GPIO_PORTF_BASE,LED0|LED1|LED2, 0x00);//PF1输出低电平

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOF口
	GPIODirModeSet(GPIO_PORTL_BASE,LED3|LED4|LED5|LED6|LED7,GPIO_DIR_MODE_OUT); ////设置为输出模式
	GPIOPadConfigSet(GPIO_PORTL_BASE,LED3|LED4|LED5|LED6|LED7,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////进一步设置为8mA、带转换速率控制的推挽输出
	GPIOPinWrite(GPIO_PORTL_BASE,LED3|LED4|LED5|LED6|LED7, 0x00);//PF1输出低电平
}
void delay()
{
	int i,j;
	for(i=2000;i>0;i--)
		for(j=2000;j>0;j--)
		{
		}
}
void led_liushuideng()
{
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1); //PF1输出高，点亮LED0
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0); //PF1输出低，关闭LED0

	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); //PF2输出高，点亮LED1
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0); //PF2输出低，点亮LED1

	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0);

	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_0,GPIO_PIN_0);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_0,0);

	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_1,GPIO_PIN_1);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_1,0);

	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_2,GPIO_PIN_2);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_2,0);

	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_3,GPIO_PIN_3);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_3,0);

	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_4,GPIO_PIN_4);
	SysCtlDelay(100*(10000000/3000));         //延时n*1ms
	GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_4,0);
}
void led_test()
{
	led_initAll();
	led_liushuideng();
}
