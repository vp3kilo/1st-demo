# makefile
# target … : prerequisites …
#		recipe
#		…
#		…

# Setting compiler
PRO_DIR		:= .
PROJ_NAME	:= stm32f0_discovery_sort
OUTPUT_PATH := $(PRO_DIR)/Output

INC_DIR		:= $(PRO_DIR)/Inc
SRC_DIR 	:= $(PRO_DIR)/Src
LINKER_FILE	:= $(PRO_DIR)/Linker/stm32f0_discovery.ld

COMPILER_DIR 	:= C:/GCC_CPL/7_2017-q4-major

PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o

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

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "____________________________________________________________________________"
	@echo  "Link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf
	
clean:
	@rm -rf $(OUTPUT_PATH)/*