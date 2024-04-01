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
#include "IR.h"

extern volatile uint8_t rec_cmd,fuwei;

volatile uint32_t  error= 0;
volatile uint32_t  count= 0;
unsigned char  IrData[4];
//红外解码输出，数字0-9对应的关系如下，地址吗为0x00
/*address 0x00
 * 0->22
 * 1->12
 * 2->24
 * 3->94
 * 4->8
 * 5->28
 * 6->90
 * 7->66
 * 8->82
 * 9->74
 * ch- ->0x45
 * ch  ->0x46
 * ch+ ->0x47
 * <-- ->0x44
 * --> ->0x40
 * >|| ->0x43
 * -   ->07
 * +   ->0x15
 * EQ  ->0x09
 */
/*
 * N1->D1
 * N0->D2
 * F4->D3
 * F0->D4
 * */
void IrOutput()
{
		//UARTprintf("%c",IrData[2]);
		//UARTprintf("\n");-
		switch(IrData[2])
		{

			case 22:  rec_cmd=0;
					  fuwei=1;
					  SysCtlReset();
					  IntMasterDisable();
					  break;

			case 12 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x02);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x02);
					  rec_cmd=1;
					  break;

			case 24 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x01);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x00);
					  rec_cmd=2;
					  break;

			case 94 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x03);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x00);
					  rec_cmd=3;
					  break;

			case 8 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x00);
					 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x10);
					 rec_cmd=4;
					 break;

			case 28 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x02);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x10);
					  rec_cmd=5;
					  break;

			case 90 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x01);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x10);
					  rec_cmd=6;
					  break;

			case 66 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x03);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x10);
					  rec_cmd=7;
					  break;

			case 82 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x00);
					  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x01);
					  rec_cmd=8;
					  break;

			case 74 : GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x02);
				      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x01);
				      rec_cmd=9;
				      break;

			default: GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1|GPIO_PIN_0 , 0x03);
					 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0 , 0x11);
		}
}
//////////////////////////////////////
//中断初始化
void GPIOIntInitial(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPION);//
    GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_4 );
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_4,GPIO_LOW_LEVEL);
    GPIOIntEnable(GPIO_PORTN_BASE,GPIO_INT_PIN_4);
}
/////////////////////////////////////
//红外解码
bool getdata()
{
		unsigned int i,j,IrAddressData,IrValueData;
		volatile uint32_t   temp = 0x00;
		IrAddressData = 0x00;
		IrValueData = 0x00;
		for(i=0;i<4;i++)
		{
			for(j=0;j<8;j++)
			{
				temp = temp>>1;
				while((GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_4)&0x10)==0x00)
				{
				}

				SysCtlDelay(7*120000000/30000);

		    	if((GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_4)&0x10)==0x10)
		    	{
		    		temp = temp|0x80;
		    		while((GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_4)&0x10)==0x10)
		    		{
		    			count++;
		    			if(count>0x200000)
		    			{
		    				count=0;
		    				return 0;
		    			}
		    		}
		    	}
		    	else
		    	{
		    		temp = temp&0x7f;
		    	}

			}
			IrData[i] = temp;
		}
		//abc = IrData[2];
		IrAddressData = IrData[0]+IrData[1];
		IrValueData = IrData[2]+IrData[3];
		if((IrAddressData==0xff)&&(IrValueData==0xff))
			return 1;
		else
			return 0;
}

