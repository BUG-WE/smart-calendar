#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "TFT_400x240_OTM4001A_16bit.h"
#include "IICaccelermeter.h"

#define _NOP() _nop()
#define SLAVE_ADDRESS_W 0x3A //дADXL345Lʱ�Ĵӻ���ַ
#define SLAVE_ADDRESS_R 0x3B //��ADXL345Lʱ�Ĵӻ���ַ

//**************************************
//��ʱ5��ָ������
//��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
//**************************************


//**************************************
 #define NUM 0
//IIC ����������ʱ������
 char I2C_RECV_DATA1[] =
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
void I2C_Set_sda_high1( void )
{
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4); //����PE4
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SDA �ź�
********************************************/
void I2C_Set_sda_low1 ( void )
{
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0X00000000); //����PE4
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SCL �ź�
********************************************/
void I2C_Set_scl_high1( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5,GPIO_PIN_5); //����PB5
    _NOP();
    _NOP();
    return;
}

/*******************************************
		����SCL �ź�
********************************************/
void I2C_Set_scl_low1 ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5,0X00000000); //����PB5
    _NOP();
    _NOP();
    return;
}

/*******************************************
		IIC �źŽ����źź���
********************************************/
void I2C_STOP1(void)
{
    int i;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //����PE4Ϊ�����
    I2C_Set_sda_low1();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low1();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high1();
    for(i = NUM+1;i > 0;i--);
    return;
}

/*******************************************
		IIC �źų�ʼ��
********************************************/
void I2C_Initial1( void )
{
    I2C_Set_scl_low1();
    I2C_STOP1();
    return;
}

/*******************************************
		IIC �ź���ʼ�źź���
********************************************/
void I2C_START1(void)
{
    int i;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //����PE4Ϊ�����
    I2C_Set_sda_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_low1();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low1();
    return;
}

/*******************************************
		IIC ��ȡӦ����
********************************************/
int  I2C_GetACK1(void)
{
    int j;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //����PE4Ϊ�����
    _NOP();
    _NOP();
    I2C_Set_scl_low1();
    for(j = NUM;j> 0;j--);
    I2C_Set_scl_high1();
    for(j = NUM;j> 0;j--);
    I2C_Set_sda_low1();
    for(j = NUM;j > 0;j--);
    I2C_Set_scl_low1();
    return 1;
}

/*******************************************
		IIC ����Ӧ����
********************************************/
void I2C_SetNAk1(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //����PE4Ϊ�����
    I2C_Set_scl_low1();
    I2C_Set_sda_high1();
    I2C_Set_scl_high1();
    I2C_Set_scl_low1();
    return;
}

/*******************************************
		IIC �����ֽں���
		���� 	1��Ҫ�����ֽ�ֵ
		return ���޷���
********************************************/
void I2C_TxByte1(unsigned char nValue)
{
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);//����PE4Ϊ�����
    int i;
    int j;
    for(i = 0;i < 8;i++)
    {
    	if(nValue & 0x80) //��λ�жϣ�1����SDA��0����SDA
    	I2C_Set_sda_high1();
    	else
    	I2C_Set_sda_low1();
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_high1();
    	nValue <<= 1;    //����1λ
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_low1();
    }

    return;
}

/*******************************************
		IIC �����ֽں���
		���� 		��
		return ���޷���
********************************************/
unsigned char  I2C_RxByte1(void)
{
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);//����PE4Ϊ�����
     char nTemp=0 ;
    int i;

    I2C_Set_sda_high1();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    for(i = 0;i < 8;i++)
    {
    	I2C_Set_scl_high1(); //ģ��SCL�ź�
    	SysCtlDelay(5);
    	if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4) == 0x10) //�����ж�PE4��SDA������
     	{
    	    nTemp |= (0x01 << (7-i));  //8λSDA������һλΪ�߾���1
    	}
    	I2C_Set_scl_low1();
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
void i2c_write1(int num, unsigned char device_addr, char *data)
{
    int i = 0;
    int count = num;
     char *send_data = data;
    unsigned char write_addr = device_addr;

    I2C_Set_scl_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high1();
    for(i = NUM;i > 0;i--);

    for(i = 0;i < count;i++)
    {
      I2C_START1();           //ģ��I2Cд���ݵ�ʱ��
      I2C_TxByte1(write_addr);
      I2C_GetACK1();
      I2C_TxByte1(send_data[i]);
      I2C_GetACK1();
      i++;
      I2C_TxByte1(send_data[i]);
      I2C_GetACK1();
      I2C_STOP1();
      SysCtlDelay(5);
    }

}

