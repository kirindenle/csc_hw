// The myPuts function writes a null-terminated string to
// the standard output device.

// The export mechanism used here is the __declspec(export)
// method supported by Microsoft Visual Studio, but any
// other export method supported by your development
// environment may be substituted.
#define EOF (-1)

#include <cmath>
#include <vector>


extern "C" {
    __declspec(dllexport) double Sum(std::vector<double> v)
    {
        return v[0] + v[1];
    }

    __declspec(dllexport) double Mul(std::vector<double> v)
    {
        return v[0] * v[1];
    }

    __declspec(dllexport) double Div(std::vector<double> v)
    {
        return v[0] / v[1];
    }

    __declspec(dllexport) double Minus(std::vector<double> v)
    {
        return v[0] - v[1];
    }

    __declspec(dllexport) double Pow(std::vector<double> v)
    {
        return pow(v[0], v[1]);
    }

    __declspec(dllexport) double Sqrt(std::vector<double> v)
    {
        return sqrt(v[0]);
    }

    __declspec(dllexport) double Sinus(std::vector<double> v)
    {
        return sin(v[0]);
    }

    __declspec(dllexport) double Cosinus(std::vector<double> v)
    {
        return cos(v[0]);
    }

    __declspec(dllexport) const char * exportInfo()
    {
        return 
           "Sum sum 2\n\
            Mul mul 2\n\
            Div div 2\n\
            Minus minus 2\n\
            Pow pow 2\n\
            Sqrt pow 1\n\
            Sinus sin 1\n\
            Cosinus cos 1\n";
    }
}
