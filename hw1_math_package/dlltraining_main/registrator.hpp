#pragma once
#include "expression.hpp"
#include <map>

// Register names of loaded math functions
class Registrator
{
public:
    bool addFunction(const std::string & name, MathFunction f, int n_args)
    {
        NArgsFunc tmp = { f, n_args };
        return functions_.insert(std::make_pair(name, tmp)).second;
    }

    bool replaceFunction(const std::string & name, MathFunction f, int n_args)
    {
        NArgsFunc tmp = { f, n_args };
        return functions_.insert_or_assign(name, tmp).second;
    }

    bool getFunction(const std::string & name, NArgsFunc & result)
    {
        auto it = functions_.find(name);
        if (it != functions_.end())
        {
            result = (*functions_.find(name)).second;
            return true;
        }
        return false;
    }

    static Registrator & instance()
    {
        static Registrator s;
        return s;
    }

    Registrator(Registrator &) = delete;
    Registrator(Registrator &&) = delete;
    Registrator& operator=(Registrator &) = delete;
    Registrator& operator=(Registrator &&) = delete;

private:
    Registrator() = default;
    ~Registrator() = default;

    std::map<std::string, NArgsFunc> functions_;
};