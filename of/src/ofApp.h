#pragma once

#include "ofMain.h"
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cv_cvt.h"
#include "caffe_face_det.h"

using namespace std;

class ofApp : public ofBaseApp{public:

	ofVideoGrabber grabber;
	caffe_face_det detector;

	void setup(){

		cout << "OpenCV version : " << CV_VERSION << endl;
		grabber.setup(640,480);
		detector.setup();
	}
	void update(){
		grabber.update();

	}
	void draw(){
		ofSetColor(255);
		grabber.draw(0,0);
		ofPixels pix = grabber.getPixels();
		cv::Mat mat = cv_cvt::pix2mat(pix);
		cv::cvtColor(mat,mat,CV_RGB2BGR);
		// cv::imwrite( "../../../img.jpg", mat);

		vector<a_det> detections = detector.detect(mat);
		for (int i = 0; i < detections.size(); i++){
			ofPushStyle();
			ofSetColor(255,0,0);
			ofNoFill();
			ofSetLineWidth(5);
			ofDrawRectangle(detections[i].left, detections[i].top, detections[i].right-detections[i].left, detections[i].bottom-detections[i].top);
			ofPopStyle();

		}
	}

};
