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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "TFT_400x240_OTM4001A_16bit.h"

extern uint32_t g_ui32SysClock;
void ADC_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	/*
	 * ʹ�� GPIOPinTypeADC �� GPIO �ܽ�����Ϊ ADC ����
	 */
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_7);
    //����ADC0ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE,3,ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_END | ADC_CTL_IE);
    ADCSequenceEnable(ADC0_BASE, 3);
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    ADCIntClear(ADC0_BASE, 3);
}
void ADC_Get(void)
{
	uint32_t ulADC0_Value;
	uint32_t temp;
	//float value;
	// �����ɼ�
	/*
	 * ����Ϊֱ���ɴ������ں�����
	 * */
	ADCProcessorTrigger(ADC0_BASE, 3);
	// �ȴ��ɼ�����
	while(!ADCIntStatus(ADC0_BASE, 3, false)) ;
	// ��ȡ�ɼ����
	ADCSequenceDataGet(ADC0_BASE, 3, &ulADC0_Value);
	ulADC0_Value=147.5-((75*3.3*(float)ulADC0_Value)/4096);
	if(ulADC0_Value<10){
		Number_Show_one(10,190,0,32,BLACK, WHITE);//��������1
		Number_Show_one(25,190,ulADC0_Value,32,BLACK, WHITE);//��������2
	}else{
		temp=ulADC0_Value % 10;
		ulADC0_Value=ulADC0_Value/10;
		Number_Show_one(10,190,ulADC0_Value,32,BLACK, WHITE);//��������1
		Number_Show_one(25,190,temp,32,BLACK, WHITE);//��������2
	}
	//UARTprintf("%04d   \n ", ulADC0_Value );
	SysCtlDelay(SysCtlClockGet());
}
