#pragma once

//Working with files

#include "ofMain.h"


bool ofxKuFileExists( string fileName );
int ofxKuFileSize( string fileName );

vector<string> ofxKuFileReadStrings( string fileName );
bool ofxKuFileWriteStrings( const vector<string> &list, string fileName );

//string ofxKuFileGetExtension( string fileName, bool lowerCase = true );
//vector<string> readStringsFilterAndNotEmpty( const string &fileName );
//vector<float> readFloats( const string &fileName );
//bool writeFloats( const vector<float> &list, const string &fileName );
//vector<int> readInts( const string &fileName );
//bool writeInts( const vector<int> &list, const string &fileName );
//	struct PairFloat {
//		PairFloat( const string &name0, float value0 ) {
//			name = name0;
//			value = value0;
//		}
//		string name;
//		float value;
//	};

//	static vector<PairFloat> readPairs( const string &fileName ); 
//	static void writePairs( const vector<PairFloat> &list, const string &fileName  ); 
//	static float findValue( const vector<PairFloat> &list, string name, float defValue = 0 );

//static string readOneString( const string &fileName );
//static void writeOneString( const string &fileName, const string &s );


