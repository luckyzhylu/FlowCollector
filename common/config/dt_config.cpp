#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dt_config.h"

void cfg_print_desc(cfg_desc *desc)
{
	if (!desc)
		goto err;

	printf("CFG_DESC: key_name(%s), maxlen(%u), type(%u), compulsive(%u), valid(%u), initial_value(%s)\n", 
			desc->key_name, desc->maxlen, desc->type, desc->compulsive, desc->valid, desc->initial_value);
err:
	return;
}

/* parse @val_str to @addr */
int cfg_conv_value(char *val_str, void *addr, unsigned int maxlen, unsigned char type)
{
	if (!val_str  || !addr || !maxlen)
		return -1;

	if (!strlen(val_str))
		return 0;

	switch (type) {
	case CFG_TYPE_STR:
		strncpy((char *)addr, val_str, maxlen);
		break;

	case CFG_TYPE_LONG:
		if (maxlen < sizeof(int))
			return -1;
		*(int *)addr = strtol((const char *)val_str, NULL, 0);
		break;

	case CFG_TYPE_ULONG:
		if (maxlen < sizeof(unsigned int))
			return -1;
		*(unsigned int*)(addr) = strtoul((const char*)val_str, NULL, 0);
		break;

	case CFG_TYPE_YN:
		if (!strcasecmp(val_str, "yes"))
			*(char *)addr = 1;
		else if (!strcasecmp(val_str, "no"))
			*(char *)addr = 0;
		else
			return -1;

		break;
	case CFG_TYPE_USHORT:
		if (maxlen < sizeof(u_int16_t)) 
			return -1;
		*(u_int16_t *)(addr) = atoi((const char*)val_str);
		break;

	default:
		return -1;
	}

	return 0;
}

//
// cfg_init_value
//
int cfg_init_value(cfg_desc *desc_table)
{
	int nret = 0;
	int dt_index = 0;

	if (!desc_table)
		goto err;

	while (1) {
		if (desc_table[dt_index].key_name[0] == 0)
			break;

		if (cfg_conv_value(desc_table[dt_index].initial_value, desc_table[dt_index].addr, \
				desc_table[dt_index].maxlen, desc_table[dt_index].type) < 0) {
#ifdef DEBUG
			fprintf(stderr, "Error: cfg_init_value: convert value error\n");
			cfg_print_desc(desc_table + dt_index);
#endif
		}

		dt_index++;
	}

	return nret;
err:
	return -1;
}

/* parse @doc to @desc_table */ 
int cfg_fill(xmlDocPtr doc, cfg_desc *desc_table)
{
	int dt_index = 0;
	char buf[1024] = {0};


	if (!doc || !desc_table)
		return -1;

	while (1) {
		/* indicates the end of parse */
		if (!(desc_table[dt_index].key_name)[0]\
				|| !desc_table[dt_index].addr\
				|| desc_table[dt_index].maxlen == 0) {
			return 0;
		}
		
		memset(buf, 0, sizeof(buf));
		
		if (xml_get_value_by_path_key(doc, desc_table[dt_index].key_name, buf, sizeof(buf)) < 0){
			desc_table[dt_index].valid = 0;
			
			if (desc_table[dt_index].compulsive) {
#ifdef DEBUG
				fprintf(stderr, "Error: not found config (%s)\n", desc_table[dt_index].key_name);
#endif
				return -1;
			}
		}
		else{
			/* parse @buf,store the value to @addr */
			if (cfg_conv_value(buf, desc_table[dt_index].addr, desc_table[dt_index].maxlen, desc_table[dt_index].type) < 0) {
				desc_table[dt_index].valid = 0;

				if (desc_table[dt_index].compulsive) {
#ifdef DEBUG
					fprintf(stderr, "Error: cfg_fill: 'compulsive' cfg_desc haven't been right\n");
					cfg_print_desc(desc_table + dt_index);
#endif
					return -1;
				} 
#ifdef DEBUG
				else {

					fprintf(stderr, "Error: cfg_fill: convert value error\n");
					cfg_print_desc(desc_table + dt_index);
				}
#endif
			}
			else
				desc_table[dt_index].valid = 1;
		}

		dt_index++;
	}

	return 0;
}

