all:
	g++ main.cpp WTANeuron.h NPoint.h NeuralNet.h Zipped.h AllData.h pngimage.h Test.h Gnuplot.h -lpng -std=c++11 && make clean

clean:
	rm *.gch

run:
	./a.out
