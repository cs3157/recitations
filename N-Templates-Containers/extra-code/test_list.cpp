#include <iostream>
#include <list>

template <class List>
double some_func(const std::list<double>& l1, const List& l2)
{
    // do something complicated ...
    return l1.front();
}

int main()
{
    char arr1[] = "hello";
    char arr2[] = "world";
    // This list contains nodes with data pointing to char array (string)
    std::list<char*> list; 
    list.push_front(arr2);
    list.push_front(arr1);

    double x[] = {1., 2.};
    // This list contains nodes with data pointing to a double
    std::list<double> list2;
    list2.push_front(x[0]);
    list2.push_front(x[1]);

    //double value = some_func(list, list2);  // now this raises compiler error!
    double value = some_func(list2, list);  // now this raises compiler error!
    std::cout << "value: " << value << std::endl;
    return 0;
}
