#include <iostream>
#include <vector>
#include <string>
#include "externalFunction/circle.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code!", "and the C++ extension!"};
    cout << "Hello" << endl;

    Circle circle(5);
    cout << circle.GetArea() << endl;

    Mat img(500, 1000, CV_8UC1, Scalar(70));
    cout << img.size().width << endl;
    return 0;
}