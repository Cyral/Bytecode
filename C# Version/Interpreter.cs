//#define benchmark

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cyral
{
    public class Interpreter
    {
        private readonly StackVal[] locals = new StackVal[100];
        private readonly Optimizer optimizer;
        private readonly Parser parser;
        private readonly string[] source;

        private readonly FastStack stack = new FastStack();
        private readonly Dictionary<uint, uint> tempLabels;

        private uint from;
        private Instruction[] instructions;
        private Dictionary<Instruction, long> iterations;

        public Interpreter(string[] source)
        {
            this.source = source;
            parser = new Parser();
            optimizer = new Optimizer();

            tempLabels = new Dictionary<uint, uint>();
        }

        public void Run()
        {
            // Run the parser.
            var parserResult = parser.Run(source);
            var optimizedResult = optimizer.Run(parserResult);
            instructions = optimizedResult.Instructions;

            // Calculate jumps.
            for (uint i = 0; i < instructions.Length; i++)
            {
                var instruction = instructions[i];
                if (instruction.Label.HasValue)
                {
                    tempLabels[instruction.Label.Value] = i;
                }
            }

            for (uint i = 0; i < instructions.Length; i++)
            {
                var instruction = instructions[i];
                if (instruction.OpCode == OpCode.JMP || instruction.OpCode == OpCode.BRFALSE
                    || instruction.OpCode == OpCode.BRTRUE || instruction.OpCode == OpCode.BRLE ||
                    instruction.OpCode == OpCode.BRLT)
                {
                   instructions[i].Jump = tempLabels[(uint) instruction.DataAs<int>()] - 1;
                }
            }

#if benchmark
            iterations = new Dictionary<Instruction, long>();
            for (uint ip = 0; ip < instructions.Length; ip++)
            {
                iterations[instructions[ip]] = 0;
            }
#endif

            long total = 0;
  
            for (uint ip = 0; ip < instructions.Length; ip++)
            {
                total++;

                var instruction = instructions[ip];
#if benchmark
                iterations[instruction]++;
#endif
                switch (instruction.OpCode)
                {
                    case OpCode.PUSH:
                        stack.Push(new StackVal(instruction.DataType, instruction.Data));
                        break;
                    case OpCode.ST:
                    {
                        locals[instruction.DataAs<int>()] = stack.Pop();
                        break;
                    }
                    case OpCode.SET:
                    {
                        var data = instruction.DataAs<object[]>();
                        locals[(int) data[1]] = (StackVal) data[0];
                        break;
                    }
                    case OpCode.LD:
                    {
                        stack.Push(locals[instruction.DataAs<int>()]);
                        break;
                    }
                    case OpCode.LD_PAIR:
                    {
                        var data = instruction.DataAs<int[]>();
                        stack.Push(locals[data[0]]);
                        stack.Push(locals[data[1]]);
                        break;
                    }
                    case OpCode.BRFALSE:
                    {
                        if (!stack.Pop().GetBoolWithCheck())
                        {
                            from = ip;
                            ip = instruction.Jump;
                        }
                        break;
                    }
                    case OpCode.BRTRUE:
                    {
                        if (stack.Pop().GetBoolWithCheck())
                        {
                            from = ip;
                            ip = instruction.Jump;
                        }
                        break;
                    }
                    case OpCode.JMP:
                    {
                        from = ip;
                        ip = instruction.Jump;

                        break;
                    }
                    case OpCode.MUL:
                        stack.Push(new StackVal(ValueType.INT, stack.Pop().DataAs<int>() * stack.Pop().DataAs<int>()));
                        break;
                    case OpCode.ADD:
                    {
                        //if (val2.Type == ValueType.STR || val1.Type == ValueType.STR)
                        //   stack.Push(new StackVal(ValueType.STR, val1.DataAs<string>() + val2.DataAs<string>()));
                        //else
                        //    stack.Push(new StackVal(ValueType.INT, val1.DataAs<int>() + val2.DataAs<int>()));
                        stack.Add();
                        break;
                    }
                    case OpCode.INC:
                    {
                         var index = instruction.DataAs<int>();
                        locals[index] = new StackVal(ValueType.INT, locals[index].DataAs<int>() + 1);
                            break;
                    }
                    case OpCode.SUB:
                        stack.Push(new StackVal(ValueType.INT, stack.Pop().DataAs<int>() - stack.Pop().DataAs<int>()));
                        break;
                    case OpCode.DIV:
                    {
                        var val2 = stack.Pop().DataAs<int>();
                        var val1 = stack.Pop().DataAs<int>();
                        stack.Push(new StackVal(ValueType.INT, val1 / val2));
                        break;
                    }
                    case OpCode.MOD:
                    {
                        stack.Mod();
                        break;
                    }
                    case OpCode.EQ:
                    {
                        var val1 = stack.Pop().Data;
                        var val2 = stack.Pop().Data;
                        stack.Push(new StackVal(ValueType.BOOL, val1.Equals(val2)));
                        break;
                    }
                    case OpCode.NEQ:
                    {
                        var val1 = stack.Pop().Data;
                        var val2 = stack.Pop().Data;
                        stack.Push(new StackVal(ValueType.BOOL, !val1.Equals(val2)));
                        break;
                    }
                    case OpCode.COMP:
                    {
                        var val2 = stack.Pop().DataAs<int>();
                        var val1 = stack.Pop().DataAs<int>();

                        stack.Push(new StackVal(ValueType.BOOL, val1 > val2));
                        break;
                    }
                    case OpCode.BRLE:
                    {
                        var val2 = stack.Pop().DataAs<int>();
                        var val1 = stack.Pop().DataAs<int>();
                        if (val1 <= val2)
                        {
                            from = ip;
                            ip = instruction.Jump;
                        }
                        break;
                    }
                    case OpCode.BRLT:
                    {
                        var val2 = stack.Pop().DataAs<int>();
                        var val1 = stack.Pop().DataAs<int>();
                        if (val1 < val2)
                        {
                            from = ip;
                            ip = instruction.Jump;
                        }
                        break;
                    }
                    case OpCode.CALL:
                        var name = instruction.DataAs<string>();
                        RunNativeFunction(name);
                        break;
                    case OpCode.RET:
                        ip = from;
                        break;
                }
            }

            Console.WriteLine();
            Console.WriteLine($"{total} instructions executed.");
#if benchmark
            Console.WriteLine();
            Console.WriteLine("Benchmark Results:");
            for (uint ip = 0; ip < instructions.Length; ip++)
            {
                var instruction = instructions[ip];
                var iteration = iterations[instruction];
                if (instruction.Label.HasValue)
                Console.Write(instruction.Label.Value + ": ");
                Console.WriteLine($"{instruction.OpCode} {iteration}");
            }
#endif
        }

        private void RunNativeFunction(string name)
        {
            if (name == "print")
            {
                //stack.Pop();
                Console.WriteLine(stack.Pop().Data);
            }
            else if (name == "input")
            {
                stack.Push(new StackVal(ValueType.STR, Console.ReadLine()));
            }
            else if (name == "alert")
            {
                MessageBox.Show(stack.Pop().DataAs<string>(), stack.Pop().DataAs<string>());
            }
        }
    }
}