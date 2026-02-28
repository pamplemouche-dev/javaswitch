DEVKITPRO := /opt/devkitpro
CC        := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-gcc
NACP      := $(DEVKITPRO)/tools/bin/nacp

TARGET    := Mekanism

all:
	# 1. Generation des metadonnees
	$(NACP) -c --name "Mekanism" --author "Pamplemouche" --version "1.0.0" $(TARGET).nacp
	# 2. Compilation du binaire brut ELF
	$(CC) -O2 -Wall -I$(DEVKITPRO)/libnx/include main.c -o $(TARGET).elf -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -lnx
	@echo "Composants NSP prets."

clean:
	rm -f *.elf *.nacp
