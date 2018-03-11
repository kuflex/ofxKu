#pragma once

//Generator of values with given

#include "ofMain.h"


struct ofxKuProbability {
	ofxKuProbability();

	//Setup from density array, density can be unnormalized
	void setup(const vector<float> &density);

	//Setup from file, density can be unnormalized
	//File consists of lines with density numbers:
	//0.001
	//0.2
	//...
	void setup(string density_file);
	float generate(float range0, float range1);

private:
	vector<float> prob_;
	int n_;

};


