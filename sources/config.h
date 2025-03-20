#ifndef CONFIG_H
#define CONFIG_H
/// "config.h"
///----------------------------------------------------------------------------|
/// Config
///--------------------------------------------------------------------- Config:
#include "debug.h"

namespace cfg
{
    using Validate = std::function<unsigned(std::string_view)>;

    ///------------------------------------------------------------------------|
    /// AgrVal
    ///----------------------------------------------------------------- AgrVal:
    struct AgrVal
    {   const std::string_view       key;
        const std::string_view byDefault;
        Validate                validate;
        std::string_view             val;
        bool            isDefault {true};
        unsigned         n{(unsigned)-1};
    };

    using CfgBD = std::map<std::string_view, AgrVal*>;

    ///------------------------------------------------------------------------|
    /// Args
    ///------------------------------------------------------------------- Args:
    struct  Args : CfgBD
    {       Args()
            {
            }

        std::string set(int argc, const char* argv[])
        {   std::stringstream ss;
            for(int i = 1; i < argc; ++i)
            {   if(!isArg(argv[i]))
                {   ss << "ERROR ARGUMENT: " << argv[i] << '\n';
                }
            }
            return ss.str() + info();
        }

        std::string info() const
        {   std::string inf   {"\nКонфиг ---------------:\n"};
            std::string byDef {"Дефолтные:\n"};
            std::string byUser{"Юзерские:\n" };

            for(auto&[mkey, mval] : *this)
            {
                auto makeTxt
                {   [&mkey, &mval]()->std::string
                    {   std::stringstream ss;
                        ss  << "  "  << std::setw(12) << mkey
                            << " : " << mval->val     << '\n';
                        return ss.str();
                    }
                };

                if(mval->isDefault) byDef  += makeTxt();
                else                byUser += makeTxt();
            }
                    inf += byDef ;
                    inf += byUser;
            return  inf ;
        }

    private:
        bool isArg(const char* arg)
        {
            const auto&[akey, aval] = getKeyVal(arg);

            auto p =  find(akey);

            if (p == end()) return false;

            if((p->second->n = p->second->validate(aval)) != unsigned(-1))
            {
                p->second->val       = aval ;
                p->second->isDefault = aval == p->second->byDefault;

                return true;
            }
            return false;
        }

        using Str = std::string_view;
        const std::tuple<Str, Str> getKeyVal(Str arg) const
        {   if(const size_t pos = arg.find(':'); pos != std::string::npos)
            {   const size_t a = pos + 1;
                return {arg.substr(0, pos), arg.substr(a, arg.size() - a)};
            }
            return {"", ""};
        }

        ///---------------|
        /// Тест разраба. |
        ///---------------:
        TEST
        {   std::cout << "Run cfg::Args::test()\n\n";

            bool isGood{true};

            const char* test[]
            {   {"---"},{"true"},{"test:2042"}
            };

            Args args;
              ln(args.set(3, test))

            {   std::string_view s{"test:123"};
                const auto&[a, b] = args.getKeyVal(s);
                isGood &= a == "test";
                isGood &= b == "123" ;
            }
            {   std::string_view s{"testx:123"};
                const auto&[a, b] = args.getKeyVal(s);
                isGood &= a != "test";
                isGood &= b == "123" ;
            }
            {   std::string_view s{"test:123x"};
                const auto&[a, b] = args.getKeyVal(s);
                isGood &= a == "test";
                isGood &= b != "123" ;
            }

            const auto resultTest = isGood ? "isGood" : "ERROR";
            l(resultTest)
        }
    };

    ///------------------------------------------------------------------------|
    /// Config
    ///----------------------------------------------------------------- Config:
    struct  Config
    {       Config()
            {
            }

        ///-----------------------------|
        /// ...                         |
        ///-----------------------------:
        bool doIndex{true};

        bool checkText{false};
        unsigned   testa{333};

        std::string set(int argc, const char* argv[])
        {
            for(auto& e : argVals) args[e.key] = &e;

            std::string inf = args.set(argc,  argv);

            update();

            return inf;
        }

    private:
        Args args;

        inline static
        Validate fooBool = [](std::string_view val)
        {   if(val == "true" ) return 1;
            if(val == "false") return 0;
            return                   -1;
        };

        inline static
        Validate fooUint = [](std::string_view val)
        {   unsigned long res;
            try
            {   std::size_t  pos;
                res     = std::stoul(val.data(), &pos);
                if(pos != val.size()) return unsigned(-1);
            }
            catch(...)
            {   return unsigned(-1);
            }
            return unsigned(res);
        };

        AgrVal argVals[3]
        {   { "-doIndex"  , "true" , fooBool, "true" }
        //  { "checkText", "false", fooBool, "false"},
        //  { "testa"    , "2025" , fooUint, "2025" },
        };

        unsigned get(std::string_view s)
        {   if(const auto p = args.find(s); p != args.end())
            {   return    p->second->n;
            }
            throw(s.data());
        }

        void update()
        {   try
            {   //  checkText = get("checkText");
                //  testa     = get("testa");
                doIndex = get("-doIndex");

                std::cout << "Message::update(): GOOD!\n\n";
            }
            catch(const char* what)
            {   std::cout << "ERROR::update(): " << what << '\n';
            }
        }

        ///---------------|
        /// Тест разраба. |
        ///---------------:
        TEST
        {   std::cout << "Run cfg::Config::test()\n\n";

            const char* test[]
            {   {"---"},{"checkText:truex"},{"testa:222"},{"xisTree:true"}
            };

            const unsigned N = sizeof test / sizeof *test;

            Config  config;
                 ln(config.set(N, test))

                 l(config.checkText)
                 l(config.testa)

            l(fooUint("12345" ))
            l(fooUint("12345x"))
            l(fooUint("x12345"))
            l(fooBool("true"  ))
            l(fooBool("false" ))
            l(fooBool("truex" ))
        }
    };
}

extern cfg::Config config;

#endif // CONFIG_H
