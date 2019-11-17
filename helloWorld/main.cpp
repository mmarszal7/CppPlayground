#include <iostream>
#include <vector>
#include <string>
#include "externalFunction/circle.h"

using namespace std;

int main()
{
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code!", "and the C++ extension!"};
    cout << "Hello" << endl;

    Circle circle(5);
    cout << circle.GetArea() << endl;
    return 0;
}