#include <math.h>

#include "Synthesizer.h"
#include "Timer.h"

// Just some temporary foo stuff

double NTF(int note)
{
	return 440.0 * pow(2.0, note / 12.0);
}

int main()
{
	Synthesizer *s = new Synthesizer("/dev/fd0");
	Timer t;
	t.sleep(1, 0);
	char *q = "AAHHJJH  FFEECCA  GGFFEEC  GGFFEEC  AAHHJJH  FFEECCA";
	for(int i = 0; q[i]; i++)
	{
		if(q[i] != ' ')
			s->play(NTF(q[i] - 95), 0.4);
		t.sleep(0, 300000000);
	}
	delete s;
}
