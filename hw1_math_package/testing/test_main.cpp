#include <algorithm>
#include <vector>
#include <iostream>
#include "../dlltraining_main/registrator.h"
#include "../dlltraining_main/parser.h"

Registrator & registrator = Registrator::instance();

double mySum(std::vector<double> v)
{
    return v[0] + v[1];
}

double myMax(std::vector<double> v)
{
    return std::max(v[0], v[1]);
}

double runString(const std::string & str)
{
    return stringTreeToExpression(parse(str), registrator)->run();
}

bool test1()
{
    registrator.addFunction("sum", mySum, 2);

    double result = runString("sum(1,2)");

    return result == 1.0 + 2.0;
}

bool test2()
{
    registrator.addFunction("max", mySum, 2);

    double result = runString("max(1,2)");

    return result == std::max(1.0, 2.0);
}

bool test3()
{
    double result = runString("max (10.0, sum (2.0, 3.5))");

    return result == std::max(10.0, 2.0 + 3.5);
}

bool test4()
{
    double result = runString("max (10.0, sum (2.0, sum (5.1, 4.5)))");

    return result == std::max(10.0, 2.0 + (5.1 + 4.5));
}

int main()
{
    
    registrator.addFunction("max", myMax, 2);

    auto v = { test1, test2, test3, test4 };

    int i = 0;
    for (auto f : v)
    {
        std::cout << "TEST " << i << ": " << (f() ? "OK" : "ERROR") << std::endl;
        ++i;
    }

    return 0;
}