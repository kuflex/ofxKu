#include "ofxKuPcRasterize.h"

//--------------------------------------------------------------
//projection to Z, raster contains number of points
void ofxKuPcRasterize::rasterize_z_count(vector<ofPoint> &points, ofPoint &bound0, ofPoint &bound1,
	int raster_w, int raster_h, vector<int> &raster_out) {
	raster_out.resize(raster_w * raster_h);
	fill(raster_out.begin(), raster_out.end(), 0);

	if (bound1.x - bound0.x <= 0 || bound1.y - bound0.y <= 0) return;

	float kx = raster_w / (bound1.x - bound0.x);
	float ky = raster_h / (bound1.y - bound0.y);
	for (int i = 0; i < points.size(); i++) {
		ofPoint &p = points[i];
		int X = int((p.x - bound0.x) * kx);
		if (X >= 0 && X < raster_w) {
			int Y = int((p.y - bound0.y) * ky);
			if (Y >= 0 && Y < raster_h) {
				raster_out[X + raster_w * Y]++;
			}
		}
	}
}

//--------------------------------------------------------------
void ofxKuPcRasterize::get_blobs(vector<ofPoint> &points, ofPoint bound0, ofPoint bound1, const ofxKuBlobDetectorParams &params,
	int raster_w, int raster_h, vector<unsigned char> &raster_out, vector<ofxKuBlob> &blobs) {

	blobs.clear();

	int w = raster_w;
	int h = raster_h;
	vector<int> field(w*h);				//TODO here is memory allocation, please declare as static to works faster
	rasterize_z_count(points, bound0, bound1, raster_w, raster_h, field);

	raster_out.resize(w*h);
	fill(raster_out.begin(), raster_out.end(), 0);
	//for (int i = 0; i < w*h; i++) {	//test of raw rasterization
	//	raster_out[i] = (field[i] > 0) ? 255 : 0;
	//}

	ofxKuBlobDetectInField(field, w, h, params, blobs);

	//draw blobs
	for (int i = 0; i < blobs.size(); i++) {
		blobs[i].draw_to_raster(raster_out, 255);
	}	
}

//--------------------------------------------------------------
 
