#pragma once

//Analyzing file creation time
//Currently uses POCO, so works for oF 0.8.4, not oF 0.9.X

#include "ofMain.h"

/*
struct ofxKuFileTime {
	//This function is usable for updating caches.
	//It checks if fileName1 is newer than fileName2
	//if one of the files doesn't exists, returns true
	static bool isNewerThan(string fileName1, string fileName2);
};
*/

//bool Filetime_is_file_older_hours(string fileName, int hours);