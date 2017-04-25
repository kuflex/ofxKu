#pragma once

//kuSlowBit - бит, который переключается из 0 в 1 и 1 в 0 постепенно.

#include "ofMain.h"


struct ofxKuSlowBit {
    ofxKuSlowBit();
    //line is 4 numbers with transition times, 0->0, 0->1, 1->0, 1->1,
    //for example, "1.0, 0.1, 1.0, 0.1"
    //void setup( string line, string title="" );
	void setup( float time00, float time01, float time10, float time11);
    void update( float dt, int target ); //target - state to go
    void update_times( float time00, float time01, float time10, float time11 );

    int state();       //current state
    float stateFloat() { return _value; }   //current state as float
    bool became0();     //state became 0
    bool became1();     //state became 1
    bool changed();     //state was changes

    void reset0();
    void reset( int value );
    
    //void draw( float x, float y, float w, float h );

private:
	//transition speeds
    float speed01, speed00, speed10, speed11;

    int _state;     
    int _lastState;
    float _value;  

};


