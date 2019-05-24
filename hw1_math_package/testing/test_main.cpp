#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include "../dlltraining_main/registrator.h"
#include "../dlltraining_main/parser.h"

using namespace math_pack;

Registrator registrator;
std::unique_ptr<IParser> parser = std::make_unique<BasicParser>(registrator);

double mySum(std::vector<double> & v)
{
    return v[0] + v[1];
}

double myMax(std::vector<double> & v)
{
    return std::max(v[0], v[1]);
}

double runString(const std::string & str)
{
    return parser->buildExpression(str)->run();
}

bool test1()
{
    registrator.addFunction("sum", mySum, 2);

    double result = runString("sum(1,2)");

    assert(result == 1.0 + 2.0);

    return true;
}

bool test2()
{
    registrator.addFunction("max", myMax, 2);

    double result = runString("max(1,2)");

    assert(result == std::max(1.0, 2.0));

    return true;
}

bool test3()
{
    assert(runString("max (10.0, sum (2.0, 3.5))") == std::max(10.0, 2.0 + 3.5));
    return true;
}

bool test4()
{
    assert(runString("max (10.0, sum (2.0, sum (5.1, 4.5)))") == std::max(10.0, 2.0 + (5.1 + 4.5)));
    return true;
}

int main()
{
    auto v = { test1, test2, test3, test4 };

    int i = 0;
    for (auto f : v)
    {
        std::cout << "TEST " << i << ": " << (f() ? "OK" : "ERROR") << std::endl;
        ++i;
    }

    return 0;
}