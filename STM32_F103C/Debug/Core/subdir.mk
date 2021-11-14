################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/syscalls.c \
../Core/sysmem.c \
../Core/system_stm32f1xx.c 

CPP_SRCS += \
../Core/boot.cpp \
../Core/handlers.cpp \
../Core/main.cpp 

C_DEPS += \
./Core/syscalls.d \
./Core/sysmem.d \
./Core/system_stm32f1xx.d 

OBJS += \
./Core/boot.o \
./Core/handlers.o \
./Core/main.o \
./Core/syscalls.o \
./Core/sysmem.o \
./Core/system_stm32f1xx.o 

CPP_DEPS += \
./Core/boot.d \
./Core/handlers.d \
./Core/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.cpp Core/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core -I../QA_Drivers -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/%.o: ../Core/%.c Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core -I../QA_Drivers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

