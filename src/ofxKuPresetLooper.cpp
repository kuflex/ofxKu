#include "ofxKuPresetLooper.h"

//--------------------------------------------------------------
void ofxKuPresetLooper::setup(ofxKuPreset *preset) {
	preset_ = preset;
	time0_ = ofGetElapsedTimef();
	loop_pos_last_ = -1;
	show_ = 0;
}

//--------------------------------------------------------------
void ofxKuPresetLooper::update() {
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time-time0_, 0.01, 0.1);
	time0_ = time;

	//looping
	if (*enable_) {
		if (show_>=*show_time_) {
			show_ = 0;
			int &pos = *loop_pos_;
			pos++;
			if (pos >= *loop_start_ + *loop_len_) {
				pos = *loop_start_;
			}
		}
		else {
			show_ += dt;
		}
	}
	//transition
	if (loop_pos_last_ != *loop_pos_) {
		loop_pos_last_ = *loop_pos_;
		preset_->trans_to(*loop_pos_-1, trans_time0_);
	}
}

//--------------------------------------------------------------
void ofxKuPresetLooper::restart() {
	*loop_pos_ = *loop_start_;
	show_ = 0;
}

//--------------------------------------------------------------