/* print watchdog config */
void cfg_print(cfg_desc *desc_table)
{
	int index = 0;

	printf("%16s\t%16s\t%5s\t%s\n", "TITLE", "KEYNAME", "VALID", "VALUE");
	while (1) {
		if ((desc_table[index].key_name)[0] == 0)
			break;

		switch (desc_table[index].type) {
		case CFG_TYPE_STR:
			printf("%16s\t%5d\t%s\n", 
					desc_table[index].key_name, desc_table[index].valid, 
					(char *) desc_table[index].addr);
			break;
		case CFG_TYPE_LONG:
			printf("%16s\t%5d\t%d\n", 
					desc_table[index].key_name, desc_table[index].valid, 
					*(int *)desc_table[index].addr);
			break;
		case CFG_TYPE_ULONG:
			printf("%16s\t%5d\t%u\n", 
					desc_table[index].key_name, desc_table[index].valid, 
					*(unsigned int *)desc_table[index].addr);
			break;
		case CFG_TYPE_YN:
			printf("%16s\t%5d\t%d\n", 
					desc_table[index].key_name, desc_table[index].valid, 
					*(char *) desc_table[index].addr);
			break;
		}

		index++;
	}

	return;
}

int common_read_conf(char *filename, cfg_desc *desc)
{
	xmlDocPtr doc = NULL;

	if (filename == NULL || desc == NULL){
		goto err;
	}
	if (xml_parse_file(filename, &doc) != 0){
		goto err;
	}

	if (cfg_fill(doc, desc) < 0) {
		fprintf(stderr, "Error: configuration error\n");
		goto err;
	}
	xml_free_doc(doc);
	return 0;
err:
	xml_free_doc(doc);
	return -1;
}

#ifdef TEST_CFE_FUNCTION
#define TEST_CONF_FILE	"./test.conf"
static char c_name[100];
static long c_index;
static char c_yorn;

cfg_desc test_desc_table[] = {
	{"Anonymous", "Name", c_name, sizeof(c_name), CFG_TYPE_STR, 1, 0, "Default value"},
	{"Title1", "Index", &c_index, sizeof(c_index), CFG_TYPE_LONG, 1, 0, "-1"},
	{"Title2", "YorN", &c_yorn, sizeof(c_yorn), CFG_TYPE_YN, 1, 0, "No"},
	{"", "", NULL, 0, 0, 0, 0, ""}

};

int main(int argc, char **argv)
{
	FILE *conf_file = NULL;
	rule_entry *elist = NULL;
	rule_entry *rep = NULL;
	int nread = 0;

	if (cfg_init_value(test_desc_table) < 0)
		goto err;

	printf("\nDEBUG: setting default value after cfg_init_value\n");
	cfg_print(test_desc_table);

	conf_file = open_rule_table(TEST_CONF_FILE);
	if (!conf_file)
		goto err;

	init_rule_entry_list(&elist);

	while (1) {
		rep = new_rule_entry();
		if (!rep)
			goto err;
		nread = read_rule_entry(conf_file, rep);
		if (nread <= 0)
			break;
		add_to_rule_entry_list(&elist, rep);
		rep = NULL;
	}
	if (nread < 0)
		goto err;

	if (cfg_fill(elist, test_desc_table) < 0)
		goto err;

	destroy_rule_entry_list(&elist);
	close_rule_table(conf_file);

	printf("\nDEBUG: setting default value after cfg_fill\n");
	cfg_print(test_desc_table);
	return 0;
err:
	fprintf(stderr, "Sth. error\n");
	return -1;
}
#endif
