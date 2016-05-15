#ifndef __STTY_H_
#define __STTY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define STTY_DEV 		"/dev/ttyS0"
#define BUFF_SIZE		512
int zigbee_stty_init(const char *pSttyDev);

#ifdef __cplusplus
}
#endif

#endif
