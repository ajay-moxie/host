#include "typedef.h"
#include "slave.h"
static uint8_t slave_count = 0;
static struct slave slaves[MAX_NO_SLAVE];

void set_slave_count(uint8_t count)
{
	slave_count = count;
}


uint8_t get_slave_count()
{
	return slave_count;
}
