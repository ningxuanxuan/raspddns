#include "request.h"
#include "common.h"
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
    
    if( init_info(&domain_info) )
    {
        printf("init domain info failed!\n");
    }
    
    printf( "get info success! begin daemon\n" );
    
    daemon(1, 0);
    
    while(1)
    {
        if ( getlocalip(strip, 16) || strcmp(strip, domain_info.record ) == 0 )
        {
            printf("记录没改变！\n");
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
            printf("update domain record failed!\n");
            break;
        }

        strncpy(domain_info.record, strip, 16);
        domain_info.record[15] = '\0';
        sleep(TIME_SLOT);
    }

    dumpinfo( &domain_info );
    return 0;
}

int getlocalip(char *ipbuffer, unsigned int len)
{
    struct sockaddr_in serv_addr;

    int sockfd = -1;
    struct hostent *host = NULL;
    unsigned short int serv_port=6666;

    char recv_buf[100] = {'\0'};

    if ( !ipbuffer )
    {
        return -1;
    }
    
    //get ip addr
    if( (host = gethostbyname("ns1.dnspod.net")) == NULL)
    {
        perror("get host ip error ");
        return -1;
    }
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);

    serv_addr.sin_port = htons(serv_port);

    memset(&(serv_addr.sin_zero),0,8);

    if((sockfd=socket(PF_INET,SOCK_STREAM,0))==-1)

    {

        perror("建立socket失败");

        return -1;

    }

    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))==-1)

    {

        //perror(“connect failed!”);

        return -1;

    }

    recv(sockfd,recv_buf,16,0);

    close(sockfd);

    strncpy(ipbuffer, recv_buf, len);
    ipbuffer[len - 1] = '\0';
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

