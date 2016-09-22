#include "log_ut.h"
#include "../log.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
void LogTest::testgetdatestr(void)
{
	char buffer[]="yyyy-mm-dd hh:ii:ss";
	
	if( NULL == _get_current_date_string(buffer, sizeof(buffer)))
	{
		CPPUNIT_ASSERT( false );
	}
	
	std::cout << "\n" << buffer << std::endl;
	
	CPPUNIT_ASSERT_EQUAL(_get_current_date_string(NULL, 0), (char *) NULL);
	
	
}

void LogTest::testinitlog(void)
{
	FILE *stream = NULL;
	if( NULL != raspddns_init_log(NULL))
	{
		CPPUNIT_ASSERT_MESSAGE( "null init failed", false);
	}
	
	stream = raspddns_init_log("raspddns.log");
	
	CPPUNIT_ASSERT_MESSAGE("init failed", stream != NULL);
	raspddns_close_log(stream);
	
	CPPUNIT_ASSERT_EQUAL_MESSAGE("log file not exists", access("raspddns.log", F_OK), 0);
	
	
}

void LogTest::testappendlog(void)
{
	FILE *stream = NULL;
	struct stat info = {0};
	if( NULL != raspddns_init_log(NULL))
	{
		CPPUNIT_ASSERT(false);
	}
	
	stream = raspddns_init_log("raspddns.log");
	CPPUNIT_ASSERT(stream != NULL);
	CPPUNIT_ASSERT_EQUAL(raspddns_append_log(stream, "this is a test!"), 0);
	raspddns_close_log(stream);
	stat("raspddns.log", &info);
	CPPUNIT_ASSERT(info.st_size == 20 + strlen("this is a test!") + 1);
	
}

void LogTest::testmaxappendlog(void)
{
	FILE *stream = NULL;
	struct stat info = {0};
	if( NULL != raspddns_init_log(NULL))
	{
		CPPUNIT_ASSERT(false);
	}
	
	stream = raspddns_init_log("raspddns.log");
	CPPUNIT_ASSERT(stream != NULL);
	
	for(unsigned int i = 0; i < 500000; i++)
	{
		CPPUNIT_ASSERT_EQUAL(raspddns_append_log(stream, "this is a test!"), 0);
	}
	
	raspddns_close_log(stream);
	stream = raspddns_init_log("raspddns.log");
	CPPUNIT_ASSERT(stream != NULL);
	CPPUNIT_ASSERT_EQUAL(raspddns_append_log(stream, "this is a test!"), 0);
	raspddns_close_log(stream);
	stat("raspddns.log", &info);
	CPPUNIT_ASSERT(info.st_size == 20 + strlen("this is a test!") + 1);
	
}


