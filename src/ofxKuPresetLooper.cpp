#include "ofxKuPresetLooper.h"

//--------------------------------------------------------------
void ofxKuPresetLooper::setup(ofxKuPreset *preset) {
	preset_ = preset;
	time0_ = ofGetElapsedTimef();
	loop_pos_last_ = -1;
}

//--------------------------------------------------------------
void ofxKuPresetLooper::update() {
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time-time0_, 0.01, 0.1);
	time0_ = time;

	//looping
	if (*enable_) {
		if (*timer_>=*show_time_) {
			*timer_ = -*trans_time_; //wait for transition
			int &pos = *loop_pos_;
			pos++;
			if (pos > *loop_end_) {
				pos = *loop_start_;
			}
		}
		else {
			*timer_ += dt;
		}
	}
	//transition
	if (loop_pos_last_ != *loop_pos_) {
		int id = *loop_pos_;
		loop_pos_last_ = id;
		if (*enable_) {
			preset_->trans_to(id, *trans_time_); //if enabled - smooth transition
		}
		else {
			preset_->recall(id);				//if disabled - fast switch
		}
		*preset_num_ = id;
	}
}

//--------------------------------------------------------------
void ofxKuPresetLooper::restart() {
	*loop_pos_ = *loop_start_;
	preset_->recall(*loop_pos_);
	*timer_ = 0;
}

//--------------------------------------------------------------
