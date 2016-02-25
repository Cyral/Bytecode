using System.Collections.Generic;
using System.Linq;

namespace Cyral
{
    public class Optimizer
    {
        private Instruction[] instructions;
        private int length;

        public Result Run(Result parserResult)
        {
            length = parserResult.Instructions.Length;
            instructions = parserResult.Instructions;
            var optimized = new List<Instruction>(length);

            for (var ip = 0; ip < length - 1; ip++)
            {
                var instruction = instructions[ip];
                var next = Peek(ip, 1);

                // Optimize push then store into one call to set a local var.
                if (instruction.OpCode == OpCode.PUSH && next.OpCode == OpCode.ST
                    && !next.Label.HasValue)
                {
                    optimized.Add(new Instruction(OpCode.SET, ValueType.NONE, instruction.Label, new[]
                    {
                        new StackVal(instruction.DataType, instruction.Data),
                        next.Data,
                    }));
                    ip++;
                }
                // Optimize two var loads, a common operation before doing math operations.
                else if (instruction.OpCode == OpCode.LD && next.OpCode == OpCode.LD && !next.Label.HasValue)
                {
                    optimized.Add(new Instruction(OpCode.LD_PAIR, ValueType.NONE, instruction.Label,
                        new[] {instruction.DataAs<int>(), next.DataAs<int>()}));
                    ip++;
                }
                // Optimize a LD, PUSH 1, ADD, ST into a a call to ++ the value.
                else if (instruction.OpCode == OpCode.LD && next.OpCode == OpCode.PUSH
                         && next.DataType == ValueType.INT && next.DataAs<int>() == 1 && !next.Label.HasValue)
                {
                    var addPotential = Peek(ip, 2);
                    var stPotential = Peek(ip, 3);
                    if (addPotential.OpCode == OpCode.ADD && stPotential.OpCode == OpCode.ST &&
                        instruction.DataAs<int>() == stPotential.DataAs<int>()
                        && !addPotential.Label.HasValue && !stPotential.Label.HasValue)
                    {
                        optimized.Add(new Instruction(OpCode.INC, ValueType.INT, instruction.Label, instruction.DataAs<int>()));
                        ip += 3;
                    }
                    else
                        optimized.Add(instruction);
                }
                else
                {
                    optimized.Add(instruction);
                }
            }
            optimized.Add(instructions[instructions.Length - 1]);

            var final = RemoveNoOps(optimized);

            var result = new Result(final);
            return result;
        }

        private static Instruction[] RemoveNoOps(List<Instruction> optimized)
        {
            // Remove No-ops that were added as spacers, and ajust jump labels accordingly.
            var count = optimized.Count - 1;
            for (var ip = count; ip-- > 0;)
            {
                var instruction = optimized[ip];
                if (instruction.OpCode == OpCode.NOP)
                    optimized.RemoveAt(ip);
            }
            return optimized.ToArray();
        }

        private Instruction Peek(int index, int ahead)
        {
            return index + ahead < length ? instructions[index + ahead] : new Instruction(OpCode.NOP);
        }
    }
}