# ofxKu
Kuflex extension for openFrameworks.

It contains classes and functions for rendering, image analysis and working with files, which we are using in Kuflex projects:

## Drawing
* ofxKuRectRender class for fast rendering rectangles
* ofxKuLineRender class for fast rendering lines
* ofxKuVertexRender class for fast rendering points
* ofxKuDrawTextureFit(ofTexture &tex, float x, float y, float w, float h) function in ofxKuDrawUtils for fitting texture in rectangle
* ofxKuDrawRaster draws raster array

## Image processing
* ofxKuRasterBlur_int, ofxKuRasterBlur_float - box blur for raster arrays
* ofxKuRasterResize_nearest - resize raster arrays
* ofxKuFloodFill function which do flood fill in array

## Utilities for files
* ofxKuBufferRecorder class for recording/replaying data buffers, such as kinect data
* ofxKuFileTime::isNewerThan(string fileName1, string fileName2) function which compares file creation times


