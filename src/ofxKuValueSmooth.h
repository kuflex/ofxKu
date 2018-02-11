#pragma once

//Smoothing

#include "ofMain.h"

template <typename T>
void ofxKuValueSmooth(T &value, T target, float smooth) {
    value += (target - value) * (1-smooth);
}


template <typename T>
void ofxKuValueSmoothDirected(T &value, T target, float smooth0, float smooth1) {
	float smooth = (target < value) ? smooth0 : smooth1;
	ofxKuValueSmooth(value, target, smooth);
}
