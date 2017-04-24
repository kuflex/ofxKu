#include "ofxKuRasterOptFlow.h"
#include "ofxKuRaster.h"
#include "ofxKuDrawRasters.h"

//-------------------------------------------------------------------------------
ofxKuRasterOptFlow::ofxKuRasterOptFlow() {
	w_ = 100;
	h_ = 100;
	blur_input = 6;
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
	//resize and blur input mask
	vector<float> &mask = (mask1_.empty())?mask1_:mask2_;
	ofxKuRasterResize_nearest(mask0,w0,h0,mask_temp_,w_,h_);
	ofxKuRasterBlur_float(mask_temp_,w_,h_,blur_input,mask);

	//moves
	vector<float> X( w_ * h_ );
	vector<float> Y( w_ * h_ );
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			X[ x + w_ * y ] = x;
			Y[ x + w_ * y ] = y;
		}
	}

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

//-------------------------------------------------------------------------------
void ofxKuRasterOptFlow::draw(float x, float y, float w, float h, float amp) {
	ofSetColor(255);
	ofxKuDrawRaster(mask2_, w_, h_, x, y, w, h, 0, 255);
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

