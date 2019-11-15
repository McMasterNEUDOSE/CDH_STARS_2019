# OBC make module
OBC_DIR = target/obc

# Paths
STM32L4_HAL = hw/stcubehal/L4
STM32L4_CMSIS	= hw/stcmsis/L4

# OBC includes
INCLUDES +=	-I$(OBC_DIR)/inc

# STM32HAL includes
INCLUDES +=	-I${STM32L4_HAL}/Inc

# OBC config includes
INCLUDES +=	-I${OBC_DIR}/conf

# OBC drivers includes
INCLUDES +=	-I${OBC_DIR}/drivers

# OBC includes
INCLUDES +=	-I${OBC_DIR}/inc

# STM32L4 CMSIS includes
INCLUDES +=	-I${STM32L4_CMSIS}/Include

# STM32HAL source files
SOURCES +=	${STM32L4_HAL}/Src/stm32l4xx_hal_can.c \
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

# Startup file (STM32L476 - Nucleo L476RG)
SOURCES += ${STM32L4_CMSIS}/Source/Templates/gcc/startup_stm32l476xx.s


# STM32L4 hardware initialization
SOURCES +=	$(OBC_DIR)/src/obc_board.c

# STM32L4 msp initialization and deinitialization
SOURCES +=	$(OBC_DIR)/src/obc_msp.c

# Main source file
SOURCES +=	$(OBC_DIR)/src/obc_main.c

# Linker script (OBC)
LINKER_SCRIPT =	$(OBC_DIR)/obc_flash.ld

# Toolchain stuff
CC		= 	arm-none-eabi-gcc
LD 		= 	arm-none-eabi-gcc
AR 		= 	arm-none-eabi-ar
OBJCOPY = 	arm-none-eabi-objcopy
CFLAGS	+=	-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
			-DUSE_HAL_DRIVER -DSTM32L476xx -fshort-enums -fmessage-length=0 \
			-ffunction-sections -fdata-sections -Wall -ffreestanding -Og -g	\
			-gdwarf-2 -DDEBUG
LDFLAGS +=	-lc -lm -lnosys -specs=nano.specs -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -u _printf_float -T$(LINKER_SCRIPT)