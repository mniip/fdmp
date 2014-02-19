CFLAGS= -g
LDFLAGS= -lrt

SOURCES= Floppy.cpp Synthesizer.cpp Timer.cpp Main.cpp Midi.cpp
OBJECTS= $(SOURCES:%.cpp=%.o)

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

all: $(OBJECTS)
	g++ -o fdmp $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

Floppy.cpp: Floppy.h
Timer.cpp: Timer.h
Synthesizer.h: Floppy.h
Synthesizer.cpp: Synthesizer.h Timer.h
Main.cpp: Synthesizer.h Timer.h Midi.h
Midi.cpp: Midi.h
