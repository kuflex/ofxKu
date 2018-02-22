#include "ofxKuCompress.h"

//--------------------------------------------------------------
//RLE compression for masks - zero values are compressed
//if v==0, then 0,count(0..255)
//if v=1..255, then just v
void ofxKuCompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut) {
	int n = dataIn.size();
	dataOut.reserve(n);
	int zero = 0;
	for (int i=0; i<n; i++) {
		unsigned char &v = dataIn[i];
		if (zero>0 && (zero==255 || v>0)) {
			dataOut.push_back(zero);
			zero = 0;
		}
		if (v == 0) {
			if (zero==0) dataOut.push_back(0);
			zero++;
		}
		else {
			dataOut.push_back(v);
		}
	}
	if (zero>0) dataOut.push_back(zero);
}

//--------------------------------------------------------------
//RLE decompression
//size - expected size
void ofxKuDecompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut, int size) {
	dataOut.resize(size);
	int n = dataIn.size();
	int k = 0;
	int state_zero=0;
	unsigned char fill_value = 0;
	unsigned char fill_count = 0;
	for (int i=0; i<n; i++) {
		unsigned char &v = dataIn[i];
		if (state_zero) {
			state_zero = 0;
			fill_value = 0;
			fill_count = v;
		}
		else {
			if (v==0) {
				state_zero = 1;
				fill_count = 0;
			}
			else {
				fill_value = v;
				fill_count = 1;
			}
		}
		for (int j=0; j<fill_count && k<size; j++) {
			dataOut[k++] = fill_value;
		}
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//RLE compression for depth data - zero values are compressed
//if v==0, then 0,count(0..65535)
//if v=1..65535, then just v
void ofxKuCompressRle(unsigned short *dataIn, int size, vector<unsigned short> &dataOut) {
	int n = size;
	dataOut.reserve(n);
	int zero = 0;
	for (int i = 0; i<n; i++) {
		unsigned short &v = dataIn[i];
		if (zero>0 && (zero == 65535 || v>0)) {
			dataOut.push_back(zero);
			zero = 0;
		}
		if (v == 0) {
			if (zero == 0) dataOut.push_back(0);
			zero++;
		}
		else {
			dataOut.push_back(v);
		}
	}
	if (zero>0) dataOut.push_back(zero);
}

//--------------------------------------------------------------
void ofxKuCompressRle(vector<unsigned short> &dataIn, vector<unsigned short> &dataOut) {
	ofxKuCompressRle(&dataIn[0], dataIn.size(), dataOut);
}

//--------------------------------------------------------------
//RLE decompression
//size - expected size
void ofxKuDecompressRle(vector<unsigned short> &dataIn, vector<unsigned short> &dataOut, int size) {
	dataOut.resize(size);
	int n = dataIn.size();
	int k = 0;
	int state_zero = 0;
	unsigned short fill_value = 0;
	unsigned short fill_count = 0;
	for (int i = 0; i<n; i++) {
		unsigned short &v = dataIn[i];
		if (state_zero) {
			state_zero = 0;
			fill_value = 0;
			fill_count = v;
		}
		else {
			if (v == 0) {
				state_zero = 1;
				fill_count = 0;
			}
			else {
				fill_value = v;
				fill_count = 1;
			}
		}
		for (int j = 0; j<fill_count && k<size; j++) {
			dataOut[k++] = fill_value;
		}
	}
}

//--------------------------------------------------------------
