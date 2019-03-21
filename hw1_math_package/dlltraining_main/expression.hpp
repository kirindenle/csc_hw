#pragma once
#include <vector>
#include <memory>

typedef double(*MathFunction)(std::vector<double>);

struct NArgsFunc
{
    MathFunction f;
    int nArgs;
};

class Expression
{
public:
    virtual ~Expression() = default;
    virtual double run() = 0;
};

class MyFunction : public Expression
{
public:
    MyFunction(NArgsFunc f_, std::vector<std::unique_ptr<Expression>> && args_)
    {
        f = f_;
        args = std::move(args_);
    }

    double run() override
    {
        std::vector<double> argsValues;
        argsValues.resize(args.size());
        for (int i = 0; i < args.size(); ++i)
        {
            argsValues[i] = args[i]->run();
        }
        return f.f(argsValues);
    }

    NArgsFunc f;
    std::vector<std::unique_ptr<Expression>> args;
};

class MyNumber : public Expression
{
public:
    MyNumber(double num_) : num(num_) {}
    double run() override
    {
        return num;
    }
    double num;
};