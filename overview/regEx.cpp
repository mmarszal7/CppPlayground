#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <ctime>

#include <regex>

using namespace std;

int main(int argc, char **argv)
{

    // The string to search
    string str = "The ape was at the apex";

    // We want to match for ape with or
    // without a space after it
    regex reg("(ape)[^ ]?");

    // Provides useful function when you
    // are searching a string
    smatch matches;

    // If there is a match for the regex
    if (regex_search(str, matches, reg) == true)
    {

        // Output the number of matches
        cout << matches.size() << " Matches" << endl;

        // Cycle through the matches
        while (regex_search(str, matches, reg))
        {

            // Get the match
            cout << matches.str(1) << endl;
            // Get the index
            cout << "At Index " << matches.position(1) << endl;

            // Eliminate the previous match and create
            // a new string to search
            str = matches.suffix().str();
        }
    }
    return 0;
}