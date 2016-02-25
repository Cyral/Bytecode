namespace Cyral
{
    public struct Instruction
    {
        public OpCode OpCode;

        public object Data;

        public ValueType DataType;

        public uint? Label;

        internal uint Jump;

        public Instruction(OpCode opcode, ValueType dataType, object data = null)
        {
            OpCode = opcode;
            DataType = dataType;
            Jump = 0;
            Label = null;

            // ReSharper disable PossibleNullReferenceException
            if (dataType == ValueType.INT)
                Data = int.Parse(data.ToString());
            else if (dataType == ValueType.BOOL)
                Data = bool.Parse(data.ToString()) ? 1 : 0;
            else if (dataType == ValueType.STR)
            {
                var str = data.ToString();
                Data = str.Substring(1, str.Length - 2);
            }
            else
                Data = data;
            // ReSharper enable PossibleNullReferenceException
        }

        public Instruction(OpCode opcode, ValueType dataType, uint? label, object data = null)
            : this(opcode, dataType, data)
        {
            Label = label;
        }

        public Instruction(OpCode opcode)
        {
            OpCode = opcode;
            Data = null;
            Jump = 0;
            Label = null;
            DataType = ValueType.NONE;
        }

        public override string ToString()
        {
            return $"{OpCode} {Data}";
        }

        public T DataAs<T>()
        {
            return (T) Data;
        }
    }
}