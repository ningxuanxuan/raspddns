#ifndef _RASPDDNS_LOG_UT_H_
#define _RASPDDNS_LOG_UT_H_    1
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>



class LogTest : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(LogTest);
    //CPPUNIT_TEST(testHelloWorld);
	CPPUNIT_TEST(testgetdatestr);
	CPPUNIT_TEST(testinitlog);
	CPPUNIT_TEST(testappendlog);
	CPPUNIT_TEST(testmaxappendlog);
	//CPPUNIT_TEST(testgetdatestr);
    CPPUNIT_TEST_SUITE_END();
public:
    //void setUp(void) {if(access("raspddns.log", F_OK) == 0){unlink("raspddns.log");}}

    //void tearDown(void) {if(access("raspddns.log", F_OK) == 0){unlink("raspddns.log");}}
    
protected:	

    void testgetdatestr(void);
	void testinitlog(void);
	void testappendlog(void);
	void testmaxappendlog(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(LogTest);

#endif
