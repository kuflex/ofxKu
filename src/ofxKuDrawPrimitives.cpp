#include "ofxKuDrawPrimitives.h"

//--------------------------------------------------------------
float coarse( float x, float size ) {
    return int( x / size + 0.5 ) * size;
}

//--------------------------------------------------------------
int randomSign() {
    return ( ofRandom( 0, 1 ) < 0.5 ) ? 1 : (-1);
}

//--------------------------------------------------------------
float sqr( float x ) {
    return x * x;
}


//--------------------------------------------------------------
ofxKuRectRender::ofxKuRectRender() {
	N = 0;
	N_normals = 0;
	normals_enabled = false;
}

//--------------------------------------------------------------
void ofxKuRectRender::clear() {
	N = 0;
	points.clear();
	colors.clear();
	texs.clear();

	N_normals = 0;
	normals.clear();
}

//--------------------------------------------------------------
void ofxKuRectRender::start() {	//starts drawing, not clear
	N = 0;
	N_normals = 0;
}

//--------------------------------------------------------------
void ofxKuRectRender::allocate_normals(int n) {
	if (normals_enabled) {
		normals.resize(n*4);
	}
}

//--------------------------------------------------------------
void ofxKuRectRender::allocate_colored(int n) {
	points.resize(n*4);
	colors.resize(n*4);
	allocate_normals(n);
}

//--------------------------------------------------------------
void ofxKuRectRender::allocate_textured(int n) {
	points.resize(n*4);
	texs.resize(n*4);
	allocate_normals(n);
}

//--------------------------------------------------------------
void ofxKuRectRender::allocate_colored_textured(int n) {
	points.resize(n*4);
	colors.resize(n*4);
	texs.resize(n*4);
	allocate_normals(n);
}
	
//--------------------------------------------------------------
void ofxKuRectRender::draw_colored() {
	if ( N == 0 ) { return; }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( ofColor ), &colors[0].v[0]);
    
	link_normals();

    glDrawArrays(GL_QUADS, 0, N);

	unlink_normals();
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//--------------------------------------------------------------
void ofxKuRectRender::draw_textured( ofTexture &texture ) {
	if ( N == 0 ) { return; }
   
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glTexCoordPointer( 2, GL_FLOAT, sizeof( ofVec2f ), &texs[0].x );
    
	link_normals();

    texture.bind();
    glDrawArrays(GL_QUADS, 0, N);
    texture.unbind();
		
	unlink_normals();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//--------------------------------------------------------------
void ofxKuRectRender::draw_colored_textured( ofTexture &texture ) {
	if ( N == 0 ) { return; }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( ofColor ), &colors[0].v[0]);
    glTexCoordPointer( 2, GL_FLOAT, sizeof( ofVec2f ), &texs[0].x );
    
	link_normals();

    texture.bind();
    glDrawArrays(GL_QUADS, 0, N);
    texture.unbind();

	unlink_normals();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//-------------------------------------------------------------- 
void ofxKuRectRender::link_normals() {
	if (normals_enabled) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer( GL_FLOAT, sizeof( ofPoint ), &normals[0].x );
	}
}

