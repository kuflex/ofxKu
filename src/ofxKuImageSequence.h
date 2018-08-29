#pragma once

#include "ofMain.h"

//Draw image sequence

struct ofxKuImageSequence {
	void load(string folder);
	int size();
	ofTexture &get_texture(int i);
	vector<ofTexture> &textures() { return tex_; }

	void draw(int i, float x, float y, float w = 0, float h = 0);
	void setAnchorPercent(float x, float y);

protected:
	vector<ofTexture> tex_;
	ofTexture empty_;

};