################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DKL46Z -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/Sources" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/Generated_Code" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/include" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/config" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/kernel" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/B48923/Documents/KDSWorkspace/FSFK_KL46Z/MQXLITE/psp/cortex_m/compiler/cwgcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

