#ifndef FILES_CARGO_H
#define FILES_CARGO_H
/// "files-cargo.h"
///----------------------------------------------------------------------------|
/// Файловый коллектор.
///     -   как испльзовать смотрим тест.
///----------------------------------------------------------------------------:
#include "debug.h"

using Pathes = std::set<fs::path>;

///----------------------------------------------------------------------------|
/// FilesCargo.
///----------------------------------------------------------------- FilesCargo:
struct  FilesCargo : Pathes
{       FilesCargo()
        {   scan("./resources/");
        }

    ///--------------------------------------|
    /// Получить отчёт.                      |
    ///--------------------------------------:
    std::string debug() const
    {   std::stringstream ss;

        ss << "|------------------ FilesCargo:\n";
        for(const auto& filename : *this)
        {   ss << "   " << filename << "\n";
        }
        ss << "\nВсего файлов: " << size() << '\n';

        return ss.str();
    }

    ///--------------------------------------|
    /// Тест разраба.                        |
    ///--------------------------------------:
    static void test()
    {   FilesCargo   filesCargo;
        std::cout << filesCargo.debug() << '\n';
    }

    ///--------------------------------------|
    /// Этот м. тут случайно затесался.      |
    ///--------------------------------------:
    static void remove(const fs::path& path)
    {   fs::remove(path);
    }

private:

    ///--------------------------------------|
    /// ...                                  |
    ///--------------------------------------:
    void scan(std::string_view dirImg)
    {
        const auto& spd = fs::directory_options::skip_permission_denied;

        const fs::recursive_directory_iterator START(dirImg, spd);
        const fs::recursive_directory_iterator END  {};

        for (auto ifile  = START; ifile != END; ++ifile)
        {
            if (fs::is_regular_file(ifile->path()))
            {   this->insert(ifile->path());
            }
        }
    }
};


#endif // FILES_CARGO_H
