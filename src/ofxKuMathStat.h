#pragma once

//Statistics

#include "ofMain.h"

//mean value of the projection vector
template <typename T>
double ofxKuMathMeanProj(const vector<T> &input) {
	int n = input.size();
	if (n==0) return 0;
	double M = 0;
	double sum = 0;
	for (int i=0; i<n; i++) {
		M += i * input[i];
		sum += input[i];
	}
	if (sum>0) M/=sum;
	return M;
}

//median value of the projection vector
template <typename T>
double ofxKuMathMedianProj(const vector<T> &input) {
	int n = input.size();
	if (n==0) return 0;
	double sum = 0;
	for (int i=0; i<n; i++) {
		sum += input[i];
	}

	double q = 0;
	for (int i=0; i<n; i++) {
		if (q + input[i] > sum/2) return i;
		q += input[i];
	}
	return n-1;
}

