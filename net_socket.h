#ifndef __NET_SOCKET_
#define __NET_SOCKET_

#ifdef __cplusplus
extern "C"
{
#endif

#include <event.h>

int zigbee_net_server_Init();
void on_accept(int sock, short event, void* arg);

#ifdef __cplusplus
}
#endif

#endif
