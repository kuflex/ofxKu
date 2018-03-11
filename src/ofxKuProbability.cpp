#include "ofxKuProbability.h"
#include "ofxKuFile.h"

//--------------------------------------------------------------
ofxKuProbability::ofxKuProbability() {
	n_ = 0;
}

//--------------------------------------------------------------
//Setup from density array, density can be unnormalized
void ofxKuProbability::setup(const vector<float> &density) {
	prob_ = density;
	n_ = prob_.size();
	double sum = 0;
	for (int i = 0; i<n_; i++) {
		sum += prob_[i];
	}
	if (sum > 0) {
		for (int i = 0; i<n_; i++) {
			prob_[i] /= sum;
		}
	}
}

//--------------------------------------------------------------
void ofxKuProbability::setup(string density_file) {
	vector<string> file = ofxKuFileReadStrings(density_file);
	int n = file.size();
	vector<float> v(n);
	for (int i = 0; i<n; i++) {
		v[i] = max(ofToFloat(file[i]), 0.0f);
	}
	setup(v);
}

//--------------------------------------------------------------
float ofxKuProbability::generate(float range0, float range1) {
	if (n_ <= 1) return range0;
	float p = ofRandom(0, 1);
	float sum = 0;
	int n = prob_.size();
	int I = 0;
	for (int i = 0; i<n; i++) {
		if (p <= sum) {
			I = i;
			break;
		}
		sum += prob_[i];
	}
	return ofMap(I, 0, n - 1, range0, range1);
}

//--------------------------------------------------------------
