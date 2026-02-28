DEVKITPRO := /opt/devkitpro
PREFIX    := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-
CC        := $(PREFIX)gcc
NRO       := $(DEVKITPRO)/tools/bin/elf2nro
NACP      := $(DEVKITPRO)/tools/bin/nacp

TARGET    := MekanismLauncher
SOURCES   := main.c

# Chemins pour inclure SDL2 (Portlibs)
CFLAGS    := -O2 -Wall -I$(DEVKITPRO)/libnx/include -I$(DEVKITPRO)/portlibs/switch/include -D__SWITCH__
LDFLAGS   := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -L$(DEVKITPRO)/portlibs/switch/lib

# Bibliothèques nécessaires pour un "vrai" jeu
LIBS      := -lSDL2_image -lSDL2 -lpng -ljpeg -lz -lnx

all:
	@# Création des métadonnées du "Jeu" pour le menu Switch
	$(NACP) -c --name "Mekanism Launcher" --author "Pamplemouche" --version "1.0.0" $(TARGET).nacp
	@# Compilation
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET).elf $(LDFLAGS) $(LIBS)
	@# Création du NRO avec icône et infos
	$(NRO) $(TARGET).elf $(TARGET).nro --nacp=$(TARGET).nacp --name="Mekanism"

clean:
	rm -f *.elf *.nro *.nacp
