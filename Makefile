# makefile
# target … : prerequisites …
#		recipe
#		…
#		…

# Setting compiler
PRO_DIR		:= .
PROJ_NAME	:= stm32f0_discovery_sort
OUTPUT_PATH := $(PRO_DIR)/Output

DELAY_DIR	:= $(PRO_DIR)/Lib/delay
INC_DIR		:= $(PRO_DIR)/Inc
SRC_DIR 	:= $(PRO_DIR)/Src
LINKER_FILE	:= $(PRO_DIR)/Linker/stm32f0_discovery.ld

COMPILER_DIR 	:= C:/GCC_CPL/7_2017-q4-major

PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
OBJCPY			:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-objcopy
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o $(OUTPUT_PATH)/delay.o

# Compiler option
CC_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -O0 -g -mthumb -I$(INC_DIR)
ASM_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "____________________________________________________________________________"
	@echo "Compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.s
	@echo "____________________________________________________________________________"
	@echo  "Compile $(SRC_DIR)/startup_ARMCM0.s file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

$(OUTPUT_PATH)/delay.o: $(DELAY_DIR)/delay.c
	@echo "____________________________________________________________________________"
	@echo  "Compile $(DELAY_DIR)/delay.c file"
	$(CC) $(CC_OPT) $(DELAY_DIR)/delay.c -o $(OUTPUT_PATH)/delay.o

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "____________________________________________________________________________"
	@echo  "Link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf

hex: $(OUTPUT_PATH)/$(PROJ_NAME).elf
	@echo "____________________________________________________________________________"
	@echo  "Create new file: ($(PROJ_NAME).hex)"
	$(OBJCPY) -O ihex $(OUTPUT_PATH)/$(PROJ_NAME).elf $(OUTPUT_PATH)/$(PROJ_NAME).hex	

clean:
	@rm -rf $(OUTPUT_PATH)/*