/*******************************************
		IIC ��ȡ���麯��
	����  	1 num : �����ֽ���
	    2 device_addr : iicĿ���ַ
	    3 *data	�����������ַ
	return ���޷���
********************************************/
void i2c_read1(int num, unsigned char device_addr, char *data)
{
    int i = 0;
    int count = num;
     char *send_data = data;
    unsigned char read_addr = device_addr;

    I2C_Set_scl_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high1();
    for(i = NUM;i > 0;i--);

    for(i = 0; i < count;i++)
    {
      I2C_START1();        //ģ��I2C������
      I2C_TxByte1((read_addr - 1));
      I2C_GetACK1();

      I2C_TxByte1(send_data[i]);
      I2C_GetACK1();

      I2C_START1();
      I2C_TxByte1(read_addr);
      I2C_GetACK1();

      I2C_RECV_DATA1[i] = I2C_RxByte1();
      I2C_SetNAk1();
      I2C_STOP1();
      SysCtlDelay(5);
    }
}

//************����һ���ֽ�����****************

unsigned char SINGLE_read1(unsigned char device_addr,char data)
{
    int i = 0;
     char value;
     char send_data = data;
    unsigned char read_addr = device_addr;

    I2C_Set_scl_high1();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high1();
    for(i = NUM;i > 0;i--);

    I2C_START1();
    I2C_TxByte1((read_addr - 1));
    I2C_GetACK1();

    I2C_TxByte1(send_data);
    I2C_GetACK1();

    I2C_START1();
    I2C_TxByte1(read_addr);
    I2C_GetACK1();

    value = I2C_RxByte1();
    I2C_SetNAk1();
    I2C_STOP1();
    SysCtlDelay(5);
    return value;
}

