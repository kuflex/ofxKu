#pragma once

#include "ofMain.h"

//Graph, working as storage with fixed history length

struct ofxKuGraph {
	void setup(int capacity);
	void save(string file_name = "");
	void load(string file_name);

	void set_capacity(int capacity);
	void draw(float X, float Y, float W, float H,
		bool normalize = false,
		const ofColor &pen = ofColor(255), 
		const ofColor &background = ofColor(0),
		const ofColor &frame = ofColor(64));
	void push(float value);
	vector<float> data;
	int n_ = 0;

	float get_min();
	float get_max();

	string file_name_ = "";
};

