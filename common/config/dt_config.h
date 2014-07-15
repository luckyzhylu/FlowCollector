#ifndef _J_CONFIG_H
#define _J_CONFIG_H
#include <sys/types.h>
#include <stdio.h>
#include "libxml2_derive.h"

#define CFG_TYPE_LONG	1
#define CFG_TYPE_ULONG	2
#define CFG_TYPE_STR	3
#define CFG_TYPE_YN	4
#define CFG_TYPE_USHORT 5

#define MAX_VAR_NAME_LENGTH	1024
#define MAX_VAR_VALUE_LENGTH	1024

/* used to convert xml string value to internal data type */
typedef struct config_description {
	char key_name[MAX_VAR_NAME_LENGTH];	/* xml node path */
	void *addr;	/* where to store the parsed value */
	unsigned int	maxlen;		/* addr length */
	unsigned char type;		/* addr data type */
	unsigned char compulsive;
	unsigned char valid;
	char initial_value[MAX_VAR_VALUE_LENGTH];
} cfg_desc;

int cfg_fill(xmlDocPtr doc, cfg_desc *desc_table);
int cfg_init_value(cfg_desc *desc_table);
int common_read_conf(char *filename, cfg_desc *desc);
void cfg_print(cfg_desc *desc_table);

#endif // _J_CONFIG_H
