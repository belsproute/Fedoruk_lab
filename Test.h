//
// Created by ws on 12/15/16.
//

#ifndef LAB4_TEST_H
#define LAB4_TEST_H


#include "WTANeuron.h"
#include "AllData.h"

using namespace std;

class Test {
public:

    void test2() {
        vector<double> v = {3.0, 4.0};
        NPoint p(v);
        cout << p.normalize() << endl;
    }

    void test3() {
        AllData allData(3);

        vector<double> weights = {1, 3, 4, 5, 6, 7};
        NPoint data(weights);

        auto frames = allData.convertImageToFrames(data.getCoords(), 3);
        cout << "Size = " << frames.size() << endl;
        cout << frames[0] << endl;
        cout << frames[1] << endl;

        cout << "Image: " << endl << NPoint(allData.convertFramesToImage(frames)) << endl;
    }

    void test4() {
        NeuralNet net({WTANeuron({1, 2, 3}), WTANeuron({-1, -2, -3})});

        vector<NPoint> learning = {
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1})),
                NPoint(vector<double>({-1, -1, -1})),
                NPoint(vector<double>({1, 1, 1}))
        };

        net.learn(learning);

        cout << net << endl;
    }

    void test5() {
        NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
        cout << "Net to save " << net << endl;

        AllData allData(3);
        allData.saveNet(net);

        cout << "Restored net: " << allData.createNet() << endl;
    }

    void test6() {
        NeuralNet net({WTANeuron({1, 1, 1}), WTANeuron({-1, 1, 1}), WTANeuron({1, -1, -1})});
        cout << "Net to save " << net << endl;

        AllData allData(3);
        allData.saveNet(net);

        cout << "Restored net: " << allData.createNet() << endl;
    }

    void test7() {
        NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
        vector<double> imageData = {2, 0, 0,
                                    0, 3, 0,
                                    0, 0, 5};
        AllData allData(3);

        cout << "Compressed:\n" << allData.saveImage(net, imageData).getImage() << endl;
    }

    void test8() {
        NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
        vector<double> imageData = {2, 0, 0,
                                    0, 3, 0,
                                    0, 0, 5,
                                    0, 9, 0,
                                    7, 0, 0,
                                    0, 0, 2};
        AllData allData(3);
        cout << "Restored:\n" << NPoint(allData.saveImage(net, imageData).getImageData()) << endl;
    }

    void test9() {
        vector<NPoint> learning = {
                NPoint(vector<double>({5, 0, 0})),
                NPoint(vector<double>({0, 8, 0})),
                NPoint(vector<double>({0, 0, 4})),
                NPoint(vector<double>({100, 0, 0})),
                NPoint(vector<double>({0, 13, 0})),
                NPoint(vector<double>({0, 0, 16})),
                NPoint(vector<double>({10, 0, 0})),
                NPoint(vector<double>({0, 22, 0})),
                NPoint(vector<double>({0, 0, 33})),
                NPoint(vector<double>({55, 0, 0})),
                NPoint(vector<double>({0, 60, 0})),
                NPoint(vector<double>({0, 0, 70})),
                NPoint(vector<double>({80, 0, 0})),
                NPoint(vector<double>({0, 90, 0})),
                NPoint(vector<double>({0, 0, 100})),
                NPoint(vector<double>({89, 0, 0})),
                NPoint(vector<double>({0, 91, 0})),
                NPoint(vector<double>({0, 0, 14})),
                NPoint(vector<double>({19, 0, 0})),
                NPoint(vector<double>({0, 20, 0})),
                NPoint(vector<double>({0, 0, 44})),
        };
        NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
        net.learn(learning);

        cout << net << endl;
    }

    void test10() {
        vector<NPoint> learning = {
                NPoint(vector<double>({5, 0, 0})),
                NPoint(vector<double>({0, 8, 0})),
                NPoint(vector<double>({0, 0, 4})),
                NPoint(vector<double>({100, 0, 0})),
                NPoint(vector<double>({0, 13, 0})),
                NPoint(vector<double>({0, 0, 16})),
                NPoint(vector<double>({10, 0, 0})),
                NPoint(vector<double>({0, 22, 0})),
                NPoint(vector<double>({0, 0, 33})),
                NPoint(vector<double>({55, 0, 0})),
                NPoint(vector<double>({0, 60, 0})),
                NPoint(vector<double>({0, 0, 70})),
                NPoint(vector<double>({80, 0, 0})),
                NPoint(vector<double>({0, 90, 0})),
                NPoint(vector<double>({0, 0, 100})),
                NPoint(vector<double>({89, 0, 0})),
                NPoint(vector<double>({0, 91, 0})),
                NPoint(vector<double>({0, 0, 14})),
                NPoint(vector<double>({19, 0, 0})),
                NPoint(vector<double>({0, 20, 0})),
                NPoint(vector<double>({0, 0, 44})),
        };
        NeuralNet net({WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1})});
        net.learn(learning);

        vector<double> imageData = {2, 0, 0,
                                    0, 3, 0,
                                    0, 0, 5,
                                    0, 9, 0,
                                    7, 0, 0,
                                    0, 0, 2};
        AllData allData(3);
        cout << "Restored:\n" << NPoint(allData.saveImage(net, imageData).getImageData()) << endl;
    }

    void test11() {
        NeuralNet net(16, 4);
        cout << net << endl;
    }

    void test12() {
        vector<WTANeuron> ns = { WTANeuron({1, 0, 0}), WTANeuron({0, 1, 0}), WTANeuron({0, 0, 1}) };

        ns.front().potential = 0.4;
        cout << ns.front().potential << endl;

        vector<double> tmp = {1, 1, 1};

        ns.front().adjust(1, 1, NPoint(tmp));

        cout << ns.front().getWeights() << endl;

        vector<WTANeuron> anotherOne = ns;
        cout << anotherOne.front().potential << endl;
        cout << anotherOne.front().getWeights() << endl;
    }
};


#endif //LAB4_TEST_H
