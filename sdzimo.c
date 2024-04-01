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
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"
#include "driverlib/ssi.h"
#include "driverlib/rom_map.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
#include "TOUCHinit/TOUCH_TSC2046.h"
#include "EPIinit/EPIinit.h"
#include "sdzimo.h"

FATFS myfs[2];                 // Work area (file system object) for logical drive
FIL myfsrc, myfdst;            // file objects
FRESULT myres;                 // FatFs function common result code
BYTE mybuffer[512];            // file copy buffer
BYTE my_latest_buffer[512];
uint8_t mystring[512]="this is a MicroSD demo base on fatfs";
UINT mybr, mybw;               // File R/W count
int mya = 0;
char mypath[512]="0:";         //

/*******************************************************************************
* Function Name  : GetGBKCode_from_sd
* Description    : 从SD卡字库中读取自摸数据到指定的缓冲区
* Input          : pBuffer---数据保存地址
*				   					c--汉字字符低字节码
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/
int GetGBKCode_from_sd(unsigned char* pBuffer,const unsigned char * c)
{
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    High8bit=*c;     /* 取高8位数据 */
    Low8bit=*(c+1);  /* 取低8位数据 */

//  printf("%d ,%d\r\n",High8bit,Low8bit);
//	printf("%x ,%x\r\n",High8bit,Low8bit);

    pos = ((High8bit-0xa0-16)*94+Low8bit-0xa0-1)*2*16 ;
    f_mount(0, &myfs[0]);
    myres = f_open(&myfsrc , "/HZLIB.bin",  FA_READ);//FA_OPEN_EXISTING |

    if ( myres == FR_OK )
    {
        f_lseek (&myfsrc, pos);		//指针偏移
        myres = f_read( &myfsrc, pBuffer, 32, &mybr );		 //16*16大小的汉字 其字模 占用16*2个字节

        f_close(&myfsrc);

        return 0;
    }
    else
        return -1;
}
