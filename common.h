#ifndef _COMMON_H_
#define _COMMON_H_ 1

typedef struct
{
    unsigned int domain_id;
    unsigned int record_id;
    char record_type[10];
    char line_type[10];
    char record[16];
    char domain_name[256];
    char username   [256];
    char password   [256];
    char sub_domain_name[256];
}domain_info_t;

typedef struct 
{
    unsigned int domain_id;
    int status;
    char name[64];
}result_domain_t;

typedef struct
{
    unsigned int record_id;
    int status;
    char name[64];
    char value[16];
}result_sub_domain_t;       

typedef struct 
{
    int code;
    unsigned int domain_num;
    unsigned int sub_domain_num;
    result_domain_t *domain;
    result_sub_domain_t *sub_domain;
}result_t;

struct MemoryStruct {
  char *memory;
  unsigned int size;
};

#endif //_COMMON_H_