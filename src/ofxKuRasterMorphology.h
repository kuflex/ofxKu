#pragma once

//Raster Morphology - dilatation and erosion

#include "ofMain.h"


template <typename T>
void ofxKuRasterDilate(const vector<T> &input, vector<T> &output,
							   int w, int h, int rad) {
	if (rad <= 0 ) {
		output = input;
		return;
	}
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

