using System;
using System.Runtime.CompilerServices;

namespace Cyral
{
    public struct TypedPointer
    {
        public IntPtr Location;
        public ValueType Type;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public unsafe TypedPointer(ValueType type, int data)
        {
            Type = type;
            Location = new IntPtr(&data);

            Console.WriteLine("Location: " + Location);

        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public unsafe int GetInt()
        {
            Console.WriteLine(*((int*)Location));
            return *((int*) Location);
        }
    }
}