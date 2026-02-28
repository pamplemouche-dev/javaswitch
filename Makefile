DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
OBJCOPY   := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-objcopy
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c
DATA      := config_default.json

# Inclusion des dossiers de la bibliothèque Switch
CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__ -I$(DEVKITPRO)/libnx/include
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib

all:
	@# 1. Préparation du JSON
	$(OBJCOPY) -I binary -O elf64-littleaarch64 -B aarch64 $(DATA) config_data.o
	@# 2. Compilation et Lien (SOURCES avant LIBS)
	$(CC) $(CFLAGS) $(SOURCES) config_data.o -o $(TARGET).elf $(LDFLAGS) -lnx
	@# 3. Création du fichier final pour la console
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Java" --author="Dev"

clean:
	rm -f *.elf *.nro *.o
