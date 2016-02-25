using System;
using System.Runtime.CompilerServices;

namespace Cyral
{
    public class StackVal
    {
        public object Data;
        public ValueType Type;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public StackVal(ValueType type, object data)
        {
            Type = type;
            Data = data;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public bool GetBoolWithCheck()
        {
            if (Type == ValueType.INT)
                return ((int)(Data) != 0);
            return (bool)Data;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public T DataAs<T>()
        {
            //if (Type == ValueType.INT && typeof (T) == typeof (string))
            //    return (T) (object) ((int) Data).ToString();
            return (T) Data;
        }
    }
}