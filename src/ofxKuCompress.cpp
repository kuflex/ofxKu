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
void ofxKuPackToBits(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut) {
	int size = dataIn.size();
	int n = size / 8;
	if (n * 8 < size) n++;

	dataOut.resize(n);
	for (int i = 0; i<n; i++) {
		int I = i * 8;
		int K = (8<=size - I)?8:(size-I);
		int v = 0;
		int d = 1;
		for (int k = 0; k<K; k++) {
			if (dataIn[I + k] > 0) {
				v += d;
			}
			d *= 2;
		}
		dataOut[i] = v;
	}
}

//--------------------------------------------------------------
void ofxKuUnpackFromBits(vector<unsigned char> &dataIn, int sizeOut, vector<unsigned char> &dataOut) {
	dataOut.resize(sizeOut);
	int v = 0;
	for (int i = 0; i<sizeOut; i++) {
		if (i % 8 == 0) {
			v = dataIn[i / 8];
		}
		dataOut[i] = (v % 2)*255;
		v /= 2;
	}
}


//--------------------------------------------------------------
