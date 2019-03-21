#pragma once
#include <vector>
#include <string>
#include "expression.hpp"
#include "registrator.hpp"

struct StringTree
{
    std::string s;
    std::vector<StringTree> children;
};

// parses string in format:
// s = name(s,...,s) | number
// spaces between elements are allowed
StringTree parse(const std::string & s);

// takes tree of string with names of numbers and make it to expression
std::unique_ptr<Expression> 
stringTreeToExpression(
    const StringTree & stree, 
    Registrator & registrator);