################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Path/Particales.cpp \
../Path/PathSearcher.cpp \
../Path/WayPointsManager.cpp 

OBJS += \
./Path/Particales.o \
./Path/PathSearcher.o \
./Path/WayPointsManager.o 

CPP_DEPS += \
./Path/Particales.d \
./Path/PathSearcher.d \
./Path/WayPointsManager.d 


# Each subdirectory must supply rules for building sources it contributes
Path/%.o: ../Path/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


