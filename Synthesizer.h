#include "Floppy.h"

class Synthesizer: public Floppy
{
private:
	int direction;	
public:
	Synthesizer(std::string device);
	void play(double frequence, double duration);
	~Synthesizer();
};
