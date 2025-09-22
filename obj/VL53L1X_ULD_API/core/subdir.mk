################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VL53L1X_ULD_API/core/VL53L1X_api.c \
../VL53L1X_ULD_API/core/VL53L1X_calibration.c 

OBJS += \
./VL53L1X_ULD_API/core/VL53L1X_api.o \
./VL53L1X_ULD_API/core/VL53L1X_calibration.o 

C_DEPS += \
./VL53L1X_ULD_API/core/VL53L1X_api.d \
./VL53L1X_ULD_API/core/VL53L1X_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
VL53L1X_ULD_API/core/%.o: ../VL53L1X_ULD_API/core/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\Debug" -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\Core" -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\User" -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\Peripheral\inc" -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\VL53L1X_ULD_API\core" -I"C:\Working projects\Driver-VL53L1X-for-CH32V003\VL53L1X_ULD_API\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

