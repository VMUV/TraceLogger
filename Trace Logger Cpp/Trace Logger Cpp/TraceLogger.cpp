// TraceLogger.cpp

#include "stdafx.h"

#include "TraceLogger.h"


Trace_Logger_Cpp::TraceLogger::TraceLogger()
{
	_maxListSize = 32;
	_numMessagesQueued = 0;
}

Trace_Logger_Cpp::TraceLogger::TraceLogger(int maximumListSize)
{
	_numMessagesQueued = 0;
	_maxListSize = maximumListSize;
}

Trace_Logger_Cpp::TraceLogger::~TraceLogger()
{
}

// note: does not take ownership of msg - rather it makes a copy
bool Trace_Logger_Cpp::TraceLogger::QueueMessage(Trace_Logger_Cpp::TraceLoggerMessage msg)
{
	if (!IsRoomInBuff())
		return false;

	// inserts a copy of msg at list begenning
	messageList.push_back(msg);
	_numMessagesQueued++;
	return true;
}

Trace_Logger_Cpp::TraceLoggerMessage Trace_Logger_Cpp::TraceLogger::DeQueueMessage()
{
	TraceLoggerMessage rtn;
	if (_numMessagesQueued > 0)
	{
		--_numMessagesQueued;
		rtn = messageList.back();
		messageList.pop_back();
		return rtn;
	}
	throw INDEXOUTOFRANGEEXCEPTION;
}

Trace_Logger_Cpp::TraceLoggerMessage Trace_Logger_Cpp::TraceLogger::BuildMessage(string modName, string method, string msg)
{
	TraceLoggerMessage rtn;
	{
		rtn.moduleName = modName;
		rtn.methodName = method;
		rtn.message = msg;
	};

	return rtn;
}

// for now this function will return a copy of the entire list. I will revisit this
// if it turns out that we really do need the messages to be in the form of an array
list<Trace_Logger_Cpp::TraceLoggerMessage> Trace_Logger_Cpp::TraceLogger::GetAllMessages()
{
	list<Trace_Logger_Cpp::TraceLoggerMessage> rtn = messageList;
	messageList.clear();

	_numMessagesQueued = 0;
	return rtn;
}

string Trace_Logger_Cpp::TraceLogger::TraceLoggerMessageToString(Trace_Logger_Cpp::TraceLoggerMessage msg)
{
	return (msg.moduleName + ": " + msg.methodName + ": " + msg.message);
}

