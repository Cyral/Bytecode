using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace Cyral
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Console.WriteLine("Bytecode VM\n");

            // Read file.
            var source = File.ReadAllLines("il.txt");

            var sw = Stopwatch.StartNew();

            // Parse, optimize, and run bytecode.
            var interpreter = new Interpreter(source);
            interpreter.Run();

            // Print time.
            sw.Stop();
            Console.WriteLine("\nCompleted in " + sw.ElapsedMilliseconds + "ms.");
            Console.ReadLine();
        }
    }
}