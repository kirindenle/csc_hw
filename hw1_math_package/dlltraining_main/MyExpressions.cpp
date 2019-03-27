#include "expression.h"
#include "MyExpressions.h"

MyFunction::MyFunction(
    NArgsFunc f_, 
    std::vector<std::unique_ptr<Expression>> && args_) : f(f_), args(std::move(args_)) {}

double MyFunction::run()
{
    std::vector<double> argsValues;
    argsValues.resize(args.size());
    for (int i = 0; i < args.size(); ++i)
    {
        argsValues[i] = args[i]->run();
    }
    return f.f(argsValues);
}

MyNumber::MyNumber(double num_) : num(num_) {}

double MyNumber::run()
{
    return num;
}