#ifndef FILES_2_CODE_H
#define FILES_2_CODE_H
/// "files2code.h"
///----------------------------------------------------------------------------|
/// Файловый коллектор.
///     -   как испльзовать смотрим тест.
///----------------------------------------------------------------------------:
#include "myl.h"

using Pathes = std::set<fs::path>;
using Buffer = std::vector<unsigned char>;

extern const char* const header1;
extern const char* const header2;

///----------------------------------------------------------------------------|
/// Files2Code.
///----------------------------------------------------------------- Files2Code:
struct  Files2Code
{       Files2Code()
        {
            fileCPP.open(filenameCPP.data());
            fileH  .open(filenameH  .data());

            ASSERTM(fileCPP.is_open(), std::format("fail {}\n", filenameCPP))
            ASSERTM(fileH  .is_open(), std::format("fail {}\n", filenameH  ))

            go();

            fileCPP.close();
            fileH  .close();
        }

    void go()
    {
        fileH << header1;

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

            fileCPP << "unsigned char "        << name << "[]\n";
            fileH   << "extern unsigned char " << name << "[];\n"
                    << "const size_t " << (name + "_len = ")
                    << buffer.size()   << ";\n\n";

            std::cout << "extern unsigned char " << name << "[];\n"
                      << "const size_t " << (name + "_len = ")
                      << buffer.size()   << ";\n\n";

            add2cpp(buffer);
        }
        fileH << header2;
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
    std::string_view filenameH  {"allRes.h"  };

    std::ofstream fileCPP;
    std::ofstream fileH  ;

    void add2cpp(const Buffer& buffer)
    {
        size_t cnt{};

        fileCPP <<"{\n    ";
        for(const auto byte : buffer)
        {
            fileCPP << std::setw(3) << uint16_t(byte) << ',';

            if(++cnt%19 == 0) fileCPP << "\n    ";
        }
        fileCPP <<"\n};\n\n";
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

    ///--------------------------------------|
    /// Тест разраба.                        |
    ///--------------------------------------:
    TEST
    {   Files2Code files2Code;
    }
};

const char* const header1
{
R"(#ifndef ALL_RES_H
#define ALL_RES_H
/// myXXD: "allRes.h"
///----------------------------------------------------------------------------|
/// Тут все ваши ресурсы.
///----------------------------------------------------------------------------:
)"};

const char* const header2
{
R"(
#endif // header guard
)"};

#endif // FILES_2_CODE_H
