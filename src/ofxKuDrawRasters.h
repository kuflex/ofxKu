#pragma once

#include "ofMain.h"

//Drawing rasters

void ofxKuDrawRaster(vector<unsigned char> &pix, int w, int h, float X, float Y, float W, float H);
void ofxKuDrawRaster(vector<float> &pix, int w, int h, float X, float Y, float W, float H, float val0=0, float val1=255);