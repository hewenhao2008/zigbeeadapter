#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

int Log_Print(const char * format, ...);

#define PrintDebugLog Log_Print
#define PrintErrorLog Log_Print

#ifdef __cplusplus
}
#endif

#endif

