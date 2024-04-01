
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"
#include "led.h"
#include "Button.h"
//#include "touchTFT.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
volatile uint32_t ui32Loop;
volatile uint32_t key;
int led1,led2;

void delay1()
{
	int ui32Loop0;
	for(ui32Loop0=0;ui32Loop0<1000;ui32Loop0++)  //delay1
	{;}
}
int identify_key()
{
    key=0;
    GPIO_PORTD_AHB_DATA_R = 0x00;
    GPIO_PORTH_AHB_DATA_R = 0x0c;
    GPIO_PORTM_DATA_R = 0x08;
    for(ui32Loop=0;ui32Loop<1000;ui32Loop++)  //delay
    {
        ;
    }
 if((GPIO_PORTP_DATA_R&0x04)==0x00)//&&(GPIO_PORTP_DATA_R==0x04)
     {
     delay();
     if((GPIO_PORTP_DATA_R&0x04)==0x00)
     {
         key=1;
         return 0;
     }
     }
 else
     if((GPIO_PORTN_DATA_R&0x08)==0x00)
     {

         delay();
         if((GPIO_PORTN_DATA_R&0x08)==0x00)
         {
             key=5;
             return 0;
         }
     }
     else
         if((GPIO_PORTN_DATA_R&0x04)==0x00)
         {
             delay();
             if((GPIO_PORTN_DATA_R&0x04)==0x00)
             {
                 key=9;
                 return 0;
             }
         }
         else
             if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
             {
                 delay();
                 if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                 {
                     key=13;
                     return 0;
                 }
             }

    GPIO_PORTD_AHB_DATA_R = 0x02;
    GPIO_PORTH_AHB_DATA_R = 0x04;
    GPIO_PORTM_DATA_R = 0x08;
    for(ui32Loop=0;ui32Loop<1000;ui32Loop++)
    {
        ;
    }
    if((GPIO_PORTP_DATA_R&0x04)==0x00)//&&(GPIO_PORTP_DATA_R==0x04)
             {
                 delay();
                 if((GPIO_PORTP_DATA_R&0x04)==0x00)
                 {
                     key=2;
                     return 0;
                 }
             }
         else
             if((GPIO_PORTN_DATA_R&0x08)==0x00)
             {

                 delay();
                 if((GPIO_PORTN_DATA_R&0x08)==0x00)
                 {
                     key=6;
                     //rec_cmd=1;
                     return 0;
                 }
             }
             else
                 if((GPIO_PORTN_DATA_R&0x04)==0x00)
                 {
                     delay();
                     if((GPIO_PORTN_DATA_R&0x04)==0x00)
                     {
                         key=10;
                         return 0;
                     }
                 }
                 else
                     if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                     {
                         delay();
                         if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                         {
                             key=14;
                             return 0;
                         }
                     }

    GPIO_PORTD_AHB_DATA_R = 0x02;
    GPIO_PORTH_AHB_DATA_R = 0x08;
    GPIO_PORTM_DATA_R = 0x08;
    for(ui32Loop=0;ui32Loop<1000;ui32Loop++)
    {
        ;
    }
    if((GPIO_PORTP_DATA_R&0x04)==0x00)//&&(GPIO_PORTP_DATA_R==0x04)
             {
                 delay();
                 if((GPIO_PORTP_DATA_R&0x04)==0x00)
                 {
                     key=3;
                     return 0;
                 }
             }
         else
             if((GPIO_PORTN_DATA_R&0x08)==0x00)
             {

                 delay();
                 if((GPIO_PORTN_DATA_R&0x08)==0x00)
                 {
                     key=7;
                     return 0;
                 }
             }
             else
                 if((GPIO_PORTN_DATA_R&0x04)==0x00)
                 {
                     delay();
                     if((GPIO_PORTN_DATA_R&0x04)==0x00)
                     {
                         key=11;
                         return 0;
                     }
                 }
                 else
                     if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                     {
                         delay();
                         if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                         {
                             key=15;
                             return 0;
                         }
                     }


    GPIO_PORTD_AHB_DATA_R = 0x02;
    GPIO_PORTH_AHB_DATA_R = 0x0c;
    GPIO_PORTM_DATA_R = 0x00;
    for(ui32Loop=0;ui32Loop<1000;ui32Loop++)
    {
        ;
    }
    if((GPIO_PORTP_DATA_R&0x04)==0x00)//&&(GPIO_PORTP_DATA_R==0x04)
             {
                 delay();
                 if((GPIO_PORTP_DATA_R&0x04)==0x00)
                 {
                     key=4;
                     return 0;
                 }
             }
         else
             if((GPIO_PORTN_DATA_R&0x08)==0x00)
             {

                 delay();
                 if((GPIO_PORTN_DATA_R&0x08)==0x00)
                 {
                     key=8;
                     return 0;
                 }
             }
             else
                 if((GPIO_PORTN_DATA_R&0x04)==0x00)
                 {
                     delay();
                     if((GPIO_PORTN_DATA_R&0x04)==0x00)
                     {
                         key=12;
                         return 0;
                     }
                 }
                 else
                     if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                     {
                         delay();
                         if((GPIO_PORTD_AHB_DATA_R&0x01)==0x00)
                         {
                             key=16;
                             return 0;
                         }
                     }
return 1;
}

