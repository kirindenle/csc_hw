#pragma once
#include "func_types.h"
#include <map>

// Register names of loaded math functions
class Registrator
{
public:
    bool addFunction(const std::string & name, MathFunction f, int n_args);
    bool replaceFunction(const std::string & name, MathFunction f, int n_args);
    bool getFunction(const std::string & name, NArgsFunc & result);
    static Registrator & instance();

    Registrator(Registrator &) = delete;
    Registrator(Registrator &&) = delete;
    Registrator& operator=(Registrator &) = delete;
    Registrator& operator=(Registrator &&) = delete;
private:
    Registrator() = default;
    ~Registrator() = default;

    std::map<std::string, NArgsFunc> functions_;
};