#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    
#include <termios.h>
#include <unistd.h>
#include "stty.h"
#include "log.h"

int zigbee_stty_init(const char *pSttyDev)
{
	if (NULL == pSttyDev)
	{
		ZIGBEE_ERROR(("pSttyDev is NULL!"));
		return -1;
	}

	int stty_fd, n;
	char buffer[BUFF_SIZE] = {0};
	struct termios opt = {0};

	/*?򿪴???*/
	stty_fd = open(pSttyDev, O_RDWR);
	if (-1 == stty_fd)
	{
		ZIGBEE_ERROR(("stty open failed!"));
		return -1;
	}

	ZIGBEE_DEBUG(("%s open success, waiting input...", pSttyDev));

	/*??ȡ??ǰ???ڲ???*/
	tcgetattr(stty_fd, &opt);
	tcflush(stty_fd, TCIOFLUSH);

	/*???ô??ڴ???????*/
	/*??????*/
	cfsetispeed(&opt, B19200);
	cfsetospeed(&opt, B19200);

	/*????λ*/
	opt.c_cflag &= ~CSIZE;
	opt.c_iflag |= CS8;

	/*??żλ*/
	opt.c_cflag &= ~PARENB;
	opt.c_iflag &- ~INPCK;

	/*ֹͣλ*/
	opt.c_cflag &= ~CSTOPB;

	/*???ó?ʱ*/
	opt.c_cc[VTIME] = 150;
	opt.c_cc[VMIN] = 0;

	if (0 != tcsetattr(stty_fd, TCSANOW, &opt))
	{
		ZIGBEE_ERROR(("set stty option error!"));
		return -1;
	}

	tcflush(stty_fd, TCIOFLUSH);
	

	return 0;
}
