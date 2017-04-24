#pragma once

//Resize raster

#include "ofMain.h"


template <typename T, typename T1, typename T2>
void ofxKuRasterAdd(const vector<T> &input1, const vector<T> &input2, vector<T> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]+input2[i];
	}
}


template <typename T, typename T1, typename T2>
void ofxKuRasterMultiply(const vector<T> &input1, const vector<T> &input2, vector<T> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]*input2[i];
	}
}

template <typename T, typename T1, typename T2>
void ofxKuRasterDivide(const vector<T> &input1, const vector<T> &input2, vector<T> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]/input2[i];
	}
}
