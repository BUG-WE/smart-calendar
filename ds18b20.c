#include "stdint.h"
#include "stdbool.h"
#include "driverlib/debug.h"//调试
#include "inc/hw_types.h"//数据类型设置，寄存器访问封装
#include "inc/hw_memmap.h"//基址
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"//使能寄存器
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "grlib/grlib.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c1294ncpdt.h"
#include "TFT_400x240_OTM4001A_16bit.h"
#include "ds18b20.h"

void ds18b20_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	/*
	 * 使用 GPIOPinTypeADC 将 GPIO 管脚配置为 ADC 功能
	 */
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    //开启ADC0时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE,3,ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_END | ADC_CTL_IE);
    ADCSequenceEnable(ADC0_BASE, 3);
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    ADCIntClear(ADC0_BASE, 3);
}
void ds18b20_Get(void)
{
	uint32_t ulADC0_Value;
	float value;
	// 触发采集
	/*
	 * 配置为直接由处理器内核启动
	 * */
	ADCProcessorTrigger(ADC0_BASE, 3);
	// 等待采集结束
	while(!ADCIntStatus(ADC0_BASE, 3, false)) ;
	// 获取采集结果
	ADCSequenceDataGet(ADC0_BASE, 3, &ulADC0_Value);
	value=1.8663-ulADC0_Value/4096.0*3.3;
	ulADC0_Value=value*1000/11.69;
	TFTLCD_ShowData(100,110,ulADC0_Value,BLACK,WHITE);
	SysCtlDelay(SysCtlClockGet());
}
