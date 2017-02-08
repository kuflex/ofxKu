#include "ofxKuFloodFill.h"

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

