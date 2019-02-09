// c++ main.cpp -lopencv_videostab -lopencv_photo -lopencv_objdetect -lopencv_video -lopencv_ml -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_flann -lopencv_imgproc -lopencv_dnn -lopencv_imgcodecs -lopencv_core -lopencv_videoio -I/usr/local/Cellar/opencv/3.4.1_5/include -std=c++11
// c++ main.cpp -lopencv_highgui -lopencv_imgproc -lopencv_dnn -lopencv_core -lopencv_videoio -I/usr/local/Cellar/opencv/3.4.1_5/include -std=c++11

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "caffe_face_det.h"


using namespace std;

int main() {
    cv::VideoCapture cap(0);
    cout << "hello there." << endl;

    if(!cap.isOpened()){
        return -1;
    }
    cv::namedWindow("frame",1);
    caffe_face_det detector;
    detector.setup();

    for(;;){
        cv::Mat frame;
        cap >> frame;
        vector<a_det> detections = detector.detect(frame);
        for (int i = 0; i < detections.size(); i++){
            a_det det = detections[i];
            cv::rectangle(frame, cv::Point(det.left,det.top), cv::Point(det.right,det.bottom), cv::Scalar(0,255,255),3);
        }
        cv::imshow("frame", frame);
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}