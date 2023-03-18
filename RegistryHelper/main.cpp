// RegistryHelper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


namespace Test {
    extern void GetSetString();
    extern void GetSetFloat();
    extern void GetSetDouble();
    extern void GetSetInt32();
    extern void GetSetInt64();
    extern void GetSetBinary();
}

int main()
{
    Test::GetSetString();
    Test::GetSetFloat();
    Test::GetSetDouble();
    Test::GetSetInt32();
    Test::GetSetInt64();
    Test::GetSetBinary();
}


