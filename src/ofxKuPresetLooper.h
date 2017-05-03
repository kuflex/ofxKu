#pragma once

//Preset looper

#include "ofMain.h"
#include "ofxKuPreset.h"


struct ofxKuPresetLooper {
	void setup(ofxKuPreset *preset);
	void update();
	void restart();

	bool pos_is_inside_bank();
	void recall(int id);
	void recall_random();	

    ofxKuPresetLooper() {
		enable0_ = 0;
		loop_start0_ = 1;
		loop_end0_ = 5;
		loop_pos0_ = 1;
		show_time0_ = 3;
		trans_time0_ = 0.5;
		preset_num0_ = 0;
		timer0_ = 0;

		link_enable(&enable0_);
		link_loop_start(&loop_start0_);
		link_loop_end(&loop_end0_);
		link_loop_pos(&loop_pos0_);
		link_show_time(&show_time0_);
		link_trans_time(&trans_time0_);

		link_preset_num(&preset_num0_);
		link_timer(&timer0_);
	}

	void link_enable(int *v)				{ enable_ = v; }
	void link_loop_start(int *id)			{ loop_start_ = id; }
	void link_loop_end(int *end)			{ loop_end_ = end; }
	void link_loop_pos(int *pos)			{ loop_pos_ = pos; }
	void link_show_time(float *time)		{ show_time_ = time; }
	void link_trans_time(float *time)		{ trans_time_ = time; }
	void link_preset_num(int *preset_num)	{ preset_num_ = preset_num; }
	void link_timer(float *timer)			{ timer_ = timer; }

	float glob_timer() { return glob_timer_/60.0; }

protected:
	ofxKuPreset *preset_;
	int *enable_;
	int *loop_start_;	
	int *loop_end_;
	int *loop_pos_;		
	float *show_time_;
	float *trans_time_;

	int *preset_num_;

	int enable0_;
	int loop_start0_;
	int loop_end0_;
	int loop_pos0_;
	float show_time0_;
	float trans_time0_;
	int preset_num0_;
	float timer0_;

	//---
	float time0_;	//for dt measurement
	float *timer_;	//current preset showing timer
	int loop_pos_last_;	

	float glob_timer_start_;
	float glob_timer_;	//global loop timer

	void begin();

};


