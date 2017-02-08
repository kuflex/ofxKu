#pragma once

#include "ofMain.h"

//Flood fill and blobs processing

//--------------------------------------------------------------
//Flood fill
//sv=4 or 8 - connectivity of pixels
//outPoints as x+w*y
size_t ofxKuFloodFill(vector<unsigned char> &input, int w, int h, int sv,
                 int x0, int y0, int search, int fillColor, vector<int> *outPoints); 

//--------------------------------------------------------------
