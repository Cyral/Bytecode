using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace Cyral
{
    public class Parser
    {
        public Result Run(IEnumerable<string> input)
        {
            var lines = input.Select(x => x.Trim())
                .Where(s => !string.IsNullOrWhiteSpace(s) && !s.StartsWith("/")).ToArray();

            var result = new Result(lines.Length);

            // Parse opcodes.
            for (var i = 0; i < lines.Length; i++)
            {
                var line = lines[i];

                var parts = line.Split(new[] {' '}, 3);
                var part = 0;

                // Check if line has a label.
                uint label = 0;
                var labelDefined = false;
                var colonIndex = parts[part].IndexOf(':');
                if (colonIndex > 0)
                {
                    label = uint.Parse(line.Substring(0, colonIndex));
                    labelDefined = true;
                    part++;
                }
                else
                    parts = line.Split(new[] {' '}, 2);

                var typeSep = parts[part].IndexOf('.');
                var type = ValueType.NONE;
                if (typeSep > 0)
                    type = (ValueType) Enum.Parse(typeof (ValueType), parts[part].Substring(typeSep + 1), true);

                var opcode =
                    (OpCode)
                        Enum.Parse(typeof (OpCode), typeSep > 0 ? parts[part].Substring(0, typeSep) : parts[part], true);

                part++;
                var data = part == parts.Length - 1 ? parts[part] : null;
                object fdata = data;

                if (opcode == OpCode.ST || opcode == OpCode.LD || opcode == OpCode.JMP || opcode == OpCode.BRFALSE ||
                    opcode == OpCode.BRTRUE || opcode == OpCode.BRLE || opcode == OpCode.BRLT || opcode == OpCode.INC)
                {
                    fdata = int.Parse(data);
                    type = ValueType.INT;
                }

                result.Instructions[i] = new Instruction(opcode, type, fdata);
                if (labelDefined)
                    result.Instructions[i].Label = label;
            }

            return result;
        }
    }
}