#ifndef _RASPDDNS_LOG_H_
#define _RASPDDNS_LOG_H_	1
#include <stdio.h>
#include <time.h>
#define MAX_LOGFILE_LEN (3 * 1024 * 1024)

FILE *raspddns_init_log(const char *file);
int raspddns_append_log(FILE *p, const char *content);
void raspddns_close_log(FILE *file);

int _bkp_logfile(const char *file);
char * _get_current_date_string(char *dst, unsigned int len);
struct tm * _getlocaltime(tm *_tm);

#endif