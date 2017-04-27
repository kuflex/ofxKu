#pragma once

//Utilities for 3D objects - loading OBJ files, computing normals

#include "ofMain.h"

void ofxKuLoadObjFile( ofMesh &mesh, string fileName, bool useTex,
                   bool setupNormals, bool normalize,
                   bool separateFaces, bool shuffle, int texW, int texH,
				   bool caching_to_ply = true);

void ofxKuSetNormals( ofMesh &mesh );

//shuffle vertices and triangles
void ofxKuMeshShuffle( vector<ofPoint> &v, vector<ofIndexType> &t, vector<ofVec2f> &tex,
                   bool useTex = true, float shuffle_count=2 );

//-------------------------







