using System;

namespace Trace_Logger_CSharp
{
    static class Logger
    {
        private static string _currentDir = System.IO.Directory.GetCurrentDirectory();
        private static string _logFileName = "log.txt";
        private static string _logFilePath = System.IO.Path.Combine(_currentDir, _logFileName);

        public static bool PrintToConsole { get; set; }

        public static void CreateLogFile()
        {
            try
            {
                string[] str = { "*** New log file created ***" };
                System.IO.File.WriteAllLines(_logFilePath, str);
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
            string msg = "";
            foreach (string element in msgs)
            {
                msg += element;
            }

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
    }
}
