################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/approximations.c \
../Sources/drivers.c \
../Sources/fusion.c \
../Sources/magnetic.c \
../Sources/main.c \
../Sources/matrix.c \
../Sources/mqx_tasks.c \
../Sources/orientation.c \
../Sources/tasks.c \
../Sources/user_tasks.c 

OBJS += \
./Sources/Events.o \
./Sources/approximations.o \
./Sources/drivers.o \
./Sources/fusion.o \
./Sources/magnetic.o \
./Sources/main.o \
./Sources/matrix.o \
./Sources/mqx_tasks.o \
./Sources/orientation.o \
./Sources/tasks.o \
./Sources/user_tasks.o 

C_DEPS += \
./Sources/Events.d \
./Sources/approximations.d \
./Sources/drivers.d \
./Sources/fusion.d \
./Sources/magnetic.d \
./Sources/main.d \
./Sources/matrix.d \
./Sources/mqx_tasks.d \
./Sources/orientation.d \
./Sources/tasks.d \
./Sources/user_tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DKL46Z -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/Sources" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/Generated_Code" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/include" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/config" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/kernel" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


