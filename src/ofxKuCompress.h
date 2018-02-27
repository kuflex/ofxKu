#pragma once

//RLE compression

#include <vector>
using namespace std;

//RLE compression
//if v==0, then 0,count(0..255)
//if v=1..255, then just v
void ofxKuCompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut);

//RLE decompression
//size - expected size
void ofxKuDecompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut, int size);


