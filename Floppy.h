#include <string>

class Floppy
{
private:
	int fd;
public:
	int track;
	Floppy(std::string device);
	void seek(int track);
	void speed(int srt);
	~Floppy();
};
