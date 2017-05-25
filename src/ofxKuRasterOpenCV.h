#pragma once

//Operations using openCV. 
//To use, please include ofxOpenCv addons to your project.

#include "ofMain.h"

//Gauss smoothing
void ofxKuRasterGaussSmooth( vector<float> &mask, int w, int h, int rad, vector<float> &res );

void ofxKuRasterResized( vector<float> &mask, int w, int h, int rad, vector<float> &res, int wres, int hres );

//Field direction
void ofxKuRasterFieldDirection( vector<float> &energy, int w, int h, int step, vector<ofPoint> &res );

//Convex hull
void ofxKuRasterConvexHull( vector<unsigned char> &input, vector<unsigned char> &output, int w, int h, int threshold );

//Заполняет нулевые направления в accum значениями из source
//void pbCombineFieldDirection( vector<ofPoint> &accum, int w, int h, vector<ofPoint> &source, int ws, int hs  );

//Заполняет нулевые направления, а также граничные, направлением в center
//void pbFillFieldDirection( vector<ofPoint> &accum, int w, int h, ofPoint &center, int border  );