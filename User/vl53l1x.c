/**
 *****************************************************************************
 * @file	vl53l1x.c
 * @author 	Arnaud C.
 *****************************************************************************
 */

#include "vl53l1x.h"

/* Variables ----------------------------------------------------------------*/
uint16_t vl53l1x_distance = 0;

/* End of variables ---------------------------------------------------------*/

/* Functions ----------------------------------------------------------------*/
static void vl53l1x_LL_Init(void)
{
    GPIO_InitTypeDef MyGPIO = {0};
    I2C_InitTypeDef MyI2C = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1  , ENABLE);

    MyGPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; // sda&scl
    MyGPIO.GPIO_Mode = GPIO_Mode_AF_OD;
    MyGPIO.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &MyGPIO);

    MyGPIO.GPIO_Pin = GPIO_Pin_3 ; // xshut pin
    MyGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    MyGPIO.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &MyGPIO);

    MyI2C.I2C_ClockSpeed = 100000;
    MyI2C.I2C_DutyCycle = I2C_DutyCycle_16_9;
    MyI2C.I2C_OwnAddress1 = 0;
    MyI2C.I2C_Mode = I2C_Mode_I2C;
    MyI2C.I2C_Ack = I2C_Ack_Enable;
    MyI2C.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &MyI2C);

    I2C_Cmd(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);

}

int vl53l1x_init(void)
{
    uint8_t status = 0;
    uint8_t sensorState = 0;
    //uint8_t byteData; uint16_t wordData;

    vl53l1x_LL_Init();

    // xshut pin
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	HAL_Delay(250);
    GPIO_SetBits(GPIOC,GPIO_Pin_3);
    HAL_Delay(250);

		// Retrieve sensor boot state
		while(sensorState == 0){
			status = VL53L1X_BootState(VL53L1X_DEFAULT_ADDRESS, &sensorState);
			HAL_Delay(250);
		}
		//printf("Chip booted...\r\n");

		// Sensor init
		status = VL53L1X_SensorInit(VL53L1X_DEFAULT_ADDRESS);
		//if(status == VL53L1_ERROR_NONE) printf("VL53L1X Initial OK!\r\n");
		//else printf("VL53L1X Initial ERROR! %d\r\n", status);

		status = VL53L1X_SetDistanceMode(VL53L1X_DEFAULT_ADDRESS, 1);
		status = VL53L1X_SetInterMeasurementInMs(VL53L1X_DEFAULT_ADDRESS, 52); // in ms, IM must be > = TB
	    status = VL53L1X_SetTimingBudgetInMs(VL53L1X_DEFAULT_ADDRESS, 50);

        //if(status == VL53L1_ERROR_NONE) printf("VL53L1X setting OK!\r\n");
        //else printf("VL53L1X setting ERROR! %d\r\n", status);

		HAL_Delay(250);

	status = VL53L1X_StartRanging(VL53L1X_DEFAULT_ADDRESS);
    //if(status == VL53L1_ERROR_NONE) printf("VL53L1X starting OK!\r\n");
    //else printf("VL53L1X starting ERROR! %d\r\n", status);

	return 0;
}

void vl53l1x_Polling(void)
{
        uint8_t DataReady =0;
        VL53L1X_CheckForDataReady(VL53L1X_DEFAULT_ADDRESS, &DataReady);
        if(DataReady)
        {
            VL53L1X_GetDistance(VL53L1X_DEFAULT_ADDRESS,&vl53l1x_distance);
            VL53L1X_ClearInterrupt(VL53L1X_DEFAULT_ADDRESS);
            printf("Distance %d\r\n",vl53l1x_distance);
        }
}
uint16_t vl53l1x_Get_Distance(void)
{
    return vl53l1x_distance;
}

/* End of functions ---------------------------------------------------------*/
