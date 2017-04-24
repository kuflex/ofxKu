#pragma once

//Resize raster

#include "ofMain.h"

//integer types
template <typename T, typename T1>
void ofxKuRasterResize_nearest(vector<T> &input, int w, int h, vector<T1> &output, int out_w, int out_h) {
	int w1 = out_w;
	int h1 = out_h;
	output.resize(w1*h1);
	if (w<=0 || h<=0) {
		fill(output.begin(), output.end(),0);
		return;
	}
	for (int y1=0; y1<h1; y1++) {
		int y = y1 * h / h1;
		for (int x1=0; x1<w1; x1++) {
			int x = x1 * w / w1;
			output[x1 + w1*y1] = input[x + w*y];
		}
	}

}
