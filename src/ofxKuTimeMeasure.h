#pragma once

//Time measurement

#include "ofMain.h"


struct ofxKuTimeMeasure {

	void start();
	float measure();	//can call multiple times
	void measure(float &out_duration); //can call multiple times
	void measure(string &out_duration); //can call multiple times

private:
	float time_ = 0;

};


