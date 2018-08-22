#pragma once

#include "ofMain.h"

//Fast sin/cos

struct ofxKuMathFastSinCos {
	ofxKuMathFastSinCos() {
		setup();
	}

	void setup(int table_size=1000);
	float get_sin(float a);
	float get_cos(float a);

	int size_ = 0;
	vector<float> sin_;
	vector<float> cos_;

};

