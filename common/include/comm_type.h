#ifndef _COMM_TYPE_H
#define _COMM_TYPE_H


#if 0


#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#endif

//typedef u_int8_t bool;

#ifndef __int8_t_defined
#define __int8_t_defined


typedef char int8_t;
//typedef unsigned char u_int8_t;

typedef short int int16_t;
//typedef unsigned short int u_int16_t;

typedef int int32_t;
//typedef unsigned int u_int32_t;

typedef long long int int64_t;
//typedef unsigned long long int u_int64_t;
#endif


typedef int64_t ptr_len;
#include <sys/types.h>
typedef u_int64_t session_id_t;



#endif	/*_COMM_TYPE_H*/
