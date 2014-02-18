#include <string>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fd.h>

#include "Floppy.h"

Floppy::Floppy(std::string device)
{
	fd = open(device.c_str(), O_ACCMODE);
	if(fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void Floppy::seek(int tr)
{
	struct floppy_raw_cmd command = {0};
	command.flags = FD_RAW_NEED_SEEK;
	command.track = tr;
	if(ioctl(fd, FDRAWCMD, &command))
	{
		perror("seek");
		printf("error code: %d\n", command.resultcode);
		exit(EXIT_FAILURE);
	}
	track = tr;
}

void Floppy::speed(int srt)
{
	struct floppy_drive_params params = {0};
	if(ioctl(fd, FDGETDRVPRM, &params))
	{
		perror("getparams");
		exit(EXIT_FAILURE);
	}
	params.srt = srt;
	if(ioctl(fd, FDSETDRVPRM, &params))
	{
		perror("getparams");
		exit(EXIT_FAILURE);
	}
}

Floppy::~Floppy()
{
	close(fd);
}
