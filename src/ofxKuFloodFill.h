#pragma once

#include "ofMain.h"

//Flood fill and blobs processing

//Flood fill
//sv=4 or 8 - connectivity of pixels
//outPoints as x+w*y
size_t ofxKuFloodFill(vector<unsigned char> &input, int w, int h, int sv,
                 int x0, int y0, int search, int fillColor, vector<int> *outPoints = 0); 

//Remove small blobs, which has values [good_val0, good_val1] and area < min_area. For this blobs, set these to erase_val
//Function can work in-place, that is "output" can be "input"
void ofxKuRasterBlobsFilter(vector<unsigned char> &input, vector<unsigned char> &output, int w, int h, int sv,
							int min_area, unsigned char good_val0, unsigned char  good_val1, unsigned char erase_val );