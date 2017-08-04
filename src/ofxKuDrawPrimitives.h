#pragma once

#include "ofMain.h"

//Fast drawing

//--------------------------------------------------------------
//coarsing with step с шагом size
float coarse( float x, float size );

//1, -1
int randomSign();

float sqr( float x );
//--------------------------------------------------------------

class ofxKuRectRender {
public:
	ofxKuRectRender();

	bool normals_enabled;	//set to true for using normals

	void clear();
	void start();	//starts drawing, not clear
	void allocate_colored(int n);		//do allocate is size is known, and use start
	void allocate_textured(int n);
	void allocate_colored_textured(int n);

	void draw_colored();
	void draw_textured( ofTexture &texture );
	void draw_colored_textured( ofTexture &texture );
	
	//Colored rectangles
	void pushRect( float x, float y, float w, float h, const ofColor &color );
	void pushRect( float x, float y, float z, float w, float h, const ofColor &color );
	void pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h, const ofColor &color );
	void pushRect( const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofColor &color);
	

	//Textured rectangles
	void pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h, const ofRectangle &texRect );
	void pushRect( float x, float y, float z, float w, float h, const ofRectangle &texRect );
	void pushRect( const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofRectangle &texRect );

	//Colored textured rectangles
	void pushRect( float x, float y, float z, float w, float h,
                const ofColor &color, const ofRectangle &texRect );

	void pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h,
                const ofColor &color, const ofRectangle &texRect );

	void pushRect( vector<ofPoint> &points, vector<ofColor> &colors,
                 vector<ofVec2f> &texs, ofTexture &texture );

	vector<ofPoint> points;
	vector<ofColor> colors;
	vector<ofVec2f> texs;
	int N;


	//Normals are controlled separately
	vector<ofPoint> normals;
	void pushNormals( const ofPoint &norm );

private:
	void check_size_colored();
	void check_size_textured();
	void check_size_colored_textured();

	void check_size_normals();
	void link_normals();
	void unlink_normals();
	void allocate_normals(int n);
	int N_normals;
};


void ofxKuStartSmoothing();    //Line smoothing
void ofxKuEndSmoothing();

class ofxKuLineRender {
public:
	ofxKuLineRender();
	bool normals_enabled;	//set to true for using normals

	void clear();
	void start();	//starts drawing, not clear
	void allocate_colored(int n);
	void allocate_textured(int n);
	void allocate_colored_textured(int n);

	void draw_colored();
	void draw_textured( ofTexture &texture );
	void draw_colored_textured( ofTexture &texture );

	void pushLine( const ofPoint &p1, const ofPoint &p2, const ofColor &color );
	void pushLine( const ofPoint &p1, const ofPoint &p2, const ofColor &color1,
                const ofColor &color2 );
	void pushLine( const ofPoint &p1, const ofPoint &p2,
                const ofColor &color1, const ofColor &color2, float bright );
	void pushLine( vector<ofPoint> &points, vector<ofColor> &colors );

	vector<ofPoint> points;
	vector<ofColor> colors;
	vector<ofVec2f> texs;
	int N;

	//Normals are controlled separately
	vector<ofPoint> normals;
	void pushNormals( const ofPoint &norm );
	void pushNormals( const ofPoint &norm1, const ofPoint &norm2 );
private:
	void check_size_colored();
	void check_size_textured();
	void check_size_colored_textured();

	void check_size_normals();
	void link_normals();
	void unlink_normals();
	void allocate_normals(int n);
	int N_normals;

};





//Вершины, рисуются текстурой
//Внимание: сами используют шейдеры, поэтому не должны вызываться при включенном шейдере
class ofxKuVertexRender {
public:
    void setup( string pointImageFile, string shaderVert = "", string shaderFrag = "" );
    //если оставить пути к шейдеру пустыми - то нужно самим подключать шейдер,
    //после drawBegin и выключать после drawEnd
    
    void clearPoints();
    void addPoint( const ofPoint &p, float rad, float alpha );
    void setPoints( vector<ofPoint> &v, float minRad, float maxRad );
    
    //data - данные, которые передаются в шейдер как нормаль
    //например, data.x - size, data.y,z - текстурные координаты
    void setPoints( vector<ofPoint> &v, vector<ofPoint> &data );
    
    void draw();
    
    void drawBegin( float part = 1 );   //начало рисования, можно установить параметры в шейдер
    //part - доля сколько частиц рисовать, 0..1
    ofShader &shader() { return shader_; }
    void drawEnd( float part = 1 ); //конец рисования, part должен совпадать с началом
    
private:
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    
    ofTexture texture;
    bool useShader_;
    ofShader shader_;
    ofVbo vbo;
    
};



