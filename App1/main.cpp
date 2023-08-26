// App.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <algorithm>
#include <omp.h>
#include <chrono>

#include "header.h"

using namespace std;

// sort comparator
bool compareR(shared_ptr<Circle> i1, shared_ptr<Circle> i2)
{
    return (i1->getRadius() < i2->getRadius())||false;
}

int main()
{
    // Create curves
    int size = 10;
    vector<shared_ptr<Curve>> curves;
    curves.reserve(size);
    for (int i = 0; i < size; i++)
    {
        curves.push_back(getRandomCurve());
    }

    // Print
    cout << "Coords : Derivatives" << endl;
    for (shared_ptr<Curve> it : curves) {
        vector<double> coord = it->getCoord(M_PI / 4);
        vector<double> deriv = it->getDeriv(M_PI / 4);
        for (int i = 0; i < 3; ++i) {
            cout << coord.at(i) << "\t" << deriv.at(i) << endl;
        }
        cout << "\n" << endl;
    }

    // Copy circles ans sort
    cout << "Address(original container) : Radius" << endl;
    vector<shared_ptr<Circle>> circles;
    for (auto curve : curves) {
        shared_ptr<Circle> circle(dynamic_cast<Circle*>(curve.get()));
        if (circle.get()) {
            circles.push_back(circle);
            cout << curve.get() << " " << circle->getRadius() << endl;
        }
    }
    sort(circles.begin(), circles.end(), compareR); // multimap?

    cout << "\n" << endl;
    cout << "Address(new container) : Radius" << endl;
    for (auto circle : circles) {
        cout << circle.get() << " " << circle->getRadius() << endl;
    }
    cout << "\n" << endl;

    // Find sum
    // Takes 8874 ms for 200k elements
    double sum = 0;
    auto start = chrono::high_resolution_clock::now();
    for (auto circle : circles) {
        sum += circle->getRadius();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Radius sum: " << sum << ", Time: " << duration.count() << endl;

    // Find sum with OpenMP
    // Takes 2575 ms for 200k elements
    sum = 0;
    omp_set_num_threads(2);

    start = chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i<circles.size(); ++i)
    {
        sum += circles.at(i)->getRadius();
    }
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Radius sum: " << sum << ", Time: " << duration.count() << endl;

    cin.get();
}
