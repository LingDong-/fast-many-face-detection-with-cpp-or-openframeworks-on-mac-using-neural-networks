// caffe face detector
#pragma once

class a_det{public:
  float left;
  float top;
  float right;
  float bottom;
  float certainty;
};

class caffe_face_det{public:
  cv::dnn::Net net;
  cv::Mat blob;
  cv::Mat net_out;
  std::string model_location = "../data/models";
  void setup(){
    net = cv::dnn::readNetFromCaffe(model_location+"/deploy.prototxt",
                                                                        model_location+"/res10_300x300_ssd_iter_140000.caffemodel");
  }
  void forward(cv::Mat mat){
    cv::resize(mat,mat,cv::Size(300,300));
    blob = cv::dnn::blobFromImage(mat,1.0,cv::Size(300,300),cv::Scalar(104.0, 177.0, 123.0),false,false);
    net.setInput(blob);
    net_out = net.forward();
  }

  std::vector<a_det> detect(cv::Mat mat, float thresh=0.15){
    forward(mat);
    std::vector<a_det> detections;

    for(int i = 0; i < net_out.size[2]; i++) {
      cv::Vec<float,7> a = net_out.at<cv::Vec<float,7>>(0,0,i);
      float cert = a[2];
      if (cert >= thresh){
        a_det d;
          d.certainty = cert;
        d.left = a[3] * mat.cols;
        d.top = a[4] * mat.rows;
        d.right = a[5] * mat.cols;
        d.bottom = a[6] * mat.rows;
        detections.push_back(d);
        }
    }
    //cout << detections.size() << "/" << net_out.size[2] << endl;
    return detections;
  }

};
