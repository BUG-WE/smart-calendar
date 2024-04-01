/*
 * TOUCH_TSC2046.h
 *
 *  Created on: 2014Äê8ÔÂ28ÈÕ
 *      Author: Sam
 */

#ifndef TOUCH_TSC2046_H_
#define TOUCH_TSC2046_H_


extern uint32_t TouchXData[10];
extern uint32_t TouchYData[10];
uint32_t GetData[6];


extern void TOUCH_TSC2046init(uint32_t ui32SysClockSpeed);
extern void SoftSPI_PutData(uint8_t ui8Data);
extern uint16_t SoftSPI_GetData();
extern uint16_t touch_gety();
extern uint16_t touch_getx();
extern uint16_t TOUCH_PointAdjust(void);
#endif /* TOUCH_TSC2046_H_ */
