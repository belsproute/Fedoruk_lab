
#ifndef LAB4_ZIPPED_H
#define LAB4_ZIPPED_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Zipped {
private:
    vector<std::pair<int, double>> results;
public:
    Zipped() { results = vector<std::pair<int, double>>(); }

    Zipped &add(std::pair<int, double> pair) {
        results.push_back(pair);
        return *this;
    }

    const vector<std::pair<int, double>> &getResults() const {
        return results;
    }

    friend ostream& operator<<(ostream& os, const Zipped& p);
};

ostream &operator<<(ostream &os, const Zipped &p) {
    vector<std::pair<int, double>>::const_iterator it = p.results.begin();
    os << "Zipped result: " << endl;
    for(; it != p.results.end(); ++it)
        os << "{ NeuronId: " << it->first << ", Amplitude: " << it->second << '}' << endl;
    return os;
}

#endif //LAB4_ZIPPED_H
