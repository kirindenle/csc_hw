#pragma once
#include "expression.h"
#include "func_types.h"
#include <memory>

class MyFunction : public default_expression::Expression
{
public:
    MyFunction(NArgsFunc f_, std::vector<std::unique_ptr<Expression>> && args_);
    double run() override;

    NArgsFunc f;
    std::vector<std::unique_ptr<Expression>> args;
};

class MyNumber : public default_expression::Expression
{
public:
    MyNumber(double num_);
    double run() override;
    double num;
};