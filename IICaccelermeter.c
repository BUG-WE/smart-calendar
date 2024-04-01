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
#define SLAVE_ADDRESS_W 0x3A //写ADXL345L时的从机地址
#define SLAVE_ADDRESS_R 0x3B //读ADXL345L时的从机地址

//**************************************
//延时5个指令周期
//不同的工作环境,需要调整此函数，注意时钟过快时需要修改
//**************************************


//**************************************
 #define NUM 0
//IIC 接受数据临时缓冲区
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
		拉高 SDA 信号
********************************************/
void I2C_Set_sda_high1( void )
{
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4); //拉高PE4
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉低SDA 信号
********************************************/
void I2C_Set_sda_low1 ( void )
{
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0X00000000); //拉低PE4
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉高SCL 信号
********************************************/
void I2C_Set_scl_high1( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5,GPIO_PIN_5); //拉高PB5
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉低SCL 信号
********************************************/
void I2C_Set_scl_low1 ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5,0X00000000); //拉低PB5
    _NOP();
    _NOP();
    return;
}

/*******************************************
		IIC 信号结束信号函数
********************************************/
void I2C_STOP1(void)
{
    int i;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //配置PE4为输出口
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
		IIC 信号初始化
********************************************/
void I2C_Initial1( void )
{
    I2C_Set_scl_low1();
    I2C_STOP1();
    return;
}

/*******************************************
		IIC 信号起始信号函数
********************************************/
void I2C_START1(void)
{
    int i;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //配置PE4为输出口
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
		IIC 获取应答函数
********************************************/
int  I2C_GetACK1(void)
{
    int j;
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //配置PE4为输出口
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
		IIC 设置应答函数
********************************************/
void I2C_SetNAk1(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //配置PE4为输出口
    I2C_Set_scl_low1();
    I2C_Set_sda_high1();
    I2C_Set_scl_high1();
    I2C_Set_scl_low1();
    return;
}

/*******************************************
		IIC 发送字节函数
		参数 	1：要发送字节值
		return ：无返回
********************************************/
void I2C_TxByte1(unsigned char nValue)
{
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);//配置PE4为输出口
    int i;
    int j;
    for(i = 0;i < 8;i++)
    {
    	if(nValue & 0x80) //逐位判断，1拉高SDA，0拉低SDA
    	I2C_Set_sda_high1();
    	else
    	I2C_Set_sda_low1();
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_high1();
    	nValue <<= 1;    //左移1位
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_low1();
    }

    return;
}

/*******************************************
		IIC 接收字节函数
		参数 		无
		return ：无返回
********************************************/
unsigned char  I2C_RxByte1(void)
{
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);//配置PE4为输入口
     char nTemp=0 ;
    int i;

    I2C_Set_sda_high1();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    for(i = 0;i < 8;i++)
    {
    	I2C_Set_scl_high1(); //模拟SCL信号
    	SysCtlDelay(5);
    	if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4) == 0x10) //依次判断PE4（SDA）输入
     	{
    	    nTemp |= (0x01 << (7-i));  //8位SDA数据哪一位为高就置1
    	}
    	I2C_Set_scl_low1();
    	SysCtlDelay(5);
    }
    return nTemp;
}

