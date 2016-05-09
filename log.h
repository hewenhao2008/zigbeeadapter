#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG_LEN_MAX	128
int Debug_Log_Print(const char * format, ...);
int Error_Log_Print(const char * format, ...);

#define PrintDebugLog Debug_Log_Print
#define PrintErrorLog Error_Log_Print


int log_time_print(void);
#define ZIGBEE_TRACE	printf
#define ZIGBEE_DEBUG(msg)\
	do{\
		ZIGBEE_TRACE("[DEBUG]: ");\
		log_time_print();\
		ZIGBEE_TRACE (msg);\
		ZIGBEE_TRACE("[%s] %s:%d \n", __FUNCTION__, __FILE__,__LINE__);\
	}while(0)

#define ZIGBEE_ERROR(err)\
		do{\
			ZIGBEE_TRACE("\033[1;40;31m");\
			ZIGBEE_TRACE("[ERROR]: ");\
			log_time_print();\
			ZIGBEE_TRACE (err);\
			ZIGBEE_TRACE("[%s] %s:%d \033[0m \n",__FUNCTION__, __FILE__,__LINE__);\
		}while(0)


#ifdef __cplusplus
}
#endif

#endif

