
#ifndef LAB4_ALLDATA_H
#define LAB4_ALLDATA_H

#include "Zipped.h"
#include "NeuralNet.h"
#include <fstream>
#include <iostream>

using namespace std;

class AllData {
private:
    int frameSize;
    vector<vector<double>> weights;
    Zipped image;

public:
    AllData(int frameSize) { this->frameSize = frameSize; }

    // save
    AllData saveNet(const NeuralNet net) {
        auto ns = net.getNeurons();
        for (int i = 0; i < ns.size(); ++i) {
            weights.push_back(ns[i].getWeights().getCoords());
        }
        return *this;
    }

    Zipped zip(const NeuralNet& net, const vector<NPoint> inputs) {
        Zipped result;
        for (int i = 0; i < inputs.size(); ++i) {
            auto winnerIndex = net.findWinnerIndex(inputs[i]);
            result.add(pair<int, double>(winnerIndex, inputs[i].length()));
        }
        return result;
    }

    const vector<NPoint> convertImageToFrames(const vector<double>& image, int frameSize) {
        vector<NPoint> result;
        int j = 0;
        while(j < image.size()) {
            vector<double> frameVal;
            for (int i = 0; i < frameSize; ++i, ++j) {
                frameVal.push_back(image[j]);
            }
            result.push_back(NPoint(frameVal));
        }
        return result;
    }

    AllData saveImage(const NeuralNet& net, const vector<double>& image) {
        return saveImage(net, convertImageToFrames(image, frameSize));
    }

    AllData saveImage(const NeuralNet& net, const vector<NPoint>& image) {
        saveNet(net);
        this->image = zip(net, image);
        return *this;
    }


    // retrieve
    NeuralNet createNet() const {
        vector<WTANeuron> neurons;

        for (int i = 0; i < weights.size(); ++i) {
            neurons.push_back(WTANeuron(weights[i]));
        }

        return NeuralNet(neurons);
    }

    vector<double> convertFramesToImage(const vector<NPoint>& frames) {
        vector<double> result;
        for (int i = 0; i < frames.size(); ++i) {
            auto frameData = frames[i].getCoords();
            for (int j = 0; j < frameData.size(); ++j) {
                result.push_back(frameData[j]);
            }
        }
        return result;
    }

    vector<NPoint> getImageData(NeuralNet& net) {
        vector<NPoint> result;
        auto frames = image.getResults();
        for (int i = 0; i < frames.size(); ++i) {
            auto pair = frames[i];
            auto n = net.getNeurons()[pair.first];
            result.push_back((n.getWeights() * pair.second).round());
        }
        return result;
    }

    vector<double> getImageData() {
        auto net = createNet();
        auto data = getImageData(net);
        return convertFramesToImage(data);
    }

    const Zipped &getImage() const {
        return image;
    }
};

#endif //LAB4_ALLDATA_H
