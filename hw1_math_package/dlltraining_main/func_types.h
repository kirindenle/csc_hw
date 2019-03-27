#pragma once
#include <vector>

typedef double(*MathFunction)(std::vector<double>);

struct NArgsFunc
{
    MathFunction f;
    int nArgs;
};