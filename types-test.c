#include<stdio.h>
#include "typedef.h"
main()
{
	printf("\nhello world");
	printf("\nuint8_t %d", sizeof(uint8_t) * 8);
	printf("\nint8_t %d", sizeof(int8_t) * 8);
	printf("\nuint16_t %d", sizeof(uint16_t) * 8);
	printf("\nint16_t %d", sizeof(int16_t) * 8);
	printf("\nuint32_t %d", sizeof(uint32_t) * 8);
	printf("\nint32_t %d", sizeof(int32_t) * 8);
	printf("\nint %d", sizeof(int) * 8);
}
