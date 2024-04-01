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

/*! 枚举LED编号 */
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
 * 0XFF为亮
 * 0x00为灭
 * */

/*! 枚举LED亮灭状态 */
typedef enum LED_status
{
  LED_ON  =   0xff,            //灯亮(对应低电平)
  LED_OFF =   0x00             //灯暗(对应高电平)
}LED_status;

extern void    led_init(int ledn);            //初始化LED端口
extern void    led(int,LED_status);      //设置LED灯亮灭
extern void    led_turn(int);            //设置LED灯亮灭反转
extern void    led_liushuideng();			//流水灯
extern void    led_initAll();				//全部初始化
extern void    delay();
extern void    led_test();
#endif