void buttonInit()
{
    SYSCTL_RCGCGPIO_R |= (SYSCTL_RCGCGPIO_R13 | SYSCTL_RCGCGPIO_R12 | SYSCTL_RCGCGPIO_R11 |SYSCTL_RCGCGPIO_R10| SYSCTL_RCGCGPIO_R7 |SYSCTL_RCGCGPIO_R3 );//

    GPIO_PORTN_DIR_R = 0x03;
    GPIO_PORTM_DIR_R = 0x28;
    GPIO_PORTH_AHB_DIR_R = 0x0c;
    GPIO_PORTP_DIR_R = 0x00;
    GPIO_PORTD_AHB_DIR_R = 0x02;
    GPIO_PORTL_DIR_R = 0x0f;

    GPIO_PORTN_DEN_R = 0x0f;
    GPIO_PORTM_DEN_R = 0x28;
    GPIO_PORTH_AHB_DEN_R = 0x0c;
    GPIO_PORTP_DEN_R = 0x04;
    GPIO_PORTD_AHB_DEN_R = 0x03;
    GPIO_PORTL_DEN_R = 0x0f;

    return;
}



void buttonShow()
{
	while(1)
	{
		int a;
		identify_key();
		a=key;
		int temp;
		int temp2;
		UARTprintf("%d\n",a);
		if(0<a<10){
			Number_Show_one(90,70,0,64,BLACK, WHITE);
			Number_Show_one(120,70,a,64,BLACK, WHITE);
		}else if (a>10){
			temp=a % 10;
			temp2=a/10;
			Number_Show_one(90,70,temp2,64,BLACK, WHITE);
			Number_Show_one(120,70,temp,64,BLACK, WHITE);
		}
		/*switch(a)
		{

		case 1 : GPIO_PORTN_DATA_R |= 0x02;GPIO_PORTF_AHB_DATA_R = 0x00;GPIO_PORTM_DATA_R|=0x20;break;
		case 2 : GPIO_PORTN_DATA_R |= 0x01;GPIO_PORTF_AHB_DATA_R = 0x00;GPIO_PORTM_DATA_R|=0x20;break;
		case 3 : GPIO_PORTN_DATA_R |= 0x03;GPIO_PORTF_AHB_DATA_R = 0x00;GPIO_PORTM_DATA_R|=0x20;break;
		case 4 : GPIO_PORTN_DATA_R |= 0x00;GPIO_PORTF_AHB_DATA_R = 0x10;GPIO_PORTM_DATA_R|=0x20;break;
		case 5 : GPIO_PORTN_DATA_R |= 0x02;GPIO_PORTF_AHB_DATA_R = 0x10;GPIO_PORTM_DATA_R|=0x20;break;
		case 6 : GPIO_PORTN_DATA_R |= 0x01;GPIO_PORTF_AHB_DATA_R = 0x10;GPIO_PORTM_DATA_R|=0x20;break;
		case 7 : GPIO_PORTN_DATA_R |= 0x03;GPIO_PORTF_AHB_DATA_R = 0x10;GPIO_PORTM_DATA_R|=0x20;break;
		case 8 : GPIO_PORTN_DATA_R |= 0x00;GPIO_PORTF_AHB_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;break;
		case 9 : GPIO_PORTN_DATA_R |= 0x02;GPIO_PORTF_AHB_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;break;
		case 10 : GPIO_PORTN_DATA_R |= 0x01;GPIO_PORTF_AHB_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;break;
		case 11 : GPIO_PORTN_DATA_R |= 0x03;GPIO_PORTF_AHB_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;break;
		case 12 : GPIO_PORTN_DATA_R |= 0x00;GPIO_PORTF_AHB_DATA_R = 0x11;GPIO_PORTM_DATA_R|=0x20;break;
		case 13 : GPIO_PORTN_DATA_R |= 0x02;GPIO_PORTF_AHB_DATA_R = 0x11;GPIO_PORTM_DATA_R|=0x20;break;
		case 14 : GPIO_PORTN_DATA_R |= 0x01;GPIO_PORTF_AHB_DATA_R = 0x11;GPIO_PORTM_DATA_R|=0x20;break;
		case 15 : GPIO_PORTN_DATA_R |= 0x03;GPIO_PORTF_AHB_DATA_R = 0x11;GPIO_PORTM_DATA_R|=0x20;break;
		case 16 : GPIO_PORTN_DATA_R |= 0x00;GPIO_PORTF_AHB_DATA_R = 0x00;GPIO_PORTM_DATA_R|=0x20;break;
		default: GPIO_PORTN_DATA_R = 0x00;GPIO_PORTF_AHB_DATA_R = 0x00;GPIO_PORTM_DATA_R&=0xdf;
		}*/

		switch(a)
				{

				case 1 : break;//GPIO_PORTL_DATA_R = 0x01;
				//GPIO_PORTM_DATA_R|=0x20;break;
				case 2 :break; //GPIO_PORTL_DATA_R = 0x02;
				//GPIO_PORTM_DATA_R|=0x20;break;
				//case 3 : GPIO_PORTL_DATA_R = 0x03;
				//GPIO_PORTM_DATA_R|=0x20;break;
				case 4 :break; //GPIO_PORTL_DATA_R = 0x04;
				//GPIO_PORTM_DATA_R|=0x20;break;
				case 5 : break;//GPIO_PORTL_DATA_R = 0x05;
					//GPIO_PORTM_DATA_R|=0x20;break;
				case 6 : break;//GPIO_PORTL_DATA_R = 0x06;GPIO_PORTM_DATA_R|=0x20;break;
				case 7 :break; //GPIO_PORTL_DATA_R = 0x07;GPIO_PORTM_DATA_R|=0x20;break;
				case 8 : break;//GPIO_PORTL_DATA_R = 0x08;GPIO_PORTM_DATA_R|=0x20;break;
				case 9 : break;//GPIO_PORTL_DATA_R = 0x09;
				//GPIO_PORTM_DATA_R|=0x20;break;
				case 10 : break;//GPIO_PORTL_DATA_R = 0x0a;GPIO_PORTM_DATA_R|=0x20;break;
				case 11 : break;//GPIO_PORTL_DATA_R = 0x0b;GPIO_PORTM_DATA_R|=0x20;break;
				case 12 : break;//GPIO_PORTL_DATA_R = 0x0c;GPIO_PORTM_DATA_R|=0x20;break;
				case 13 : break;//GPIO_PORTL_DATA_R = 0x0d;
				//GPIO_PORTM_DATA_R|=0x20;break;
				case 14 : break;//GPIO_PORTL_DATA_R = 0x0e;GPIO_PORTM_DATA_R|=0x20;break;
				case 15 : break;//GPIO_PORTL_DATA_R = 0x0f;GPIO_PORTM_DATA_R|=0x20;break;
				case 16 : break;//GPIO_PORTL_DATA_R = 0x00;GPIO_PORTM_DATA_R|=0x20;break;
				default: break;//GPIO_PORTN_DATA_R = 0x00;GPIO_PORTM_DATA_R&=0xdf;
				}
		for(ui32Loop=0;ui32Loop<5000;ui32Loop++)
		{
			;
		}
	}
}
