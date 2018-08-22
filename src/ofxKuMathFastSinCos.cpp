#include "ofxKuMathFastSinCos.h"
#include "ofxKuValueInterpolate.h"

//--------------------------------------------------------------
void ofxKuMathFastSinCos::setup(int table_size) {
	size_ = table_size;
	sin_.resize(size_+1);
	cos_.resize(size_+1);
	for (int i = 0; i < size_+1; i++) {
		float a = M_TWO_PI * float(i) / size_;
		sin_[i] = sin(a);
		cos_[i] = cos(a);
	}

}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_sin(float a) {
	if (a < 0) {
		a = fmodf(-a, M_TWO_PI) * size_ / M_TWO_PI;
		return -ofxKuInterpolate_1d(a, sin_, size_ + 1);
	}
	a = fmodf(a, M_TWO_PI) * size_ / M_TWO_PI;
	return ofxKuInterpolate_1d(a, sin_, size_ + 1);
}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_cos(float a) {
	if (a < 0) a = -a;
	a = fmodf(a, M_TWO_PI) * size_ / M_TWO_PI;
	return ofxKuInterpolate_1d(a, cos_, size_ + 1);
}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_sin_raw(float a) {	//without interpolation
	if (a < 0) {
		a = fmodf(-a, M_TWO_PI) * size_ / M_TWO_PI;
		return -sin_[int(a)];
	}
	a = fmodf(a, M_TWO_PI) * size_ / M_TWO_PI;
	return sin_[int(a)];
}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_cos_raw(float a) {
	a = fmodf(fabs(a), M_TWO_PI) * size_ / M_TWO_PI;
	return cos_[int(a)];
}


//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_sin_raw_nowarp(float a) {
	return sin_[int(a * size_ / M_TWO_PI)];
}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_cos_raw_nowarp(float a) {
	return cos_[int(a * size_ / M_TWO_PI)];
}


//--------------------------------------------------------------





