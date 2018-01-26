#include "ofxKuFloodFill.h"
#include "ofxKuRaster.h"

//--------------------------------------------------------------
//sv=4 or 8 - connectivity of pixels
vector<int> ofxKuRoseOfWinds(int sv, int w) {
	vector<int> rose(sv);
	rose[0] = 1;
	rose[1] = -1;
	rose[2] = w;
	rose[3] = -w;
	if (sv == 8) {
		rose[4] = 1 + w;
		rose[5] = 1 - w;
		rose[6] = -1 + w;
		rose[7] = -1 - w;
	}
	return rose;
}

//--------------------------------------------------------------
size_t ofxKuFloodFill(vector<unsigned char> &input, int w, int h, int sv,
                 int x0, int y0, int search, int fillColor, vector<int> *outPoints) {
	vector<int> *res = (outPoints)?outPoints:(new vector<int>());
	res->clear();
	if (input[x0+w*y0] != search) return 0;
    res->push_back(x0 + w*y0);
    input[x0 + w*y0] = fillColor;

	vector<int> rose = ofxKuRoseOfWinds(sv, w);

    size_t begin = 0;
    while (begin < res->size()) {
        int p = (*res)[begin];
        //int px = p%w;
        //int py = p/h;

        begin++;
		for (int i=0; i<sv; i++) {
			int q = p+rose[i];
			int x = q % w;
			int y = q / w;
			if (x >= 0 && x < w && y >= 0 && y < h && input[q] == search) {
				res->push_back(q);
				input[q] = fillColor;
			}
		}
    }
	int n = res->size();
    if ( !outPoints ) { delete res; }
    return n;
}

//--------------------------------------------------------------
//remove small blobs, which has values [good_val0, good_val1] and area < min_area. For this blobs, set these to erase_val
void ofxKuRasterBlobsFilter(vector<unsigned char> &input, vector<unsigned char> &output, int w, int h, int sv,
							int min_area, unsigned char good_val0, unsigned char good_val1, unsigned char erase_val ) {
	output = input;
	vector<unsigned char> mask;
	ofxKuRasterRangeMask(input, mask, w, h, good_val0, good_val1, (unsigned char) (0), (unsigned char) (255) );
	vector<int> fillPoints;
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			if (mask[x+w*y] == 255) {
				int area = ofxKuFloodFill(mask, w, h, sv, x, y, 255, 128, &fillPoints);
				if (area < min_area) {
					//erasing small area
					for (int i=0; i<fillPoints.size(); i++) {
						int p = fillPoints[i];
						output[p%w + w*(p/w)] = 0;
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
//Find blobs with area in the given range and also sum(field values over blob) in the given range
void ofxKuBlobDetectInField(vector<int> &field, int w, int h, const ofxKuBlobDetectorParams &params, vector<ofxKuBlob> &blobs) {
	
	vector<int> rose = ofxKuRoseOfWinds(params.sv, w);

	//scan
	vector<unsigned char> mask(w*h, 1);  //TODO here is memory allocation, please declare as static to works faster
	vector<int> res;
	for (int Y = 0; Y < h; Y++) {
		for (int X = 0; X < w; X++) {
			int I = X + w*Y;
			if (field[I] > 0 && mask[I]) {
				mask[I] = 0;
				int sum = field[I];
				res.clear();
				res.push_back(I);

				size_t begin = 0;
				while (begin < res.size()) {
					int p = res[begin];
					begin++;
					for (int i = 0; i<params.sv; i++) {
						int q = p + rose[i];
						int x = q % w;
						int y = q / w;
						if (x >= 0 && x < w && y >= 0 && y < h && field[q] > 0 && mask[q]) {
							res.push_back(q);
							mask[q] = 0;
							sum += field[q];
						}
					}
				}
				if ((res.size() >= params.min_blob_area || params.min_blob_area == -1)
					&& (res.size() <= params.max_blob_area || params.max_blob_area == -1)
					&& (sum >= params.min_count_in_blob || params.min_count_in_blob == -1)
					&& (sum <= params.max_count_in_blob || params.max_count_in_blob == -1)
					) {
					blobs.push_back(ofxKuBlob());
					ofxKuBlob &blob = blobs[blobs.size() - 1];
					blob.w = w;
					blob.h = h;
					blob.pnt = res;
					blob.Sum = sum;
				}
			}
		}
	}

}


//--------------------------------------------------------------
ofPoint ofxKuBlob::center_mass() {
	double X = 0;
	double Y = 0;
	int n = pnt.size();
	for (int i = 0; i < n; i++) {
		X += pnt[i] % w;
		Y += pnt[i] / w;
	}
	if (n) {
		X /= n;
		Y /= n;
	}
	return ofPoint(X, Y);
}

//--------------------------------------------------------------
float ofxKuBlob::rad(ofPoint center) {
	float R = 0;
	int n = pnt.size();
	for (int i = 0; i < n; i++) {
		int x = pnt[i] % w;
		int y = pnt[i] / w;
		R = max(R, ofDist(x, y, center.x, center.y));
	}
	return R;
}

//--------------------------------------------------------------
void ofxKuBlob::draw_to_raster(vector<unsigned char> &raster, unsigned char value) {
	int n = pnt.size();
	for (int i = 0; i < n; i++) {
		int x = pnt[i] % w;
		int y = pnt[i] / w;
		raster[x + w*y] = value;
	}
}

//--------------------------------------------------------------
