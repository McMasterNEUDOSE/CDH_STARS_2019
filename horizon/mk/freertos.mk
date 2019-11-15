# FreeRTOS make module

# FreeRTOS path
FREERTOS_DIR = ext/freertos

# Includes
INCLUDES += -I$(FREERTOS_DIR)/include

# Includes (CM4 specific)
INCLUDES += -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F

# Source files
SOURCES +=	$(FREERTOS_DIR)/croutine.c      \
			$(FREERTOS_DIR)/event_groups.c  \
			$(FREERTOS_DIR)/list.c  		\
			$(FREERTOS_DIR)/queue.c 		\
			$(FREERTOS_DIR)/stream_buffer.c \
			$(FREERTOS_DIR)/tasks.c 		\
			$(FREERTOS_DIR)/timers.c

# CM4 FreeRTOS port
SOURCES +=	$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c

# FreeRTOS heap_4 memmang
SOURCES += $(FREERTOS_DIR)/portable/MemMang/heap_4.c
