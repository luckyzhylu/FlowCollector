#include <stdio.h>
#include <zlog.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "vito_log.h"

#define LOG_CONF  "/vca_dt/conf/log.conf"

int32_t vito_log_flag = 0;
zlog_category_t *vito_log_zc = NULL;

void set_vito_log_flag(int32_t flag)
{
	vito_log_flag = flag == 0 ? 0 : 1;
}

int32_t get_vito_log_flag()
{
	return vito_log_flag;
}

int32_t load_vito_log_flag(const char *confpath)
{
	FILE *fd;
	char buf[32];
	int32_t ret = 0;

	fd = fopen(confpath,"r");
	if(fd == NULL) {
		printf("open file %s error",confpath);
		return -1;
	}
	if(NULL == fgets(buf,sizeof(buf),fd)){
		printf("fgets error");
		ret = -1;
		goto out;
	};
	if(strstr(buf,"#vito_log_flag=1")){
		vito_log_flag = 1;
	}else{
		vito_log_flag = 0;
	}

out:
	fclose(fd);
	return ret;
}

int initmsg(const char *conffile, const char *category)
{
	int vito_log_rc;

	vito_log_rc = zlog_init(conffile);

	if(vito_log_rc){
		printf("init failed log configfile : %s\n", conffile);
		zlog_fini();
		return -1;
	}

	vito_log_zc = zlog_get_category(category);
	if(!vito_log_zc){
		printf("get category fial\n");
		return -2;
	}

	load_vito_log_flag(conffile);

	fatallog("vito log init success (%s, %s)",conffile,category);
	return 0;
}

void uninitmsg(void)
{
	zlog_fini();
}
