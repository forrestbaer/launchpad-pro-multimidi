BUILDDIR = build

TOOLS = tools

SOURCES += src/app.c src/util/clear_func.c src/util/delve.c 
SOURCES += src/util/drum.c src/util/note_func.c src/util/octave.c src/util/phrase.c
SOURCES += src/midi/aftertouch.c src/midi/cc.c src/midi/midi.c src/midi/note.c 
SOURCES += src/midi/pc.c src/midi/sysex.c
SOURCES += src/time/step.c src/time/loopevent.c src/visual/color.c 
SOURCES += src/visual/particle.c src/visual/pressure.c
SOURCES += src/visual/overlay.c src/state/state.c src/visual/surface.c src/time/timer.c
SOURCES += src/music/diatonic.c src/music/arp.c src/music/kill.c
SOURCES += src/time/animation.c src/time/arpegiator.c src/time/loop.c src/time/sequence.c
SOURCES += src/midi/event.c src/visual/clear.c src/visual/pad.c
SOURCES += src/state/states/setup.c src/state/states/scalearp.c src/state/states/mastercontrol.c 
SOURCES += src/state/states/digitonepad.c src/state/states/circuitpad.c src/state/states/keyscale.c
SOURCES += src/visual/areaset.c src/visual/columnset.c src/visual/rowset.c

INCLUDES += -Iinclude -I

LIB = lib/launchpad_pro.a

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# output files
SYX = $(BUILDDIR)/openlaunch_lpp.syx
ELF = $(BUILDDIR)/launchpad_pro.elf
HEX = $(BUILDDIR)/launchpad_pro.hex
HEXTOSYX = $(BUILDDIR)/hextosyx
SIMULATOR = $(BUILDDIR)/simulator

# tools
HOST_GPP = g++
HOST_GCC = gcc
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = -Os -g -Wall -I.\
-D_STM32F103RBT6_  -D_STM3x_  -D_STM32x_ -mthumb -mcpu=cortex-m3 \
-fsigned-char  -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=6000000UL \
-DCMSIS -DUSE_GLOBAL_CONFIG   -g3 -ffunction-sections -std=c99  -mlittle-endian \
$(INCLUDES) -o

LDSCRIPT = stm32_flash.ld

LDFLAGS += -T$(LDSCRIPT) -u _start -u _Minimum_Stack_Size  -mcpu=cortex-m3 -mthumb -specs=nano.specs -specs=nosys.specs -nostdlib -Wl,-static  -g3 -N -nostartfiles -Wl,--gc-sections

all: $(SYX)

# build the final sysex file from the ELF - run the simulator first
$(SYX): $(HEX) $(HEXTOSYX) $(SIMULATOR)
	./$(SIMULATOR)
	./$(HEXTOSYX) $(HEX) $(SYX)

# build the tool for conversion of ELF files to sysex, ready for upload to the unit
$(HEXTOSYX):
	$(HOST_GPP) -Ofast -std=c++0x -I./$(TOOLS)/libintelhex/include ./$(TOOLS)/libintelhex/src/intelhex.cc $(TOOLS)/hextosyx.cpp -o $(HEXTOSYX)

# build the simulator (it's a very basic test of the code before it runs on the device!)
$(SIMULATOR):
	$(HOST_GCC) -g3 -O0 -std=c99 -Iinclude $(TOOLS)/simulator.c $(SOURCES) -o $(SIMULATOR)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB)

DEPENDS := $(OBJECTS:.o=.d)

-include $(DEPENDS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -MMD -o $@ $<

clean:
	rm -rf $(BUILDDIR)
