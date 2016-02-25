using System;
using System.Runtime.CompilerServices;

namespace Cyral
{
    public class FastStack
    {
        private StackVal[] contents;
        private int index;
        private int size;
        private const int InitialSize = 32;

        public FastStack()
        {
            size = InitialSize;
            contents = new StackVal[size];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Push(StackVal obj)
        {
            contents[index] = obj;
            index++;

            if (index >= size)
            {
                size = size * 2;
                Array.Resize(ref contents, size);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public StackVal Pop()
        {
            index--;
            return contents[index];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Mod()
        {
            index--;
            contents[index - 1] = new StackVal(ValueType.INT,
                contents[index -1].DataAs<int>() % contents[index].DataAs<int>());
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Add()
        {
            index--;
            contents[index - 1] = new StackVal(ValueType.INT,
                contents[index - 1].DataAs<int>() + contents[index].DataAs<int>());
        }
    }
}