#include "request.h"
#include "common.h"
#include "log.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <curl/curl.h>

#define TIME_SLOT (5 * 60) //s

int getlocalip(char *ipbuffer, unsigned int len);
void dumpinfo(domain_info_t *info);
int main()
{
	
    domain_info_t domain_info = 
    {
        /*.domain_id = */       0,
        /*.record_id = */       0,
        /*.record_type = */       "A",
        /*.record_id = */       "默认",
        /*.record = */          "",
        /*.domain_name = */     "yourdomain.com",
        /*.username = */        "yourusername",
        /*.password = */        "yourpasswd",
        /*.sub_domain_name = */ "yoursubdomain"
    };

    char strip[16] = "";
    
	if(NULL == (log_stream = raspddns_init_log("raspddns.log")))
	{
		printf("init log failed!");
		return -1;
	}
	
	raspddns_append_log("raspddns start!");
	
    if( init_info(&domain_info) )
    {
		raspddns_append_log("init domain info failed!");
        printf("init domain info failed!\n");
    }
    
    printf( "get info success! begin daemon\n" );
    
    daemon(1, 0);
    
    while(1)
    {
        if ( getlocalip(strip, 16) || strcmp(strip, domain_info.record ) == 0 )
        {
            raspddns_append_log("记录没改变！");
            sleep(TIME_SLOT);
            continue;
        }
    
        if( update_record(&domain_info) )
        {
            if ( init_info(&domain_info) == 0 && update_record(&domain_info) == 0)
            {
                strncpy(domain_info.record, strip, 16);
                domain_info.record[15] = '\0';
                sleep(TIME_SLOT);
                continue;
            }
            raspddns_append_log("update domain record failed!\n");
            break;
        }

        strncpy(domain_info.record, strip, 16);
        domain_info.record[15] = '\0';
        sleep(TIME_SLOT);
    }

    dumpinfo( &domain_info );
    return 0;
}



void dumpinfo(domain_info_t *info)
{
    if( !info )
    {
        return;
    }
    
    printf("domain_name=%s, domain_id=%d, record_name=%s, record_id=%d, record=%s\n"
    , info->domain_name, info->domain_id, info->sub_domain_name, info->record_id, info->record);
}

