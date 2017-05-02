#pragma once

//Raster Morphology - dilatation and erosion, boundary points

#include "ofMain.h"

//Find boundary points - it is points with value > threshold, and having at least one pixel in cross neighborhood with value <= threshold
//Point class - can be any class having x,y fields, for example, ofPoint or CvPoint.
template <typename T, typename PointClass>
void ofxKuRasterBoundaryPoints(const vector<T> &input, vector<PointClass> &pnt, int w, int h, T threshold) {
	pnt.reserve(w*h);
	PointClass p;
	for (int y=1; y<h-1; y++) {
		for (int x=1; x<w-1; x++) {
			int i=x+w*y;
			if (input[i] >= threshold
				&& (input[i-1]<threshold || input[i+1]<threshold
				|| input[i-w]<threshold || input[i+w]<threshold)) {
					p.x = x;
					p.y = y;
					pnt.push_back(p);
			}
		}				
	}
}

template <typename T>
void ofxKuRasterDilate(const vector<T> &input, vector<T> &output,
							   int w, int h, int rad) {
	if (rad <= 0 ) {
		output = input;
		return;
	}
	output.resize(w*h);
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			int i=x+w*y;
			T val = input[i];
			int x0 = max(x-rad,0);
			int y0 = max(y-rad,0);
			int x1 = min(x+rad,w-1);
			int y1 = min(y+rad,h-1);
			for (int yy=y0; yy<=y1; yy++) {
				for (int xx=x0; xx<=x1; xx++) {
					val = max(val, input[xx+w*yy]);
				}
			}
			output[i] = val;
		}
	}
}

template <typename T>
void ofxKuRasterErode(const vector<T> &input, vector<T> &output,
							   int w, int h, int rad) {
	if (rad <= 0 ) {
		output = input;
		return;
	}
	output.resize(w*h);
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			int i=x+w*y;
			T val = input[i];
			int x0 = max(x-rad,0);
			int y0 = max(y-rad,0);
			int x1 = min(x+rad,w-1);
			int y1 = min(y+rad,h-1);
			for (int yy=y0; yy<=y1; yy++) {
				for (int xx=x0; xx<=x1; xx++) {
					val = min(val, input[xx+w*yy]);
				}
			}
			output[i] = val;
		}
	}
}

