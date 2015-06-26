################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CoaxXSection.cpp \
../MicrostripXSection.cpp \
../StriplineXSection.cpp \
../TRLine.cpp \
../TRLineXSect.cpp \
../TRLinesTotal.cpp \
../TRTest.cpp 

OBJS += \
./CoaxXSection.o \
./MicrostripXSection.o \
./StriplineXSection.o \
./TRLine.o \
./TRLineXSect.o \
./TRLinesTotal.o \
./TRTest.o 

CPP_DEPS += \
./CoaxXSection.d \
./MicrostripXSection.d \
./StriplineXSection.d \
./TRLine.d \
./TRLineXSect.d \
./TRLinesTotal.d \
./TRTest.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


