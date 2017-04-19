#include "ofxKuBufferRecorder.h"

//--------------------------------------------------------------
ofxKuBufferRecorder::ofxKuBufferRecorder() {
	frame_ = 0;
	recording_ = false;
}

//--------------------------------------------------------------
void ofxKuBufferRecorder::start_rec(string folder) {	//folder must exists
	folder_ = folder;
	recording_ = true;
	frame_ = 0;
}

//--------------------------------------------------------------
void ofxKuBufferRecorder::stop_rec() {
	recording_ = false;
}

//--------------------------------------------------------------
bool ofxKuBufferRecorder::is_recording() {
	return recording_;
}

//--------------------------------------------------------------
void ofxKuBufferRecorder::store_buffer(vector<unsigned char> &buffer) {
	if (recording_) {
		string fileName = folder_ + "/" + ofToString(frame_,5,'0');
		fileName = ofToDataPath(fileName);
		FILE *file = fopen(fileName.c_str(),"wb");
		if (file) {
			fwrite(&buffer[0], 1, buffer.size(), file);
			frame_++;
			fclose(file);
		}
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
ofxKuBufferPlayer::ofxKuBufferPlayer() {
	playing_ = false;
	fps_ = 30;

	time_ = 0;
	isFrameNew_ = false;
}

//--------------------------------------------------------------
void ofxKuBufferPlayer::set_fps(float fps) {
	fps_ = fps;
}

//--------------------------------------------------------------
void ofxKuBufferPlayer::start_play(string folder) {	//folder will be created
	folder_ = folder;
	playing_ = true;
	ofDirectory dir;
	int n = dir.listDir(folder);
	files.resize(n);
	for (int i=0; i<n; i++) {
		files[i] = dir.getPath(i);
	}
	
	time_frame_ = 0;
	frame_ = 0;

	cout << "start play " << folder << " " << n << endl;
}

//--------------------------------------------------------------
void ofxKuBufferPlayer::stop_play() {
	playing_ = false;
}

//--------------------------------------------------------------
bool ofxKuBufferPlayer::is_playing() {
	return playing_;
}

//--------------------------------------------------------------
bool ofxKuBufferPlayer::isFrameNew() {
	return isFrameNew_;
}

//--------------------------------------------------------------
vector<unsigned char> &ofxKuBufferPlayer::getBuffer() {	//please use buffer before next update() calling
	return buffer_;
}

//--------------------------------------------------------------
bool ofxKuBufferPlayer::get_next_frame() {
	int n = files.size();
	if (n==0) return false;
	int f = frame_ % n;
	frame_ = f;
	frame_++;
	string fileName = folder_ + "/" + ofToString(f,5,'0');
	fileName = ofToDataPath(fileName);
	FILE *file = fopen(fileName.c_str(),"rb");
	if (file) {
		ofFile file_f(fileName);
		size_t size = file_f.getSize();
		buffer_.resize(size);
		fread(&buffer_[0], 1, buffer_.size(), file);
		fclose(file);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
void ofxKuBufferPlayer::update() {
	if (is_playing()) {
		float time = ofGetElapsedTimef();
		float dt = ofClamp(time - time_, 0.001, 1);
		time_ = time;

		cout << "ofxKuBufferPlayer::update(), dt " << dt << endl;
		isFrameNew_ = false;
		time_frame_ += dt;
		while (time_frame_ > 1.0 / fps_ && dt>0) {
			get_next_frame();
			time_frame_ -= dt;
			isFrameNew_ = true;
		}
	}

}

//--------------------------------------------------------------
