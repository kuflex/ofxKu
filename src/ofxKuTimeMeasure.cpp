#include "ofxKuTimeMeasure.h"

//--------------------------------------------------------------
void ofxKuTimeMeasure::start() {
	time_ = ofGetElapsedTimef();
}

//--------------------------------------------------------------
float ofxKuTimeMeasure::measure() {
	float time = ofGetElapsedTimef();
	float result = time - time_;
	time_ = time;
	return result;
}

//--------------------------------------------------------------
void ofxKuTimeMeasure::measure(float &out_duration) { //can call multiple times
	out_duration = measure();
}

//--------------------------------------------------------------
void ofxKuTimeMeasure::measure(string &out_duration) { //can call multiple times
	out_duration = ofToString(measure(), 4);
}

//--------------------------------------------------------------
