#include <iostream>
#include <algorithm>
#include <sstream>
#include "WTANeuron.h"
#include "NeuralNet.h"
#include "AllData.h"
#include "Gnuplot.h"

using namespace std;
const int evolutionsAmount = 10;
const int size = 5;

string createOutName(int nv, int nh, int neuronsAmount, char* filename) {
    string name_base;
    name_base.append(filename);
    name_base = name_base.substr(0, name_base.find_first_of('.'));

    ostringstream s;
    s.str("");
    s << name_base.c_str() << "_" << nh << "_" << nv << "_" << neuronsAmount << ".png";

    string out_name;
    out_name.clear();
    out_name.assign(s.str());
    return out_name;
}

void logDistribution(int neuronsAmount, AllData& allData) {
    vector<int> groupedBy;
    cout << "Ns " << neuronsAmount << endl;
    for (int i = 0; i < neuronsAmount; ++i)
        groupedBy.push_back(0);
    auto rs = allData.getImage().getResults();
    cout << "Size: " << rs.size() << endl;
    for (int i = 0; i < rs.size(); ++i) {
        groupedBy[rs[i].first] = groupedBy[rs[i].first] + 1;
    }
    for (int i = 0; i < groupedBy.size(); ++i) {
        cout << "Neurons[" << i << "]: amount = " << groupedBy[i] << endl;
    }
}

int executeWith(int nv, int nh, int neuronsAmount, Gnuplot& gnuplot, char* filename) {
    cout << "Nv = " << nv << "; ";
    cout << "Nh = " << nh << "; ";
    PngImage img;
    if (!img.readImage(filename))
        return -1;

    int inputsAmount = nv * nh;
    NeuralNet net(neuronsAmount, inputsAmount);

    if (net.getNeurons()[0].getWeights().getCoords().size() != inputsAmount) {
        cerr << "Wrong params!";
        return -2;
    }

    int blocksAmount = img.getBlockCount(nv, nh);
    cout << blocksAmount << endl;

    vector<NPoint> input;
    for (int i = 0; i < blocksAmount; ++i)
        input.push_back(NPoint(img.getBlock(i, nv, nh)));

    for (int j = 0; j < evolutionsAmount; j++)
        net.learn(input);

    AllData allData(inputsAmount);
    allData.saveImage(net, input);

    logDistribution(neuronsAmount, allData);

    auto results = allData.getImageData(net);

    for (int i = 0; i < results.size(); ++i)
        img.setBlock(results[i].toUchars(), i, nv, nh);

    string out_name = createOutName(nv, nh, (int)net.getNeurons().size(), filename);
    img.writeImage(out_name.c_str());
    gnuplot.finish(nv, nh, out_name);
    return 0;
}

int lab(char* filename) {
    int Nv = 2;
    int Nh = 2;
    int NeuronsAmount[size];

    NeuronsAmount[0] = 2;
    NeuronsAmount[1] = 4;
    NeuronsAmount[2] = 8;
    NeuronsAmount[3] = 16;
    NeuronsAmount[4] = 32;

    Gnuplot gnuplot;
    gnuplot.init(filename);

    for (int k = 0; k < size - 1; k++) {
        if (executeWith(Nv, Nh, NeuronsAmount[k], gnuplot, filename) == 0)
            cerr << "Done..." << endl;
        else {
            cerr << "Error..." << endl;
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    lab((char *) "/home/ws/Lab4/1307773732.png");

    return 0;
}