#ifndef FILES_2_CODE_INDEX_H
#define FILES_2_CODE_INDEX_H
/// "files2codeIndex.h"
///----------------------------------------------------------------------------|
/// Ресурсы для юзера теперь, как индексы.
///----------------------------------------------------------------------------:
#include "myl.h"

using Pathes = std::set<fs::path>;
using Buffer = std::vector<unsigned char>;

///----------------------------------------------------------------------------|
/// Files2CodeIndex.
///------------------------------------------------------------ Files2CodeIndex:
struct  Files2CodeIndex
{       Files2CodeIndex()
        {   go                 ();
            assembleIntoFileCpp();
        }

    void go()
    {
        FilesCargo filesCargo;
                ln(filesCargo.debug())

        for(const auto& path : filesCargo)
        {

        ///--------------------------------------|
        /// Мультияз имена файлов.               |
        ///--------------------------------------:
        #ifdef __WIN32
            std::ifstream input(win::utf8toWstr(path.string()).c_str());
        #else
            std::ifstream input(path.string().c_str());
        #endif // __WIN32

            ASSERTM(input.is_open(), std::format("fail: {}", path.string()))

            Buffer buffer(std::istreambuf_iterator<char>(input), {});

            if(path.extension() == ".txt") buffer.push_back(0);

            const std::string name{getName(path.filename())};

            codeFrag01 << "unsigned char " << name << "[]\n";

            codeFrag03
                << "        {"
                << buffer.size() << ", "
                << name          << ", \"";

            if(std::filesystem::path::preferred_separator == '\\')
            {
                 codeFrag03 << fixSlash(path) << "\"},\n";
            }
            else codeFrag03 << path << "\"},\n";

            add2cpp(buffer);
        }
    }

    ///--------------------------------------|
    /// Получить отчёт.                      |
    ///--------------------------------------:
    std::string debug() const
    {   std::stringstream ss;



        return ss.str();
    }

private:
    std::string_view filenameCPP{"allRes.cpp"};

    void add2cpp(const Buffer& buffer)
    {
        size_t cnt{};

        codeFrag01 <<"{\n    ";
        for(const auto byte : buffer)
        {
            codeFrag01 << std::setw(3) << uint16_t(byte) << ',';

            if(++cnt%19 == 0) codeFrag01 << "\n    ";
        }
        codeFrag01 <<"\n};\n\n";
    }

    std::string getName(const fs::path& path) const
    {
        std::string name{path.string()};

        for(auto& c : name)
        {
            switch(c)
            {   case '!':
                case '+':
                case '-':
                case '=':
                case '.':
                case ' ': c = '_'; break;
            }
        }
        return name;
    }

    std::string fixSlash(const fs::path& path)
    {
        static_assert( std::filesystem::path::preferred_separator == '\\' );

        std::string  s{path.string()};
        std::replace(s.begin(), s.end(), '\\', '/');
        return s;
    }

    void assembleIntoFileCpp()
    {
        std::ofstream fileCPP(filenameCPP.data());
        ASSERTM(fileCPP.is_open(), std::format("fail {}\n", filenameCPP))

        fileCPP   << codeFrag00
                  << codeFrag01.str()
                  << codeFrag02
                  << codeFrag03.str().substr(0, codeFrag03.str().size() - 2)
                  << codeFrag04 << std::endl;

        std::cout << codeFrag03.str().substr(0, codeFrag03.str().size() - 2)
                  << std::endl;
    }

    ///--------------------------------------|
    /// Тест разраба.                        |
    ///--------------------------------------:
    TEST
    {   Files2CodeIndex task;
    }

///----------------------------------------------------------------------------|
/// Константные куски кода.
///----------------------------------------------------------------------------:
const std::string_view  codeFrag00
{
R"(#include "allResIndex.h"
///----------------------------------------------------------------------------|
/// myXXD-ver:0.2
///----------------------------------------------------------------------------:
)"
};

      std::stringstream codeFrag01; /// Генерируется.
const std::string_view  codeFrag02
{
R"(
namespace res
{
    std::vector<Unit> arrMyRes
    {
)"
};

      std::stringstream codeFrag03; /// Генерируется.
const std::string_view  codeFrag04
{
R"(
    };

    std::ostream& operator<<(std::ostream& o, const Unit& res)
    {   o   << "   len = "          <<        res.len
            << ",  data(adress) = " << (void*)res.data
            << ",  path = \""       <<        res.path << "\"\n";
        return  o;
    }

    std::ostream& operator<<(std::ostream& o, const std::vector<Unit*>& m)
    {   for(const auto& e : m) o << *e;
        return  o;
    }

    std::vector<Unit*> Unit::get(const std::string_view what)
    {   std::vector<Unit*> m;
        m.reserve(arrMyRes.size());

        for(auto& res : arrMyRes)
        {   const size_t pos = res.path.find(what);

            if(pos != std::string::npos)
            {   m.push_back(&res);
            }
        }
        return m;
    }

    std::string info(const std::string_view what)
    {
        std::vector<res::Unit*>  res = Unit::get(what);
        std::stringstream   ss;
                            ss << "res.size(): " << res.size() << '\n';
                            ss << res << '\n';
        return ss.str();
    }
}
)"
};

};

#endif // FILES_2_CODE_INDEX_H
