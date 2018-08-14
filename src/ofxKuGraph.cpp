#include "ofxKuGraph.h"
#include "ofxKuFile.h"

//--------------------------------------------------------------
void ofxKuGraph::setup(int capacity) {
	set_capacity(capacity);
}

//--------------------------------------------------------------
void ofxKuGraph::set_capacity(int capacity) {
	if (capacity != n_) {
		n_ = capacity;
		data.clear();
	}
}

//--------------------------------------------------------------
void ofxKuGraph::save(string file_name) {
	if (file_name.empty()) {
		file_name = file_name_;
	}
	else {
		file_name_ = file_name;
	}
	if (!file_name.empty()) {
		int n = data.size();
		vector<string> file(n);
		for (int i = 0; i < n; i++) {
			file[i] = ofToString(data[i]);
		}
		ofxKuFileWriteStrings(file, file_name);
	}
}

//--------------------------------------------------------------
void ofxKuGraph::load(string file_name) {
	file_name_ = file_name;
	if (!file_name.empty()) {
		vector<string> file = ofxKuFileReadStrings(file_name);
		int n = file.size();
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i] = ofToFloat(file[i]);
		}
	}
}


//--------------------------------------------------------------
void ofxKuGraph::draw(float X, float Y, float W, float H,
	bool normalize,
	const ofColor &pen, const ofColor &background, const ofColor &frame) {
	ofPushMatrix();
	ofTranslate(X, Y);
	ofFill();
	ofSetColor(background);
	ofNoFill();
	ofRect(0, 0, W, H);
	ofSetColor(frame);
	ofRect(-1, -1, W + 2, H + 2);
	int n = data.size();
	if (n >= 2) {
		float scl = 1;
		if (normalize) {
			float maxx = get_max();
			if (maxx > 0.000001) scl = 1.0 / maxx;
		}
		//scaling
		ofTranslate(0, H);
		ofScale(W / (n - 1), -H*scl);


		ofSetColor(pen);
		for (int i = 0; i < n-1; i++) {
			ofLine(i, data[i], i + 1, data[i + 1]);
		}
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofxKuGraph::push(float value) {
	if (n_ > 0) {
		data.push_back(value);
		while (data.size() > n_) {
			data.erase(data.begin());
		}
	}
}

//--------------------------------------------------------------
float ofxKuGraph::get_min() {
	float v = 1;
	for (int i = 0; i < data.size(); i++) {
		v = min(v, data[i]);
	}
	return v;
}

//--------------------------------------------------------------
float ofxKuGraph::get_max() {
	float v = 0;
	for (int i = 0; i < data.size(); i++) {
		v = max(v, data[i]);
	}
	return v;
}

//--------------------------------------------------------------
