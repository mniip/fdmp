#include <fstream>

#include <math.h>

#include "Synthesizer.h"
#include "Timer.h"
#include "Midi.h"

// Just some temporary foo stuff

double NTF(int note)
{
	return 440.0 * pow(2.0, note / 12.0);
}

int main(int argc, const char *argv[])
{
	Synthesizer *s = new Synthesizer("/dev/fd0");
	Timer t;
	t.sleep(1, 0);
	Midi::Thread w;
	std::ifstream is(argv[1], std::ifstream::binary);
	w.Parse(is);
	is.close();
	unsigned long int ticks = w.tracks.rbegin()->notes.begin()->start;
	for(std::list<Midi::Note>::const_iterator i = w.tracks.rbegin()->notes.begin(), end = w.tracks.rbegin()->notes.end(); i != end; i++)
	{
		if(ticks < i->start)
		{
			t.sleep(0, (i->start - ticks) * 1.0e9 / w.bpm);
			ticks = i->start;
		}
		s->play(NTF(i->note - 100), i->duration / (double)w.bpm);
		ticks += i->duration;
	}
	delete s;
	return 0;
}
