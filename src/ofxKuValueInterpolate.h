#pragma once

//Interpolation

#include "ofMain.h"

template <typename T>
float ofxKuInterpolate_1d(T t, vector<T> &V, int n) {	//interpolate array, t=0..n-1
	int k = int(t);
	int k1 = min(k + 1, n - 1);
	t -= k;
	T v = ofLerp(V[k], V[k1], t);
	return v;
}

//--------------------------------------------------------------
template <typename T>
float interpolate_1d_y(T t, vector<ofPoint> &V, int n) { //interpolate array, t=0..n-1
	int k = int(t);
	int k1 = min(k + 1, n - 1);
	t -= k;
	float v = ofLerp(V[k].y, V[k1].y, t);
	return v;
}

//--------------------------------------------------------------

