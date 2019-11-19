#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <fstream> // Used for file IO

using namespace std;

// 1. Created to store as a variable and to
// pass into other functions
double MultBy2(double num)
{
    return num * 2;
}

// 2. Functions can receive other functions
// the first double is the return type followed
// by the data types for the parameter
double DoMath(function<double(double)> func, double num)
{
    return func(num);
}

// 3. You can store functions in a vector
double MultBy3(double num)
{
    return num * 3;
}

int main()
{
    // 1. You can store functions as variables
    auto times2 = MultBy2;
    cout << "5 * 2 = " << times2(5) << endl;

    // 2. Pass a function into a function
    cout << "6 * 2 = " << DoMath(times2, 6) << endl;

    // 3. You can store functions in a vector
    // Create a vector using the function parameters
    // and then load the functions into the vector
    vector<function<double(double)>> funcs(2);
    funcs[0] = MultBy2;
    funcs[1] = MultBy3;
    cout << "2 * 10 = " << funcs[0](10) << endl;

    return 0;
}