/*
 * Feed a file through ytalk's VT100 emulation as if a peer had sent it.
 * usage: vt100_driver FILE
 */
#include <fcntl.h>
#include "header.h"

int
main(int argc, char **argv)
{
	static yuser u;
	static unsigned char buf[65536];
	size_t i, n;
	FILE *f;

	if (argc < 2 || (f = fopen(argv[1], "rb")) == NULL)
		return 2;
	n = fread(buf, 1, sizeof(buf), f);
	fclose(f);
	memset(&u, 0, sizeof(u));
	u.fd = open("/dev/null", O_RDWR);
	resize_win(&u, 24, 80);
	for (i = 0; i < n; i++)
		vt100_process(&u, buf[i]);
	return 0;
}
