using System;

namespace Trace_Logger_CSharp
{
    public static class Logger
    {
        private static string _currentDir = System.IO.Directory.GetCurrentDirectory();
        private static string _logFileName = "log.txt";
        private static string _logFilePath = System.IO.Path.Combine(_currentDir, _logFileName);
        private static bool _logFileCreated = false;

        public static bool PrintToConsole { get; set; }

        public static void CreateLogFile()
        {
            if (_logFileCreated)
                return;

            try
            {
                string[] str = { "*** New log file created ***" };
                System.IO.File.WriteAllLines(_logFilePath, str);
                _logFileCreated = true;
            }
            catch (System.IO.IOException) { }
            catch (Exception) { }
        }

        public static void LogMessage(string msg)
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(_logFilePath, true))
            {
                try
                {
                    file.WriteLine(msg);
                    if (PrintToConsole)
                        Console.WriteLine(msg);
                }
                catch (Exception) { }
            }
        }

        public static void LogMessage(string[] msgs)
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(_logFilePath, true))
            {
                try
                {
                    foreach (string element in msgs)
                    {
                        file.WriteLine(element);

                        if (PrintToConsole)
                            Console.WriteLine(element);
                    }
                }
                catch (Exception) { }
            }
        }
    }
}
