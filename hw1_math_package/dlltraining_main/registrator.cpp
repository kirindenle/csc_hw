#include "registrator.h"
#include "func_types.h"
#include <string>
#include <map>

bool Registrator::addFunction(const std::string & name, MathFunction f, int n_args)
{
    NArgsFunc tmp = { f, n_args };
    return functions_.insert(std::make_pair(name, tmp)).second;
}

bool Registrator::replaceFunction(const std::string & name, MathFunction f, int n_args)
{
    NArgsFunc tmp = { f, n_args };
    return functions_.insert_or_assign(name, tmp).second;
}

bool Registrator::getFunction(const std::string & name, NArgsFunc & result)
{
    auto it = functions_.find(name);
    if (it != functions_.end())
    {
        result = (*functions_.find(name)).second;
        return true;
    }
    return false;
}

Registrator & Registrator::instance()
{
    static Registrator s;
    return s;
}