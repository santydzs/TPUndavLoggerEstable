################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fuentes/DateTime.cpp \
../fuentes/TPUndavEstable.cpp 

OBJS += \
./fuentes/DateTime.o \
./fuentes/TPUndavEstable.o 

CPP_DEPS += \
./fuentes/DateTime.d \
./fuentes/TPUndavEstable.d 


# Each subdirectory must supply rules for building sources it contributes
fuentes/%.o: ../fuentes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


