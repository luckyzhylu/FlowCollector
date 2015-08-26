#ifndef _BASE64_H
#define _BASE64_H

#include <ctype.h>
#include <sys/types.h>

class CBase64Encrypt {
public:
	static int Encode(char const *src, size_t srclength, char *target, size_t targsize);
	static int Decode(char const *src, char * target, size_t targsize);
};

#endif
