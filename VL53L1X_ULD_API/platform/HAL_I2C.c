/*
 * HAL_I2C.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Δενθρ
 */
#include "HAL_I2C.h"

uint8_t I2C_Write_Mem(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint16_t addr,uint8_t *buff,uint16_t size,uint32_t timeout,uint8_t addr_size)
{
    uint32_t start_tick = GetSysTick();
    i2cAddr=i2cAddr<<1;

    while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_SoftwareResetCmd(i2cHandle,ENABLE);
            HAL_Delay(5);
            start_tick = GetSysTick();
            while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
            {
                if((GetSysTick()-start_tick)>timeout)
                {
                    return I2C_BUSY;
                }
            }
        }
    }
    start_tick = GetSysTick();

    /* start */
    I2C_GenerateSTART(i2cHandle, ENABLE);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_START_ERROR;
        }
    }
    start_tick = GetSysTick();

    /* address to write */
    I2C_Send7bitAddress(i2cHandle, i2cAddr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_ADRR_NAC;
        }
    }
    start_tick = GetSysTick();

    if(addr_size==MEM_ADDR_8B)
    {
    /* data address */
    I2C_SendData(i2cHandle, (uint8_t)addr);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_DATA_ERROR;
        }
    }
    }
    else if(addr_size==MEM_ADDR_16B)
    {
        uint8_t Addr_High_Byte = (uint8_t)(addr>>8);
        uint8_t Addr_Low_Byte = (uint8_t)addr;

        I2C_SendData(i2cHandle, Addr_High_Byte);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
        I2C_SendData(i2cHandle, Addr_Low_Byte);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
    }
    /* data */
    for(int i=0;i<size;i++)
    {
        start_tick = GetSysTick();
        I2C_SendData(i2cHandle, buff[i]);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
    }

    /* stop */
    I2C_GenerateSTOP(i2cHandle, ENABLE);
    return I2C_SUCCES;
}
uint8_t I2C_Read_Mem(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint16_t addr,uint8_t *buff,uint16_t size,uint32_t timeout,uint8_t addr_size)
{
    uint32_t start_tick = GetSysTick();
    i2cAddr=i2cAddr<<1;

    while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_SoftwareResetCmd(i2cHandle,ENABLE);
            HAL_Delay(5);
            start_tick = GetSysTick();
            while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
            {
                if((GetSysTick()-start_tick)>timeout)
                {
                    return I2C_BUSY;
                }
            }
        }
    }
    start_tick = GetSysTick();

    /* start */
    I2C_GenerateSTART(i2cHandle, ENABLE);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_START_ERROR;
        }
    }
    start_tick = GetSysTick();

    /* address to write */
    I2C_Send7bitAddress(i2cHandle, i2cAddr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_ADRR_NAC;
        }
    }
    start_tick = GetSysTick();

    if(addr_size==MEM_ADDR_8B)
    {
    /* data address */
    I2C_SendData(i2cHandle, (uint8_t)addr);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_DATA_ERROR;
        }
    }
    }
    else if(addr_size==MEM_ADDR_16B)
    {
        uint8_t Addr_High_Byte = (uint8_t)(addr>>8);
        uint8_t Addr_Low_Byte = (uint8_t)addr;

        I2C_SendData(i2cHandle, Addr_High_Byte);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
        I2C_SendData(i2cHandle, Addr_Low_Byte);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
    }
    start_tick = GetSysTick();

    /* start */
    I2C_GenerateSTART(i2cHandle, ENABLE);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_START_ERROR;
        }
    }
    start_tick = GetSysTick();

    /* address to write */
    I2C_Send7bitAddress(i2cHandle, i2cAddr, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_ADRR_NAC;
        }
    }
    //start_tick = xTaskGetTickCount();

    /* data */
    for(int i=0;i<size;i++)
    {
        start_tick = GetSysTick();
        //I2C_SendData(i2cHandle, buff[i]);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_RECEIVED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
        buff[i] = I2C_ReceiveData(i2cHandle);
    }

    /* stop */
    I2C_GenerateSTOP(i2cHandle, ENABLE);
    return I2C_SUCCES;
}

uint8_t HAL_I2C_Master_Transmit(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint8_t *buff,uint16_t size,uint32_t timeout)
{
    uint32_t start_tick = GetSysTick();
    i2cAddr=i2cAddr<<1;

    while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_SoftwareResetCmd(i2cHandle,ENABLE);
            HAL_Delay(5);
            start_tick = GetSysTick();
            while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
            {
                if((GetSysTick()-start_tick)>timeout)
                {
                    return I2C_BUSY;
                }
            }
        }
    }
    start_tick = GetSysTick();

    /* start */
    I2C_GenerateSTART(i2cHandle, ENABLE);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_START_ERROR;
        }
    }
    start_tick = GetSysTick();

    /* address to write */
    I2C_Send7bitAddress(i2cHandle, i2cAddr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_ADRR_NAC;
        }
    }

    /* data */
    for(int i=0;i<size;i++)
    {
        start_tick = GetSysTick();
        I2C_SendData(i2cHandle, buff[i]);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
    }

    /* stop */
    I2C_GenerateSTOP(i2cHandle, ENABLE);
    return I2C_SUCCES;
}
uint8_t HAL_I2C_Master_Receive(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint8_t *buff,uint16_t size,uint32_t timeout)
{
    uint32_t start_tick = GetSysTick();
    i2cAddr=i2cAddr<<1;

    while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_SoftwareResetCmd(i2cHandle,ENABLE);
            HAL_Delay(5);
            start_tick = GetSysTick();
            while(I2C_GetFlagStatus(i2cHandle, I2C_FLAG_BUSY) != RESET)
            {
                if((GetSysTick()-start_tick)>timeout)
                {
                    return I2C_BUSY;
                }
            }
        }
    }

    start_tick = GetSysTick();

    /* start */
    I2C_GenerateSTART(i2cHandle, ENABLE);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_START_ERROR;
        }
    }
    start_tick = GetSysTick();

    /* address to write */
    I2C_Send7bitAddress(i2cHandle, i2cAddr, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if((GetSysTick()-start_tick)>timeout)
        {
            I2C_GenerateSTOP(i2cHandle, ENABLE);
            return I2C_ADRR_NAC;
        }
    }
    //start_tick = xTaskGetTickCount();

    /* data */
    for(int i=0;i<size;i++)
    {
        start_tick = GetSysTick();
        //I2C_SendData(i2cHandle, buff[i]);
        while(!I2C_CheckEvent(i2cHandle, I2C_EVENT_MASTER_BYTE_RECEIVED))
        {
            if((GetSysTick()-start_tick)>timeout)
            {
                I2C_GenerateSTOP(i2cHandle, ENABLE);
                return I2C_DATA_ERROR;
            }
        }
        buff[i] = I2C_ReceiveData(i2cHandle);
    }

    /* stop */
    I2C_GenerateSTOP(i2cHandle, ENABLE);
    return I2C_SUCCES;
}
