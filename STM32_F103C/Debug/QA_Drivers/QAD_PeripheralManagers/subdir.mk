################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../QA_Drivers/QAD_PeripheralManagers/QAD_TimerMgr.cpp \
../QA_Drivers/QAD_PeripheralManagers/QAD_UARTMgr.cpp 

OBJS += \
./QA_Drivers/QAD_PeripheralManagers/QAD_TimerMgr.o \
./QA_Drivers/QAD_PeripheralManagers/QAD_UARTMgr.o 

CPP_DEPS += \
./QA_Drivers/QAD_PeripheralManagers/QAD_TimerMgr.d \
./QA_Drivers/QAD_PeripheralManagers/QAD_UARTMgr.d 


# Each subdirectory must supply rules for building sources it contributes
QA_Drivers/QAD_PeripheralManagers/%.o: ../QA_Drivers/QAD_PeripheralManagers/%.cpp QA_Drivers/QAD_PeripheralManagers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core -I../QA_Drivers -I../QA_Drivers/QAD_PeripheralManagers -I../QA_Systems -I../QA_Systems/QAS_Serial -I../QA_Tools -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

