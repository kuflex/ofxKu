#pragma once

//Computing optical flow for binary masks

#include "ofMain.h"



struct ofxKuRasterOptFlow {
	ofxKuRasterOptFlow();
	void setup(int w, int h);   //320,180
	void update(vector<unsigned char> mask, int w, int h); //mask will be resized to optical flow size

	vector<float> &flowX() { return flowX_; }
	vector<float> &flowY() { return flowY_; }
	vector<float> &flowZ() { return flowZ_; }	//experimental
	
	void draw(float x, float y, float w, float h, float amp, int step);	//sets colors
	void resizeFlowTo(int outW, int outH, vector<float> &outX, vector<float> &outY);

	//params
	int w();			//flow size
	int h();
	int blur_input;		//input blurring (3)
	int blur_data;		//data blurring - for computing mean value (7)
	float eps_count;	//percent of pixels in area to use this for optical flow computing (0.05)


private:
	int w_, h_;
	vector<float> flowX_, flowY_, flowZ_;

	vector<float> mask1_, mask2_;
	vector<float> mask1Z_, mask2Z_;
	


	vector<float> mask_temp_;

};


