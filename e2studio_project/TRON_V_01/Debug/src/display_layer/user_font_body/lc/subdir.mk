################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_layer/user_font_body/lc/a.c \
../src/display_layer/user_font_body/lc/b.c \
../src/display_layer/user_font_body/lc/c.c \
../src/display_layer/user_font_body/lc/d.c \
../src/display_layer/user_font_body/lc/e.c \
../src/display_layer/user_font_body/lc/f.c \
../src/display_layer/user_font_body/lc/g.c \
../src/display_layer/user_font_body/lc/h.c \
../src/display_layer/user_font_body/lc/i.c \
../src/display_layer/user_font_body/lc/j.c \
../src/display_layer/user_font_body/lc/k.c \
../src/display_layer/user_font_body/lc/l.c \
../src/display_layer/user_font_body/lc/m.c \
../src/display_layer/user_font_body/lc/n.c \
../src/display_layer/user_font_body/lc/o.c \
../src/display_layer/user_font_body/lc/p.c \
../src/display_layer/user_font_body/lc/q.c \
../src/display_layer/user_font_body/lc/r.c \
../src/display_layer/user_font_body/lc/s.c \
../src/display_layer/user_font_body/lc/t.c \
../src/display_layer/user_font_body/lc/u.c \
../src/display_layer/user_font_body/lc/v.c \
../src/display_layer/user_font_body/lc/w.c \
../src/display_layer/user_font_body/lc/x.c \
../src/display_layer/user_font_body/lc/y.c \
../src/display_layer/user_font_body/lc/z.c 

C_DEPS += \
./src/display_layer/user_font_body/lc/a.d \
./src/display_layer/user_font_body/lc/b.d \
./src/display_layer/user_font_body/lc/c.d \
./src/display_layer/user_font_body/lc/d.d \
./src/display_layer/user_font_body/lc/e.d \
./src/display_layer/user_font_body/lc/f.d \
./src/display_layer/user_font_body/lc/g.d \
./src/display_layer/user_font_body/lc/h.d \
./src/display_layer/user_font_body/lc/i.d \
./src/display_layer/user_font_body/lc/j.d \
./src/display_layer/user_font_body/lc/k.d \
./src/display_layer/user_font_body/lc/l.d \
./src/display_layer/user_font_body/lc/m.d \
./src/display_layer/user_font_body/lc/n.d \
./src/display_layer/user_font_body/lc/o.d \
./src/display_layer/user_font_body/lc/p.d \
./src/display_layer/user_font_body/lc/q.d \
./src/display_layer/user_font_body/lc/r.d \
./src/display_layer/user_font_body/lc/s.d \
./src/display_layer/user_font_body/lc/t.d \
./src/display_layer/user_font_body/lc/u.d \
./src/display_layer/user_font_body/lc/v.d \
./src/display_layer/user_font_body/lc/w.d \
./src/display_layer/user_font_body/lc/x.d \
./src/display_layer/user_font_body/lc/y.d \
./src/display_layer/user_font_body/lc/z.d 

CREF += \
TRON_V_01.cref 

OBJS += \
./src/display_layer/user_font_body/lc/a.o \
./src/display_layer/user_font_body/lc/b.o \
./src/display_layer/user_font_body/lc/c.o \
./src/display_layer/user_font_body/lc/d.o \
./src/display_layer/user_font_body/lc/e.o \
./src/display_layer/user_font_body/lc/f.o \
./src/display_layer/user_font_body/lc/g.o \
./src/display_layer/user_font_body/lc/h.o \
./src/display_layer/user_font_body/lc/i.o \
./src/display_layer/user_font_body/lc/j.o \
./src/display_layer/user_font_body/lc/k.o \
./src/display_layer/user_font_body/lc/l.o \
./src/display_layer/user_font_body/lc/m.o \
./src/display_layer/user_font_body/lc/n.o \
./src/display_layer/user_font_body/lc/o.o \
./src/display_layer/user_font_body/lc/p.o \
./src/display_layer/user_font_body/lc/q.o \
./src/display_layer/user_font_body/lc/r.o \
./src/display_layer/user_font_body/lc/s.o \
./src/display_layer/user_font_body/lc/t.o \
./src/display_layer/user_font_body/lc/u.o \
./src/display_layer/user_font_body/lc/v.o \
./src/display_layer/user_font_body/lc/w.o \
./src/display_layer/user_font_body/lc/x.o \
./src/display_layer/user_font_body/lc/y.o \
./src/display_layer/user_font_body/lc/z.o 

MAP += \
TRON_V_01.map 


# Each subdirectory must supply rules for building sources it contributes
src/display_layer/user_font_body/lc/%.o: ../src/display_layer/user_font_body/lc/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\console_output" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\i2c_support" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\camera_layer" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\time_counter" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\common" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

