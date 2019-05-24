#pragma once
#include <vector>

namespace math_pack
{
    typedef double(*MathFunction)(std::vector<double> &);

    struct NArgsFunc
    {
        MathFunction f;
        int nArgs;
    };
}