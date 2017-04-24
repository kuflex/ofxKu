#include "ofxKuRasterOptFlow.h"
#include "ofxKuRaster.h"
#include "ofxKuDrawRasters.h"

//-------------------------------------------------------------------------------
ofxKuRasterOptFlow::ofxKuRasterOptFlow() {
	w_ = 100;
	h_ = 100;
	blur_input = 6;
	blur_data = 6;
}

//-------------------------------------------------------------------------------
void ofxKuRasterOptFlow::setup(int w, int h) {
	mask1_.clear();
	mask2_.clear();

	w_ = w;
	h_ = h;
	flowX_.resize(w_*h_);
	flowY_.resize(w_*h_);
	fill(flowX_.begin(), flowX_.end(), 0);
	fill(flowY_.begin(), flowY_.end(), 0);

}

//-------------------------------------------------------------------------------
void ofxKuRasterOptFlow::update( vector<unsigned char> mask0, int w0, int h0) {
	if (mask2_.size() == w_*h_) {
		mask1_ = mask2_;
	}
	//resize, threshold and blur input mask	
	ofxKuRasterResize_nearest(mask0,w0,h0,mask_temp_,w_,h_);
	ofxKuRasterThreshold(mask_temp_, mask_temp_, w_, h_, 0.0f, 0.0f, 1.0f);
	ofxKuRasterBlur_float(mask_temp_,w_,h_,blur_input,mask2_);

	if (mask1_.size()!=w_*h_ || mask2_.size()!=w_*h_) {
		return;
	}

	//moves
	vector<float> X( w_ * h_ );
	vector<float> Y( w_ * h_ );
	for (int y=0; y<h_; y++) {
		for (int x=0; x<w_; x++) {
			X[ x + w_ * y ] = x;
			Y[ x + w_ * y ] = y;
		}
	}

	//multiply
	vector<float> X1,Y1,X2,Y2;
	ofxKuRasterMultiply(X, mask1_, X1, w_, h_);
	ofxKuRasterMultiply(Y, mask1_, Y1, w_, h_);
	ofxKuRasterMultiply(X, mask2_, X2, w_, h_);
	ofxKuRasterMultiply(Y, mask2_, Y2, w_, h_);

	//blur
	vector<float> X1b,Y1b,X2b,Y2b,mask1b,mask2b;
	ofxKuRasterBlur_float(X1,w_,h_,blur_data,X1b);
	ofxKuRasterBlur_float(Y1,w_,h_,blur_data,Y1b);
	ofxKuRasterBlur_float(X2,w_,h_,blur_data,X2b);
	ofxKuRasterBlur_float(Y2,w_,h_,blur_data,Y2b);
	ofxKuRasterBlur_float(mask1_,w_,h_,blur_data,mask1b);
	ofxKuRasterBlur_float(mask2_,w_,h_,blur_data,mask2b);

	//clean bad zones
	int meaning_pixels = 5;
	float eps = float(meaning_pixels)/(blur_data*blur_data);

	for (int i=0; i<w_*h_; i++) {
		if (mask1b[i] < eps || mask2b[i] < eps) {
			X1b[i] = Y1b[i] = X2b[i] = Y2b[i] = 0;
		}
	}

	//divide
	ofxKuRasterDivide(X1b,mask1b,X1,w_,h_,eps,0.0f);
	ofxKuRasterDivide(Y1b,mask1b,Y1,w_,h_,eps,0.0f);
	ofxKuRasterDivide(X2b,mask2b,X2,w_,h_,eps,0.0f);
	ofxKuRasterDivide(Y2b,mask2b,Y2,w_,h_,eps,0.0f);

	//find flow
	ofxKuRasterSubtract(X2,X1,flowX_,w_,h_);
	ofxKuRasterSubtract(Y2,Y1,flowY_,w_,h_);
}

//-------------------------------------------------------------------------------
void ofxKuRasterOptFlow::draw(float x0, float y0, float w0, float h0, 
							  float amp, int step) {
	//ofSetColor(255);
	//ofxKuDrawRaster(mask2_, w_, h_, x0, y0, w0, h0, 0, 255);
	//ofxKuDrawRaster(flowX_, w_, h_, x0, y0, w0, h0, -10, 10);

	if (w_ > 0 && h_ > 0 && flowX_.size() == w_ * h_ && flowY_.size() == w_ * h_) {
		ofPushMatrix();
		ofTranslate(x0, y0);
		ofScale(w0 / w_, h0 / h_);		
		for (int y=0; y<h_; y+=step) {
			for (int x=0; x<w_; x+=step) {
				int i = x + w_*y;
				ofLine(x, y, x+flowX_[i]*amp, y+flowY_[i]*amp);
			}
		}
		ofPopMatrix();
	}

}

//-------------------------------------------------------------------------------
void ofxKuRasterOptFlow::resizeFlowTo(int outW, int outH, vector<float> &outX, vector<float> &outY) {

}


//-------------------------------------------------------------------------------

