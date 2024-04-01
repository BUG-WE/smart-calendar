#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "IICmiziguan.h"

#define _NOP() _nop()

//*********************************************************************
//*********************************************************************
#define I2C0_MASTER_BASE 0x40020000
#define I2C0_SLAVE_BASE 0x40020000

//*********************************************************************
// ��ַ���Ĵ����ȶ��岿��
//*********************************************************************
//*********************************************************************
//
// �趨slave���ӣ�ģ��ĵ�ַ������һ��7-bit�ĵ�ַ����RSλ��������ʽ����:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
// RSλ��һ��ָʾλ�����RS=0����˵�������������ݣ��ӽ������ݣ�RS=1˵�������������ݣ��ӷ�������
//
//*********************************************************************
//U21����4�����ֹܺ�����ܽŵ�����
#define I2C0_ADDR_TUBE_SEL	      0x30  //00110000
//U22�������ֹ�7~14�ܽŶ�Ӧ�����
#define I2C0_ADDR_TUBE_SEG_LOW    0x32  //00110010
//U23�������ֹ�15~18�ܽŶ�Ӧ�����
#define I2C0_ADDR_TUBE_SEG_HIGH   0x34   //00110100
//U24����LED����

//PCA9557�ڲ��Ĵ�����Ҳ���ӵ�ַ
#define PCA9557_REG_INPUT	 0x00
#define PCA9557_REG_OUTPUT	 0x01
#define PCA9557_REG_PolInver 0x02
#define PCA9557_REG_CONFIG	 0x03

//*************************************************************************************
 #define NUM 0
//IIC ����������ʱ������
unsigned char I2C_RECV_DATA[] =
				{
					0x00,
					0x00,
					0x00,
					0x00,
					0x00,
					0x00
				};


/*******************************************
		���� SDA �ź�
********************************************/
void I2C_Set_sda_high( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,GPIO_PIN_3);  //����PB3
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SDA �ź�
********************************************/
void I2C_Set_sda_low ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,0X00000000);  //����PB3
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SCL �ź�
********************************************/
void I2C_Set_scl_high( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,GPIO_PIN_2);  //����PB2
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SCL �ź�
********************************************/
void I2C_Set_scl_low ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,0X00000000);  //����PB2
    _NOP();
    _NOP();
    return;
}

/*******************************************
		IIC �źŽ����źź���
********************************************/
void I2C_STOP(void)
{
    int i;
    I2C_Set_sda_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high();
    for(i = NUM+1;i > 0;i--);
    return;
}


/*******************************************
		IIC �źų�ʼ��
********************************************/
void I2C_Initial( void )
{
    I2C_Set_scl_low();
    I2C_STOP();
    return;
}


/*******************************************
		IIC �ź���ʼ�źź���
********************************************/
void I2C_START(void)
{
    int i;

    I2C_Set_sda_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low();
    return;
}

/*******************************************
		IIC ��ȡӦ����
********************************************/
int  I2C_GetACK(void)
{
    int j;
    _NOP();
    _NOP();
    I2C_Set_scl_low();
    for(j = NUM;j> 0;j--);
    I2C_Set_scl_high();
    for(j = NUM;j> 0;j--);
    I2C_Set_sda_low();
    for(j = NUM;j > 0;j--);
    I2C_Set_scl_low();
    return 1;
}

/*******************************************
		IIC ����Ӧ����
********************************************/
void I2C_SetNAk(void)
{
    I2C_Set_scl_low();
    I2C_Set_sda_high();
    I2C_Set_scl_high();
    I2C_Set_scl_low();
    return;
}

/*******************************************
		IIC �����ֽں���
		���� 	1��Ҫ�����ֽ�ֵ
		return ���޷���
********************************************/
void I2C_TxByte(unsigned char nValue)
{
    int i;
    int j;
    for(i = 0;i < 8;i++)
    {
    	if(nValue & 0x80)
    	    I2C_Set_sda_high();
    	else
    	    I2C_Set_sda_low();
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_high();
    	nValue <<= 1;
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_low();
    }

    return;
}

/*******************************************
		IIC �����ֽں���
		���� 		��
		return ���޷���
********************************************/
unsigned char  I2C_RxByte(void)
{
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);//����PB3Ϊ�����
    unsigned char nTemp=0 ;
    int i;

    I2C_Set_sda_high();

    _NOP();
    _NOP();
    _NOP();
    _NOP();
    for(i = 0;i < 8;i++)
    {
    	I2C_Set_scl_high(); //ģ��SCL�ź�
    	if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_3) == 0x18) //�����ж�PB3��SDA������
     	{
    	    nTemp |= (0x01 << (7-i));  //8λSDA������һλΪ�߾���1
    	}
    	I2C_Set_scl_low();
    	SysCtlDelay(5);
    }

    return nTemp;

}

