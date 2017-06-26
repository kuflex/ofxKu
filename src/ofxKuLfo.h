#pragma once

//Simple LFO module

#include "ofMain.h"


struct ofxKuLfo {
    ofxKuLfo();

    void setup(float &value, int &enabled, float &value0, float &range, float &speed);
    void update(float dt);

private:
    float *value_;
    int *enabled_;
    float *value0_;
    float *range_;
    float *speed_;
    
    float phase_;
    
};


