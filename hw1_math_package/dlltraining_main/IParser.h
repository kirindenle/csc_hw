#pragma once
#include <string>
#include "expression.h"

namespace math_pack
{
    class IParser
    {
    public:
        virtual ~IParser() = default;
        virtual std::unique_ptr<math_pack::Expression>
            buildExpression(const std::string & s) = 0;
    };
}
