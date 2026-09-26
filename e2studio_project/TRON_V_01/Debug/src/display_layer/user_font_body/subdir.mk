################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_layer/user_font_body/0.c \
../src/display_layer/user_font_body/1.c \
../src/display_layer/user_font_body/2.c \
../src/display_layer/user_font_body/3.c \
../src/display_layer/user_font_body/4.c \
../src/display_layer/user_font_body/5.c \
../src/display_layer/user_font_body/6.c \
../src/display_layer/user_font_body/7.c \
../src/display_layer/user_font_body/8.c \
../src/display_layer/user_font_body/9.c \
../src/display_layer/user_font_body/AND.c \
../src/display_layer/user_font_body/CLOSED_CURVED.c \
../src/display_layer/user_font_body/CLOSED_SQUARE.c \
../src/display_layer/user_font_body/COLON.c \
../src/display_layer/user_font_body/COMMA.c \
../src/display_layer/user_font_body/DEGREES.c \
../src/display_layer/user_font_body/FULL_STOP.c \
../src/display_layer/user_font_body/MINUS.c \
../src/display_layer/user_font_body/OPEN_CURVED.c \
../src/display_layer/user_font_body/OPEN_SQUARE.c \
../src/display_layer/user_font_body/PERCENT.c \
../src/display_layer/user_font_body/SLASH.c \
../src/display_layer/user_font_body/SPACE.c \
../src/display_layer/user_font_body/UNDERSCORE.c \
../src/display_layer/user_font_body/user_font_body_if.c 

C_DEPS += \
./src/display_layer/user_font_body/0.d \
./src/display_layer/user_font_body/1.d \
./src/display_layer/user_font_body/2.d \
./src/display_layer/user_font_body/3.d \
./src/display_layer/user_font_body/4.d \
./src/display_layer/user_font_body/5.d \
./src/display_layer/user_font_body/6.d \
./src/display_layer/user_font_body/7.d \
./src/display_layer/user_font_body/8.d \
./src/display_layer/user_font_body/9.d \
./src/display_layer/user_font_body/AND.d \
./src/display_layer/user_font_body/CLOSED_CURVED.d \
./src/display_layer/user_font_body/CLOSED_SQUARE.d \
./src/display_layer/user_font_body/COLON.d \
./src/display_layer/user_font_body/COMMA.d \
./src/display_layer/user_font_body/DEGREES.d \
./src/display_layer/user_font_body/FULL_STOP.d \
./src/display_layer/user_font_body/MINUS.d \
./src/display_layer/user_font_body/OPEN_CURVED.d \
./src/display_layer/user_font_body/OPEN_SQUARE.d \
./src/display_layer/user_font_body/PERCENT.d \
./src/display_layer/user_font_body/SLASH.d \
./src/display_layer/user_font_body/SPACE.d \
./src/display_layer/user_font_body/UNDERSCORE.d \
./src/display_layer/user_font_body/user_font_body_if.d 

CREF += \
TRON_V_01.cref 

OBJS += \
./src/display_layer/user_font_body/0.o \
./src/display_layer/user_font_body/1.o \
./src/display_layer/user_font_body/2.o \
./src/display_layer/user_font_body/3.o \
./src/display_layer/user_font_body/4.o \
./src/display_layer/user_font_body/5.o \
./src/display_layer/user_font_body/6.o \
./src/display_layer/user_font_body/7.o \
./src/display_layer/user_font_body/8.o \
./src/display_layer/user_font_body/9.o \
./src/display_layer/user_font_body/AND.o \
./src/display_layer/user_font_body/CLOSED_CURVED.o \
./src/display_layer/user_font_body/CLOSED_SQUARE.o \
./src/display_layer/user_font_body/COLON.o \
./src/display_layer/user_font_body/COMMA.o \
./src/display_layer/user_font_body/DEGREES.o \
./src/display_layer/user_font_body/FULL_STOP.o \
./src/display_layer/user_font_body/MINUS.o \
./src/display_layer/user_font_body/OPEN_CURVED.o \
./src/display_layer/user_font_body/OPEN_SQUARE.o \
./src/display_layer/user_font_body/PERCENT.o \
./src/display_layer/user_font_body/SLASH.o \
./src/display_layer/user_font_body/SPACE.o \
./src/display_layer/user_font_body/UNDERSCORE.o \
./src/display_layer/user_font_body/user_font_body_if.o 

MAP += \
TRON_V_01.map 


# Each subdirectory must supply rules for building sources it contributes
src/display_layer/user_font_body/%.o: ../src/display_layer/user_font_body/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\console_output" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\i2c_support" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\camera_layer" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\time_counter" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\common" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