/*******************************************
		IIC �������麯��
	����  	1 num : �����ֽ���
	    2 device_addr : iicĿ���ַ
	    3 *data	�����������ַ
	return ���޷���
********************************************/
void i2c_write(int num, unsigned char device_addr,unsigned char *data)
{
    int i = 0;
    int count = num;
    unsigned char *send_data = data;
    unsigned char write_addr = device_addr;

    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high();
    for(i = NUM;i > 0;i--);

    for(i = 0;i < count;i++)
    {
      I2C_START();           //ģ��I2Cд���ݵ�ʱ��
      I2C_TxByte(write_addr);
      I2C_GetACK();
      I2C_TxByte(send_data[i]);
      I2C_GetACK();
      i++;
      I2C_TxByte(send_data[i]);
      I2C_GetACK();
      I2C_STOP();
    }

}

/*******************************************
		IIC ��ȡ���麯��
	����  	1 num : �����ֽ���
	    2 device_addr : iicĿ���ַ
	    3 *data	�����������ַ
	return ���޷���
********************************************/
void i2c_read(int num, unsigned char device_addr,unsigned char *data)
{
  int i = 0;
  int count = num;
  unsigned char *send_data = data;
  unsigned char read_addr = device_addr;

  I2C_Set_scl_high();
  for(i = NUM;i > 0;i--);
  I2C_Set_sda_high();
  for(i = NUM;i > 0;i--);

  for(i = 0; i < count;i++)
  {
    I2C_START();               //ģ��I2C������
    I2C_TxByte((read_addr - 1));
    I2C_GetACK();
    I2C_TxByte(send_data[2*i]);
    I2C_GetACK();

    I2C_START();
    I2C_TxByte(read_addr);
    I2C_GetACK();

    I2C_RECV_DATA[i] = I2C_RxByte();
    data[2*i+1]=I2C_RECV_DATA[i];
    I2C_SetNAk();
    I2C_STOP();
  }

}

//*********************************************************************

//*********************************************************************
//******����I2C0ģ���IO���ţ�**********************************************
void I2C0GPIOBEnable(void)
{	// Enable GPIO portB containing the I2C pins (PB2&PB3)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3);

}

//******����PCA9557оƬ���������ֹܵĸ�����Ϊ���***********************************
void I2C0DeviceInit(void)
{
	unsigned char dataBuf[2] = {PCA9557_REG_CONFIG, 0x00};
	i2c_write(2,I2C0_ADDR_TUBE_SEL,dataBuf);
	i2c_write(2,I2C0_ADDR_TUBE_SEG_LOW,dataBuf);
	i2c_write(2,I2C0_ADDR_TUBE_SEG_HIGH,dataBuf);

}

//*******�������ֹܵĹ�ѡ�ź�**************************************************
void I2C0TubeSelSet(char data)
{   //ѡ��1��2��3��4��5�ĸ����ֹ���
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data};
	i2c_write(2,I2C0_ADDR_TUBE_SEL,dataBuf);
}
//*******�������ֹܵ���Ӧ���**************************************************
void I2C0TubeLowSet(char data)
{  //����7-14�ܽŶ�Ӧ�����
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data};
	i2c_write(2,I2C0_ADDR_TUBE_SEG_LOW,dataBuf);
}
void I2C0TubeHighSet(char data)
{  //����15-18�ܽŶ�Ӧ�����
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data};
	i2c_write(2,I2C0_ADDR_TUBE_SEG_HIGH,dataBuf);
}

//********Ԥ�����ֵ���������************************************************
static const char tubeCodeTable[10][2]=
		{ //  SegmLow, SegHigh
			{	0x10,	0x3E	},		// 	    	0
			{	0x00,	0x18	},		// 	        1
			{	0x70,	0x2C	},		//      	2
            {	0x70,	0x26	},		//       	3
            {	0x60,	0x32	},		//      	4
            {	0x70,	0x16	},		//     		5
            {	0x70,	0x1E	},		//     		6
            {	0x00,	0x26	},		//     		7
            {	0x70,	0x3E	},		//     		8
            {	0x70,	0x36	},	    //     		9
//            {	0x60,	0x3E	},	    //     		a
		};


