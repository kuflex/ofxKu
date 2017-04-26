#include "ofxKuRasterOpenCV.h"
#include "ofxOpenCv.h"


//-------------------------------------------------------------
void ofxKuRasterGaussSmooth( vector<float> &mask, int w, int h, int rad, vector<float> &res )
{
    ofxCvFloatImage img;
    img.allocate( w, h );
    img.setFromPixels( &mask[0], w, h );
    
    img.blurGaussian( 2 * rad + 1 );
    
    float *imgF = img.getPixelsAsFloats();
    res.resize( w * h );
    for (int i=0; i<w*h; i++) {
        res[i] = imgF[i];
    }
    
}

//-------------------------------------------------------------
void ofxKuRasterResized( vector<float> &mask, int w, int h, int rad, vector<float> &res, int wres, int hres )
{
    ofxCvFloatImage img;
    img.allocate( w, h );
    img.setFromPixels( &mask[0], w, h );
    img.resize( wres, hres );
    
    img.blurGaussian( 2 * rad + 1 );
    
    float *imgF = img.getPixelsAsFloats();
    res.resize( wres * hres );
    for (int i=0; i<wres*hres; i++) {
        res[i] = imgF[i];
    }
    
}

//-------------------------------------------------------------
void ofxKuRasterFieldDirection( vector<float> &energy, int w, int h, int step, vector<ofPoint> &res )
{
    res.resize( w*h );
    for (int i=0; i<w*h; i++) {
        res[i].x = res[i].y = 0;
    }
    
    float EPS = 0.000001;
    float x0, x1, y0, y1;
    ofPoint dir;
    for (int y=step; y<h-step; y++) {
        for (int x=step; x<w-step; x++) {
            x0 = energy[ x-step + w * y ];
            x1 = energy[ x+step + w * y ];
            y0 = energy[ x + w * (y-step) ];
            y1 = energy[ x + w * (y+step) ];
            if ( x0 > EPS && x1 > EPS && y0 > EPS && y1 > EPS ) {
                dir.x = x1 - x0;
                dir.y = y1 - y0;
                //dir.normalize();
                res[x + w*y] = dir;
            }
        }
    }
}

//-------------------------------------------------------------
//Заполняет нулевые направления в accum значениями из source
/*void pbCombineFieldDirection( vector<ofPoint> &accum, int w, int h, vector<ofPoint> &source, int ws, int hs  )
{
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            ofPoint &a = accum[x+w*y];
            if ( a.x == 0 && a.y == 0 ) {
                a = source[ x * ws / w + ws*( y * hs / h) ];
            }
        }
    }
}
*/

//-------------------------------------------------------------
//Заполняет нулевые направления, а также граничные, направлением в center
/*void pbFillFieldDirection( vector<ofPoint> &accum, int w, int h, ofPoint &center, int border  )
{
    ofPoint dir;
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            ofPoint &a = accum[x+w*y];
            if ( //( a.x == 0 && a.y == 0 )
                //||
                (x < border ) || ( x > w-1-border) || ( y < border ) || (y > h-1-border ) ) {
                dir = center - ofPoint( x, y );
                dir.normalize();
                a = dir;
            }
        }
    }
}
*/
//-------------------------------------------------------------
