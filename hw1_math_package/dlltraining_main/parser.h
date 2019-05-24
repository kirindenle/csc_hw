#pragma once
#include <vector>
#include <string>
#include "expression.h"
#include "registrator.h"
#include "IParser.h"

namespace math_pack
{
    // parses string in format:
    // s = name(s,...,s) | number
    // spaces between elements are allowed
    class BasicParser : public IParser
    {
        struct StringTree
        {
            std::string s;
            std::vector<StringTree> children;
        };
        StringTree parse(const std::string & s) const;
        // takes tree of string with names of numbers and make it to expression
        std::unique_ptr<math_pack::Expression>
            stringTreeToExpression(
                const StringTree & stree) const;
    public:
        explicit BasicParser(const Registrator &);
        std::unique_ptr<math_pack::Expression>
            buildExpression(const std::string & s) override;
    private:
        const Registrator * reg;
    };
}



