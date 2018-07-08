BUILDDIR = build

TOOLS = tools

SOURCES += src/app.c src/atoms/function/cc_func.c src/atoms/function/delve.c src/atoms/function/drum.c src/atoms/function/note_func.c src/atoms/function/pc_func.c src/atoms/function/phrase.c
SOURCES += src/atoms/midi/aftertouch.c src/atoms/midi/cc.c src/atoms/midi/note.c src/atoms/midi/pc.c src/atoms/midi/sysex.c src/atoms/time/step.c src/atoms/time/loopevent.c src/atoms/visual/color.c src/atoms/visual/light.c
SOURCES += src/environment/overlay.c src/environment/state.c src/environment/surface.c
SOURCES += src/molecules/music/diatonic.c src/molecules/time/animation.c src/molecules/time/loop.c src/molecules/time/sequence.c src/molecules/event.c src/molecules/external_input.c src/molecules/pad.c
SOURCES += src/organisms/visual/areaset.c src/organisms/visual/columnset.c src/organisms/visual/rowset.c src/organisms/timer.c src/organisms/valuestore.c

INCLUDES += -Iinclude -I

LIB = lib/launchpad_pro.a

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# output files
SYX = $(BUILDDIR)/launchpad_pro.syx
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
