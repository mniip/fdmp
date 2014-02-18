#include "Synthesizer.h"
#include "Timer.h"

Synthesizer::Synthesizer(std::string device):
	Floppy(device)
{
	speed(6000);
	seek(0);
	speed(1000);
	direction = 1;
}

void Synthesizer::play(double frequence, double duration)
{
	int ticks = duration * frequence;
	long target = 1.0e9 / frequence;
	Timer t;
	t.start();
	if(track > 0 && track < 79)
		if(track + (ticks % 80) * direction >= 79 || track + (ticks % 80) <= 0)
			direction = -direction;
	for(int i = 0; i < ticks; i++)
	{
		int dest = track + direction;
		if(dest == 0 || dest == 79)
			direction = -direction;
		seek(dest);
		t.sleep(0, target * (i + 1) - t.nsec_elapsed());
	}
}

Synthesizer::~Synthesizer()
{
}
