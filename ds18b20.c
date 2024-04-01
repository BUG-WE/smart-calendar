#include "stdint.h"
#include "stdbool.h"
#include "driverlib/debug.h"//����
#include "inc/hw_types.h"//�����������ã��Ĵ������ʷ�װ
#include "inc/hw_memmap.h"//��ַ
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"//ʹ�ܼĴ���
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
	 * ʹ�� GPIOPinTypeADC �� GPIO �ܽ�����Ϊ ADC ����
	 */
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    //����ADC0ʱ��
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
	// �����ɼ�
	/*
	 * ����Ϊֱ���ɴ������ں�����
	 * */
	ADCProcessorTrigger(ADC0_BASE, 3);
	// �ȴ��ɼ�����
	while(!ADCIntStatus(ADC0_BASE, 3, false)) ;
	// ��ȡ�ɼ����
	ADCSequenceDataGet(ADC0_BASE, 3, &ulADC0_Value);
	value=1.8663-ulADC0_Value/4096.0*3.3;
	ulADC0_Value=value*1000/11.69;
	TFTLCD_ShowData(100,110,ulADC0_Value,BLACK,WHITE);
	SysCtlDelay(SysCtlClockGet());
}
