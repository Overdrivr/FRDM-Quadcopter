################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../MQXLITE/psp/cortex_m/core/M0/boot.S \
../MQXLITE/psp/cortex_m/core/M0/dispatch.S 

OBJS += \
./MQXLITE/psp/cortex_m/core/M0/boot.o \
./MQXLITE/psp/cortex_m/core/M0/dispatch.o 

S_UPPER_DEPS += \
./MQXLITE/psp/cortex_m/core/M0/boot.d \
./MQXLITE/psp/cortex_m/core/M0/dispatch.d 


# Each subdirectory must supply rules for building sources it contributes
MQXLITE/psp/cortex_m/core/M0/%.o: ../MQXLITE/psp/cortex_m/core/M0/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -x assembler-with-cpp -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/include" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/config" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/kernel" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m/core/M0" -I"C:/Users/B48923/Documents/GitHub/FRDM-Quadcopter/FSFK_KL46Z/MQXLITE/psp/cortex_m/compiler/cwgcc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


