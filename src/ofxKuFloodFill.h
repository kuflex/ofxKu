#pragma once

#include "ofMain.h"

//Flood fill and blobs processing

//sv=4 or 8 - connectivity of pixels
vector<int> ofxKuRoseOfWinds(int sv, int w);

//Flood fill
//outPoints as x+w*y
size_t ofxKuFloodFill(vector<unsigned char> &input, int w, int h, int sv,
                 int x0, int y0, int search, int fillColor, vector<int> *outPoints = 0); 

//Remove small blobs, which has values [good_val0, good_val1] and area < min_area. For this blobs, set these to erase_val
//Function can work in-place, that is "output" can be "input"
void ofxKuRasterBlobsFilter(vector<unsigned char> &input, vector<unsigned char> &output, int w, int h, int sv,
							int min_area, unsigned char good_val0, unsigned char  good_val1, unsigned char erase_val );


//Blob data
struct ofxKuBlob {
	int w, h;
	vector<int> pnt;	//x = pnt[i] % w, y = pnt[i] / w;
	int Sum;			//field sum
	ofPoint center_mass();
	float rad(ofPoint center);
	void draw_to_raster(vector<unsigned char> &raster, unsigned char value);
};


//Parameters for searching blobs
struct ofxKuBlobDetectorParams {
	int sv;			//4 or 8 - connectivity
	int min_blob_area, max_blob_area;		//-1 means not use this restriction
	int min_count_in_blob, max_count_in_blob; //-1 means not use this restriction
	ofxKuBlobDetectorParams(int sv_, int min_blob_area_=-1, int max_blob_area_=-1,
		int min_count_in_blob_=-1, int max_count_in_blob_=-1) {
		sv = sv_;
		min_blob_area = min_blob_area_;
		max_blob_area = max_blob_area_;
		min_count_in_blob = min_count_in_blob_;
		max_count_in_blob = max_count_in_blob_;
	}
};


//Find blobs with area in the given range and also sum(field values over blob) in the given range
void ofxKuBlobDetectInField(vector<int> &field, int w, int h, const ofxKuBlobDetectorParams &params, vector<ofxKuBlob> &blobs);
