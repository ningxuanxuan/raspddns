#include "../log.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>



int main(void)
{
    CPPUNIT_NS::TestResult controller;
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener( &result );
    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener( &progress );     

     CPPUNIT_NS::TestRunner runner;
     runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
     runner.run( controller );
     return result.wasSuccessful() ? 0 : 1;
}