int mg_zero[3]={0x00,0x00,0x00};
void Init_Angle()
{
	int i=0;
	char REG_ADDR[6]={0x32,0x33,0x34,0x35,0x36,0x37};
	int mg_zero_sum[3]={0x00,0x00,0x00};
	char dataBuf0[2] = {0x2D, 0x00};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf0);   //ѡ���Դģʽ   �ο�pdf24ҳ
	SysCtlDelay(100*(120000000/3000));         //��ʱn*1ms

	char dataBuf1[2] = {0x31, 0x0B};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf1);   //������Χ,����16g��13λģʽ
	char dataBuf2[2] = {0x2C, 0x0A};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf2);   //�����趨Ϊ12.5 �ο�pdf13ҳ
	char dataBuf3[2] = {0x2D, 0x28};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf3);   //ѡ���Դģʽ   �ο�pdf24ҳ
	char dataBuf4[2] = {0x2E, 0x00};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf4);   //��ʹ�� DATA_READY �ж�

    char dataBuf5[2] = {0x1E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf5);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    char dataBuf6[2] = {0x1F, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf6);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    char dataBuf7[2] = {0x20, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf7);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    SysCtlDelay(40*(120000000/3000));         //��ʱn*1ms

    for(i=0;i<20;i++)
	{
		i2c_read1(6,SLAVE_ADDRESS_R,REG_ADDR);  //����6�ηֱ��ȡ0x32-0x37�е����ݡ�����I2C_RECV_DATA[]
		if(I2C_RECV_DATA1[1]>16)
		{
		   I2C_RECV_DATA1[1]=0xFF-I2C_RECV_DATA1[1];
		   I2C_RECV_DATA1[0]=0xFF-I2C_RECV_DATA1[0];
		   mg_zero[0]=I2C_RECV_DATA1[0]*4+I2C_RECV_DATA1[1]*1024;
		   mg_zero_sum[0]+=mg_zero[0];
		}
		else
		{
			mg_zero[0]=I2C_RECV_DATA1[0]*4+I2C_RECV_DATA1[1]*1024;
			mg_zero_sum[0]+=mg_zero[0];
		}
		if(I2C_RECV_DATA1[3]>16)
		{
		   I2C_RECV_DATA1[3]=0xFF-I2C_RECV_DATA1[3];
		   I2C_RECV_DATA1[2]=0xFF-I2C_RECV_DATA1[2];
		   mg_zero[1]=I2C_RECV_DATA1[2]*4+I2C_RECV_DATA1[3]*1024;
		   mg_zero_sum[1]+=mg_zero[1];
		}
		else
		{
			mg_zero[1]=I2C_RECV_DATA1[2]*4+I2C_RECV_DATA1[3]*1024;
			mg_zero_sum[1]+=mg_zero[1];
		}
		if(I2C_RECV_DATA1[5]>16)
		{
			I2C_RECV_DATA1[5]=0xFF-I2C_RECV_DATA1[5];
			I2C_RECV_DATA1[4]=0xFF-I2C_RECV_DATA1[4];
			mg_zero[2]=I2C_RECV_DATA1[4]*4+I2C_RECV_DATA1[5]*1024;
			mg_zero_sum[2]+=mg_zero[2];
		}
		else
		{
			mg_zero[2]=I2C_RECV_DATA1[4]*4+I2C_RECV_DATA1[5]*1024;
			mg_zero_sum[2]+=mg_zero[2];
		}
		//SysCtlDelay(40*(50000000/3000));         //��ʱn*1ms
	}
	mg_zero[0]=mg_zero_sum[0]/20;
	mg_zero[1]=mg_zero_sum[1]/20;
	mg_zero[2]=mg_zero_sum[2]/20;

	mg_zero[0]=-mg_zero[0]/4;
	mg_zero[1]=-mg_zero[1]/4;
	mg_zero[2]=-(mg_zero[2]-256)/4;

    char dataBuf8[2] = {0x1E, mg_zero[0]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf8);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    char dataBuf9[2] = {0x1F, mg_zero[1]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf9);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    char dataBuf10[2] = {0x20, mg_zero[2]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf10);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}
//**********************************************************************
//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�
//**********************************************************************
void Init_ADXL345(void)
{
	 char dataBuf1[2] = {0x31, 0x0B};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf1);   //������Χ,����16g��13λģʽ
	 char dataBuf2[2] = {0x2C, 0x18};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf2);   //�����趨Ϊ12.5 �ο�pdf13ҳ
    char dataBuf3[2] = {0x2D, 0x08};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf3);   //ѡ���Դģʽ   �ο�pdf24ҳ
    char dataBuf4[2] = {0x2E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf4);   //��ʹ�� DATA_READY �ж�
     char dataBuf5[2] = {0x1E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf5);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
     char dataBuf6[2] = {0x1F, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf6);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
     char dataBuf7[2] = {0x20, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf7);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}
