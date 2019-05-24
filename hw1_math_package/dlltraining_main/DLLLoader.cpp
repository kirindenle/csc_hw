#include "DLLLoader.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace  math_pack;

DllLoader::~DllLoader()
{
    for(auto lib : loaded_libs)
    {
        FreeLibrary(static_cast<HMODULE>(lib));
    }
}

DllLoader::DllLoader(Registrator& r)
{
    reg = &r;
}

void DllLoader::loadDll(const char * dllName)
{
    const auto libInstance = LoadLibrary(TEXT(dllName));
    if (libInstance == nullptr)
    {
        std::cerr << "Can't load library: " << dllName << std::endl;
        return;
    }

    loaded_libs.push_back(libInstance);

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

    for (std::string exportLine; std::getline(exportStr, exportLine); )
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

        reg->addFunction(parseName, func, nArgs);
    }
}
