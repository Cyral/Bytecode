using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cyral
{
    public class Result
    {
        public Instruction[] Instructions { get; }

        public Result(int length)
        {
            Instructions = new Instruction[length];
        }

        public Result(Instruction[] final)
        {
            Instructions = final;
        }
    }
}
