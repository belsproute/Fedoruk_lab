//
// Created by ws on 12/8/16.
//

#ifndef LAB4_WTANEURON_H
#define LAB4_WTANEURON_H


#include <numeric>
#include "NPoint.h"

class WTANeuron {
private:
    static int id;
    NPoint weights;

public:
    int myId;
    double potential;

    WTANeuron(vector<double> weights) {
        myId = id++;
        potential = 0.75;
        this->weights = NPoint(weights).normalize();
    }

    const NPoint &getWeights() const;

    double f(const NPoint input) const {
        return delta(input);
    }

    double delta(const NPoint input) const {
        return sqrt((input - weights).power(2).sum());
    }

    void adjust(double nu, double g, const NPoint& input) {
        vector<double> newWeights;
        for (int i = 0; i < weights.getCoords().size(); ++i) {
            newWeights.push_back(weights[i] + nu * g * (input[i] - weights[i]));
        }
        weights = NPoint(newWeights).normalize();
    }

    friend ostream& operator<<(ostream& os, const WTANeuron& p);
};

ostream &operator<<(ostream &os, const WTANeuron &p) {
    vector<double>::const_iterator it = p.weights.getCoords().begin();
    os << "WTA[" << p.myId << "] : (" << *it++;
    for(; it != p.weights.getCoords().end(); ++it)
        os << ", " << *it;
    os << ')';
    return os;
}

int WTANeuron::id = 0;

const NPoint &WTANeuron::getWeights() const {
    return weights;
}

#endif //LAB4_WTANEURON_H
