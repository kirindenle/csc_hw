#pragma once

namespace default_expression
{
    class Expression
    {
    public:
        virtual ~Expression() = default;
        virtual double run() = 0;
    };
}