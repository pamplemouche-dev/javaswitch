DEVKITPRO := /opt/devkitpro
CXX       := $(DEVKITPRO)/devkitA64/bin/aarch64-none-elf-g++
NRO       := $(DEVKITPRO)/tools/bin/elf2nro

TARGET    := MekanismJava
SOURCES   := main.cpp

CXXFLAGS  := -O2 -Wall -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__
LIBS      := -specs=$(DEVKITPRO)/libnx/switch.specs -L$(DEVKITPRO)/libnx/lib -lnx

all: $(TARGET).nro

$(TARGET).nro: $(TARGET).elf
	$(NRO) $< $@ --name="Mekanism Java" --author="Dev" --version="1.0"

$(TARGET).elf:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LIBS)

clean:
	rm -f *.elf *.nro
