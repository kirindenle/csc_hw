#pragma once

namespace math_pack
{
    class Expression
    {
    public:
        virtual ~Expression() = default;
        virtual double run() = 0;
    };
}