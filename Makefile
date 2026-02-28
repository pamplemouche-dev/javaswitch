DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c

# On enlève -lnx pour ne plus dépendre du linker bloqué
CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__
# On garde juste switch.specs qui est nécessaire pour la structure du fichier
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET).elf $(LDFLAGS)
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Bare" --author="Dev"

clean:
	rm -f *.elf *.nro
