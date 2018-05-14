#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
//#include "string.h"
#include "../Trace Logger Cpp/TraceLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Trace_Logger_Cpp;

namespace TraceLoggerCppTests
{		
	TEST_CLASS(TraceLoggerUnitTests)
	{
	public:
		string moduleName = "TraceLoggerTests";
		string message = "Test this method yo";

		TEST_METHOD(TestBuildTraceLoggerMessage)
		{
			string methodName = "TestBuildTraceLoggerMessage";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);
			Assert::IsFalse(moduleName.compare(msg.moduleName));
			Assert::IsFalse(methodName.compare(msg.methodName));
			Assert::IsFalse(message.compare(msg.message));
		}

		TEST_METHOD(TestGetBuffSize)
		{
			int buffSize = 128;
			TraceLogger logger(buffSize);
			Assert::IsTrue(logger.GetBuffSize() == buffSize);
		}

		TEST_METHOD(TestQueueMessage)
		{
			string methodName = "TestQueueMessage";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);

			// buffer maximum amount of messages
			for (int i = 0; i < logger.GetBuffSize(); i++)
				Assert::IsTrue(logger.QueueMessage(msg));

			Assert::IsTrue(logger.GetBuffSize() == logger.GetNumMessagesQueued());
			Assert::IsFalse(logger.QueueMessage(msg));
		}

		TEST_METHOD(TestIsRoomInBuff)
		{
			string methodName = "TestIsRoomInBuff";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);

			while (logger.IsRoomInBuff())
				Assert::IsTrue(logger.QueueMessage(msg));

			Assert::IsTrue(logger.GetBuffSize() == logger.GetNumMessagesQueued());
		}

		TEST_METHOD(TestMessageCount)
		{
			string methodName = "TestMessageCount";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);
			Assert::IsFalse(logger.HasMessages());
			Assert::IsTrue(logger.GetNumMessagesQueued() == 0);
			Assert::IsTrue(logger.QueueMessage(msg));
			Assert::IsTrue(logger.HasMessages());
			Assert::IsTrue(logger.GetNumMessagesQueued() == 1);
		}

		TEST_METHOD(TestDequeueEmptyList)
		{
			TraceLogger logger;
			bool rtn = false;
			try {
				logger.DeQueueMessage();
			}
			catch (int) {
				rtn = true;
			}
			Assert::IsTrue(rtn);
		}

		TEST_METHOD(TestDeQueueMessages)
		{
			string methodName = "TestDeQueueMessages";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);

			while (logger.IsRoomInBuff())
				Assert::IsTrue(logger.QueueMessage(msg));

			while (logger.HasMessages()) 
			{
				TraceLoggerMessage rtn = logger.DeQueueMessage();
				Assert::IsFalse(moduleName.compare(rtn.moduleName));
				Assert::IsFalse(methodName.compare(rtn.methodName));
				Assert::IsFalse(message.compare(rtn.message));
			}

			Assert::IsFalse(logger.HasMessages());
			Assert::IsTrue(logger.GetNumMessagesQueued() == 0);
		}

		TEST_METHOD(TestDeQueueAllMessagesEmptyList)
		{
			TraceLogger logger;
//			list<Trace_Logger_Cpp::TraceLoggerMessage> all = logger.GetAllMessages();
			vector<Trace_Logger_Cpp::TraceLoggerMessage> all = logger.GetAllMessages();
			Assert::IsTrue(all.size() == 0);
		}

		TEST_METHOD(TestDeQueueAllMessages)
		{
			string methodName = "TestDeQueueAllMessages";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);

			while (logger.IsRoomInBuff())
				Assert::IsTrue(logger.QueueMessage(msg));

			Assert::IsTrue(logger.GetNumMessagesQueued() == logger.GetBuffSize());

//			list<Trace_Logger_Cpp::TraceLoggerMessage> rtn = logger.GetAllMessages();
			vector<Trace_Logger_Cpp::TraceLoggerMessage> rtn = logger.GetAllMessages();
			Assert::IsTrue(rtn.size() == logger.GetBuffSize());
			Assert::IsTrue(logger.GetNumMessagesQueued() == 0);

//			list<Trace_Logger_Cpp::TraceLoggerMessage>::iterator itr;
			vector<Trace_Logger_Cpp::TraceLoggerMessage>::iterator itr;
			for (itr = rtn.begin(); itr != rtn.end(); ++itr)
			{
				Trace_Logger_Cpp::TraceLoggerMessage item = *itr;

				Assert::IsFalse(moduleName.compare(item.moduleName));
				Assert::IsFalse(methodName.compare(item.methodName));
				Assert::IsFalse(message.compare(item.message));
			}
		}

		TEST_METHOD(TestQueueAndDeQueue)
		{
			string methodName = "TestQueueAndDeQueue";
			string testMod = "im gay";
			string testMeth = "you are gay";
			string testMsg = "everyone is gay";
			TraceLogger logger;
			TraceLoggerMessage msg = logger.BuildMessage(moduleName, methodName, message);

			while (logger.IsRoomInBuff())
				Assert::IsTrue(logger.QueueMessage(msg));

			// get the last message 
			TraceLoggerMessage rtn = logger.DeQueueMessage();
			Assert::IsFalse(moduleName.compare(rtn.moduleName));
			Assert::IsFalse(methodName.compare(rtn.methodName));
			Assert::IsFalse(message.compare(rtn.message));

			// requeue the last message and make sure the values are good
			msg.message = testMsg;
			msg.methodName = testMeth;
			msg.moduleName = testMod;
			Assert::IsTrue(logger.QueueMessage(msg));
			rtn = logger.DeQueueMessage();
			Assert::IsFalse(testMod.compare(rtn.moduleName));
			Assert::IsFalse(testMeth.compare(rtn.methodName));
			Assert::IsFalse(testMsg.compare(rtn.message));

			// get the rest and assure they are good
//			list<Trace_Logger_Cpp::TraceLoggerMessage> rtnBuf = logger.GetAllMessages();
			vector<Trace_Logger_Cpp::TraceLoggerMessage> rtnBuf = logger.GetAllMessages();
			Assert::IsTrue(rtnBuf.size() == logger.GetBuffSize() - 1);

			msg = logger.BuildMessage(moduleName, methodName, message);

//			list<Trace_Logger_Cpp::TraceLoggerMessage>::iterator itr;
			vector<Trace_Logger_Cpp::TraceLoggerMessage>::iterator itr;
			for (itr = rtnBuf.begin(); itr != rtnBuf.end(); ++itr)
			{
				Trace_Logger_Cpp::TraceLoggerMessage item = *itr;
				Assert::IsFalse(moduleName.compare(item.moduleName));
				Assert::IsFalse(methodName.compare(item.methodName));
				Assert::IsFalse(message.compare(item.message));
			}

			// fill it up and dump it one more time
			while (logger.IsRoomInBuff())
				Assert::IsTrue(logger.QueueMessage(msg));

			Assert::IsTrue(logger.GetBuffSize() == logger.GetNumMessagesQueued());
			logger.GetAllMessages();
			Assert::IsTrue(logger.GetNumMessagesQueued() == 0);
		}
	};
}