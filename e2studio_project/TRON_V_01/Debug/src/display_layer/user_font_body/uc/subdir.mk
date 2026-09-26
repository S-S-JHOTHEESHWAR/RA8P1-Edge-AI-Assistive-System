################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_layer/user_font_body/uc/A.c \
../src/display_layer/user_font_body/uc/B.c \
../src/display_layer/user_font_body/uc/C.c \
../src/display_layer/user_font_body/uc/D.c \
../src/display_layer/user_font_body/uc/E.c \
../src/display_layer/user_font_body/uc/F.c \
../src/display_layer/user_font_body/uc/G.c \
../src/display_layer/user_font_body/uc/H.c \
../src/display_layer/user_font_body/uc/I.c \
../src/display_layer/user_font_body/uc/J.c \
../src/display_layer/user_font_body/uc/K.c \
../src/display_layer/user_font_body/uc/L.c \
../src/display_layer/user_font_body/uc/M.c \
../src/display_layer/user_font_body/uc/N.c \
../src/display_layer/user_font_body/uc/O.c \
../src/display_layer/user_font_body/uc/P.c \
../src/display_layer/user_font_body/uc/Q.c \
../src/display_layer/user_font_body/uc/R.c \
../src/display_layer/user_font_body/uc/S.c \
../src/display_layer/user_font_body/uc/T.c \
../src/display_layer/user_font_body/uc/U.c \
../src/display_layer/user_font_body/uc/V.c \
../src/display_layer/user_font_body/uc/W.c \
../src/display_layer/user_font_body/uc/X.c \
../src/display_layer/user_font_body/uc/Y.c \
../src/display_layer/user_font_body/uc/Z.c 

C_DEPS += \
./src/display_layer/user_font_body/uc/A.d \
./src/display_layer/user_font_body/uc/B.d \
./src/display_layer/user_font_body/uc/C.d \
./src/display_layer/user_font_body/uc/D.d \
./src/display_layer/user_font_body/uc/E.d \
./src/display_layer/user_font_body/uc/F.d \
./src/display_layer/user_font_body/uc/G.d \
./src/display_layer/user_font_body/uc/H.d \
./src/display_layer/user_font_body/uc/I.d \
./src/display_layer/user_font_body/uc/J.d \
./src/display_layer/user_font_body/uc/K.d \
./src/display_layer/user_font_body/uc/L.d \
./src/display_layer/user_font_body/uc/M.d \
./src/display_layer/user_font_body/uc/N.d \
./src/display_layer/user_font_body/uc/O.d \
./src/display_layer/user_font_body/uc/P.d \
./src/display_layer/user_font_body/uc/Q.d \
./src/display_layer/user_font_body/uc/R.d \
./src/display_layer/user_font_body/uc/S.d \
./src/display_layer/user_font_body/uc/T.d \
./src/display_layer/user_font_body/uc/U.d \
./src/display_layer/user_font_body/uc/V.d \
./src/display_layer/user_font_body/uc/W.d \
./src/display_layer/user_font_body/uc/X.d \
./src/display_layer/user_font_body/uc/Y.d \
./src/display_layer/user_font_body/uc/Z.d 

CREF += \
TRON_V_01.cref 

OBJS += \
./src/display_layer/user_font_body/uc/A.o \
./src/display_layer/user_font_body/uc/B.o \
./src/display_layer/user_font_body/uc/C.o \
./src/display_layer/user_font_body/uc/D.o \
./src/display_layer/user_font_body/uc/E.o \
./src/display_layer/user_font_body/uc/F.o \
./src/display_layer/user_font_body/uc/G.o \
./src/display_layer/user_font_body/uc/H.o \
./src/display_layer/user_font_body/uc/I.o \
./src/display_layer/user_font_body/uc/J.o \
./src/display_layer/user_font_body/uc/K.o \
./src/display_layer/user_font_body/uc/L.o \
./src/display_layer/user_font_body/uc/M.o \
./src/display_layer/user_font_body/uc/N.o \
./src/display_layer/user_font_body/uc/O.o \
./src/display_layer/user_font_body/uc/P.o \
./src/display_layer/user_font_body/uc/Q.o \
./src/display_layer/user_font_body/uc/R.o \
./src/display_layer/user_font_body/uc/S.o \
./src/display_layer/user_font_body/uc/T.o \
./src/display_layer/user_font_body/uc/U.o \
./src/display_layer/user_font_body/uc/V.o \
./src/display_layer/user_font_body/uc/W.o \
./src/display_layer/user_font_body/uc/X.o \
./src/display_layer/user_font_body/uc/Y.o \
./src/display_layer/user_font_body/uc/Z.o 

MAP += \
TRON_V_01.map 


# Each subdirectory must supply rules for building sources it contributes
src/display_layer/user_font_body/uc/%.o: ../src/display_layer/user_font_body/uc/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\console_output" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\i2c_support" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\camera_layer" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\time_counter" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\common" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

