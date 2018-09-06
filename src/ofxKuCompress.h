#pragma once

//RLE compression

#include <vector>
using namespace std;

//RLE compression for masks - zero values are compressed
//if v==0, then 0,count(0..255)
//if v=1..255, then just v
void ofxKuCompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut);

//RLE decompression
//size - expected size
void ofxKuDecompressRle(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut, int size);

//RLE compression for depth data - zero values are compressed
//if v==0, then 0,count(0..65535)
//if v=1..65535, then just v
void ofxKuCompressRle(unsigned short *dataIn, int size, vector<unsigned short> &dataOut);
void ofxKuCompressRle(vector<unsigned short> &dataIn, vector<unsigned short> &dataOut);

//RLE decompression
//size - expected size
void ofxKuDecompressRle(vector<unsigned short> &dataIn, vector<unsigned short> &dataOut, int size);


//Pack to bits and unpack from bits - use for compressing binary masks before transmission
void ofxKuPackToBits(vector<unsigned char> &dataIn, vector<unsigned char> &dataOut);
void ofxKuUnpackFromBits(vector<unsigned char> &dataIn, int sizeOut, vector<unsigned char> &dataOut);
