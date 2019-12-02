#include <iostream>
#include "myadd.h"

int main()
{
    std::cout << "1 + 2 = " << myadd(1, 2) << std::endl;
    std::cout << "1.3 + 2.1 = " << myadd(1.3, 2.1) << std::endl;

    return 0;
}
