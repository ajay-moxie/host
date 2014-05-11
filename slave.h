#ifndef __SLAVE__
#define __SLAVE__
#define MAX_NO_SLAVE 64
struct slave{
	uint8_t address;
	uint8_t search_h;
	uint8_t search_m;
	uint8_t search_l;
};
void set_slave_count(uint8_t count);
uint8_t get_slave_count();
#endif
