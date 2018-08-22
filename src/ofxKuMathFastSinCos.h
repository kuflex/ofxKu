#pragma once

#include "ofMain.h"

//Fast sin/cos

struct ofxKuMathFastSinCos {
	ofxKuMathFastSinCos() {
		setup();
	}

	void setup(int table_size=1000);
	float get_sin(float a);		//with interpolation
	float get_cos(float a);
	float get_sin_raw(float a);	//without interpolation
	float get_cos_raw(float a);
	float get_sin_raw_nowarp(float a);	
	float get_cos_raw_nowarp(float a);


	int size_ = 0;
	vector<float> sin_;
	vector<float> cos_;

};

