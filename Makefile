DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
OBJCOPY   := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-objcopy
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c
DATA      := config_default.json

CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs

all:
	@# 1. Transformer le JSON en code objet
	$(OBJCOPY) -I binary -O elf64-littleaarch64 -B aarch64 $(DATA) config_data.o
	@# 2. Compiler le main avec le JSON intégré
	$(CC) $(CFLAGS) $(SOURCES) config_data.o -o $(TARGET).elf $(LDFLAGS)
	@# 3. Créer le NRO
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Full" --author="Dev"

clean:
	rm -f *.elf *.nro *.o
