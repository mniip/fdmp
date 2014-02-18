CFLAGS=
LDFLAGS= -lrt

SOURCES= Floppy.c Synthesizer.c Timer.c Main.c
OBJECTS= $(SOURCES:%.c=%.o)

%.o: %.c
	g++ -o $@ -c $< $(CFLAGS)

all: $(OBJECTS)
	g++ -o fdmp $(OBJECTS) $(LDFLAGS)

Floppy.cpp: Floppy.h
Timer.cpp: Timer.h
Synthesizer.h: Floppy.h
Synthesizer.cpp: Synthesizer.h Timer.h
Main.cpp: Synthesizer.h Timer.h
