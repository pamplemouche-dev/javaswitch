DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismLauncher
SOURCES   := main.c

# Ajout des bibliothèques graphiques
CFLAGS    := -O2 -Wall -I$(DEVKITPRO)/libnx/include -I$(DEVKITPRO)/portlibs/switch/include
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -L$(DEVKITPRO)/portlibs/switch/lib

# L'ordre des LIBS est crucial pour le Linker !
LIBS      := -lSDL2_image -lSDL2 -lpng -ljpeg -lz -lnx

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET).elf $(LDFLAGS) $(LIBS)
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Launcher" --author="Pamplemouche"

clean:
	rm -f *.elf *.nro
