#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <random>

#include "header.h"

using namespace std;

// Helix
Helix::Helix(double a, double b, double step) {
    if (a < 0 || b < 0) {
        throw invalid_argument("Radius is negative");
    }
    this->a = a;
    this->b = b;
    this->step = step;
}
Helix::Helix(double r, double step) :Helix(r, r, step) {};

vector<double> Helix::getCoord(double t) {
    vector<double> v = { a * cos(t), b * sin(t), t / (2 * M_PI) * step };
    return v;
}

vector<double> Helix::getDeriv(double t) {
    vector<double> v = { -a * sin(t), b * cos(t), step / (2 * M_PI) };
    return v;
}

// Ellips
Ellips::Ellips(double a, double b) : Helix(a, b, 0) {};

// Circle
Circle::Circle(double r) :Helix(r, r, 0) {
    this->r = r;
}
double Circle::getRadius() {
    return r;
}

shared_ptr<Curve> getRandomCurve() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<double> rdis(0, 100);
    static uniform_int_distribution<int> idis(0, 2);
    try
    {
        switch (idis(gen))
        {
        case 0:
            return make_shared<Circle>(rdis(gen));
            break;
        case 1:
            return make_shared<Ellips>(rdis(gen), rdis(gen));
            break;
        case 2:
            return make_shared<Helix>(rdis(gen), rdis(gen));
            break;
        }
    }
    catch (const invalid_argument& e)
    {
        cout << e.what() << endl;
        exit;
    }
}