//
// Created by ws on 12/15/16.
//

#ifndef LAB4_GNUPLOT_H
#define LAB4_GNUPLOT_H

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Gnuplot {
private:
    ofstream plot;

public:
    Gnuplot() {
        plot.open("plot.plt", ofstream::out | ofstream::trunc);
    }

    void init(char* filename) {
        plot << "set multiplot layout 2,2 rowsfirst" << endl;
        plot << "unset key; unset tics; unset border" << endl;
        plot << "set size ratio 1" << endl;

        plot << "set title \"Source image\"" << endl;
        plot << "plot \"" << filename << "\" binary filetype=png with rgbimage" << endl;
    }

    void finish(int nv, int nh, string out_name) {
        plot << "set title \"Image Nv = " << nv
             << ", Nh = "<< nh
             << "\"" << endl;
        plot << "plot \"" << out_name.c_str()
             << "\" binary filetype=png with rgbimage\n" << endl;
    }

    ~Gnuplot() {
        plot.close();
    }
};


#endif //LAB4_GNUPLOT_H
