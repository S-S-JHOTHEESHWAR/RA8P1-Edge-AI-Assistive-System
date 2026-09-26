################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/mcu/all/bsp_clocks.c \
../ra/fsp/src/bsp/mcu/all/bsp_common.c \
../ra/fsp/src/bsp/mcu/all/bsp_delay.c \
../ra/fsp/src/bsp/mcu/all/bsp_group_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_guard.c \
../ra/fsp/src/bsp/mcu/all/bsp_io.c \
../ra/fsp/src/bsp/mcu/all/bsp_ipc.c \
../ra/fsp/src/bsp/mcu/all/bsp_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_macl.c \
../ra/fsp/src/bsp/mcu/all/bsp_ospi_b.c \
../ra/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../ra/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../ra/fsp/src/bsp/mcu/all/bsp_sdram.c \
../ra/fsp/src/bsp/mcu/all/bsp_security.c 

C_DEPS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.d \
./ra/fsp/src/bsp/mcu/all/bsp_common.d \
./ra/fsp/src/bsp/mcu/all/bsp_delay.d \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_guard.d \
./ra/fsp/src/bsp/mcu/all/bsp_io.d \
./ra/fsp/src/bsp/mcu/all/bsp_ipc.d \
./ra/fsp/src/bsp/mcu/all/bsp_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_macl.d \
./ra/fsp/src/bsp/mcu/all/bsp_ospi_b.d \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.d \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.d \
./ra/fsp/src/bsp/mcu/all/bsp_security.d 

CREF += \
TRON_V_01.cref 

OBJS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.o \
./ra/fsp/src/bsp/mcu/all/bsp_common.o \
./ra/fsp/src/bsp/mcu/all/bsp_delay.o \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_guard.o \
./ra/fsp/src/bsp/mcu/all/bsp_io.o \
./ra/fsp/src/bsp/mcu/all/bsp_ipc.o \
./ra/fsp/src/bsp/mcu/all/bsp_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_macl.o \
./ra/fsp/src/bsp/mcu/all/bsp_ospi_b.o \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.o \
./ra/fsp/src/bsp/mcu/all/bsp_security.o 

MAP += \
TRON_V_01.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/mcu/all/%.o: ../ra/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\console_output" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\i2c_support" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\camera_layer" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\time_counter" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\common" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

