#include "ofxKuPcRasterize.h"

//--------------------------------------------------------------
//projection to Z, raster contains number of points
void ofxKuPcRasterize::rasterize_z_count(vector<ofPoint> &points, ofPoint &bound0, ofPoint &bound1,
	int raster_w, int raster_h, vector<int> &raster_out, bool fill_by_zeros) {
	raster_out.resize(raster_w * raster_h);
	if (fill_by_zeros) {
		fill(raster_out.begin(), raster_out.end(), 0);
	}

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
//projection to Y, raster contains number of points
void ofxKuPcRasterize::rasterize_y_count(vector<ofPoint> &points, ofPoint &bound0, ofPoint &bound1,
	int raster_w, int raster_h, vector<int> &raster_out, bool fill_by_zeros) {
	raster_out.resize(raster_w * raster_h);
	if (fill_by_zeros) {
		fill(raster_out.begin(), raster_out.end(), 0);
	}

	if (bound1.x - bound0.x <= 0 || bound1.z - bound0.z <= 0) return;

	float kx = raster_w / (bound1.x - bound0.x);
	float kz = raster_h / (bound1.z - bound0.z);
	for (int i = 0; i < points.size(); i++) {
		ofPoint &p = points[i];
		int X = int((p.x - bound0.x) * kx);
		if (X >= 0 && X < raster_w) {
			int Z = int((p.z - bound0.z) * kz);
			if (Z >= 0 && Z < raster_h) {
				raster_out[X + raster_w * Z]++;
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
//refilter point cloud and make points back to coordinate system, with z=0
void ofxKuPcRasterize::refilter_z(vector<ofPoint> &points, ofPoint bound0, ofPoint bound1, const ofxKuBlobDetectorParams &params,
	int raster_w, int raster_h, vector<ofPoint> &points_out) {

	points_out.clear();
	if (raster_w <= 0 || raster_h <= 0) return;

	vector<unsigned char> raster_out;
	vector<ofxKuBlob> blobs;

	get_blobs(points, bound0, bound1, params, raster_w, raster_h, raster_out, blobs);
	

	float kx = (bound1.x - bound0.x) / raster_w;
	float ky = (bound1.y - bound0.y) / raster_h;

	for (int y=0; y<raster_h; y++) {
		for (int x=0; x<raster_w; x++) {
			if (raster_out[x+raster_w*y] > 0) {
				points_out.push_back(ofPoint(bound0.x + kx * x, bound0.y + ky * y, 0));
			}
		}
	}

}

//--------------------------------------------------------------
 
