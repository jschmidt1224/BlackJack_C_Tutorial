#include <utf8.h>
#include <stdio.h>

int toUtf8(int val, char *buf)
{
	if (!(val & ~0x7F)) {
		buf[0] = (char) val;
		buf[1] = '\0';
		//printf("%04X: ASCII char %s\n", val, buf);
		return 1;
	} else if (!(val & ~0x7FF)) {
		buf[2] = '\0';
		buf[1] = 0x80 | (0x3F & val);
		buf[0] = 0xC0 | ((0x7C0 & val) >> 6);
		//printf("%04X: UTF8 char %s\n", val, buf);
		return 2;
	} else if (!(val & ~0xFFFF)) {
		buf[3] = '\0';
		buf[2] = 0x80 | (0x3F & val);
		buf[1] = 0x80 | ((0xFC0 & val) >> 6);
		buf[0] = 0xE0 | ((0xF000 &val) >> 12);
		//printf("%04X: UTF8 char %s\n", val, buf);
		return 3;
	} else {
		return -1;
	}
}