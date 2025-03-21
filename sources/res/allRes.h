#ifndef HEADER_ALL2_RES_H
#define HEADER_ALL2_RES_H

/// myXXD: "allRes.h"
///----------------------------------------------------------------------------|
/// Тут все ваши ресурсы.
///----------------------------------------------------------------------------:
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace res
{
    struct Unit;

    std::string info(const std::string_view what = "");

    std::ostream& operator<<(std::ostream&, const             res::Unit  &);
    std::ostream& operator<<(std::ostream&, const std::vector<res::Unit*>&);

    struct Unit
    {   const size_t           len ;
        const unsigned char*   data;
        const std::string_view path;

        static std::vector<Unit*> get(const std::string_view);

        ///---------------|
        /// Тест разраба. |
        ///---------------:
        static void test()
        {
            std::cout << info() << '\n';
            std::vector<res::Unit*>  res = Unit::get("");
            for(const auto& e : res)
            {   for(unsigned i = 0; i < 0x4FF && i < e->len; ++i)
                {   std::cout << char(e->data[i]);
                }   std::cout << '\n';
            }
        }
    };
}

extern unsigned char Document_1_txt[];
const size_t Document_1_txt_len = 150;

extern unsigned char Document_2_txt[];
const size_t Document_2_txt_len = 149;

extern unsigned char Document_3_txt[];
const size_t Document_3_txt_len = 152;


#endif // header guard


