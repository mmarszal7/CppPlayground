#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>

using namespace std;

int GetRandom(int max)
{
    srand(time(NULL));
    return rand() % max;
}

// ----- SIMPLE THREAD EXAMPLE -----

void ExecuteThread(int id)
{
    // Get current time
    auto nowTime = chrono::system_clock::now();

    // Convert to a time we can output
    time_t sleepTime =
        chrono::system_clock::to_time_t(nowTime);

    // Convert to current time zone
    tm myLocalTime = *localtime(&sleepTime);

    // Print full time information
    cout << "Thread " << id << " Sleep Time : " << ctime(&sleepTime) << endl;

    // Get separate pieces
    cout << "Month : " << myLocalTime.tm_mon << endl;
    cout << "Day : " << myLocalTime.tm_mday << endl;
    cout << "Year : " << myLocalTime.tm_year + 1900 << endl;
    cout << "Hours : " << myLocalTime.tm_hour << endl;
    cout << "Minutes : " << myLocalTime.tm_min << endl;
    cout << "Seconds : " << myLocalTime.tm_sec << "\n"
         << endl;

    // Put the thread to sleep for up to 3 seconds
    this_thread::sleep_for(chrono::seconds(GetRandom(3)));
    nowTime = chrono::system_clock::now();
    sleepTime =
        chrono::system_clock::to_time_t(nowTime);
    cout << "Thread " << id << " Awake Time : " << ctime(&sleepTime) << endl;
}

int main()
{
    // Create a thread and pass a parameter
    // to the function
    thread th1(ExecuteThread, 1);

    // Join the thread to the main thread
    // meaning main waits for this thread to
    // stop executing before continuing execution
    // of code in main
    th1.join();

    thread th2(ExecuteThread, 2);
    th2.join();

    return 0;
}