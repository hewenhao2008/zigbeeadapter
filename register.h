#ifndef __REGISTER_H_
#define __REGISTER_H_

#ifdef _cplusplus
extern "C"
{
#endif

enum 
{
	REG_STTY = 0,
	REG_MAX
};

void zigbee_register_init();

#ifdef _cplusplus
}
#endif

#endif
