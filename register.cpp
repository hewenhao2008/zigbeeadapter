#include <stdio.h>
#include "register.h"
#include "stty.h"
#include "log.h"

static void (*g_reg_events[REG_MAX])() = 
{
	zigbee_stty_reg_init,
};
void zigbee_register_init()
{
	int reg_index = 0;

	for (reg_index = 0; reg_index < REG_MAX; reg_index++)
	{
		g_reg_events[reg_index]();
	}
}
