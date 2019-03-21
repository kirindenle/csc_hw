// Math package 

#include <windows.h> 
#include <iostream>
#include <string>
#include <sstream>
#include "parser.h"
#include "expression.hpp"
#include "registrator.hpp"

// loads dll which has function: const char * exportInfo()
// this function must return string made of lines in format 
// "{name_of_function_in_code} {name_of_function_in_use} {number_of_arguments}\n"
void loadDll(const char * dllName, Registrator & registrator)
{
    const auto libInstance = LoadLibrary(TEXT(dllName));
    if (libInstance == nullptr)
    {
        std::cerr << "Can't load library: " << dllName << std::endl;
        return;
    }

    typedef const char*(*ExportFuncType)();

    const auto exportFuncName = "exportInfo";

    const auto dllExportInfo = reinterpret_cast<ExportFuncType>(
        GetProcAddress(libInstance, exportFuncName));

    if (dllExportInfo == nullptr)
    {
        std::cerr << "Can't load library: " << dllName << 
            ". No function " << exportFuncName << std::endl;
        return;
    }

    std::stringstream exportStr(dllExportInfo());

    for(std::string exportLine; std::getline(exportStr, exportLine); )
    {
        std::stringstream exportLineStream(exportLine);

        std::string realName;
        std::string parseName;
        int nArgs;

        exportLineStream >> realName >> parseName >> nArgs;

        const auto func = reinterpret_cast<MathFunction>(
            GetProcAddress(libInstance, realName.c_str()));

        if (func == nullptr)
        {
            std::cerr << "Can't load function " << realName << 
                "(" << parseName << ") from " << dllName << std::endl;
            continue;
        }

        registrator.addFunction(parseName, func, nArgs);
    }
}

int main(int args, char * argv[])
{
    auto& regInstance = Registrator::instance();

    for (int i = 1; i < args; ++i)
    {
        loadDll(argv[i], regInstance);
    }

    std::string input;

    std::getline(std::cin, input);

    StringTree s = parse(input);

    auto expression = stringTreeToExpression(s, regInstance);

    std::cout << expression->run() << std::endl;

    return 0;
}