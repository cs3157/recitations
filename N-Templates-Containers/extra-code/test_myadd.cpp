#include <iostream>
//#include "myadd.h"

struct Complex 
{
//...
};

int myadd(int x, int y)
{
    return x + y;
}

double myadd(double x, double y)
{
    return x + y;
}

Complex myadd(Complex x, Complex y)
{
    return x + y;
}

int main()
{
    std::cout << "1 + 2 = " << myadd(1, 2) << std::endl;
    std::cout << "1.3 + 2.1 = " << myadd(1.3, 2.1) << std::endl;

    return 0;
}
