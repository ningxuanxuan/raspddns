#include "log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

FILE *raspddns_init_log(const char *file)
{
	struct stat fileinfo = {0};
	if( !file )
	{
		return NULL;
	}
	
	if ( 0 == stat(file, &fileinfo) && fileinfo.st_size > MAX_LOGFILE_LEN && 0 != _bkp_logfile(file))
	{
		printf("stat and move failed");
		return NULL;
	}
	
	FILE *p = fopen(file, "a");
	
	return p;
}

int raspddns_append_log(FILE *p, const char *content)
{
	char buffer[] = "yyyy-mm-dd hh:ii:ss";
	if(!p || !content)
	{
		return -1;
	}
	
	if(NULL == _get_current_date_string(buffer, sizeof(buffer)))
	{
		strcpy(buffer, "0000-00-00 00:00:00");
	}
	buffer[sizeof(buffer)] = '\0';
	pthread_mutex_lock(&log_mutex);
	fwrite(buffer, 1, strlen(buffer), p);
	fwrite("\t", 1, 1, p);
	fwrite(content, 1, strlen(content), p);
	fwrite("\n", 1, 1, p);
	pthread_mutex_unlock(&log_mutex);
	return 0;
}

void raspddns_close_log(FILE *file)
{
	if(file)
	{
		fclose(file);
	}
}

int _bkp_logfile(const char *file)
{
	char *buffer = NULL;
	int ret = 0;
	if(!file || 0 != access(file, F_OK))
	{
		return -1;
	}
	
	buffer = (char *)malloc(strlen(file) + strlen(".yyyy-mm-dd HH:ii:ss") + sizeof(char));
	
	if(buffer == NULL)
	{
		return -1;
	}
	
	sprintf(buffer, "%s.", file);
	
	if(NULL == _get_current_date_string(buffer + strlen(file) + strlen("."), strlen("yyyy-mm-dd HH:ii:ss") + 1))
	{
		strcpy(buffer + strlen(file) + strlen("."), "0000-00-00 00:00:00");
	}
	ret = rename(file, buffer);
	
	free(buffer);
	return ret;
}

char * _get_current_date_string(char *dst, unsigned int len)
{
	tm nowtm = {0};
	if(!dst || len < strlen("yyyy-mm-dd HH:ii:ss") + 1 || NULL == _getlocaltime(&nowtm))
	{
		return NULL;
	}
	
	sprintf(dst,"%04d-%02d-%02d %02d:%02d:%02d", nowtm.tm_year + 1900, nowtm.tm_mon + 1,
	nowtm.tm_mday, nowtm.tm_hour, nowtm.tm_min, nowtm.tm_sec);
	
	return dst;
}

tm * _getlocaltime(tm *_tm)
{
	time_t nowtm = 0;
	tm *tmp = NULL;
	if(!_tm || time(&nowtm) == -1)
	{
		return NULL;
	}
	
	if( NULL == (tmp = localtime(&nowtm)) )
	{
		return NULL;
	}
	
	memcpy(_tm, tmp, sizeof(struct tm));
	
	return _tm;
}