#include "expression.h"
#include "MyExpressions.h"

using namespace math_pack;

NFunction::NFunction(
    NArgsFunc f_, 
    std::vector<std::unique_ptr<Expression>> && args_) : f(f_), args(std::move(args_)) {}

double NFunction::run()
{
    std::vector<double> argsValues;
    argsValues.resize(args.size());
    for (int i = 0; i < args.size(); ++i)
    {
        argsValues[i] = args[i]->run();
    }
    return f.f(argsValues);
}

Constant::Constant(double num_) : num(num_) {}

double Constant::run()
{
    return num;
}