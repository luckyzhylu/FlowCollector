#ifndef _VITO_LOG_H_
#define _VITO_LOG_H_

#include <stdio.h>
#include <zlog.h>
#include <pthread.h>
#include <stdlib.h>

extern int32_t vito_log_flag;
extern zlog_category_t *vito_log_zc;

int32_t initmsg(const char *conffile, const char *category);

void uninitmsg(void);

void set_vito_log_flag(int32_t flag);

int32_t get_vito_log_flag();

int32_t load_vito_log_flag(const char *confpath);

#define vito_log_put_zone(key, value) do { \
	zlog_put_mdc(key, value); \
}while(0)

#define vito_log_reload(confpath) do { \
	zlog_reload(confpath); \
}while(0)

#define fatallog(fmt , args...) do { \
	if(vito_log_zc != NULL)	zlog_fatal(vito_log_zc, fmt, ## args); \
} while (0)

#define errorlog(fmt , args...) do { \
       	if(vito_log_flag > 0 && vito_log_zc != NULL)	zlog_error(vito_log_zc, fmt, ## args); \
} while (0)

#define warnlog(fmt , args...) do { \
        if(vito_log_flag > 0 && vito_log_zc != NULL)	zlog_warn(vito_log_zc, fmt, ## args); \
} while (0)

#define noticelog(fmt , args...) do { \
        if(vito_log_flag > 0 && vito_log_zc != NULL)	zlog_notice(vito_log_zc, fmt, ## args); \
} while (0)

#define infolog(fmt , args...) do { \
        if(vito_log_flag > 0 && vito_log_zc != NULL)	zlog_info(vito_log_zc, fmt, ## args); \
} while (0)

#define debuglog(fmt , args...) do { \
       	if(vito_log_flag > 0 && vito_log_zc != NULL)	zlog_debug(vito_log_zc, fmt, ## args); \
}while (0)


#endif /* _VITO_LOG_H_ */
