#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <fstream> // Used for file IO
#include <deque>
#include <iterator>

using namespace std;

// ---------- MACROS ----------
// This is a macro constant that will replace
// PI with 3.14159 in the code before execution
#define PI 3.14159

// This is a macro function that will do the same with
// a function
#define AREA_CIRCLE(radius) (PI * (pow(radius, 2)))

// ----- TEMPLATE FUNCTIONS -----

// We use templates to create functions or classes
// that can work with many types
// Templates differ from function overloading in that
// instead of having a function that does similar
// things with different objects a template does the
// same thing with different objects

// This says this is a function template that generates
// functions that except 1 parameter
template <typename T>
void Times2(T val)
{
    cout << val << " * 2 = " << val * 2 << endl;
}

// Receive multiple parameters and return a value
template <typename T>
T Add(T val, T val2)
{
    return val + val2;
}

// Work with chars and strings
template <typename T>
T Max(T val, T val2)
{
    return (val < val2) ? val2 : val;
}

// ----- TEMPLATE CLASSES -----

// Template classes are classes that can work with
// different data types

// You can define that you may receive parameters
// with different types, but they don't have to
// be different
template <typename T, typename U>
class Person
{
public:
    T height;
    U weight;
    static int numOfPeople;
    Person(T h, U w)
    {
        height = h, weight = w;
        numOfPeople++;
    }
    void GetData()
    {
        cout << "Height : " << height << " and Weight : " << weight << endl;
    }
};

// You have to initialize static class members
template <typename T, typename U>
int Person<T, U>::numOfPeople;

int runContainers()
{
    cout << "Circle Area : " << AREA_CIRCLE(5) << endl;

    // ----- TEMPLATE FUNCTIONS -----
    // The template function can receive ints or floats
    Times2(5);
    Times2(5.3);

    // Multiple parameters and returned value
    cout << "5 + 4 = " << Add(5, 4) << endl;
    cout << "5.5 + 4.6 = " << Add(5.5, 4.6) << endl;

    // Get biggest value
    cout << "Max 4 or 8 = " << Max(4, 8) << endl;
    cout << "Max A or B = " << Max('A', 'B') << endl;
    cout << "Max Dog or Cat = " << Max("Dog", "Cat") << endl;

    // ----- END OF TEMPLATE FUNCTIONS -----

    // ----- TEMPLATE CLASSES -----

    // When creating the object you must define the
    // data types used
    Person<double, int> mikeTyson(5.83, 216);
    mikeTyson.GetData();

    // You access static values using the object
    // and not the class
    cout << "Number of people : " << mikeTyson.numOfPeople << endl;

    // ----- END OF TEMPLATE CLASSES -----

    // ----- CONTAINERS -----
    // We have already seen the STL container vector
    // There are many other special ways of storing data

    // ----- DOUBLE ENDED QUEUE -----

    // A double ended queue (Deck) is a dynamic array that can
    // be expanded or contracted on both ends
    deque<int> nums = {1, 2, 3, 4};
    nums.push_front(0);
    nums.push_back(5);
    for (int x : nums)
        cout << x << endl;

    // You can access index values, but they are costly
    // because values aren't stored contigously, but
    // instead use multiple arrays
    cout << nums[0] << endl;

    // ----- END DOUBLE ENDED QUEUE -----

    // ----- ITERATORS -----
    // Iterators are used to point at container
    // memory locations
    vector<int> nums2 = {1, 2, 3, 4};

    // Define an iterator as the same type
    vector<int>::iterator itr;

    // Refer to the vectors begin and end while
    // incrementing the iterator
    for (itr = nums2.begin();
         itr < nums2.end();
         itr++)
    {

        // Get value at the pointer
        cout << *itr << endl;
    }

    // You can also increment a set number of spaces
    // Create an iterator and point it at the beginning
    // of the vector
    vector<int>::iterator itr2 = nums2.begin();

    // Advance 2 spaces
    advance(itr2, 2);
    cout << *itr2 << endl;

    // Next works like advance, but it returns an
    // iterator
    auto itr3 = next(itr2, 1);
    cout << *itr3 << endl;

    // Previous moves a set number of indexes and
    // returns an iterator
    auto itr4 = prev(itr2, 1);
    cout << *itr4 << endl;

    // You can also insert at a defined index
    vector<int> nums3 = {1, 4, 5, 6};
    vector<int> nums4 = {2, 3};
    auto itr5 = nums3.begin();
    advance(itr5, 1);
    copy(nums4.begin(), nums4.end(),
         inserter(nums3, itr5));

    for (int &i : nums3)
        cout << i << endl;

    return 0;
}