#ifndef MYL_H
#define MYL_H
/// "myl.h"
///----------------------------------------------------------------------------|
/// ...
///----------------------------------------------------------------------------:
#include "debug.h"


namespace win
{
    #if __has_include(<windows.h>)
        #include      <windows.h>
        std::wstring utf8toWstr(const std::string& s)
        {   const int N   = (int)s.size();
            const int szW = MultiByteToWideChar(CP_UTF8, 0, &s[0], N, NULL, 0);
            std::wstring wstr(szW, 0);
            MultiByteToWideChar(CP_UTF8, 0, &s[0], N, &wstr[0], szW);
            return wstr;
        }

        struct  IfstreamBin : std::wifstream
        {       IfstreamBin(std::string name)
                :   std::wifstream(utf8toWstr(name).c_str(), std::ios::binary)
                {
                }

            std::wifstream& get(){ return *(dynamic_cast<std::wifstream*>(this)); }
        };
    #else
        struct  IfstreamBin : std::ifstream
        {       IfstreamBin(std::string name)
                :   std::ifstream(name.c_str(), std::ios::binary)
                {
                }
            std::ifstream& get(){ return *this; }
        };
    #endif
}


namespace myl
{


    ///--------------------------------------|
    /// Тесты.                               |
    ///--------------------------------------:
    inline void tests()
    {
    return;

        std::cout << "Start myl::tests() ...\n\n";



        std::cin.get();
    }
}

#endif // MYL_H
