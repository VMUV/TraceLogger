#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TraceLoggerCppTests
{		
	TEST_CLASS(TraceLoggerUnitTests)
	{
	public:
		
		TEST_METHOD(TestBuildTraceLoggerMessage)
		{
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);
			AssertAreEqualStrings(moduleName, msg.moduleName, "TraceLoggerTests::TestBuildTraceLoggerMessage()", 1);
			AssertAreEqualStrings(methodName, msg.methodName, "TraceLoggerTests::TestBuildTraceLoggerMessage()", 2);
			AssertAreEqualStrings(message, msg.message, "TraceLoggerTests::TestBuildTraceLoggerMessage()", 3);
		}

	};
}