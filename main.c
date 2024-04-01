//*****************************************************************************
//
// sd_card.c - Example program for reading files from an SD card.
//
// Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8049 of the EK-LM4F232 Firmware Package.
//
//*****************************************************************************

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

//*****************************************************************************
// System clock rate in Hz.
//
//*****************************************************************************
uint32_t g_ui32SysClock;


void SysTickHandler(void)
{
    //
    // Call the FatFs tick timer.
    //
    disk_timerproc();
}
//定时器B函数
void Timer0BIntHandler(void)
{
	unsigned long Status;

	//关闭中断TimerB
	TimerDisable(TIMER0_BASE, TIMER_B);
	//获取中断标志位
	Status=TimerIntStatus(TIMER0_BASE,true);
	if(Status==TIMER_TIMB_TIMEOUT)
	{
		Touch_PressKey();
		//identify_key();
//		GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1 , 0xff);
//		SysCtlDelay(500*(SysCtlClockGet()/3000));//2
//		//LED4灭
//		GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1 , 0x00);
//		SysCtlDelay(500*(SysCtlClockGet()/3000));//2
	}
	//请中断标志位
	TimerIntClear(TIMER0_BASE, Status);
	//重新设置TimerB
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet()/10);
	TimerEnable(TIMER0_BASE, TIMER_B);
}
//*****************************************************************************
//
// The program main function.  It performs initialization, then runs a command
// processing loop to read commands from the console.
//
//*****************************************************************************
int main(void)

{
	FPUInit();
    //
    // Run from the PLL at 120 MHz.
    //
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                SYSCTL_CFG_VCO_480), 120000000);
    InitAll();
    //IntPrioritySet(INT_TIMER0B, 0xe0);
    IntMasterEnable();
    IntEnable(INT_TIMER0B);
    TimerEnable(TIMER0_BASE, TIMER_B);
 	I2C0GPIOBEnable();//配置I2C0模块的IO引脚
    I2C0DeviceInit();//配置PCA9557芯片中连接米字管的各引脚为输出
    //buttonInit();
    Show_MianMenu();
	ADC_Init();

    while(1)
    {

    	//UARTgets(g_cCmdBuf, sizeof(g_cCmdBuf));//获取用户URUT输入
    	//TFTLCD_ShowChinese(10,265,g_cCmdBuf,BLACK,WHITE);
    	BoardTest();
    }
}
