DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.c

CFLAGS    := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__
# On place les bibliothèques ici pour les forcer à la FIN de la commande
LIBS      := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -lnx

all:
	@# Commande critique : SOURCES d'abord, LIBS après
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET).elf $(LIBS)
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Java" --author="Dev"

clean:
	rm -f *.elf *.nro
