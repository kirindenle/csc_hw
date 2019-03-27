#include "parser.h"
#include "MyExpressions.h"
#include <vector>
#include <string>
#include <iostream>
#include <cctype>

using namespace default_expression;

StringTree parse(const std::string & s)
{
    std::vector<StringTree> stack;

    size_t i = 0;
    bool inLeaf;
    while (i < s.size())
    {
        //std::cerr << s[i] << std::endl;
        inLeaf = false;
        if (std::isblank(s[i]) || s[i] == '(' || s[i] == ',')
        {
            //std::cerr << s[i] << std::endl;
            ++i;
        }
        else if (std::isalpha(s[i]))
        {
            std::string name{};
            while (std::isalpha(s[i]))
            {
                name.push_back(s[i++]);
            }
            //std::cerr << name << std::endl;
            stack.emplace_back();
            stack.back().s = name;
        }
        else if (std::isdigit(s[i]))
        {
            std::string number{};
            while (std::isdigit(s[i]) || s[i] == '.')
            {
                number.push_back(s[i++]);
            }
            stack.emplace_back();
            stack.back().s = number;

            //std::cerr << number << std::endl;

            inLeaf = true;
        }
        else if (s[i] == ')')
        {
            ++i;
            inLeaf = true;
        }
        else
        {
            std::cerr << "Parsing Error: Bad symbol " << s[i] << " in " << s << std::endl;
            break;
        }

        /*for (const auto & ss : stack)
        {
            std::cerr << ss.s << ";";
        }
        std::cerr << std::endl;*/

        if (inLeaf)
        {
            if (stack.size() == 1)
            {
                return stack.back();
            }

            if (stack.empty())
            {
                std::cerr << "Parsing Error: Empty stack. " << s << std::endl;
            }

            auto oldStackBack = std::move(stack.back());

            stack.pop_back();

            stack.back().children.emplace_back(std::move(oldStackBack));
        }
    }

    std::cerr << "Parsing Error in: " << s << std::endl;

    return {};
}

std::unique_ptr<Expression> 
stringTreeToExpression(
    const StringTree & stree, 
    Registrator & registrator)
{
    if (isalpha(stree.s[0]))
    {
        NArgsFunc func{};

        if (!registrator.getFunction(stree.s, func))
        {
            std::cerr << "ERROR. Can't make expression. No such function: " <<
                stree.s << std::endl;
            return nullptr;
        }

        if (func.nArgs >= 0 && func.nArgs != stree.children.size())
        {
            std::cerr << "ERROR. Can't make expression. Wrong number of args in function: " <<
                stree.s << "Get " << stree.children.size() << ". Must be " << func.nArgs << std::endl;
            return nullptr;
        }

        std::vector<std::unique_ptr<Expression>> resultArgs;
        resultArgs.resize(func.nArgs);
        for (int i = 0; i < resultArgs.size(); ++i)
        {
            resultArgs[i] = stringTreeToExpression(stree.children[i], registrator);
            if (resultArgs[i] == nullptr)
            {
                return nullptr;
            }
        }
        return std::make_unique<MyFunction>(func, std::move(resultArgs));
    }
    if (isdigit(stree.s[0]))
    {
        return std::make_unique<MyNumber>(std::stod(stree.s));
    }

    std::cerr << "ERROR. Can't make expression. Unknown word: " << stree.s << std::endl;
    return nullptr;
}