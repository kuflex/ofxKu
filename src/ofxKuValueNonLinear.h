#pragma once

//Nonlinear morph from 0 to 1

#include "ofMain.h"

//Smooth transition from 0 to 1, f(0)=0, f(1)=1, f'(0)=f'(1)=0
template <typename T>
T ofxKuValueSpline2(T t) {
    return t*t*(3-2*t);
}

//template <typename T>
//T ofxKuValueSpline3(T t) {
//    return t*t*t*(4-3*t);
//}

//template <typename T>
//T ofxKuValueSpline4(T t) {
//    return t*t*t*t*(5-4*t);
//}
