//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_NPOINT_H
#define NEIRONETS_NPOINT_H

#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <numeric>
#include "pngimage.h"

using namespace std;

class NPoint {
private:
    vector<double> coords;
public:
    NPoint() : coords(vector<double>()) { }
    NPoint(vector<double> coords_val) : coords(coords_val) { }
    NPoint(vector<uchar> coords_val) {
        coords = vector<double>();
        for (int i = 0; i < coords_val.size(); ++i) {
            auto t2 = (double)coords_val[i];
            coords.push_back(t2);
        }
    }

    NPoint(double x, double y) : coords(vector<double>()) {
        coords.push_back(x);
        coords.push_back(y);
    }

    NPoint(double x, double y, double z) : coords(vector<double>()) {
        coords.push_back(x);
        coords.push_back(y);
        coords.push_back(z);
    }

    NPoint operator + (const NPoint& p) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        vector<double>::const_iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it + *pIt);

        return result;
    }

    NPoint operator - (const NPoint& p) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        vector<double>::const_iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it - *pIt);

        return result;
    }

    NPoint operator / (const NPoint& p) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        vector<double>::const_iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it / *pIt);

        return result;
    }

    NPoint operator * (const NPoint& p) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        vector<double>::const_iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it * *pIt);

        return result;
    }

    NPoint operator * (const double multiplier) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        for(; it != coords.end(); ++it)
            result.coords.push_back(*it * multiplier);

        return result;
    }

    NPoint power(double n) const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        for(; it != coords.end(); ++it)
            result.coords.push_back(pow(*it, n));

        return result;
    }

    NPoint abs() const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        for(; it != coords.end(); ++it)
            result.coords.push_back(std::abs(*it));

        return result;
    }

    double sum() const {
        return accumulate(coords.begin(), coords.end(), 0.0);
    }

    NPoint normalize() const {
        double length = this->length();
        vector<double> result;
        for (int i = 0; i < coords.size(); ++i) {
            result.push_back(coords[i] / length);
        }
        return NPoint(result);
    }

    double length() const {
        double result = 0;
        for (int i = 0; i < coords.size(); ++i) {
            result += coords[i] * coords[i];
        }
        return sqrt(result);
    }

    NPoint round() const {
        NPoint result;
        vector<double>::const_iterator it = coords.begin();
        for(; it != coords.end(); ++it)
            result.coords.push_back(std::round(*it));

        return result;
    }

    vector<uchar> toUchars() {
        vector<uchar> result;
        for (int i = 0; i < coords.size(); ++i) {
            auto tmp = (uchar)std::round(coords[i]);
            result.push_back(tmp);
        }
        return result;
    }

    void set(int i, double val) { coords[i] = val; }

    double operator[] (const int i) const { return coords[i]; }

    const vector<double>& getCoords() const { return coords; }

    friend ostream& operator<<(ostream& os, const NPoint& p);
};

ostream &operator<<(ostream &os, const NPoint &p) {
    vector<double>::const_iterator it = p.coords.begin();
    os << '(' << *it++;
    for(; it != p.coords.end(); ++it)
        os << ", " << *it;
    os << ')';
    return os;
}

#endif //NEIRONETS_NPOINT_H
