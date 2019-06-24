################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fuentes/Appender.cpp \
../fuentes/AppenderSettings.cpp \
../fuentes/DateTime.cpp \
../fuentes/Logger.cpp \
../fuentes/LoggerSettings.cpp \
../fuentes/TPUndavEstable.cpp 

OBJS += \
./fuentes/Appender.o \
./fuentes/AppenderSettings.o \
./fuentes/DateTime.o \
./fuentes/Logger.o \
./fuentes/LoggerSettings.o \
./fuentes/TPUndavEstable.o 

CPP_DEPS += \
./fuentes/Appender.d \
./fuentes/AppenderSettings.d \
./fuentes/DateTime.d \
./fuentes/Logger.d \
./fuentes/LoggerSettings.d \
./fuentes/TPUndavEstable.d 


# Each subdirectory must supply rules for building sources it contributes
fuentes/%.o: ../fuentes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


