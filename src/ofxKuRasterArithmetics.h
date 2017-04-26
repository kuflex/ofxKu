#pragma once

//Raster arithmetics, thresholding, counting

#include "ofMain.h"

template <typename T1, typename T2>
void ofxKuRasterConvert(const vector<T1> &input, vector<T2> &output,
							   int w, int h) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = input[i];
	}
}

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

//Create mask with pixel equal to value1 if input in [value_from,value_to] and value0 in the opposite case
template <typename T1, typename T2>
void ofxKuRasterRangeMask(const vector<T1> &input, vector<T2> &output,
							   int w, int h, T1 value_from, T1 value_to, T2 value0, T2 value1) {
	output.resize(w*h);
	for (int i=0; i<w*h; i++) {
		output[i] = (input[i] >= value_from && input[i] <= value_to) ? value1 : value0;
	}
}

//Count number of pixels with values in specified range
//Usage example: 
//cout << ofxKuRasterRangeCount(mask_,w_,h_,unsigned char(1), unsigned char(255) ) << endl;
template <typename T>
int ofxKuRasterRangeCount(const vector<T> &input, int w, int h, T value_from, T value_to) {

	int sum = 0;
	for (int i=0; i<w*h; i++) {
		if (input[i] >= value_from && input[i] <= value_to) sum++;
	}
	return sum;
}

template <typename T, typename T2>
void ofxKuRasterProjectX(const vector<T> &input, vector<T2> &output, int w, int h) {
	output.resize(w);
	for (int x=0; x<w; x++) {
		T2 sum = 0;
		for (int y=0; y<h; y++) {
			sum += input[x+w*y];
		}
		output[x] = sum;
	}
}

template <typename T, typename T2>
void ofxKuRasterProjectY(const vector<T> &input, vector<T2> &output, int w, int h) {
	output.resize(h);
	for (int y=0; y<h; y++) {
		T2 sum = 0;
		for (int x=0; x<w; x++) {
			sum += input[x+w*y];
		}
		output[y] = sum;
	}
}

void ofxKuRasterHistogram(const vector<unsigned char> &input, vector<int> &histogram, int w, int h);