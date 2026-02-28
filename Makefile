DEVKITPRO := /opt/devkitpro
DEVKITA64 := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-
CC        := $(DEVKITA64)gcc
OBJCOPY   := $(DEVKITA64)objcopy
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c
DATA      := config_default.json

CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__ -I$(DEVKITPRO)/libnx/include
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib

all:
	@# 1. Convertir le JSON
	$(OBJCOPY) -I binary -O elf64-littleaarch64 -B aarch64 $(DATA) config_data.o
	@# 2. Lier TOUT ensemble avec libnx en dur
	$(CC) $(CFLAGS) $(SOURCES) config_data.o -o $(TARGET).elf $(LDFLAGS) -lnx
	@# 3. Produire le NRO
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Full" --author="Dev"

clean:
	rm -f *.elf *.nro *.o
