DEVKITPRO := /opt/devkitpro
PREFIX    := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-
CC        := $(PREFIX)gcc
OBJCOPY   := $(PREFIX)objcopy
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c
DATA      := config_default.json

CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__
# On force switch.specs car c'est lui qui définit le point d'entrée _start pour la Switch
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs

all:
	@# 1. Convertir le JSON en objet
	$(OBJCOPY) -I binary -O elf64-littleaarch64 -B aarch64 $(DATA) config_data.o
	@# 2. Compiler SANS lier la libnx (on l'évite car elle bloque)
	$(CC) $(CFLAGS) $(SOURCES) config_data.o -o $(TARGET).elf $(LDFLAGS)
	@# 3. Transformer en NRO
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Embedded" --author="Dev"

clean:
	rm -f *.elf *.nro *.o
