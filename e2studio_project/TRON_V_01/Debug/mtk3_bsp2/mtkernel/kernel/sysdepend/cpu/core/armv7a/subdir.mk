################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/dispatch.S \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_entry.S \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/int_asm.S \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_hdl.S \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/vector_tbl.S 

C_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/cpu_cntl.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_hdl.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/interrupt.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_main.c 

C_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/cpu_cntl.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_hdl.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/interrupt.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_main.d 

CREF += \
TRON_V_01.cref 

OBJS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/cpu_cntl.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/dispatch.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_entry.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_hdl.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/int_asm.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/interrupt.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_hdl.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_main.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/vector_tbl.o 

MAP += \
TRON_V_01.map 

S_UPPER_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/dispatch.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/exc_entry.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/int_asm.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/reset_hdl.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/vector_tbl.d 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\console_output" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\i2c_support" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\camera_layer" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\time_counter" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src\\common" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/core/armv7a/%.S
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -x assembler-with-cpp -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\mtkernel\\kernel\\knlinc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2\\config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\mtk3_bsp2" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg\\bsp" -I"." -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_gen" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra_cfg\\fsp_cfg" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\src" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\api" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\inc\\instances" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\tflite-micro" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ruy" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\gemmlowp" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_drw" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\jhoth\\Downloads\\TRON_V_01_scd40_uart\\TRON_V_01\\ra\\tes\\dave2d\\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c "$<" -o "$@")
	@clang  --target=arm-none-eabi @"$@.in"

