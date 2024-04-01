#ifndef __INIT_H
#define __INIT_H


//*****************************************************************************
//
// The number of SysTick ticks per second.
//
//*****************************************************************************
#define TICKS_PER_SECOND 40
#define FSECONDS_PER_TICK (1.0F / (float)TICKS_PER_SECOND)



#define SDC_SSI_BASE            SSI2_BASE
#define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI2

/* GPIO for SSI pins */
/* CLK pin */
#define SDC_SSI_CLK_GPIO_PORT_BASE   GPIO_PORTD_BASE
#define SDC_SSI_CLK             GPIO_PIN_3
/* TX pin */
#define SDC_SSI_TX_GPIO_PORT_BASE   GPIO_PORTD_BASE
#define SDC_SSI_TX              GPIO_PIN_1
/* RX pin */
#define SDC_SSI_RX_GPIO_PORT_BASE   GPIO_PORTD_BASE
#define SDC_SSI_RX              GPIO_PIN_0
/* CS pin */
#define SDC_SSI_FSS_GPIO_PORT_BASE   GPIO_PORTD_BASE
#define SDC_SSI_FSS             GPIO_PIN_2

void InitAll(void);
void ConfigureUART(void);
void TFTInit(void);
void InterInit(void);
void TFTTouchInit(void);
void IICInit(void);
void FPUInit(void);
void TimerIntInitial(void);
void RomInit(void);
void power_on(void);
#endif
