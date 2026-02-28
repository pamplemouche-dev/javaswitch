DEVKITPRO := /opt/devkitpro
DEVKITA64 := $(DEVKITPRO)/devkitA64
LIBNX     := $(DEVKITPRO)/libnx

CXX       := $(DEVKITA64)/bin/aarch64-none-elf-g++
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava

# On regroupe TOUT dans une seule commande de lien très précise
all:
	@mkdir -p build
	$(CXX) -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE \
	main.cpp \
	-o $(TARGET).elf \
	-I$(LIBNX)/include \
	-L$(LIBNX)/lib \
	-specs=$(LIBNX)/switch.specs \
	-lnx
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Java" --author="Dev"

clean:
	rm -rf build *.elf *.nro
