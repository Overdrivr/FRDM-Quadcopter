################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/FTM.c \
../Generated_Code/I2C.c \
../Generated_Code/LED_BLUE.c \
../Generated_Code/LED_GREEN.c \
../Generated_Code/LED_RED.c \
../Generated_Code/MQX1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/RNG1.c \
../Generated_Code/SystemTimer1.c \
../Generated_Code/TestPin_KF_Time.c \
../Generated_Code/TestPin_MagCal_Time.c \
../Generated_Code/UART.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/FTM.o \
./Generated_Code/I2C.o \
./Generated_Code/LED_BLUE.o \
./Generated_Code/LED_GREEN.o \
./Generated_Code/LED_RED.o \
./Generated_Code/MQX1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RNG1.o \
./Generated_Code/SystemTimer1.o \
./Generated_Code/TestPin_KF_Time.o \
./Generated_Code/TestPin_MagCal_Time.o \
./Generated_Code/UART.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/FTM.d \
./Generated_Code/I2C.d \
./Generated_Code/LED_BLUE.d \
./Generated_Code/LED_GREEN.d \
./Generated_Code/LED_RED.d \
./Generated_Code/MQX1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/RNG1.d \
./Generated_Code/SystemTimer1.d \
./Generated_Code/TestPin_KF_Time.d \
./Generated_Code/TestPin_MagCal_Time.d \
./Generated_Code/UART.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DKL46Z -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/Sources" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/Generated_Code" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/include" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/config" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/kernel" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


