#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "register.h"
#include "stty.h"
#include "log.h"


static ZIGBEE_STTY_REG g_stZigbeeSttyReg;

void *uart_recv(void *arg)
{
	int len=0, ret = 0;
	char szData[BUFF_SIZE] = {0};
	fd_set fs_read;
	struct timeval tv_timeout;
	
	FD_ZERO(&fs_read);
	FD_SET(g_stZigbeeSttyReg.fd, &fs_read);
	tv_timeout.tv_sec  = (10*20/g_stZigbeeSttyReg.braud_rate+2);
	tv_timeout.tv_usec = 0;
	
	ret = select(g_stZigbeeSttyReg.fd+1, &fs_read, NULL, NULL, &tv_timeout);
	ZIGBEE_DEBUG(("ret = %d\n", ret));	
		
	if(FD_ISSET(g_stZigbeeSttyReg.fd, &fs_read)) 
	{
		while(1)
		{
			len = read(g_stZigbeeSttyReg.fd, szData, BUFF_SIZE);
			if (len > 0)
			{
				ZIGBEE_DEBUG(("%s recv:%s", STTY_DEV, szData));
				ZIGBEE_DEBUG(("recv len = %d\n", len));
				memset(szData, 0, sizeof(szData));
				len = 0;
			}
			else
			{
				sleep(10);
			}
		}
	}
	else
	{
		ZIGBEE_ERROR(("uart recv error!"));
	}
	return NULL;
}

int uart_send(int fd, char *pSrcData, unsigned int uiSrcLen)
{
	if (NULL == pSrcData || (int)uiSrcLen <= 0)
	{
		ZIGBEE_ERROR(("uart send Src Data error!"));
		return -1;
	}

	int len = 0;
	len = write(fd, pSrcData, uiSrcLen);
	if(len == uiSrcLen) 
	{
		return len;
	}
	else 
	{
		tcflush(fd, TCOFLUSH);
		return -1;
	}
}

void zigbee_stty_reg_init()
{
	g_stZigbeeSttyReg.reg_id = REG_STTY;
	g_stZigbeeSttyReg.fd = -1;
	memset(&g_stZigbeeSttyReg.options, 0, sizeof(g_stZigbeeSttyReg.options));
	g_stZigbeeSttyReg.fnrecv = uart_recv;
	g_stZigbeeSttyReg.fnsend = uart_send;

	zigbee_stty_init(STTY_DEV);
	{
		
		pthread_t ThreadHandleStty;
		int iRet = pthread_create(&ThreadHandleStty,NULL,uart_recv,NULL);
		if (iRet)
		{
			ZIGBEE_ERROR(("stty uart recv create thread error!"));
			return ;
		}
	}
	ZIGBEE_DEBUG(("stty register OK!"));
}

int zigbee_stty_init(const char *pSttyDev)
{
	if (NULL == pSttyDev)
	{
		ZIGBEE_ERROR(("pSttyDev is NULL!"));
		return -1;
	}

	int stty_fd, n;
	char buffer[BUFF_SIZE] = {0};
	struct termios *pOpt = &g_stZigbeeSttyReg.options;

	/*open*/
	stty_fd = open(pSttyDev, O_RDWR);
	if (-1 == stty_fd)
	{
		ZIGBEE_ERROR(("stty open failed!"));
		return -1;
	}

	ZIGBEE_DEBUG(("%s open success, waiting input...", pSttyDev));

	/*get original options*/
	tcgetattr(stty_fd, pOpt);
	tcflush(stty_fd, TCIOFLUSH);

	/*set options*/
	/*boud rate*/
	cfsetispeed(pOpt, B19200);
	cfsetospeed(pOpt, B19200);
	g_stZigbeeSttyReg.braud_rate = 19200;

	/*data bit*/
	pOpt->c_cflag &= ~CSIZE;
	pOpt->c_iflag |= CS8;

	/*parity bit*/
	pOpt->c_cflag &= ~PARENB;
	pOpt->c_iflag &- ~INPCK;

	/*stop bit*/
	pOpt->c_cflag &= ~CSTOPB;

	/*delay time*/
	pOpt->c_cc[VTIME] = 150;
	pOpt->c_cc[VMIN] = 0;

	if (0 != tcsetattr(stty_fd, TCSANOW, pOpt))
	{
		ZIGBEE_ERROR(("set stty option error!"));
		return -1;
	}

	tcflush(stty_fd, TCIOFLUSH);
	return 0;
}

