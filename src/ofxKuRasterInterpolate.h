#pragma once

//Interpolate rasters. ofPoint rasters can be used too.

#include "ofMain.h"

//integer types
template <typename T>
T ofxKuRasterInterpolate_bilinear(vector<T> &input, int w, int h, float x, float y) {
	if (x < 0 || x > w-1 || y < 0 || y > h-1) return 0;
	int xi = int(x);
	int yi = int(y);
	int xi1 = min(xi+1, w-1);
	int yi1 = min(yi+1, h-1);
	x -= xi;
	y -= yi;
	return input[xi+w*yi]*(1-x)*(1-y)  
		+ input[xi1+w*yi]*(x)*(1-y)  
		+ input[xi1+w*yi1]*(x)*(y)  
		+ input[xi+w*yi1]*(1-x)*(y);
}

template <typename T>
T ofxKuRasterInterpolate_bilinear(vector<T> &input, int w, int h, const ofPoint &p) {
	return ofxKuRasterInterpolate_bilinear(input, w, h, p.x, p.y);
}