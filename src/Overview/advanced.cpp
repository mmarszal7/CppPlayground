#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <fstream> // Used for file IO
#include <regex>
#include <algorithm>
#include <functional>

using namespace std;

// ---------- STRUCTS ----------

// Classes have default private fields and methods
// while structs have public
// Structs are used to model new data types, while
// classes model more complex real world objects
struct ShapeStruct
{
	// Variables are public by default
	double length, width;

	// Constructors are public by default
	ShapeStruct(double l = 1, double w = 1)
	{
		length = l;
		width = w;
	}

	// Structs can contain functions
	double Area()
	{
		return length * width;
	}

	// Structs can contain private members
private:
	int id;
};

// You can inherit from a struct
struct CircleStruct : ShapeStruct
{
	// Override the constructor
	// You also use this with structs
	CircleStruct(double width)
	{
		this->width = width;
	}

	// Override Area()
	double Area()
	{
		return 3.14159 * pow((width / 2), 2);
	}
};

// ---------- USED WITH LAMBDA EXPRESIONS ----------
vector<int> GenerateRandVec(int numOfNums,
	int min, int max);

// ---------- OPERATOR OVERLOADING ----------
// You can define custom operators just as you define functions
// This allows you to compare, perform calculations, etc.
// with your objects in custom ways

// Create a custom Box class with overloaded operators
class Box
{
public:
	double length, width, breadth;

	// Used to hold a string representation of a box
	string boxString;

	Box()
	{
		length = 1, width = 1, breadth = 1;
	}
	Box(double l, double w, double b)
	{
		length = l, width = w, breadth = b;
	}

	// You can define customer operators just like
	// you define functions
	// This is a unary operator because it operates
	// on 1 object
	// Other Unary Operators : --, *(pointer dereference),
	// -> (Member Selection), !, & (Address of), +, -
	Box& operator++()
	{
		length++;
		width++;
		breadth++;
		return *this;
	}

	// Creates a C string representation which is a
	// pointer to an array that is null terminated
	operator const char* ()
	{
		// Creates a stream that can be loaded with
		// characters that can then be accessed as
		// a string object
		ostringstream boxStream;
		boxStream << "Box : " << length << ", " << width << ", " << breadth;

		// Return a string representation of the stream
		boxString = boxStream.str();

		// Returns the pointer to the string array
		return boxString.c_str();
	}

	// Binary operators operate on 2 objects
	// +, -, *, /, %, ==, !=, >, <, >=, <=, &&, ||,
	// !, =, +=, -=, *=, /=, ^, [], &, |

	// Let's add boxes
	Box operator+(const Box& box2)
	{
		Box boxSum;
		boxSum.length = length + box2.length;
		boxSum.width = width + box2.width;
		boxSum.breadth = breadth + box2.breadth;
		return boxSum;
	}

	// Check for box equality
	bool operator==(const Box& box2)
	{
		return ((length == box2.length) &&
			(width == box2.width) &&
			(breadth == box2.breadth));
	}
};

int runAdvanced()
{
	// Create a struct
	ShapeStruct shape(10, 10);

	// Call a Struct function
	cout << "Square Area : " << shape.Area()
		<< endl;

	// Create a struct
	CircleStruct circle(10);

	// Call a Struct function
	cout << "Circle Area : " << circle.Area()
		<< endl;

	// You can initialize a struct or class using
	// an aggregate
	ShapeStruct rectangle{10, 15};
    cout << "Rectangle Area : " << rectangle.Area() << endl;

    // ---------- LAMBDA EXPRESSIONS ----------
    vector<int> vecVals = GenerateRandVec(10, 1, 50);

    // Lambda Expressions make it easy to perform list
    // operations in one line of code. You designate
    // them with []
    // Here we sort a vector
    sort(vecVals.begin(), vecVals.end(),
         [](int x, int y) { return x < y; });

    for (auto val : vecVals)
        cout << val << endl;

    cout << endl;

    // copy_if works like filter does in other languages
    // Here we keep only even values in a new vector
    vector<int> evenVecVals;

    copy_if(vecVals.begin(), vecVals.end(),
            back_inserter(evenVecVals),
            [](int x) { return (x % 2) == 0; });

    for (auto val : evenVecVals)
        cout << val << endl;

    // ----- SUM A LIST -----
    int sum = 0;

    // for_each cycles through all values
    // [&] captures all variables used
    // in the body of the lambda by reference
    for_each(vecVals.begin(), vecVals.end(),
             [&](int x) { sum += x; });

    cout << "SUM : " << sum << endl;

    // ----- RECURSIVE LAMBDA FUNCTIONS -----

    // Recursive Lambda to calculate Fibonacci Numbers
    function<int(int)> Fib =
        [&Fib](int n) { return n < 2 ? n : Fib(n - 1) + Fib(n - 2); };

    // Fib(0) = 0
    // Fib(1) = 1
    // Fib(2) = 1
    // Fib(3) = 2
    // Fib(4) = 3
    cout << "Fib 4 : " << Fib(4) << endl;

    // ---------- OPERATOR OVERLOADING ----------

    Box box(10, 10, 10);

    // Will increment all values in the box by 1
    ++box;
    cout << box << endl;

    // Add boxes
    Box box2(5, 5, 5);
    cout << "Box1 + Box2 = " << box + box2 << endl;

    // Check equality
    cout << "Are boxes equal : " << (box == box2) << endl;

    // ---------- FILE IO ----------
    ofstream writeToFile;
    ifstream readFromFile;
    string txtToWrite = "";
    string txtFromFile = "";

    // We open the file by providing a name and then either
    // ios::app : Append to the end of the file
    // ios::trunc : If the exists delete content
    // ios::in : Open file for reading
    // ios::out : Open file for writing
    // ios::ate : Open writing and move to the end of the file
    writeToFile.open("test.txt", ios_base::out |
                                     ios_base::trunc);

    if (writeToFile.is_open())
    {
        // You can write with the stream insertion operator
        writeToFile << "Beginning of File\n";

        // You can write data in a string
        cout << "Enter data to write : ";
        getline(cin, txtToWrite);
        writeToFile << txtToWrite;

        // Close the file
        writeToFile.close();
    }

    // Open the file for reading
    readFromFile.open("test.txt", ios_base::in);

    if (readFromFile.is_open())
    {

        // Read text from file
        while (readFromFile.good())
        {
            getline(readFromFile, txtFromFile);

            // Print text from file
            cout << txtFromFile << endl;
        }
        readFromFile.close();
    }

    return 0;
}

// ---------- USED WITH LAMBDA EXPRESIONS ----------

vector<int> GenerateRandVec(int numOfNums,
                            int min, int max)
{
    vector<int> vecValues;
    srand(time(NULL));
    int i = 0, randVal = 0;
    while (i < numOfNums)
    {
        randVal = min + rand() % ((max + 1) - min);
        vecValues.push_back(randVal);
        i++;
    }
    return vecValues;
}