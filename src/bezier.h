#ifndef BEZIER_H_INCLUDED
#define BEZIER_H_INCLUDED

#include <iostream>
#include <cmath>

#include <bits/stdc++.h>
#include <vector>
using std::vector;
using namespace std;

struct Point {
    double x,y;
};

double factorial(double);

double combination(double, double);

struct Persamaan {
    Persamaan(vector <Point> &p);
    Point func(double x);

    std::vector <double> coefficients;
    std::vector <Point> points;
};

vector <Point> brute_force(int it,vector<Point> &p);

vector <Point> recurse(int it, int mIt, vector <Point> &p);

#endif // BEZIER_H_INCLUDED