void I2C0GPIOBEnable1(void) //����I2C0ģ���IO���ţ�
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);   //ʹ��  GPIO portB
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);   //ʹ��  GPIO portE

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4);//ʹ��PB4��PB5��Ϊ�����
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);//ʹ��PE5��Ϊ�����
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_PIN_4);//PB4���øߣ���ADXL345L��CS����
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);//PE5���øߣ���ADXL345L��ALT ADDRESS����
}
void showAcceler(void)
{
	int i;
    int mg[3]={0x00,0x00,0x00};
    //int mg_zero_sum[3]={0x00,0x00,0x00};
	char REG_ADDR[6]={0x32,0x33,0x34,0x35,0x36,0x37};
	I2C0GPIOBEnable1();                      //����I2C0ģ���IO����
	//Init_Angle();
	Init_ADXL345();                         //ADXL345��ʼ��

	//UARTprintf("\nX:          Y:          Z:\n");
	while(1)
	{
		for(i=0;i<20;i++)
		{
			i2c_read1(6,SLAVE_ADDRESS_R,REG_ADDR);  //����6�ηֱ��ȡ0x32-0x37�е����ݡ�����I2C_RECV_DATA[]
//	   I2C_RECV_DATA1[0]=SINGLE_read1(SLAVE_ADDRESS_R,0x32);//���ζ�ȡ0x32�е�����
//	   I2C_RECV_DATA1[1]=SINGLE_read1(SLAVE_ADDRESS_R,0x33);
//	   I2C_RECV_DATA1[2]=SINGLE_read1(SLAVE_ADDRESS_R,0x34);
//	   I2C_RECV_DATA1[3]=SINGLE_read1(SLAVE_ADDRESS_R,0x35);
//	   I2C_RECV_DATA1[4]=SINGLE_read1(SLAVE_ADDRESS_R,0x36);
//	   I2C_RECV_DATA1[5]=SINGLE_read1(SLAVE_ADDRESS_R,0x37);

/*********** *ֱ����ʾԭʼ����**********************************
 	   for(i=0;i<6;i++)
	   {
	   	   UARTprintf("%x   ",I2C_RECV_DATA1[i]);
	   	   if(i==5)
	   	   	   UARTprintf("\n");
	   }   */

//***********ԭʼ����ת��Ϊ���ٶ�������ʾ****************************
		if(I2C_RECV_DATA1[1]>16)
		{
		   I2C_RECV_DATA1[1]=0xFF-I2C_RECV_DATA1[1];
		   I2C_RECV_DATA1[0]=0xFF-I2C_RECV_DATA1[0];
		   mg[0]=I2C_RECV_DATA1[0]*4+I2C_RECV_DATA1[1]*1024;
		   //mg_zero_sum[0]+=mg_zero[0];
		}
		else
		{
		   mg[0]=I2C_RECV_DATA1[0]*4+I2C_RECV_DATA1[1]*1024;
		   //mg_zero_sum[0]+=mg_zero[0];
		}
		if(I2C_RECV_DATA1[3]>16)
		{
		   I2C_RECV_DATA1[3]=0xFF-I2C_RECV_DATA1[3];
		   I2C_RECV_DATA1[2]=0xFF-I2C_RECV_DATA1[2];
		   mg[1]=I2C_RECV_DATA1[2]*4+I2C_RECV_DATA1[3]*1024;
		   //mg_zero_sum[1]+=mg_zero[1];
		}
		else
		{
		   mg[1]=I2C_RECV_DATA1[2]*4+I2C_RECV_DATA1[3]*1024;
		   //mg_zero_sum[1]+=mg_zero[1];
		}
		if(I2C_RECV_DATA1[5]>16)
		{
			I2C_RECV_DATA1[5]=0xFF-I2C_RECV_DATA1[5];
			I2C_RECV_DATA1[4]=0xFF-I2C_RECV_DATA1[4];
			mg[2]=I2C_RECV_DATA1[4]*4+I2C_RECV_DATA1[5]*1024;
			//mg_zero_sum[2]+=mg_zero[2];
		}
		else
		{
			mg[2]=I2C_RECV_DATA1[4]*4+I2C_RECV_DATA1[5]*1024;
			//mg_zero_sum[2]+=mg_zero[2];
		}
		SysCtlDelay((1200000000/3000));         //��ʱn*1ms
		}
//		mg_zero[0]=mg_zero_sum[0]/20;
//		mg_zero[1]=mg_zero_sum[1]/20;
//		mg_zero[2]=mg_zero_sum[2]/20;
		TFTLCD_ShowData(60,110,mg[0],BLACK,WHITE);
		TFTLCD_ShowData(60,130,mg[1],BLACK,WHITE);
		TFTLCD_ShowData(60,150,mg[2],BLACK,WHITE);
	}
}
