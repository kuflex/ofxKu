#pragma once

//Preset looper

#include "ofMain.h"
#include "ofxKuPreset.h"


struct ofxKuPresetLooper {
	void setup(ofxKuPreset *preset);
	void update();
	void restart();

    ofxKuPresetLooper() {
		enable0_ = 1;
		loop_start0_ = 1;
		loop_len0_ = 5;
		loop_pos0_ = 1;
		show_time0_ = 3;
		trans_time0_ = 0.5;
		link_enable(&enable0_);
		link_loop_start(&loop_start0_);
		link_loop_len(&loop_len0_);
		link_loop_pos(&loop_pos0_);
		link_show_time(&show_time0_);
		link_trans_time(&trans_time0_);
	}

	void link_enable(int *v)			{ enable_ = v; }
	void link_loop_start(int *id)		{ loop_start_ = id; }
	void link_loop_len(int *len)		{ loop_len_ = len; }
	void link_loop_pos(int *pos)		{ loop_pos_ = pos; }
	void link_show_time(float *time)	{ show_time_ = time; }
	void link_trans_time(float *time)	{ trans_time_ = time; }

protected:
	ofxKuPreset *preset_;
	int *enable_;
	int *loop_start_;	//starts with 1, not 0
	int *loop_len_;
	int *loop_pos_;		//starts with 1, not 0
	float *show_time_;
	float *trans_time_;

	int enable0_;
	int loop_start0_;
	int loop_len0_;
	int loop_pos0_;
	float show_time0_;
	float trans_time0_;

	//---
	float time0_;
	float show_;
	int loop_pos_last_;	//starts with 1, not 0


};


