#include "ofxKuSlowBit.h"


//--------------------------------------------------------------
ofxKuSlowBit::ofxKuSlowBit()
{
    speed00 = speed01 = speed10 = speed11 = 1.0;
    _state = 0;
    _lastState = _state;
    _value = _state;
}


//--------------------------------------------------------------
void ofxKuSlowBit::setup(float time00, float time01, float time10, float time11) {
    
	update_times(time00, time01, time10, time11);
    _state = 0;
    _lastState = _state;
    _value = _state;
}

//--------------------------------------------------------------
/*void kuSlowBit::setup( string line, string title0 )
{
	vector<float> list = kuSplitStringf( line, "," );
    kuAssert( list.size() >= 4,
                     "Bad or empty slowbit '" + title0
                     + "' string '" + line + "'" );
	setup( list[0], list[1], list[2], list[3] );
}*/

//--------------------------------------------------------------
void ofxKuSlowBit::update_times( float time00, float time01, float time10, float time11 ) {
	time00 = max(time00, 0.000001f);
    time01 = max(time01, 0.000001f);
    time10 = max(time10, 0.000001f);
    time11 = max(time11, 0.000001f);
    speed00 = 1.0 / time00;
    speed01 = 1.0 / time01;
    speed10 = 1.0 / time10;
    speed11 = 1.0 / time11;
}

//--------------------------------------------------------------
void ofxKuSlowBit::reset0()
{
    reset( 0 );
}

//--------------------------------------------------------------
void ofxKuSlowBit::reset( int value )
{
    _state = value;
    _lastState = _state;
    _value = _state;
}

//--------------------------------------------------------------
void ofxKuSlowBit::update( float dt, int target ) 
{
    _lastState = _state;
    
    float d = 0;
    if ( _state == 0 ) {
        if ( target == 0 ) { d = -speed00; }
        else { d = speed01; }
    }
    else {
        if ( target == 0 ) { d = -speed10; }
        else { d = speed11; }
    }
    
    _value += d * dt;
    if ( _value >= 1 ) { _state = 1; }
    if ( _value <= 0 ) { _state = 0; }
    
    _value = ofClamp( _value, 0, 1 );
}

//--------------------------------------------------------------
int ofxKuSlowBit::state()       
{
    return _state;
}

//--------------------------------------------------------------
bool ofxKuSlowBit::became0()     //изменился в 0
{
    return ( changed() && _state == 0 );
}

//--------------------------------------------------------------
bool ofxKuSlowBit::became1()     //изменился в 1
{
    return ( changed() && _state == 1 );
}

//--------------------------------------------------------------
bool ofxKuSlowBit::changed()     //изменился (сравнивать с предыдущим состоянием)
{
    return ( _state != _lastState );
}

//--------------------------------------------------------------
/*void kuSlowBit::draw( float x, float y, float w, float h ) {
    if ( state() == 0 ) ofSetColor(64,64,255);
    else ofSetColor(64,200,64);
    ofNoFill();
    ofDrawRectangle(x, y, w, h);
    ofFill();
    ofDrawRectangle(x, y, w*stateFloat(), h);
    if( title!="") {
        ofSetColor(128);
        ofDrawBitmapString(title, x+5, y+12);
    }
}
*/

//--------------------------------------------------------------
