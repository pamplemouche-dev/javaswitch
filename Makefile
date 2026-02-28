DEVKITPRO := /opt/devkitpro
DEVKITA64 := $(DEVKITPRO)/devkitA64
LIBNX     := $(DEVKITPRO)/libnx

CXX       := $(DEVKITA64)/bin/aarch64-none-elf-g++
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava

all:
	$(CXX) -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE \
	main.cpp \
	-I$(LIBNX)/include \
	-L$(LIBNX)/lib \
	-specs=$(LIBNX)/switch.specs \
	-o $(TARGET).elf \
	-Wl,--whole-archive -lnx -Wl,--no-whole-archive
	$(NRO) $(TARGET).elf $(TARGET).nro --name="Mekanism Java" --author="Dev"

clean:
	rm -f *.elf *.nro
