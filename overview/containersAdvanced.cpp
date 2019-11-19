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
#include <deque>
#include <list>
#include <forward_list>

bool isEven(const int &val)
{
    return (val % 2) == 0;
}

int main()
{

    // Contains data stored in order

    // ---------- DEQUES ----------

    // A deque (Deck) is a dynamic array like vectors
    // except it also allows for insertion or deletion
    // from the front
    deque<int> deq1;

    // Add to the end and front
    deq1.push_back(5);
    deq1.push_front(1);

    // Add values with assign
    deq1.assign({11, 12});

    // Get the size
    cout << "Size : " << deq1.size()
         << endl;

    // Access by index
    cout << deq1[0] << endl;
    cout << deq1.at(1) << endl;

    // Add at an index using an iterator
    deque<int>::iterator it = deq1.begin() + 1;
    deq1.insert(it, 3);

    // Add multiple values
    int tempArr[5] = {6, 7, 8, 9, 10};
    deq1.insert(deq1.end(), tempArr, tempArr + 5);

    // Erase at an index
    deq1.erase(deq1.end());

    // Erase 1st 2 elements
    deq1.erase(deq1.begin(), deq1.begin() + 2);

    // Pop first value
    deq1.pop_front();

    // Pop last
    deq1.pop_back();

    // Create a deque with 2 50s
    deque<int> deq2(2, 50);

    // Swap values in deques
    deq1.swap(deq2);

    // Delete all values
    deq1.clear();

    // Cycle through the deque
    for (int i : deq1)
        cout << i << endl;

    // ---------- END DEQUES ----------

    // ---------- LIST ----------
    // Lists are the most efficient at inserting,
    // moving and extracting elements, but lack
    // direct access to elements

    // Add values
    int arr[5] = {1, 2, 3, 4, 5};
    list<int> list1;
    list1.insert(list1.begin(), arr, arr + 5);

    // Adding values with assign
    list1.assign({10, 20, 30});

    // Add to end and front
    list1.push_back(5);
    list1.push_front(1);

    // Get the size
    cout << "Size : " << list1.size()
         << endl;

    // Can't access index
    // cout << list1[0] << endl;

    // You can access the index with an iterator
    list<int>::iterator it2 = list1.begin();
    advance(it2, 1);
    cout << "2nd Index : " << *it2 << endl;

    // Insert at an index
    it2 = list1.begin();
    list1.insert(it2, 8);

    // Erase at an index
    list1.erase(list1.begin());

    // Erase 1st 2 elements
    it2 = list1.begin();
    list<int>::iterator it3 = list1.begin();
    advance(it3, 2);
    list1.erase(it2, it3);

    // Pop first value
    list1.pop_front();

    // Pop last
    list1.pop_back();

    // Create another list
    int arr2[6] = {10, 9, 8, 7, 6, 6};
    list<int> list2;
    list2.insert(list2.begin(), arr2, arr2 + 5);

    // Sort the list
    list2.sort();

    // Reverse the list
    list2.reverse();

    // Remove duplicates
    list2.unique();

    // Remove a value
    list2.remove(6);

    // Remove if a condition is true
    list2.remove_if(isEven);

    // Merge lists
    list1.merge(list2);

    for (int i : list2)
        cout << i << endl;

    cout << endl;

    // Cycle through the list
    for (int i : list1)
        cout << i << endl;

    cout << endl;

    // ---------- END LIST ----------

    // ---------- FORWARD_LIST ----------
    // A forward list is like a list, but each list
    // item only has a link to the next item in the
    // list and not to the item that proceeds it.

    // This make them the quickest of the sequence
    // containers

    forward_list<int> fl1;

    // Assign values
    fl1.assign({1, 2, 3, 4});

    // Push and pop front
    fl1.push_front(0);
    fl1.pop_front();

    // Get 1st
    cout << "Front : " << fl1.front();

    // Get iterator for 1st element
    forward_list<int>::iterator it4 = fl1.begin();

    // Insert after 1st element
    it4 = fl1.insert_after(it4, 5);

    // Delete just entered 5
    it4 = fl1.erase_after(fl1.begin());

    // Place in 1st position
    fl1.emplace_front(6);

    // Remove a value
    fl1.remove(6);

    // Remove if a condition is true
    fl1.remove_if(isEven);

    forward_list<int> fl2;
    fl2.assign({9, 8, 7, 6, 6});

    // Remove duplicates
    fl2.unique();

    // Sort
    fl2.sort();

    // Reverse
    fl2.reverse();

    // Merge lists
    fl1.merge(fl2);

    // Clear
    fl1.clear();

    for (int i : fl1)
        cout << i << endl;

    cout << endl;

    for (int i : fl2)
        cout << i << endl;

    // ---------- END FORWARD_LIST ----------

    // ----- ASSOCIATIVE CONTAINERS -----
    // Associative containers store sorted data
    // which makes insertion slower, but searching
    // faster

    // ----- SET -----
    // Sets store unique sorted values using a key
    set<int> set1{5, 4, 3, 2, 1, 1};
    cout << "Size : " << set1.size() << endl;

    // Insert value
    set1.insert(0);

    // Subscript operator doesn't work
    // cout << set1[0] << endl;

    // Get values with an iterator
    set<int>::iterator it = set1.begin();
    it++;

    cout << "2nd : " << *it << endl;

    // Erase value
    set1.erase(5);

    // Erase last 2
    it = set1.end();
    advance(it, -2);
    set1.erase(it, set1.end());

    // Add multiple values
    int arr[] = {6, 7, 8, 9};
    set1.insert(arr, arr + 4);

    // Find value, get iterator and then value
    auto val = set1.find(6);
    cout << "Found : " << *val << endl;

    // Get iterator to value
    auto eight = set1.lower_bound(8);
    cout << "8 : " << *eight << endl;

    // Get iterator to value after
    auto nine = set1.upper_bound(8);
    cout << "9 : " << *nine << endl;

    // Swap values in sets
    set<int> set2{10, 11};
    set1.swap(set2);

    // Check if empty and if not print values
    if (!set1.empty())
    {
        for (int i : set1)
            cout << i << endl;
    }

    // ----- END OF SET -----

    cout << endl;

    // ----- MULTISET -----
    // Stores duplicate values in sorted order
    // Other than that it is the same as set
    multiset<int> mset1{1, 1, 2, 3, 4};

    // Insert value
    mset1.insert(4);
    mset1.insert(0);

    if (!mset1.empty())
    {
        for (int i : mset1)
            cout << i << endl;
    }

    // ----- END MULTISET -----

    cout << endl;

    // ----- MAP -----
    // Stores using key value pairs and you
    // can't have duplicate keys
    map<int, string> map1;

    // Insert key values
    map1.insert(pair<int, string>(1, "Bart"));
    map1.insert(pair<int, string>(2, "Lisa"));
    map1.insert(pair<int, string>(3, "Marge"));
    map1.insert(pair<int, string>(4, "Homer"));

    // Find element by key
    auto match = map1.find(1);
    cout << match->second << endl;

    // Get iterator to value
    auto bart = map1.lower_bound(1);
    cout << "LB : " << bart->second << endl;

    // Get next iterator
    auto lisa = map1.upper_bound(1);
    cout << "UB : " << lisa->second << endl;

    // Print elements with an iterator
    map<int, string>::iterator it2;
    for (it2 = map1.begin(); it2 != map1.end(); ++it2)
    {
        cout << "Key : " << it2->first << endl;
        cout << "Value : " << it2->second << endl;
    }

    // ----- END OF MAP -----

    // ----- MULTIMAP -----
    // Like map except you can have duplicate keys as long
    // as the values are different
    multimap<int, string> mmap1;
    mmap1.insert(pair<int, string>(1, "Bart"));
    mmap1.insert(pair<int, string>(1, "Lisa"));
    mmap1.insert(pair<int, string>(3, "Marge"));
    map<int, string>::iterator it3;
    for (it3 = mmap1.begin(); it3 != mmap1.end(); ++it3)
    {
        cout << "Key : " << it3->first << endl;
        cout << "Value : " << it3->second << endl;
    }

    // ----- END OF MULTIMAP -----

    // ----- CONTAINER ADAPTERS -----
    // Adapt containers to provide a defined interface

    // ----- STACK -----
    // Provides an interface for storing elements in a LIFO
    // format
    stack<string> custs;
    custs.push("George");
    custs.push("Louise");
    custs.push("Florence");

    // Get number of elements
    int size = custs.size();

    // Check if empty
    if (!custs.empty())
    {
        for (int i = 0; i < size; i++)
        {

            // Get value with top
            cout << custs.top() << endl;

            // Delete last value entered
            custs.pop();
        }
    }

    // ----- END OF STACK -----

    // ----- QUEUE -----
    // Provides an interface for storing elements in a FIFO
    // format
    queue<string> cast;
    cast.push("Zoidberg");
    cast.push("Bender");
    cast.push("Leela");
    int size2 = cast.size();

    if (!cast.empty())
    {
        for (int i = 0; i < size2; i++)
        {

            // Get value with top
            cout << cast.front() << endl;

            // Delete last value entered
            cast.pop();
        }
    }

    // ----- END OF QUEUE -----

    // ----- PRIORITY QUEUE -----
    // Elements are organized with the largest first
    priority_queue<int> nums;
    nums.push(4);
    nums.push(8);
    nums.push(5);
    int size3 = nums.size();

    if (!nums.empty())
    {
        for (int i = 0; i < size3; i++)
        {

            // Get value with top
            cout << nums.top() << endl;

            // Delete last value entered
            nums.pop();
        }
    }

    // ----- END OF PRIORITY QUEUE -----

    // ----- ENUMS -----
    // Custom data type that assigns names to
    // constant integers so that a program is
    // easier to read

    // You can define the starting index, or any others
    enum day
    {
        Mon = 1,
        Tues,
        Wed,
        Thur,
        Fri = 5
    };

    enum day tuesday = Tues;

    cout << "Tuesday is the " << tuesday << "nd day of the week\n";

    // Cycle through days
    for (int i = Mon; i <= Fri; i++)
        cout << i << endl;

    // ----- END OF ENUMS -----

    return 0;
}