#include <time.h>

class Timer
{
private:
	struct timespec t;
public:
	void start();
	long int nsec_elapsed();
	long int sec_elapsed();
	void sleep(long int sec, long int nsec);
};
