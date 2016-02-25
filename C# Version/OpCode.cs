namespace Cyral
{
    public enum OpCode
    {
        NOP,
        PUSH,
        ST,
        LD,

        MUL,
        DIV,
        ADD,
        SUB,
        MOD,
        EQ,
        NEQ,
        
        JMP,

        BRFALSE,
        BRTRUE,

        BRLT,
        BRLE,

        COMP,

        CALL,
        RET,

        SET,

        INC,
        LD_PAIR
    }
}