#include "bezier.h"

double factorial(double x){
    if (x==0 || x == 1) return 1;
    else return x*factorial(x-1);
}

double combination(double n, double r){
    return factorial(n)/(factorial(r)*factorial(n-r));
}

Persamaan::Persamaan(vector <Point> &p): coefficients(p.size()) {
    double n = p.size();
    for (int i=0;i<n;i++) {
        coefficients[i] = combination(n-1,i);
    }

    points = p;
}

Point Persamaan::func(double t) {
    double x = 0, y = 0;
    Point result;

    double n = coefficients.size();
    for (int i=0;i<n;i++) {
        x += coefficients[i]*pow((1-t),n-1-i)*pow(t,i)*points[i].x;
        y += coefficients[i]*pow((1-t),n-1-i)*pow(t,i)*points[i].y;
    }

    result.x = x;
    result.y = y;

    return result;
}

void Persamaan::printInfo() {
    for (auto& i:coefficients) {
        cout << i << " ";
    }
    cout << endl;

    for (auto& i:points) {
        cout << "(" << i.x << "," << i.y << ") ";
    }
    cout << endl;
}

vector <Point> brute_force(int it,vector <Point> &p) { // it = iteration
    double steps = 1/(pow(2,it));
    Persamaan f(p);

    vector<Point> new_p;
    new_p.push_back(p[0]);
    for (int i=1;i<pow(2,it);i++){
        new_p.push_back(f.func(i*steps));
    }
    new_p.push_back(p.back());

    return new_p;
}

Point func_recurse(double t, vector<Point> &p) {
    int n = p.size();

    if (n==1) {
        return p[0];
    }
    else if (n == 2) {
        Point new_p;
        new_p.x = (1-t)*p[0].x+t*p[1].x;
        new_p.y = (1-t)*p[0].y+t*p[1].y;
        return new_p;
    } else {
        vector<Point> new_vector_p;
        Point new_p;

        for (int i=0;i<n-1;i++){
            new_p.x = (1-t)*p[i].x+t*p[i+1].x;
            new_p.y = (1-t)*p[i].y+t*p[i+1].y;

            new_vector_p.push_back(new_p);
        }

        return func_recurse(t,new_vector_p);
    }
}

vector <Point> brute_force_recurse(int it,vector<Point> &p) {
    double steps = 1/(pow(2,it));

    vector<Point> new_p;
    new_p.push_back(p[0]);
    for (int i=1;i<pow(2,it);i++){
        new_p.push_back(func_recurse(i*steps,p));
    }
    new_p.push_back(p.back());

    return new_p;
}

vector <Point> recurse(int it, int mIt, vector <Point> &p) {
    if(it == mIt) return {p[0], p.back()};
    vector<Point> pref, suf;
    while(p.size() >= 2){
        int n = p.size();
        pref.push_back(p[0]);
        suf.push_back(p.back());
        vector<Point> newP;
        for (int i=0;i<n-1;i++) {
            // find middle of 2 points
            double x = (p[i+1].x+p[i].x)/2;
            double y = (p[i+1].y+p[i].y)/2;
            Point new_p = {x, y};
            newP.push_back(new_p);
        }
        p.swap(newP);
    }

    double x = (pref.back().x+suf.back().x)/2;
    double y = (pref.back().y+suf.back().y)/2;
    Point midPoint = {x, y};
    suf.push_back(midPoint);
    reverse(suf.begin(), suf.end());
    pref.push_back(midPoint);
    vector<Point> lef = recurse(it + 1, mIt, pref);
    vector<Point> rig = recurse(it + 1, mIt, suf);
    lef.pop_back();
    for(auto &x: rig) lef.push_back(x);
    return lef;
}
