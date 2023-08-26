#pragma once

#/*ifdef CURVESLIBRARY_EXPORTS
#define CURVESLIBRARY_API __declspec(dllexport)
#else
#define CURVESLIBRARY_API __declspec(dllimport)
#endif*/

#include <vector>
#include <memory>
using namespace std;

class Curve {
private:

public:
    virtual vector<double> getCoord(double t) = 0;
    virtual vector<double> getDeriv(double t) = 0;
};

class Helix : public Curve {
private:
    double a;
    double b;
    double step;
public:
    Helix(double a, double b, double step);
    Helix(double r, double step);

    vector<double> getCoord(double t) override;
    vector<double> getDeriv(double t) override;
};

class Ellips : public Helix {
private:
public:
    Ellips(double a, double b);
};

class Circle : public Helix {
private:
    double r;
public:
    Circle(double r);
    double getRadius();
};

shared_ptr<Curve> getRandomCurve();
