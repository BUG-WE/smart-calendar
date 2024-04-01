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
//����Ƶ�ʣ�ȡֵ(ϵͳʱ��/65535UL)+1��12000����λ��Hz
#define   BUZZER_FREQUENCY     (SysCtlClockGet()/65535UL)||(usFreq>12000)
//GPIO�˿ڳ�ʼ��
void Yifan_Buzzer_Music_Play_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);  //  ʹ��PM5���ڵ�GPIO�˿�
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);                        //  ʹ��TIMER4ģ��

	GPIOPinConfigure(GPIO_PM5_T4CCP1);
    GPIOPinTypeTimer(GPIO_PORTM_BASE,GPIO_PIN_5);                     //  ����PM5���ڹܽ�ΪTimer����

    TimerConfigure(TIMER4_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PWM); //  ����Timer1BΪ16λPWM

    GPIODirModeSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_DIR_MODE_OUT);	////����Ϊ���ģʽ
	//GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD); /////��һ������Ϊ8mA����ת�����ʿ��Ƶ��������
	GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, 0);//PM5����ߵ�ƽ

	IntEnable(INT_TIMER4B);
	TimerEnable(TIMER4_BASE , TIMER_B);
}
//������ֹͣ����
void Yifan_Buzzer_Quiet()
{
    TimerDisable(TIMER4_BASE , TIMER_B);                        				//  ��ֹTimerB������PWMֹͣ���
    GPIODirModeSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_DIR_MODE_OUT);               //  ����PM5���ڹܽ�ΪGPIO���
    //GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_5,GPIO_STRENGTH_8MA_SC,GPIO_PIN_TYPE_STD);
    GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_5, 0x00);
}
//����������ָ��Ƶ�ʵ�����
//usFreq�Ƿ���Ƶ�ʣ�
void Yifan_Buzzer_Sound(ushort usFreq)
{
  ulong ulVal;
  if (usFreq<=BUZZER_FREQUENCY)
  {
    //������ֹͣ����
    Yifan_Buzzer_Quiet();
  }
  else
  {
    //������عܽ�ΪTimer����
	GPIOPinTypeTimer(GPIO_PORTM_BASE,GPIO_PIN_5);
    ulVal=(SysCtlClockGet())/usFreq;
    TimerLoadSet(TIMER4_BASE , TIMER_B , ulVal);            //  ����TimerB��ֵ������PWM����
    TimerMatchSet(TIMER4_BASE , TIMER_B , ulVal / 2);       //  ����TimerBƥ��ֵ������PWMռ�ձ�
    TimerEnable(TIMER4_BASE , TIMER_B);
  }
}
//  ��������
void Yifan_Buzzer_Music_Play(tMusic_hy *Yifan_Play_music)
{
  int i;
  for (i=0;;i++)
  {
    //����ǽ��������˳�
    if(Yifan_Play_music[i].Music_Time == 0)
    	break;
    //������������ͬ����
    Yifan_Buzzer_Sound(Yifan_Play_music[i].Music_Name);
    //����ʱֵ��λ�����������ٶȣ���ֵ��λ��ms��
    SysCtlDelay(Yifan_Play_music[i].Music_Time*(g_ui32SysClock/3000));
    //������ֹͣ����
    Yifan_Buzzer_Quiet();
    //��ʱ10ms
    SysCtlDelay(10*(g_ui32SysClock/3000));
  }
}
void MusicRun(void)
{
	int i;
	while(1)
	{
	    //���֣����������������Žܡ���
	    for (i=0;i<1;i++)//ѭ�������������
	    {
	       Yifan_Buzzer_Music_Play(my_music_kanyueliangpashanglai);
	       SysCtlDelay(2000*(g_ui32SysClock/3000));
	    }
	    //���֣���������ף����
//	    for (i=0;i<1;i++)//ѭ�������������
//	    {
//	       Yifan_Buzzer_Music_Play(my_music_huadie);
//	       SysCtlDelay(5000*(g_ui32SysClock/3000));
//	    }
	}
}
