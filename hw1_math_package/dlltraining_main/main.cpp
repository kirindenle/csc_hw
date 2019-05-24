// Math package 
#include <iostream>
#include <string>
#include "parser.h"
#include "MyExpressions.h"
#include "registrator.h"
#include "DLLLoader.h"

using namespace math_pack;

int main(int args, char * argv[])
{
    Registrator registrator;
    DllLoader dllLoader(registrator);

    for (int i = 1; i < args; ++i)
    {
        dllLoader.loadDll(argv[i]);
    }

    std::unique_ptr<IParser> parser = std::make_unique<BasicParser>(registrator);

    std::string input;

    std::getline(std::cin, input);

    auto expression = parser->buildExpression(input);

    std::cout << expression->run() << std::endl;

    return 0;
}