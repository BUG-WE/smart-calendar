#ifndef __IICMIZIGUAN_H
#define __IICMIZIGUAN_H

void I2C0GPIOBEnable(void);//配置I2C0模块的IO引脚
void I2C0DeviceInit(void);//配置PCA9557芯片中连接米字管的各引脚为输出
void showABCD(void);

#endif
