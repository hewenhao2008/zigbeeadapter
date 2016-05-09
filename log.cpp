#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

int Log_Print(const char * format, ...)
{	
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
    char szBuf[3072] = {0};
	int len = sprintf(szBuf,"[%04d-%02d-%02d %02d:%02d:%02d] ",
		tmp->tm_year+1900,tmp->tm_mon+1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);

	va_list list;
	va_start(list, format);
	vsprintf(szBuf+len, format, list);
	fprintf(stdout, szBuf);
	fflush(stdout);
	va_end(list);	
	return 0;
}


