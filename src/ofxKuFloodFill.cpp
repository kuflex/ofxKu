#include "ofxKuFloodFill.h"
#include "ofxKuRaster.h"

//--------------------------------------------------------------

size_t ofxKuFloodFill(vector<unsigned char> &input, int w, int h, int sv,
                 int x0, int y0, int search, int fillColor, vector<int> *outPoints) {
	vector<int> *res = (outPoints)?outPoints:(new vector<int>());
	res->clear();
	if (input[x0+w*y0] != search) return 0;
    res->push_back(x0 + w*y0);
    input[x0 + w*y0] = fillColor;

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


    size_t begin = 0;
    while (begin < res->size()) {
        int p = (*res)[begin];
        //int px = p%w;
        //int py = p/h;

        begin++;
		for (int i=0; i<sv; i++) {
			int q = p+rose[i];
			if (q>=0 && q<w*h && input[q] == search) {
				res->push_back(q);
				input[q] = fillColor;
			}
		}

        /*for (int y = py - 1; y <= py + 1; y++)  {
            for (int x = px - 1; x <= px + 1; x++) {
                if (x >= 0 && x < w && y >= 0 && y < h
                        && (sv==8 || x == px || y == py)
                        && input( x y ) == search ) {
                    res.push_back( int2(x,y) );
                    input.pixel( x, y ) = fillColor;
                }

            }
        }*/
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
