# SCI make module
SCI_DIR = target/sci

# Paths
STM32L4_HAL = hw/stcubehal/L4
STM32L4_CMSIS	= hw/stcmsis/L4

# SCI includes
INCLUDES +=	-I$(SCI_DIR)/inc

# SCI config includes
INCLUDES +=	-I${SCI_DIR}/conf

# SCI driver includes
INCLUDES +=	-I${SCI_DIR}/drivers

# SCI bsp includes
INCLUDES +=	-I${SCI_DIR}/bsp

# SCI library includes
INCLUDES +=	-I${SCI_DIR}/lib

# STM32HAL includes
INCLUDES +=	-I${STM32L4_HAL}/Inc

# STM32L4 CMSIS includes
INCLUDES +=	-I${STM32L4_CMSIS}/Include

# STM32HAL source files
SOURCES +=	${STM32L4_HAL}/Src/stm32l4xx_hal_can.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_dfsdm.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_i2c.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_i2c_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_rtc.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_rtc_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_tim.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_tim_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_uart.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_uart_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_rcc.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_rcc_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_flash.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_flash_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_flash_ramfunc.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_gpio.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_dma.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_dma_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_pwr.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_pwr_ex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_cortex.c \
			${STM32L4_HAL}/Src/stm32l4xx_hal_exti.c

# STM32L4 CMSIS source file
SOURCES +=	${STM32L4_CMSIS}/Source/Templates/system_stm32l4xx.c

# STM32L4 hardware initialization
SOURCES +=	$(SCI_DIR)/src/sci_board.c

# STM32L4 msp initialization and deinitialization
SOURCES +=	$(SCI_DIR)/src/sci_msp.c

# Main source file
SOURCES +=	$(SCI_DIR)/src/sci_main.c

# BSP source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01.c

# IMU source file
SOURCES +=	$(SCI_DIR)/bsp/lsm6dsl/lsm6dsl.c
# Accelerometer source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01_accelero.c

# HTS source file
SOURCES +=	$(SCI_DIR)/bsp/hts221/hts221.c
# Humidity sensor source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01_hsensor.c
# Temperature sensor source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01_tsensor.c

# Magnetometer source file
SOURCES +=	$(SCI_DIR)/bsp/lis3mdl/lis3mdl.c
# Magnetometer source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01_magneto.c

# Pressure sensor source file
SOURCES +=	$(SCI_DIR)/bsp/lps22hb/lps22hb.c
# Pressure sensor source file
SOURCES +=	$(SCI_DIR)/bsp/stm32l475e_iot01_psensor.c

# LibSci source file
SOURCES +=	$(SCI_DIR)/lib/libsci/libsci.c

# Startup file (STM32L475 - B-L475E)
SOURCES += ${STM32L4_CMSIS}/Source/Templates/gcc/startup_stm32l475xx.s

# Linker script (SCi)
LINKER_SCRIPT =	$(SCI_DIR)/sci_flash.ld

# Toolchain stuff
CC		= 	arm-none-eabi-gcc
LD 		= 	arm-none-eabi-gcc
AR 		= 	arm-none-eabi-ar
OBJCOPY = 	arm-none-eabi-objcopy
CFLAGS	+=	-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
			-DUSE_HAL_DRIVER -DSTM32L475xx -fshort-enums -fmessage-length=0 \
			-ffunction-sections -fdata-sections -Wall -ffreestanding -Og -g	\
			-gdwarf-2 -DDEBUG
LDFLAGS +=	-lc -lm -lnosys -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nano.specs -u _printf_float -T$(LINKER_SCRIPT)