/*******************************************
		IIC 发送数组函数
	参数  	1 num : 发送字节数
	    2 device_addr : iic目标地址
	    3 *data	：发送数组地址
	return ：无返回
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
      I2C_START1();           //模拟I2C写数据的时序
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
		IIC 读取数组函数
	参数  	1 num : 发送字节数
	    2 device_addr : iic目标地址
	    3 *data	：接收数组地址
	return ：无返回
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
      I2C_START1();        //模拟I2C读数据
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

//************单读一个字节数据****************

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
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf0);   //选择电源模式   参考pdf24页
	SysCtlDelay(100*(120000000/3000));         //延时n*1ms

	char dataBuf1[2] = {0x31, 0x0B};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf1);   //测量范围,正负16g，13位模式
	char dataBuf2[2] = {0x2C, 0x0A};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf2);   //速率设定为12.5 参考pdf13页
	char dataBuf3[2] = {0x2D, 0x28};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf3);   //选择电源模式   参考pdf24页
	char dataBuf4[2] = {0x2E, 0x00};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf4);   //不使用 DATA_READY 中断

    char dataBuf5[2] = {0x1E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf5);   //X 偏移量 根据测试传感器的状态写入pdf29页
    char dataBuf6[2] = {0x1F, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf6);   //Y 偏移量 根据测试传感器的状态写入pdf29页
    char dataBuf7[2] = {0x20, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf7);   //Z 偏移量 根据测试传感器的状态写入pdf29页
    SysCtlDelay(40*(120000000/3000));         //延时n*1ms

    for(i=0;i<20;i++)
	{
		i2c_read1(6,SLAVE_ADDRESS_R,REG_ADDR);  //连续6次分别读取0x32-0x37中的数据。存于I2C_RECV_DATA[]
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
		//SysCtlDelay(40*(50000000/3000));         //延时n*1ms
	}
	mg_zero[0]=mg_zero_sum[0]/20;
	mg_zero[1]=mg_zero_sum[1]/20;
	mg_zero[2]=mg_zero_sum[2]/20;

	mg_zero[0]=-mg_zero[0]/4;
	mg_zero[1]=-mg_zero[1]/4;
	mg_zero[2]=-(mg_zero[2]-256)/4;

    char dataBuf8[2] = {0x1E, mg_zero[0]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf8);   //X 偏移量 根据测试传感器的状态写入pdf29页
    char dataBuf9[2] = {0x1F, mg_zero[1]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf9);   //Y 偏移量 根据测试传感器的状态写入pdf29页
    char dataBuf10[2] = {0x20, mg_zero[2]};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf10);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
//**********************************************************************
//初始化ADXL345，根据需要请参考pdf进行修改
//**********************************************************************
void Init_ADXL345(void)
{
	 char dataBuf1[2] = {0x31, 0x0B};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf1);   //测量范围,正负16g，13位模式
	 char dataBuf2[2] = {0x2C, 0x18};
	i2c_write1(2,SLAVE_ADDRESS_W,dataBuf2);   //速率设定为12.5 参考pdf13页
    char dataBuf3[2] = {0x2D, 0x08};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf3);   //选择电源模式   参考pdf24页
    char dataBuf4[2] = {0x2E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf4);   //不使用 DATA_READY 中断
     char dataBuf5[2] = {0x1E, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf5);   //X 偏移量 根据测试传感器的状态写入pdf29页
     char dataBuf6[2] = {0x1F, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf6);   //Y 偏移量 根据测试传感器的状态写入pdf29页
     char dataBuf7[2] = {0x20, 0x00};
    i2c_write1(2,SLAVE_ADDRESS_W,dataBuf7);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
void I2C0GPIOBEnable1(void) //配置I2C0模块的IO引脚，
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);   //使能  GPIO portB
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);   //使能  GPIO portE

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4);//使能PB4、PB5作为输出口
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);//使能PE5作为输出口
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_PIN_4);//PB4口置高，即ADXL345L的CS引脚
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);//PE5口置高，即ADXL345L的ALT ADDRESS引脚
}
void showAcceler(void)
{
	int i;
    int mg[3]={0x00,0x00,0x00};
    //int mg_zero_sum[3]={0x00,0x00,0x00};
	char REG_ADDR[6]={0x32,0x33,0x34,0x35,0x36,0x37};
	I2C0GPIOBEnable1();                      //配置I2C0模块的IO引脚
	//Init_Angle();
	Init_ADXL345();                         //ADXL345初始化

	//UARTprintf("\nX:          Y:          Z:\n");
	while(1)
	{
		for(i=0;i<20;i++)
		{
			i2c_read1(6,SLAVE_ADDRESS_R,REG_ADDR);  //连续6次分别读取0x32-0x37中的数据。存于I2C_RECV_DATA[]
//	   I2C_RECV_DATA1[0]=SINGLE_read1(SLAVE_ADDRESS_R,0x32);//单次读取0x32中的数据
//	   I2C_RECV_DATA1[1]=SINGLE_read1(SLAVE_ADDRESS_R,0x33);
//	   I2C_RECV_DATA1[2]=SINGLE_read1(SLAVE_ADDRESS_R,0x34);
//	   I2C_RECV_DATA1[3]=SINGLE_read1(SLAVE_ADDRESS_R,0x35);
//	   I2C_RECV_DATA1[4]=SINGLE_read1(SLAVE_ADDRESS_R,0x36);
//	   I2C_RECV_DATA1[5]=SINGLE_read1(SLAVE_ADDRESS_R,0x37);

/*********** *直接显示原始数据**********************************
 	   for(i=0;i<6;i++)
	   {
	   	   UARTprintf("%x   ",I2C_RECV_DATA1[i]);
	   	   if(i==5)
	   	   	   UARTprintf("\n");
	   }   */

//***********原始数据转换为加速度数据显示****************************
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
		SysCtlDelay((1200000000/3000));         //延时n*1ms
		}
//		mg_zero[0]=mg_zero_sum[0]/20;
//		mg_zero[1]=mg_zero_sum[1]/20;
//		mg_zero[2]=mg_zero_sum[2]/20;
		TFTLCD_ShowData(60,110,mg[0],BLACK,WHITE);
		TFTLCD_ShowData(60,130,mg[1],BLACK,WHITE);
		TFTLCD_ShowData(60,150,mg[2],BLACK,WHITE);
	}
}
