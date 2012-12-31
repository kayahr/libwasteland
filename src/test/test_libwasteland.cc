/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

using std::cerr;
using CPPUNIT_NS::TestResult;
using CPPUNIT_NS::TestResultCollector;
using CPPUNIT_NS::BriefTestProgressListener;
using CPPUNIT_NS::TestRunner;
using CPPUNIT_NS::CompilerOutputter;
using CPPUNIT_NS::TestFactoryRegistry;

int main()
{
    TestResult result;
    TestResultCollector results;
    result.addListener(&results);
    BriefTestProgressListener progress;
    result.addListener(&progress);
    TestRunner runner;
    runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
    runner.run(result);
    CompilerOutputter outputter(&results, cerr);
    outputter.write();
    return results.wasSuccessful() ? 0 : 1;
}
