#ifndef __WIFI_WINDOWS_H__
#define __WIFI_WINDOWS_H__
int open_wifi(char *addr, uint32_t port);
int write_wifi(char *buff, int size);
int read_wifi(char *buff, int size);
#endif
