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
	if (size_ > 0) {
		a = fmodf(a, M_TWO_PI) * size_ / M_TWO_PI;
		return ofxKuInterpolate_1d(a, sin_, size_ + 1);
	}
	else return 0;
}

//--------------------------------------------------------------
float ofxKuMathFastSinCos::get_cos(float a) {
	if (size_ > 0) {
		a = fmodf(a, M_TWO_PI) * size_ / M_TWO_PI;
		return ofxKuInterpolate_1d(a, cos_, size_ + 1);
	}
	else return 1;
}

//--------------------------------------------------------------





