# Default target is OBC if env var isn't defined
TARGET ?= OBC

include mk/cmsis.mk
include mk/freertos.mk
include mk/libcsp.mk

ifeq ($(TARGET), OBC)
include target/obc/obc.mk
else ifeq ($(TARGET), SCI)
include target/sci/sci.mk
else
all:
	@echo "$(TARGET) IS NOT A TARGET (OBC, SCI)"
endif

INCLUDES +=	-Iinc \
			-Iconf \
			-Idrivers

# Syscalls (needed for printf)
SOURCES +=	src/syscalls.c

# FreeRTOS required hooks
SOURCES +=	src/freertos_hooks.c

# CSP CAN driver
SOURCES +=	drivers/csp/can_horizon.c

BUILD_DIR = build/$(TARGET)

ELF = $(BUILD_DIR)/$(TARGET)_fw.elf
HEX = $(BUILD_DIR)/$(TARGET)_fw.hex
BIN = $(BUILD_DIR)/$(TARGET)_fw.bin


OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))
ifeq ($(OS), Windows_NT)
$(BUILD_DIR)/%.o: %.c
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.s
	if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
else
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
endif 

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

all: $(BIN)

flash: $(ELF)
	openocd -f board/st_nucleo_l476rg.cfg -c "program $(ELF) verify reset exit"
ifeq ($(OS), Windows_NT)
clean:
	rd /s /q $(BUILD_DIR)
else
clean:
	rm -rf $(BUILD_DIR)
endif