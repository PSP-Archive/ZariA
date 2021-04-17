TARGET = main
OBJS = main.o framebuffer.o graphics.o home.o mp3player.o 

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
STDLIBS=   -lSDL_mixer -lSDLmain  -lSDL_image -lSDL   -lvorbisfile -lvorbis  -logg -lpng -ljpeg -lm -lz \
		 -lmad -lpspsdk -lpspctrl  -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lpsphprm 
LIBS += $(STDLIBS)$(YOURLIBS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Z@riA test Versi0N


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


