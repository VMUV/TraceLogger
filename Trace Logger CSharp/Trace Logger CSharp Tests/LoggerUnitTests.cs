using Microsoft.VisualStudio.TestTools.UnitTesting;
using Trace_Logger_CSharp;

namespace Trace_Logger_CSharp_Tests
{
    [TestClass]
    public class LoggerUnitTests
    {
        [TestMethod]
        public void TestCreateFile()
        {
            Logger.CreateLogFile();
            Logger.CreateLogFile();
        }

        [TestMethod]
        public void TestLogMessage()
        {
            string message = "Test message";
            Logger.LogMessage(message);
        }

        [TestMethod]
        public void TestLogMessages()
        {
            string[] messages = { "Test message 1", "Test message 2" };
            Logger.LogMessage(messages);
        }
    }
}