/*
void SurfaceFlow::updateFlow1(Mat &img1, Mat &img2 )
{
	//обновляем поток
	if ( !img1.empty() ) {
		int w = _wflow;
		int h = _hflow;

		//заполняем картинки
		if ( _optX.empty() ) {
			vector<float> X( w * h );
			vector<float> Y( w * h );
			for (int y=0; y<h; y++) {
				for (int x=0; x<w; x++) {
					X[ x + w * y ] = x;
					Y[ x + w * y ] = y;
				}
			}
			_optX = Mat( cv::Size( w, h ), CV_32FC1, &X[0] ).clone();
			_optY = Mat( cv::Size( w, h ), CV_32FC1, &Y[0] ).clone();
		}

		//приводим к нужному размеру
		resize( img1, small1, cv::Size( _wflow, _hflow ) ); 
		resize( img2, small2, cv::Size( _wflow, _hflow) ); 

		//Поток
		small1.convertTo( _temp1, CV_32FC1, 1.0 / 255.0 );
		small2.convertTo( _temp2, CV_32FC1, 1.0 / 255.0 );
		cv::multiply( _optX, _temp1, _tempX1 );
		cv::multiply( _optY, _temp1, _tempY1 );
		cv::multiply( _optX, _temp2, _tempX2 );
		cv::multiply( _optY, _temp2, _tempY2 );

		int blurSize = flowSmooth;
		cv::Size blurS( blurSize, blurSize );
		blur( _tempX1, _tempX1, blurS);				//TODO - можно и гауссово сглаживание попробовать будет!
		blur( _tempY1, _tempY1, blurS );
		blur( _tempX2, _tempX2, blurS );
		blur( _tempY2, _tempY2, blurS );

		//усредняем
		blur( _temp1, _wgh1, blurS );
		blur( _temp2, _wgh2, blurS );
		max( _wgh1, 0.001, _wgh1 );
		max( _wgh2, 0.001, _wgh2 );
		divide( _tempX1, _wgh1, _tempX1 );
		divide( _tempY1, _wgh1, _tempY1 );
		divide( _tempX2, _wgh2, _tempX2 );
		divide( _tempY2, _wgh2, _tempY2 );


		//расчет веса
		_diffX = _tempX2 - _tempX1;
		_diffY = _tempY2 - _tempY1;

		//Заполняем _flow

		//сначала строим вектор потока в большем размере
		pcvConverter::matFlowToVectorFloat( _diffX, _diffY, _flowTemp );

		//контроль длин
		float thresh = blurSize * 2;	//если значение больше - значит, выброс
		for (int y=0; y<h; y++) {
			for (int x=0; x<w; x++) {
				float &fx = _flowTemp[ 2*(x + w * y) ];
				float &fy = _flowTemp[ 2*(x + w * y) + 1 ];
				if ( fabs( fx ) > thresh || fabs( fy ) > thresh ) {
					fx = fy = 0;
				}
			}
		}

		//теперь уменьшаем - не сглаживая, а по принципу максимального значения 
		if ( !flowUseNewFrame ) {
			//resize( img1, _newFrameSmooth, cv::Size( _wflow, _hflow) );
			//GaussianBlur( _newFrameSmooth, _newFrameSmooth, cv::Size(flowSmooth, flowSmooth), 0 );
			//resizeFlow( _newFrameSmooth ); //small1
			
			resizeFlow( small2 ); //small1
		}
	}
}
*/

//----------------------------------------------------------------------
/*void SurfaceFlow::resizeFlow( const Mat &smooth )	//схлопнуть поток по маске
{
	//теперь уменьшаем - не сглаживая, а по принципу максимального значения 
	fill( _flow.begin(), _flow.end(), 0.0f );

	if ( !_flowTemp.empty() ) {
		float *flow = &_flow[0];
		float *flowTemp = &_flowTemp[0];
		for (int y=0; y<_hflow; y++) {
			for (int x=0; x<_wflow; x++) {
				int X = x * _wf / _wflow;
				int Y = y * _hf / _hflow;
				float &fx = flowTemp[ (x + _wflow * y) * 2 ];
				float &fy = flowTemp[ (x + _wflow * y) * 2 + 1 ];
				//зануляем поток вне движущегося контура
				//float value = smooth1.at<unsigned char>(y,x) / 255.0;
				float value = smooth.at<unsigned char>(y,x) / 255.0;
				fx *= value;
				fy *= value;

				float &FX = flow[ (X + _wf * Y) * 2 ];
				float &FY = flow[ (X + _wf * Y) * 2 + 1 ];
				if ( fabs( fx ) + fabs( fy ) > fabs( FX ) + fabs( FY ) ) {
					FX = fx;
					FY = fy;
				}
			}
		}
		//масштабируем
		float scl = 1.0 * _wf / _wflow;
		for ( int i=0; i<_wf * _hf; i++ ) {
			flow[i] *= scl;
		}
	}

}
*/
//-------------------------------------------------------------------------------

