#include "ofxKuDrawRasters.h"

//--------------------------------------------------------------
void ofxKuDrawRaster(vector<unsigned char> &pix, int w, int h, float X, float Y, float W, float H) {
	if (pix.size() != w*h) return;
	ofTexture texture;
	texture.loadData(&pix[0],w,h,GL_LUMINANCE);
	texture.draw(X,Y,W,H);
}

//--------------------------------------------------------------
void ofxKuDrawRaster(vector<float> &pix, int w, int h, float X, float Y, float W, float H, float val0, float val1) {
	if (pix.size() != w*h) return;
	vector<unsigned char> pix1(w*h);
	for (int i=0; i<w*h; i++) {
		pix1[i] = ofMap(pix[i],val0,val1,0,255,true);
	}
	ofxKuDrawRaster(pix1, w, h, X, Y, W, H);
}

//--------------------------------------------------------------
void ofxKuOfGrayPixelsToRaster(ofPixels &pixels, vector<unsigned char> &pix, int &w, int &h) {
	w = pixels.getWidth();
	h = pixels.getHeight();
	pix.resize(w*h);
	unsigned char *data = pixels.getPixels();
	for (int i=0; i<w*h; i++) {
		pix[i] = data[i];
	}
}

//--------------------------------------------------------------
