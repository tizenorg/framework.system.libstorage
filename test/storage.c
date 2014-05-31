#include <stdio.h>
#include <storage.h>

/**
 * Test program for libstorage
 */

#define _D(fmt, argc...)	printf(fmt"\n", ##argc)
#define _E(fmt, argc...)	printf("[ERR] "fmt"\n", ##argc)

int main(int argc, char *agrv[])
{
	struct statvfs s;
	int r;

#ifdef _FILE_OFFSET_BITS == 64
	r = storage_get_internal_memory_size64(&s);
#else
	r = storage_get_internal_memory_size(&s);
#endif
	if (r < 0)
		_E("ret : %d", r);

	return r;
}