unsigned char a[2];
void setnumber(char value)
{
    char b;
    b=value;
    switch(b){
    case 0:{ a[0]=tubeCodeTable[0][0];a[1]=tubeCodeTable[0][1];break;}
    case 1:{ a[0]=tubeCodeTable[1][0];a[1]=tubeCodeTable[1][1];break;}
    case 2:{ a[0]=tubeCodeTable[2][0];a[1]=tubeCodeTable[2][1];break;}
    case 3:{ a[0]=tubeCodeTable[3][0];a[1]=tubeCodeTable[3][1];break;}
    case 4:{ a[0]=tubeCodeTable[4][0];a[1]=tubeCodeTable[4][1];break;}
    case 5:{ a[0]=tubeCodeTable[5][0];a[1]=tubeCodeTable[5][1];break;}
    case 6:{ a[0]=tubeCodeTable[6][0];a[1]=tubeCodeTable[6][1];break;}
    case 7:{ a[0]=tubeCodeTable[7][0];a[1]=tubeCodeTable[7][1];break;}
    case 8:{ a[0]=tubeCodeTable[8][0];a[1]=tubeCodeTable[8][1];break;}
    case 9:{ a[0]=tubeCodeTable[9][0];a[1]=tubeCodeTable[9][1];break;}
    	     }
}
void I2C0Tubeset(void)
{
	I2C0TubeLowSet(a[0]);
	I2C0TubeHighSet(a[1]);

}
void showvalue(char value)
{
    setnumber(value);
    I2C0Tubeset();
}
//      SysCtlDelay(SysCtlClockGet()/6);
//*********************************************************************
// main ����
//*********************************************************************

/*
 * I2C0TubeSelSet();ѡ�����ֹ� 1 2 3 4�������
 * 11011111������һ�����ֹ�
 * 11111101���ڶ������ֹ�
 * 11111011�����������ֹ�
 * 11110111�����ĸ����ֹ�
 * 11101111��������ֹܣ����������ֹ�
 *
 *I2C0TubeLowSet();��һλû�ã�14,13,12,11,10,9,8,_
 *I2C0TubeHighSet();��һλ�͸���λû�ã�_,_,15,7,18,17,16,_
 *
 *
 *A��A,B,C,E,F,G1,G2�������Զ�Ӧ17,15,16,18,7,12,13Ϊ�ߵ�ƽ,01100000��00111110��0x60��0x3e
 *B��A,B,C,D,E,F,G1,G2�������Զ�Ӧ17,15,16,11,18,7,12,13Ϊ�ߵ�ƽ��01110000��00111110��0x70��0x3e
 *C��A,D,E,F������Ӧ17,11,18,7Ϊ�ߵ�ƽ����00010000��00011100��0x10��0x1c
 *D��A,B,C,D,E,F������Ӧ17,15,16,11,18,7������00010000��00111110��0x10��0x3e
 * */
void showABCD(void)
{
	while(1)
	{
		I2C0TubeSelSet(~0x20);         	//ѡ���һ�����ֹܣ�11011111
		I2C0TubeLowSet(0x60);         	//01100000
		I2C0TubeHighSet(0x3e);        	//  00111110
		SysCtlDelay(20000*(1000000/3000));           	//��ʱn*3��ָ��ʱ��

		I2C0TubeSelSet(~0x02);		   	//ѡ��ڶ������ֹܣ�11111101
		I2C0TubeLowSet(0x70);      	   	//01110000
		I2C0TubeHighSet(0x3e);		   	//00111110
		SysCtlDelay(20000*(1000000/3000));

		I2C0TubeSelSet(~0x04);			//ѡ����������ֹܣ�11111011
		I2C0TubeLowSet(0x10);        	//00010000
		I2C0TubeHighSet(0x1c);			//00011100
		SysCtlDelay(20000*(1000000/3000));

		I2C0TubeSelSet(~0x08);			//ѡ����ĸ����ֹܣ�11110111
		I2C0TubeLowSet(0x10);			//00010000
		I2C0TubeHighSet(0x3e);			//00111110
		SysCtlDelay(20000*(1000000/3000));
	}
}
void ShowNumber(int Number,int SelSet)
{
    switch(SelSet)
    {
        case 1:I2C0TubeSelSet(~0x20);break;
        case 2:I2C0TubeSelSet(~0x02);break;
        case 3:I2C0TubeSelSet(~0x04);break;
        case 4:I2C0TubeSelSet(~0x08);break;
        default:I2C0TubeSelSet(0xFF);
    }
    switch(Number)
    {
        case 0:I2C0TubeLowSet(0x10);I2C0TubeHighSet(0x3E);break;
        case 1:I2C0TubeLowSet(0x00);I2C0TubeHighSet(0x18);break;
        case 2:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x2C);break;
        case 3:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x26);break;
        case 4:I2C0TubeLowSet(0x60);I2C0TubeHighSet(0x32);break;
        case 5:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x16);break;
        case 6:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x1E);break;
        case 7:I2C0TubeLowSet(0x00);I2C0TubeHighSet(0x26);break;
        case 8:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x3E);break;
        case 9:I2C0TubeLowSet(0x70);I2C0TubeHighSet(0x36);break;
        default:I2C0TubeLowSet(0x00);I2C0TubeHighSet(0x00);
    }
    if(SelSet==0)SysCtlDelay(20000);
    else SysCtlDelay(80000);

    return;
}


