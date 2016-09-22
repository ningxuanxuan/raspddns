#ifndef _RASPDDNS_CONFIG_H_
#define _RASPDDNS_CONFIG_H_    1

typedef struct raspddns_config
{
	char username[255];
	char passwd[255];
	char domain[255];
	char sub_domain[255];
	int  delay;
}raspddns_config_t;

int parseconfig(raspddns_config_t *config);
#endif