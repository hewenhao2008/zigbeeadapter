#include <stdio.h>
#include <stdarg.h>
#include "log.h"

int Log_Print(const char * format, ...)
{
	va_list list;
	va_start(list, format);
	vprintf(format, list);
	fflush(stdout);
	va_end(list);	
	return 0;
}


