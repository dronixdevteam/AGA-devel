/*
 * Functions for \oct encoding used in mtab/fstab/swaps/etc.
 *
 * Based on code from mount(8).
 *
 * Copyright (C) 2010 Karel Zak <kzak@redhat.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mangle.h"

#define isoctal(a) (((a) & ~7) == '0')

static unsigned char need_escaping[] = { ' ', '\t', '\n', '\\' };

char *mangle(const char *s)
{
	char *ss, *sp;
	int n;

	n = strlen(s);
	ss = sp = malloc(4*n+1);
	if (!sp)
		return NULL;
	while(1) {
		for (n = 0; n < sizeof(need_escaping); n++) {
			if (*s == need_escaping[n]) {
				*sp++ = '\\';
				*sp++ = '0' + ((*s & 0300) >> 6);
				*sp++ = '0' + ((*s & 070) >> 3);
				*sp++ = '0' + (*s & 07);
				goto next;
			}
		}
		*sp++ = *s;
		if (*s == 0)
			break;
	next:
		s++;
	}
	return ss;
}

void unmangle_to_buffer(char *s, char *buf, size_t len)
{
	size_t sz = 0;

	while(*s && sz < len - 1) {
		if (*s == '\\' && sz + 4 < len - 1 && isoctal(s[1]) &&
		    isoctal(s[2]) && isoctal(s[3])) {

			*buf++ = 64*(s[1] & 7) + 8*(s[2] & 7) + (s[3] & 7);
			s += 4;
			sz += 4;
		} else {
			*buf++ = *s++;
			sz++;
		}
	}
	*buf = '\0';
}

static inline char *skip_nonspaces(char *s)
{
	while (*s && !(*s == ' ' || *s == '\t'))
		s++;
	return s;
}

/*
 * Returns mallocated buffer or NULL in case of error.
 */
char *unmangle(char *s)
{
	char *buf, *end;
	size_t sz;

	end = skip_nonspaces(s);
	sz = end - s + 1;

	buf = malloc(sz);
	if (!buf)
		return NULL;

	unmangle_to_buffer(s, buf, sz);
	return buf;
}

#ifdef TEST_PROGRAM
#include <err.h>
#include <errno.h>
int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "usage: %s --mangle | --unmangle <string>\n",
						program_invocation_short_name);
		return EXIT_FAILURE;
	}

	if (!strcmp(argv[1], "--mangle"))
		printf("mangled: '%s'\n", mangle(argv[2]));

	else if (!strcmp(argv[1], "--unmangle")) {
		char *x = unmangle(argv[2]);
		if (x)
			printf("unmangled: '%s'\n", x);
		else
			err(EXIT_FAILURE, "unmangle failed");
	}

	return EXIT_SUCCESS;
}
#endif /* TEST_PROGRAM */
