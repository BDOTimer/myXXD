///----------------------------------------------------------------------------|
/// myXXD::[version:2025-03-20]
///     bin\allRes.h    -   включить в вашу программу.
///     bin\libres.a    -   скомпилированные ресы подключить к линкеру.
///---------------------------------------------------------------------- myXXD:
#include <iostream>
#include "files-cargo.h"
#include "files2code.h"
#include "files2codeIndex.h"
#include "config.h"

#include "../bin/allResIndex.h"

cfg::Config config;

namespace win
{
    #if __has_include(<windows.h>)
        #include      <windows.h>
        void init()
        {   std::system("chcp 65001>nul");
            win::SetConsoleTitle("Debug: myXXD");
        //  std::system("mode 70,40");
        }
    #else
        void init(){}
    #endif
}

///----------------------------------------------------------------------------|
/// Program.
///-------------------------------------------------------------------- Program:
struct  Program
{       Program()
        {

        }

private:

};


bool foo()
{
#ifdef  TESTRES
    std::cout << "|------------------TEST:\n";
    ln(Document_1_txt)
    ln(Document_2_txt)
    ln(Document_3_txt)
    return true;
#endif
    return false;
}


///----------------------------------------------------------------------------|
/// Тесты классов.
///-------------------------------------------------------------------- tests():
void tests()
{
    if(foo()) return;

    if(true)
    {
    /// res::Unit::test();

    /// FilesCargo ::test();
    /// cfg::Args  ::test();
    /// cfg::Config::test();
    }

    ///---------------|
    /// Итоговое.     |
    ///---------------:
    if(config.doIndex)  Files2CodeIndex::test();
    else                Files2Code     ::test();
}


///----------------------------------------------------------------------------|
/// main.
///----------------------------------------------------------------------- main:
int main(int argc, const char* argv[])
{
    win::init();

    std::cout << "Hello, I'm myXXD!\n" << std::endl;

    if(argc > 1)
    {   ln(config.set(argc, argv))
    }

    const char* mess = "\nProgram myXXD shut down ";

    try
    {
        tests();

        std::cout << mess <<  "correctly!\n"            << std::endl;
        std::cout << "Press ENTER for run Compiler ..." << std::endl;
        std::cin.get();
        std::system("compiler.bat");
    }
    catch(...)
    {   std::cout << mess << "failed..." << std::endl;
    }

    std::cin.get();
    return 0;
}
