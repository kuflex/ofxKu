#pragma once

//Rasterize point clouds

#include "ofMain.h"
#include "ofxKuFloodFill.h"


struct ofxKuPcRasterize {	
	//projection to Z, raster contains number of points
	static void rasterize_z_count(vector<ofPoint> &points, ofPoint &bound0, ofPoint &bound1,
		int raster_w, int raster_h, vector<int> &raster_out);

	//binary projection to Z. Compute raster and blobs	
	static void get_blobs(vector<ofPoint> &points, ofPoint bound0, ofPoint bound1, const ofxKuBlobDetectorParams &params,
		int raster_w, int raster_h, vector<unsigned char> &raster_out, vector<ofxKuBlob> &blobs);

	//refilter point cloud and make points back to coordinate system, with z=0
	static void refilter_z(vector<ofPoint> &points, ofPoint bound0, ofPoint bound1, const ofxKuBlobDetectorParams &params,
		int raster_w, int raster_h, vector<ofPoint> &points_out);


};


