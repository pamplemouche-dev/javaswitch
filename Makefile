DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
# Chemin absolu vers l'outil nacp pour corriger l'erreur 127
NACP      := $(DEVKITPRO)/tools/bin/nacp

TARGET    := Mekanism

all:
	# Génération du fichier d'identité
	$(NACP) -c --name "Mekanism" --author "Pamplemouche" --version "1.0.0" $(TARGET).nacp
	# Compilation en binaire ELF
	$(CC) -O2 -Wall -I$(DEVKITPRO)/libnx/include main.c -o $(TARGET).elf -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -lnx
