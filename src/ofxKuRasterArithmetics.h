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
void ofxKuRasterSubtract(const vector<T1> &input1, const vector<T2> &input2, vector<T3> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input1[i]-input2[i];
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
							   int w, int h, T2 eps, T3 use_if_less_eps) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		if (fabs(input2[i])>eps) { 
			output[i] = input1[i]/input2[i];
		}
		else output[i] = use_if_less_eps;
	}
}

template <typename T1, typename T2>
void ofxKuRasterThreshold(const vector<T1> &input, vector<T2> &output,
							   int w, int h, T1 threshold, T1 value0, T2 value1) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = (input[i] > threshold) ? value1 : value0;
	}
}