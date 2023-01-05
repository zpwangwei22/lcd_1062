# path to STM32F103 standard peripheral library
#STD_PERIPH_LIBS ?= ./STM32F10x_StdPeriph_Lib_V3.5.0/

# list of source files
SOURCES  = ./user/main.c
SOURCES += ./core/system_stm32f10x.c
SOURCES += ./lib/src/stm32f10x_rcc.c
SOURCES += ./lib/src/stm32f10x_gpio.c
#SOURCES += ./lib/src/stm32f10x_adc.c
#SOURCES += ./lib/src/stm32f10x_tim.c
#SOURCES += ./lib/src/stm32f10x_exti.c
SOURCES += ./core/startup_stm32f10x_md.s
#SOURCES += ./user/led.c
#SOURCES += ./user/tim2.c
SOURCES += ./lib/src/misc.c
SOURCES += ./core/system_stm32f10x.c
SOURCES += ./user/delay.c
SOURCES += ./user/lcd_1602.c
#SOURCES += ./user/exti.c
#SOURCES += ./user/key.c
SOURCES += ./lib/src/stm32f10x_usart.c
SOURCES += ./user/my_usart.c
SOURCES += ./user/dht11.c
#SOURCES += ./user/adc.c

# name for output binary files
PROJECT ?= DHT11

# compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

# specify compiler flags
CFLAGS  = -g -O2 -Wall 
CFLAGS += -T./core/stm32f103c8t6.ld
CFLAGS += -fdata-sections -ffunction-sections -u _printf_float
CFLAGS += --specs=nosys.specs --specs=nano.specs 
#--specs=rdimon.specs -lc -lrdimon
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 #-mthumb-interwork
#CFLAGS += -Wno-unknown-pragmas
#CFLAGS += -mfloat-abi=soft -mfpu=fpv4-sp-d16
#CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
#CFLAGS += -Wl,--gc-sections
#CFLAGS += -I.
#CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I./core
CFLAGS += -I./lib/inc
CFLAGS += -I./user

#OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile -lm -lc is used to compile math.h
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o ./obj/$@ -lm -lc
	$(OBJCOPY) -O ihex ./obj/$(PROJECT).elf ./obj/$(PROJECT).hex
	$(OBJCOPY) -O binary ./obj/$(PROJECT).elf ./obj/$(PROJECT).bin

# remove binary files
clean:
	-rm -f ./obj/*.o ./obj/*.elf ./obj/*.hex ./obj/*.bin

# flash
burn:
	$(ST_FLASH) write ./obj/$(PROJECT).bin 0x8000000
