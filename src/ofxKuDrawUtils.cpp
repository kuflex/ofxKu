#include "ofxKuDrawUtils.h"


//--------------------------------------------------------------
void ofxKuDrawTextureFit(ofTexture &tex, float x, float y, float w, float h) {
	float tw = tex.getWidth();
	float th = tex.getHeight();
	if (tw>0 && th>0) {
		float scl = min(w/tw,h/th);
		tw *= scl;
		th *= scl;
		tex.draw(x+w/2-tw/2, y+h/2-th/2, tw, th);
	}
}
//--------------------------------------------------------------

