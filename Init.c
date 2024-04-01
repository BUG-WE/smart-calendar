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
#include "driverlib/timer.h"
#include "driverlib/ssi.h"
#include "driverlib/fpu.h"
#include "utils/uartstdio.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
#include "TOUCHinit/TOUCH_TSC2046.h"
#include "EPIinit/EPIinit.h"
#include "Init.h"


extern uint32_t g_ui32SysClock;
//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}
void TFTInit(void)
{
    EPIGPIOinit();

    TFT_400x240_OTM4001Ainit(g_ui32SysClock);
    // Open BackLight.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
void InterInit(void)
{
    SysTickPeriodSet(g_ui32SysClock / TICKS_PER_SECOND);
    //
    // Enable interrupts to the processor.
    //
    //IntMasterEnable();

    //
    // Enable the SysTick Interrupt.
    //
    SysTickIntEnable();

    //
    // Enable SysTick.
    //
    SysTickEnable();
}
void FPUInit(void)
{
    //
    // The FPU should be enabled because some compilers will use floating-
    // point registers, even for non-floating-point code.  If the FPU is not
    // enabled this will cause a fault.  This also ensures that floating-
    // point operations could be added to this application and would work
    // correctly and use the hardware floating-point unit.  Finally, lazy
    // stacking is enabled for interrupt handlers.  This allows floating-
    // point instructions to be used within interrupt handlers, but at the
    // expense of extra stack usage.
    //
    FPUEnable();
    FPULazyStackingEnable();
}
void TFTTouchInit(void)
{
    TOUCH_TSC2046init(g_ui32SysClock);
}
extern void Timer0BIntHandler(void);
void TimerIntInitial(void)
{
	//初始化Timer0时钟
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	//配置Timer0，TIMER_CFG_SPLIT_PAIR 拆分寄存器A和B,设置寄存器B为连续减计数
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR  | TIMER_CFG_B_PERIODIC);

	//设置时钟计数范围，g_ui32SysClock=120M,则计数为600000,5ms
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet()/10);

	TimerIntRegister(TIMER0_BASE,TIMER_B,Timer0BIntHandler);
	//用TimerIntRegister向系统注册中断处理函数，用TimerIntEnable来允许某个定时器的中断请求
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}
void power_on (void)
{
    /*
     * This doesn't really turn the power on, but initializes the
     * SSI port and pins needed to talk to the card.
     */

    /* Enable the peripherals used to drive the SDC on SSI */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SDC_SSI_SYSCTL_PERIPH);

    ROM_GPIOPinConfigure(GPIO_PD3_SSI2CLK);
    ROM_GPIOPinConfigure(GPIO_PD2_SSI2FSS);
    ROM_GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);
    ROM_GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);


    /*
     * Configure the appropriate pins to be SSI instead of GPIO. The FSS (CS)
     * signal is directly driven to ensure that we can hold it low through a
     * complete transaction with the SD card.
     */
    ROM_GPIOPinTypeSSI(SDC_SSI_TX_GPIO_PORT_BASE, SDC_SSI_TX);
    ROM_GPIOPinTypeSSI(SDC_SSI_RX_GPIO_PORT_BASE, SDC_SSI_RX);
    ROM_GPIOPinTypeSSI(SDC_SSI_CLK_GPIO_PORT_BASE, SDC_SSI_CLK);
    ROM_GPIOPinTypeGPIOOutput(SDC_SSI_FSS_GPIO_PORT_BASE, SDC_SSI_FSS);

    /*
     * Set the SSI output pins to 4MA drive strength and engage the
     * pull-up on the receive line.
     */
    MAP_GPIOPadConfigSet(SDC_SSI_RX_GPIO_PORT_BASE, SDC_SSI_RX,
                         GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    MAP_GPIOPadConfigSet(SDC_SSI_CLK_GPIO_PORT_BASE, SDC_SSI_CLK,
                         GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    MAP_GPIOPadConfigSet(SDC_SSI_TX_GPIO_PORT_BASE, SDC_SSI_TX,
                         GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    MAP_GPIOPadConfigSet(SDC_SSI_FSS_GPIO_PORT_BASE, SDC_SSI_FSS,
                         GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    /* Configure the SSI3 port */
    ROM_SSIConfigSetExpClk(SDC_SSI_BASE, g_ui32SysClock,
                           SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 400000, 8);
    ROM_SSIEnable(SDC_SSI_BASE);
}
void RomInit(void)
{
    //
    // Enable the peripherals used by this example.
    //

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);
    ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
    //
    // Configure SysTick for a 100Hz interrupt.  The FatFs driver wants a 10 ms
    // tick.
    //

    ROM_SysTickPeriodSet(g_ui32SysClock / 240);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();

    //
    // Enable Interrupts
    //
    ROM_IntMasterEnable();
    power_on();
}
void InitAll(void)
{
	InterInit();
	TFTTouchInit();
	ConfigureUART();
	TFTInit();
	RomInit();
	SysCtlDelay(1000*SysCtlClockGet()/3000);//SysCtlClockGet()/3000 1ms
	TimerIntInitial();
}
