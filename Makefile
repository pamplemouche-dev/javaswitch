DEVKITPRO := /opt/devkitpro
DEVKITA64 := $(DEVKITPRO)/devkitA64
LIBNX     := $(DEVKITPRO)/libnx

CXX       := $(DEVKITA64)/bin/aarch64-none-elf-g++
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava

all:
	@echo "--- VERIFICATION DES CHEMINS ---"
	@ls -l $(LIBNX)/lib/libnx.a || echo "ERREUR: libnx.a introuvable"
	@ls -l $(LIBNX)/switch.specs || echo "ERREUR: switch.specs introuvable"
	@echo "--------------------------------"
	$(CXX) -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE \
	main.cpp \
	$(LIBNX)/lib/libnx.a \
	-I$(LIBNX)/include \
	-specs=$(LIBNX)/switch.specs \
	-o $(TARGET).elf
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Java" --author="Dev"

clean:
	rm -f *.elf *.nro
