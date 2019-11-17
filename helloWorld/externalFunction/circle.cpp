#include "circle.h"
#include "cmath"

Circle::Circle(double radious)
{
    this->radious = radious;
}

Circle::~Circle() = default;

void Circle::SetRadious(double radious) { this->radious = radious; }
double Circle::GetRadious() { return radious; }

double Circle::GetArea()
{
    return 3.14 * pow(radious, 2.0);
}