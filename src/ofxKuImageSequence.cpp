#include "ofxKuImageSequence.h"

//--------------------------------------------------------------
void ofxKuImageSequence::load(string folder) {
	ofDirectory dir;
	int n = dir.listDir(folder);
	tex_.resize(n);
	for (int i = 0; i < n; i++) {
		ofLoadImage(tex_[i], dir.getPath(i));
	}

}

//--------------------------------------------------------------
void ofxKuImageSequence::setAnchorPercent(float x, float y) {
	for (int i = 0; i < tex_.size(); i++) {
		tex_[i].setAnchorPercent(x, y);
	}
}

//--------------------------------------------------------------
int ofxKuImageSequence::size() {
	return tex_.size();
}

//--------------------------------------------------------------
ofTexture &ofxKuImageSequence::get_texture(int i) {
	if (i >= 0 && i < size()) {
		return tex_[i];
	}
	else {
		if (!empty_.isAllocated()) {
			empty_.allocate(1, 1, GL_RGB);
		}
		return empty_;
	}
}

//--------------------------------------------------------------
void ofxKuImageSequence::draw(int i, float x, float y, float w, float h) {
	if (i >= 0 && i < size()) {
		if (w == 0 && h == 0) tex_[i].draw(x, y);
		else tex_[i].draw(x, y, w, h);
	}
}

//--------------------------------------------------------------

