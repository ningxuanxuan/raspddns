#ifndef _REQUEST_H_
#define _REQUEST_H_ 1
#include "common.h"
#include <curl/curl.h>

int parseresult(const char *src, int length, result_t *result);
int getdomainid(domain_info_t *info);
int getrecordid(domain_info_t *info);
int setcommonparam(struct curl_httppost **formpost, struct curl_httppost **lastptr, const domain_info_t *info);
int init_info(domain_info_t *info);
int update_record(domain_info_t *info);

#endif //_REQUEST_H_
