#pragma once

//Box blurring

#include "ofMain.h"

//integer types
template <typename T>
void ofxKuRasterBlur_int(vector<T> &input, int w, int h, int rad, vector<T> &output) {
	//TODO now implementation eats the borders, should repeat/mirror
	output.resize(w*h);
	fill(output.begin(), output.end(), 0);
	int k=2*rad+1;
	int k2 = k*k;
	if (w < k || h < k) {
		cout << "ofxKuRasterBlur_int error: too small image size" << endl;
		return;
	}
	for (int y=rad; y<h-rad;y++) {
		int sum = 0;
		for (int x=0; x<k-1; x++) {
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum += input[x+w*y1];
			}
		}
		for (int x=rad; x<w-rad; x++) {
			int x1 = x+rad;
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum += input[x1+w*y1];
			}
			output[x+w*y] = sum / k2;
			x1 = x-rad;
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum -= input[x1+w*y1];
			}
		}
	}
}

//float, double
template <typename T>
void ofxKuRasterBlur_float(vector<T> &input, int w, int h, int rad, vector<T> &output) {
	//TODO now implementation eats the borders, should repeat/mirror
	output.resize(w*h);
	fill(output.begin(), output.end(), 0);
	int k=2*rad+1;
	int k2 = k*k;
	if (w < k || h < k) {
		cout << "ofxKuRasterBlur_float error: too small image size" << endl;
		return;
	}
	for (int y=rad; y<h-rad;y++) {
		T sum = 0;
		for (int x=0; x<k-1; x++) {
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum += input[x+w*y1];
			}
		}
		for (int x=rad; x<w-rad; x++) {
			int x1 = x+rad;
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum += input[x1+w*y1];
			}
			output[x+w*y] = sum / k2;
			x1 = x-rad;
			for (int y1=y-rad; y1<=y+rad; y1++) {
				sum -= input[x1+w*y1];
			}
		}
	}
}