//
// Created by ws on 12/8/16.
//

#ifndef LAB4_NEURALNET_H
#define LAB4_NEURALNET_H

#include <list>
#include <algorithm>
#include "WTANeuron.h"

class NeuralNet {
private:
    vector<WTANeuron> neurons;

    double sMin = 0.01;
    double sMax = 1;

    int iteration = 0;
    unsigned long iterationAmount;

    double nuMin = 0.1;
    double nuMax = 1;

    double pMin = 0.75;
    double pMax = 1;
public:
    NeuralNet(int neuronsAmount, int inputSize) {
        srand(time(NULL));
        vector<WTANeuron> neurons;
        for (int i = 0; i < neuronsAmount; ++i) {
            vector<double> weights;
            for (int j = inputSize - 1; j >= 0; --j) {
                weights.push_back(rand() % 100 / 100.0);
            }
            WTANeuron n(weights);
            n.myId = i;
            neurons.push_back(n);
        }
        this->neurons = neurons;
    }

    NeuralNet(vector<WTANeuron> neurons) {
        this->neurons = neurons;
    }

    const vector<WTANeuron> &getNeurons() const;

    void learn(vector<NPoint>& inputs) {
        iterationAmount = inputs.size();
        for (iteration = 0; iteration < inputs.size(); ++iteration) {
            learn(inputs[iteration].normalize());
        }
    }

    vector<WTANeuron> filter(vector<WTANeuron>& ns) {
        vector<WTANeuron> result;
        for (int i = 0; i < ns.size(); ++i) {
            if (ns[i].potential >= pMin)
                result.push_back(ns[i]);
        }
        if (result.size() == 0)
            return ns;
        else
            return result;
    }

    void learn(NPoint input) {
        vector<WTANeuron> sortedNeurons = sorted(input);
        auto filtered = filter(sortedNeurons);
        for (int i = 0; i < filtered.size(); ++i) {
            neurons[filtered[i].myId].adjust(nu(), gNeighbor(i), input);
        }

        auto winner = filtered[0];
        for (int i = 0; i < neurons.size(); ++i) {
            if (neurons[i].myId == winner.myId) {
                neurons[i].potential = neurons[i].potential - pMin;
            } else {
                double newPot = neurons[i].potential + (1.0 / neurons.size());
                neurons[i].potential = (newPot > pMax) ? pMax : newPot;
            }
        }
    }

    int findWinnerIndex(const NPoint input) const {
        int winner = 0;
        double maxValue = neurons.front().f(input);
        for (int i = 1; i < neurons.size(); ++i) {
            double temp = neurons[i].f(input);
            if (temp < maxValue) {
                maxValue = temp;
                winner = i;
            }
        }
        return winner;
    }

    vector<WTANeuron> sorted(NPoint& input) {
        vector<WTANeuron> neurons(this->neurons);
        std::sort(neurons.begin(), neurons.end(),
                  [&input]( const WTANeuron &a, const WTANeuron &b ) { return a.delta(input) <= b.delta(input); });
        return neurons;
    }

    double nu() {
        return nuMax * pow(nuMin / nuMax, ((double)iteration) / iterationAmount);
    }

    double sk() {
        return sMax * pow(sMin / sMax, ((double)iteration) / iterationAmount);
    }

    double gNeighbor(int position) {
        return exp(-1.0 * position / sk());
    }

    friend ostream& operator<<(ostream& os, const NeuralNet& p);
};

ostream &operator<<(ostream &os, const NeuralNet &p) {
    vector<WTANeuron>::const_iterator it = p.neurons.begin();
    os << "NeuralNet: " << endl;
    for(; it != p.neurons.end(); ++it)
        os << *it << endl;
    return os;
}

const vector<WTANeuron> &NeuralNet::getNeurons() const {
    return neurons;
}

#endif //LAB4_NEURALNET_H
