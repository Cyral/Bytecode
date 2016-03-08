using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test_App
{
    class Program
    {
        static void Main(string[] args)
        {
            var max = 10000;
            for (int i = 0; i <= max; i++)
            {
                var isPrime = true;
                for (var j = 2; j <= max; j++)
                {
                    if (i != j && i % j == 0)
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                    Console.WriteLine(i);
            }

            Console.ReadLine();
        }
    }
}