//-------------------------------------------------------------- 
void ofxKuRectRender::unlink_normals() {
	if (normals_enabled) {
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

//-------------------------------------------------------------- 
void ofxKuRectRender::check_size_colored() {
	if (points.size() < N+4) points.resize(N+4);
	if (colors.size() < N+4) colors.resize(N+4);
}

//-------------------------------------------------------------- 
void ofxKuRectRender::check_size_textured() {
	if (points.size() < N+4) points.resize(N+4);
	if (texs.size() < N+4) texs.resize(N+4);

}

//-------------------------------------------------------------- 
void ofxKuRectRender::check_size_colored_textured() {
	if (points.size() < N+4) points.resize(N+4);
	if (colors.size() < N+4) colors.resize(N+4);
	if (texs.size() < N+4) texs.resize(N+4);
}

//-------------------------------------------------------------- 
void ofxKuRectRender::check_size_normals() {
	if (normals.size() < N_normals + 4) normals.resize(N_normals+4);
}


//--------------------------------------------------------------
void ofxKuRectRender::pushNormals( const ofPoint &norm ) {
	check_size_normals();
	normals[N_normals++] = norm;
	normals[N_normals++] = norm;
	normals[N_normals++] = norm;
	normals[N_normals++] = norm;
}

//-------------------------------------------------------------- 
void ofxKuRectRender::pushRect( float x, float y, float w, float h, const ofColor &color )
{
	check_size_colored();
    points[N] = ofPoint( x, y );
    colors[N++] = color;
    points[N] = ofPoint( x + w, y );
    colors[N++] = color;
    points[N] = ofPoint( x + w, y + h );
    colors[N++] = color;
    points[N] = ofPoint( x, y + h );
    colors[N++] = color;
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect( float x, float y, float z, float w, float h, const ofColor &color )
{
	check_size_colored();
    points[N] = ofPoint( x, y, z );
    colors[N++] = color;
    points[N] = ofPoint( x + w, y, z );
    colors[N++] = color;
    points[N] = ofPoint( x + w, y + h, z );
    colors[N++] = color;
    points[N] = ofPoint( x, y + h, z );
    colors[N++] = color;
}


//--------------------------------------------------------------
void ofxKuRectRender::pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h, const ofColor &color )
{
	check_size_colored();
    points[N] = p;
    colors[N++] = color;
    points[N] = p + w;
    colors[N++] = color;
    points[N] = p + w + h;
    colors[N++] = color;
    points[N] = p + h;
    colors[N++] = color;
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect(const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofColor &color) {
	check_size_colored();
	points[N] = p1;
	colors[N++] = color;
	points[N] = p2;
	colors[N++] = color;
	points[N] = p3;
	colors[N++] = color;
	points[N] = p4;
	colors[N++] = color;
}


//--------------------------------------------------------------
void ofxKuRectRender::pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h,
                const ofRectangle &texRect )
{
	check_size_textured();
    points[N] = p;
    texs[N++] = texRect.getTopLeft();
    points[N] = p + w;
    texs[N++] = texRect.getTopRight();
    points[N] = p + w + h;
    texs[N++] = texRect.getBottomRight();
    points[N] = p + h;
    texs[N++] = texRect.getBottomLeft();
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect( float x, float y, float z, float w, float h,
                const ofRectangle &texRect )
{
	check_size_textured();
    points[N] = ofPoint( x, y, z );
    texs[N++] = texRect.getTopLeft();
    points[N] = ofPoint( x + w, y, z );
    texs[N++] = texRect.getTopRight();
    points[N] = ofPoint( x + w, y + h, z );
    texs[N++] = texRect.getBottomRight();
    points[N] = ofPoint( x, y + h, z );
    texs[N++] = texRect.getBottomLeft();    
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect( const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4,
                const ofRectangle &texRect ) 
{
	check_size_textured();
    points[N] = p1;
    texs[N++] = texRect.getTopLeft();
    points[N] = p2;
    texs[N++] = texRect.getTopRight();
    points[N] = p3;
    texs[N++] = texRect.getBottomRight();
    points[N] = p4;
    texs[N++] = texRect.getBottomLeft();     
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect( float x, float y, float z, float w, float h,
                const ofColor &color, const ofRectangle &texRect )
{
	check_size_colored_textured();
    points[N] = ofPoint( x, y, z );
	colors[N] = color;
    texs[N++] = texRect.getTopLeft();
    points[N] = ofPoint( x + w, y, z );
	colors[N] = color;
    texs[N++] = texRect.getTopRight();
    points[N] = ofPoint( x + w, y + h, z );
	colors[N] = color;
    texs[N++] = texRect.getBottomRight();
    points[N] = ofPoint( x, y + h, z );
	colors[N] = color;
    texs[N++] = texRect.getBottomLeft();    
}

//--------------------------------------------------------------
void ofxKuRectRender::pushRect( const ofPoint &p, const ofPoint &w, const ofPoint &h,
                const ofColor &color, const ofRectangle &texRect )
{
	check_size_colored_textured();
    points[N] = p;
	colors[N] = color;
    texs[N++] = texRect.getTopLeft();
    points[N] = p + w;
	colors[N] = color;
    texs[N++] = texRect.getTopRight();
    points[N] = p + w + h;
	colors[N] = color;
    texs[N++] = texRect.getBottomRight();
    points[N] = p + h;
	colors[N] = color;
    texs[N++] = texRect.getBottomLeft();
}


//----------------------------------------------------------
void ofxKuStartSmoothing(){
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
    
	//why do we need this?
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


//----------------------------------------------------------
void ofxKuEndSmoothing(){
    glDisable(GL_LINE_SMOOTH);
}



//--------------------------------------------------------------
ofxKuLineRender::ofxKuLineRender() {
	N = 0;
	N_normals = 0;
	normals_enabled = false;
}

//--------------------------------------------------------------
void ofxKuLineRender::clear() {
	N = 0;
	points.clear();
	colors.clear();
	texs.clear();

	N_normals = 0;
	normals.clear();
}

//--------------------------------------------------------------
void ofxKuLineRender::start() {	//starts drawing, not clear
	N = 0;
	N_normals = 0;
}

//--------------------------------------------------------------
void ofxKuLineRender::allocate_normals(int n) {
	if (normals_enabled) {
		normals.resize(n*2);
	}
}

//--------------------------------------------------------------
void ofxKuLineRender::allocate_colored(int n) {
	points.resize(n*2);
	colors.resize(n*2);
	allocate_normals(n);
}

//--------------------------------------------------------------
void ofxKuLineRender::allocate_textured(int n) {
	points.resize(n*2);
	texs.resize(n*2);
	allocate_normals(n);
}

//--------------------------------------------------------------
void ofxKuLineRender::allocate_colored_textured(int n) {
	points.resize(n*2);
	colors.resize(n*2);
	texs.resize(n*2);
	allocate_normals(n);
}

//--------------------------------------------------------------
void ofxKuLineRender::draw_colored() {
	if ( N == 0 ) { return; }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( ofColor ), &colors[0].v[0]);
    
	link_normals();
	glDrawArrays(GL_LINES, 0, N);
    unlink_normals();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//--------------------------------------------------------------
void ofxKuLineRender::draw_textured( ofTexture &texture ) {
	if ( N == 0 ) { return; }
   
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glTexCoordPointer( 2, GL_FLOAT, sizeof( ofVec2f ), &texs[0].x );
    
    texture.bind();

	link_normals();
	glDrawArrays(GL_LINES, 0, N);
    unlink_normals();

    texture.unbind();
		
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//--------------------------------------------------------------
void ofxKuLineRender::draw_colored_textured( ofTexture &texture ) {
	if ( N == 0 ) { return; }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glVertexPointer( 3, GL_FLOAT, sizeof( ofPoint ), &points[0].x);
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( ofColor ), &colors[0].v[0]);
    glTexCoordPointer( 2, GL_FLOAT, sizeof( ofVec2f ), &texs[0].x );
    
    texture.bind();

	link_normals();
	glDrawArrays(GL_LINES, 0, N);
    unlink_normals();

    texture.unbind();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//-------------------------------------------------------------- 
void ofxKuLineRender::link_normals() {
	if (normals_enabled) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer( GL_FLOAT, sizeof( ofPoint ), &normals[0].x );
	}
}

//-------------------------------------------------------------- 
void ofxKuLineRender::unlink_normals() {
	if (normals_enabled) {
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

//-------------------------------------------------------------- 
void ofxKuLineRender::check_size_colored() {
	if (points.size() < N+2) points.resize(N+2);
	if (colors.size() < N+2) colors.resize(N+2);
}

//-------------------------------------------------------------- 
void ofxKuLineRender::check_size_textured() {
	if (points.size() < N+2) points.resize(N+2);
	if (texs.size() < N+2) texs.resize(N+2);

}

//-------------------------------------------------------------- 
void ofxKuLineRender::check_size_colored_textured() {
	if (points.size() < N+2) points.resize(N+2);
	if (colors.size() < N+2) colors.resize(N+2);
	if (texs.size() < N+2) texs.resize(N+2);
}


//-------------------------------------------------------------- 
void ofxKuLineRender::check_size_normals() {
	if (normals.size() < N_normals + 2) normals.resize(N_normals+2);
}


//--------------------------------------------------------------
void ofxKuLineRender::pushNormals( const ofPoint &norm ) {
	check_size_normals();
	normals[N_normals++] = norm;
	normals[N_normals++] = norm;
}

//--------------------------------------------------------------
void ofxKuLineRender::pushNormals( const ofPoint &norm1, const ofPoint &norm2 ) {
	check_size_normals();
	normals[N_normals++] = norm1;
	normals[N_normals++] = norm2;
}


//--------------------------------------------------------------
void ofxKuLineRender::pushLine( const ofPoint &p1, const ofPoint &p2, const ofColor &color )
{
 	check_size_colored();
    points[N] = p1;
    colors[N++] = color;
    points[N] = p2;
    colors[N++] = color;
}


//--------------------------------------------------------------
void ofxKuLineRender::pushLine( const ofPoint &p1, const ofPoint &p2,
                const ofColor &color1, const ofColor &color2 )
{
 	check_size_colored();
    points[N] = p1;
    colors[N++] = color1;
    points[N] = p2;
    colors[N++] = color2;
}

//--------------------------------------------------------------
void ofxKuLineRender::pushLine( const ofPoint &p1, const ofPoint &p2,
                const ofColor &color1, const ofColor &color2, float bright )
{
 	check_size_colored();
    points[N] = p1;
    colors[N++] = ofColor(color1.r*bright, color1.g*bright, color1.b*bright, color1.a);
    points[N] = p2;
    colors[N++] = ofColor(color2.r*bright, color2.g*bright, color2.b*bright, color2.a);
}

//--------------------------------------------------------------
void ofxKuVertexRender::setup( string pointImageFile, string shaderVert, string shaderFrag )
{
    ofDisableArbTex();
	ofLoadImage( texture, pointImageFile );
	ofEnableArbTex();

    useShader_ = (shaderVert!="" && shaderFrag!="");
    if ( useShader_ ) {
        shader_.load( shaderVert, shaderFrag );
    }
}

//--------------------------------------------------------------
void ofxKuVertexRender::clearPoints()
{
    points.clear();
    sizes.clear();
}

//--------------------------------------------------------------
void ofxKuVertexRender::addPoint( const ofPoint &p, float rad, float alpha )
{
    points.push_back( p );
    sizes.push_back( ofPoint( rad, alpha, 0 ) );
}

//--------------------------------------------------------------
void ofxKuVertexRender::setPoints( vector<ofPoint> &v, float minRad, float maxRad ) {
    points = v;
    int n = v.size();
    sizes.resize( n );
    for (int i=0; i<n; i++) {
        sizes[i] = ofPoint( ofRandom( minRad, maxRad ), 1, 0 );
    }
}

//--------------------------------------------------------------
void ofxKuVertexRender::setPoints( vector<ofPoint> &v, vector<ofPoint> &data ) {
    points = v;
    sizes = data;
}

//--------------------------------------------------------------
void ofxKuVertexRender::drawBegin( float part ) {
    //начало рисования, можно установить параметры в шейдер
    if ( points.empty() ) { return; }
    part = ofClamp( part, 0, 1 );
    int total = (int)points.size() * part;
    if ( total == 0 ) return;
    
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
	
    //	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();

    if ( useShader_ ) {
        shader_.begin();
    }
}

//--------------------------------------------------------------
void ofxKuVertexRender::drawEnd( float part ){ //конец рисования
    if ( points.empty() ) { return; }
    part = ofClamp( part, 0, 1 );
    int total = (int)points.size() * part;
    if ( total == 0 ) return;
    
    texture.bind();
	vbo.draw(GL_POINTS, 0, total);
	texture.unbind();
	
    if ( useShader_ ) {
        shader_.end();
    }
	
	ofDisablePointSprites();
	//ofDisableBlendMode();
    
    //    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofxKuVertexRender::draw()
{
	drawBegin();
    drawEnd();
	
}
    
//--------------------------------------------------------------

