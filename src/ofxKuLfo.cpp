#include "ofxKuLfo.h"


//--------------------------------------------------------------
ofxKuLfo::ofxKuLfo() {
    phase_ = 0;
}
    
//--------------------------------------------------------------
void ofxKuLfo::setup(float &value, int &enabled, float &value0, float &range, float &speed) {
    value_      = &value;
    enabled_    = &enabled;
    value0_     = &value0;
    range_      = &range;
    speed_      = &speed;
    
}

//--------------------------------------------------------------
void ofxKuLfo::update(float dt) {
    if (*enabled_) {
        phase_ += *speed_ * dt;
        float v = sin(phase_ * M_TWO_PI);
        *value_ = *value0_ + *range_*v;
    }
    else {
        *value_ = *value0_;
    }
}

//--------------------------------------------------------------
