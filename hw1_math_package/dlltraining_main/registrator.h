#pragma once
#include "func_types.h"
#include <map>

namespace math_pack
{
    // Register names of loaded math functions
    class Registrator
    {
    public:
        bool addFunction(const std::string & name, MathFunction f, int n_args);
        bool replaceFunction(const std::string & name, MathFunction f, int n_args);
        bool getFunction(const std::string & name, NArgsFunc & result) const;
    private:
        std::map<std::string, NArgsFunc> functions_;
    };
}