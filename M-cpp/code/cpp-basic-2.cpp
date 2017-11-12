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
    Echoer e0 = Echoer(0);
    {
        Echoer e1 = Echoer(1);
    }

    if (1)
        Echoer e2 = Echoer(2);

    int i;
    for (i = 3; i < 6; i++)
        Echoer ei = Echoer(i);

    return 0;
}
