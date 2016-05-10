#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

int Debug_Log_Print(const char * format, ...)
{	
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
    char szBuf[LOG_LEN_MAX] = {0};
	int len = sprintf(szBuf,"[%04d-%02d-%02d %02d:%02d:%02d] ",
		tmp->tm_year+1900,tmp->tm_mon+1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);

	va_list list;
	va_start(list, format);
	len += vsprintf(szBuf+len, format, list);
	len += sprintf(szBuf+len, "\n");
	if (len < LOG_LEN_MAX)
	{
		;
	}
	else
	{
		szBuf[LOG_LEN_MAX-1] = '\0';
	}
	fprintf(stdout, szBuf);
	fflush(stdout);
<<<<<<< HEAD
	va_end(list);	
	return 0;
}

int Error_Log_Print(const char * format, ...)
{	
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
    char szBuf[3072] = {0};
	int len = sprintf(szBuf,"\033[1;40;31m[%04d-%02d-%02d %02d:%02d:%02d] ",
		tmp->tm_year+1900,tmp->tm_mon+1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);

	va_list list;
	va_start(list, format);
	len += vsprintf(szBuf+len, format, list);
	len += sprintf(szBuf+len, "\033[0m \n");
	if (len < LOG_LEN_MAX)
	{
		;
	}
	else
	{
		szBuf[LOG_LEN_MAX-1] = '\0';
	}
	fprintf(stdout, szBuf);
	fflush(stdout);
=======
>>>>>>> f939615f2616874b0f94d80d5f44d1db7c56297e
	va_end(list);	
	return 0;
}

int log_time_print(void)
{
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);

	ZIGBEE_TRACE ("[%04d-%02d-%02d %02d:%02d:%02d] ", 
		tmp->tm_year+1900,tmp->tm_mon+1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	
	return 0;
}


