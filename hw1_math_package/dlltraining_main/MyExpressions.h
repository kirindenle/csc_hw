#pragma once
#include "expression.h"
#include "func_types.h"
#include <memory>

namespace math_pack
{
    class NFunction : public math_pack::Expression
    {
    public:
        NFunction(NArgsFunc f_, std::vector<std::unique_ptr<Expression>> && args_);
        double run() override;

        NArgsFunc f;
        std::vector<std::unique_ptr<Expression>> args;
    };

    class Constant : public math_pack::Expression
    {
    public:
        Constant(double num_);
        double run() override;
        double num;
    };

}