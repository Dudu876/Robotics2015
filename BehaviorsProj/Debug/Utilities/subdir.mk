################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utilities/Global.cpp \
../Utilities/Point.cpp \
../Utilities/Position.cpp 

OBJS += \
./Utilities/Global.o \
./Utilities/Point.o \
./Utilities/Position.o 

CPP_DEPS += \
./Utilities/Global.d \
./Utilities/Point.d \
./Utilities/Position.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


