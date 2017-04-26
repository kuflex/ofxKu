#pragma once

//Check if value was changed

#include "ofMain.h"

//integer types
template <typename T>
bool ofxKuValueCheckChange(T &value, const T &new_value) {
	if (value != new_value) {
		value = new_value;
		return true;
	}
	return false;
}
