#include <cstdio>
#include <iostream>

using namespace std;

class Echoer {
public:
    int id;
    Echoer(int eid) {
        id = eid;
        cout << "constructor: " << id << endl;
    }

    ~Echoer() {
        cout << "destructor: " << id << endl;
    }

    void echo() {
        cout << "echoer: " << id << endl;
    }
};

int main(void)
{
    Echoer e0 = Echoer(0); // created in main() block, not destroyed until end

    {   // new block
        Echoer e1 = Echoer(1);
    }   // end block, e1 destructor called

    if (1)
        Echoer e2 = Echoer(2);
        // there is an implicit block at the end of one-liner conditionals
        // even if there is no end curly brace

    int i;
    for (i = 3; i < 6; i++)
        Echoer ei = Echoer(i);
        // same with one-liner looping statements
        // each ei will be destroyed before the next iteration
        
    return 0;
}   // end of main() block, e0 destroyed here
