/**
 *****************************************************************************
 * @file	vl53l1x.h
 * @author 	Arnaud C.
 *****************************************************************************
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef INC_VL53L1X_H_
#define INC_VL53L1X_H_

/* Includes -----------------------------------------------------------------*/
#include <stdint.h>
#include "ch32v00x.h"
//#include "gpio.h"
#include "VL53L1X_api.h"
#include "VL53l1X_calibration.h"
#include "vl53l1_error_codes.h"

/* Exported types -----------------------------------------------------------*/
/*
typedef struct VL53L1X_xshut{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

} xshut;

typedef struct vl53l1x_Cfg{
	uint16_t i2c_address;
	xshut pin_xshut;

} vl53l1x_Cfg;
*/
/* End of exported types ----------------------------------------------------*/

/* Exported macros ----------------------------------------------------------*/
//#define VL53L1X_MAX_NB	16
#define VL53L1X_DEFAULT_ADDRESS 0b0101001//(0x52 )

/* End of exported macros ---------------------------------------------------*/

/* Exported functions -------------------------------------------------------*/
int vl53l1x_init(void);
void vl53l1x_Polling(void);
uint16_t vl53l1x_Get_Distance(void);
//int vl53l1x_clearCfg();
//int vl53l1x_setParameters(int i);
//uint16_t vl53l1x_getDistance(int i);

/* End of exported functions ------------------------------------------------*/

#endif /* INC_VL53L1X_H_ */
