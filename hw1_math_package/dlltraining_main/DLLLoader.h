#pragma once
#include <vector>
#include "registrator.h"

namespace math_pack
{
    // loads dll which has function: const char * exportInfo()
    // this function must return string made of lines in format 
    // "{name_of_function_in_code} {name_of_function_in_use} {number_of_arguments}\n"
    class DllLoader
    {
    public:
        DllLoader(Registrator & r);
        ~DllLoader();
        void loadDll(const char * dllName);
    private:
        std::vector<void *> loaded_libs;
        Registrator * reg;
    };
}
