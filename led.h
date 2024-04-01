#ifndef __LED_H_
#define __LED_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"

#define LED03   GPIO_PORTF_BASE
#define LED0   	GPIO_PIN_1
#define LED1   	GPIO_PIN_2
#define LED2    GPIO_PIN_3

#define LED37   GPIO_PORTF_BASE
#define LED3    GPIO_PIN_0
#define LED4    GPIO_PIN_1
#define LED5    GPIO_PIN_2
#define LED6    GPIO_PIN_3
#define LED7    GPIO_PIN_4

/*! ö��LED��� */
/*
typedef enum
{
  LED0=0x00000002,
  LED1=0x00000004,
  LED2=0x00000008,
  LED3=0x00000001,
  LED4=0x00000002,
  LED5=0x00000004,
  LED6=0x00000008,
  LED7=0x00000010,
  LED_MAX,
}LED_e;*/
/*
 * 0XFFΪ��
 * 0x00Ϊ��
 * */

/*! ö��LED����״̬ */
typedef enum LED_status
{
  LED_ON  =   0xff,            //����(��Ӧ�͵�ƽ)
  LED_OFF =   0x00             //�ư�(��Ӧ�ߵ�ƽ)
}LED_status;

extern void    led_init(int ledn);            //��ʼ��LED�˿�
extern void    led(int,LED_status);      //����LED������
extern void    led_turn(int);            //����LED������ת
extern void    led_liushuideng();			//��ˮ��
extern void    led_initAll();				//ȫ����ʼ��
extern void    delay();
extern void    led_test();
#endif
