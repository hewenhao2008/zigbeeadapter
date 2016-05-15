#ifndef __STTY_H_
#define __STTY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <termios.h>

//#define DEVICE_NAME_LEN_MAX		16
#define STTY_DEV 				"/dev/ttyS0"
#define BUFF_SIZE				512

typedef struct _tagZIGBEE_STTY_REG
{
	int reg_id;
	int fd;
	int braud_rate;
//	char szDeviceName[DEVICE_NAME_LEN_MAX];
	struct termios options;

//	int (*fnprev)(char *pDeviceName);
	void * (*fnrecv)(void *arg);
	int (*fnsend)(int fd, char *szData, unsigned int uiDataLen);
	
}ZIGBEE_STTY_REG;

void zigbee_stty_reg_init();
int zigbee_stty_init(const char *pSttyDev);
void * uart_recv(void *arg);
int uart_send(int fd, char *pData, unsigned int uiDataLen);

#ifdef __cplusplus
}
#endif

#endif
