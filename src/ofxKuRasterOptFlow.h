#pragma once

//Computing optical flow for binary masks

#include "ofMain.h"



struct ofxKuRasterOptFlow {
	ofxKuRasterOptFlow();
	void setup(int w, int h);
	void update(vector<unsigned char> mask, int w, int h);

	vector<float> &flowX() { return flowX_; }
	vector<float> &flowY() { return flowY_; }
	
	void draw(float x, float y, float w, float h, float amp, int step);
	void resizeFlowTo(int outW, int outH, vector<float> &outX, vector<float> &outY);

	//params
	int w();			//flow size
	int h();
	int blur_input;		//input blurring
	int blur_data;		//data blurring - for computing mean value


private:
	int w_, h_;
	vector<float> flowX_, flowY_;

	vector<float> mask1_, mask2_;

	vector<float> mask_temp_;

};


