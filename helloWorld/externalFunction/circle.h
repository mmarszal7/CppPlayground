#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
private:
    double radious;

public:
    Circle();
    Circle(double radious);

    void SetRadious(double radious);
    double GetRadious();

    double GetArea();

    virtual ~Circle();
};

#endif /* CIRCLE_H */