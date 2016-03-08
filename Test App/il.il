.assembly 'Test App'
{

}

.class private auto ansi beforefieldinit Test_App.Program
       extends [mscorlib]System.Object
{
  .method private hidebysig static void  Main(string[] args) cil managed
  {
    .entrypoint
    .maxstack  2
    .locals init ([0] int32 max,
             [1] int32 i,
             [2] bool isPrime,
             [3] int32 j)
    IL_0000:  ldc.i4     0x2710
    IL_0005:  stloc.0
    IL_0006:  ldc.i4.0
    IL_0007:  stloc.1
    IL_0008:  br.s       IL_0032

    IL_000a:  ldc.i4.1
    IL_000b:  stloc.2
    IL_000c:  ldc.i4.2
    IL_000d:  stloc.3
    IL_000e:  br.s       IL_0021

    IL_0010:  ldloc.1
    IL_0011:  ldloc.3
    IL_0012:  beq.s      IL_001d

    IL_0014:  ldloc.1
    IL_0015:  ldloc.3
    IL_0016:  rem
    IL_0017:  brtrue.s   IL_001d

    IL_0019:  ldc.i4.0
    IL_001a:  stloc.2
    IL_001b:  br.s       IL_0025

    IL_001d:  ldloc.3
    IL_001e:  ldc.i4.1
    IL_001f:  add
    IL_0020:  stloc.3
    IL_0021:  ldloc.3
    IL_0022:  ldloc.0
    IL_0023:  ble.s      IL_0010

    IL_0025:  ldloc.2
    IL_0026:  brfalse.s  IL_002e

    IL_0028:  ldloc.1
    IL_0029:  call       void [mscorlib]System.Console::WriteLine(int32)
    IL_002e:  ldloc.1
    IL_002f:  ldc.i4.1
    IL_0030:  add
    IL_0031:  stloc.1
    IL_0032:  ldloc.1
    IL_0033:  ldloc.0
    IL_0034:  ble.s      IL_000a

    IL_0036:  call       string [mscorlib]System.Console::ReadLine()
    IL_003b:  pop
    IL_003c:  ret
  }
  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  ret
  } 
}