#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "TraceLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Trace_Logger_Cpp;

namespace TraceLoggerCppTests
{		
	TEST_CLASS(TraceLoggerUnitTests)
	{
	public:
		string moduleName = "TraceLoggerTests::TestBuildTraceLoggerMessage()";
		TEST_METHOD(TestBuildTraceLoggerMessage)
		{
			string methodName = "TraceLoggerTests::TestBuildTraceLoggerMessage()";
			string message = "TraceLoggerTests::TestBuildTraceLoggerMessage()";

			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);
			Assert::IsFalse(moduleName.compare(msg.moduleName));
		}

	};
}