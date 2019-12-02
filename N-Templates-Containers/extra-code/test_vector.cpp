#include <iostream>
#include "vector.h"

int main()
{
    myvector<int> v;
    v.push_back(1);
    v.push_back(3);

    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << std::endl;
    } 

    return 0;
}
