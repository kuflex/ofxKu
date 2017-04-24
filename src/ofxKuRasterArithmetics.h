#pragma once

//Resize raster

#include "ofMain.h"


template <typename T1, typename T2, typename T3>
void ofxKuRasterAdd(const vector<T1> &input1, const vector<T2> &input2, vector<T3> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]+input2[i];
	}
}


template <typename T1, typename T2, typename T3>
void ofxKuRasterMultiply(const vector<T1> &input1, const vector<T2> &input2, vector<T3> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]*input2[i];
	}
}

template <typename T1, typename T2, typename T3>
void ofxKuRasterDivide(const vector<T1> &input1, const vector<T2> &input2, vector<T3> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]/input2[i];
	}
}

