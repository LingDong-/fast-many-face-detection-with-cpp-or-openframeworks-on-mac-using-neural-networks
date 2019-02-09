// adapted from ofxCv
#pragma once
namespace cv_cvt{
  inline int pix_depth(ofPixels pixels) {
    switch(pixels.getBytesPerChannel()) {
      case 4: return CV_32F;
      case 2: return CV_16U;
      case 1: default: return CV_8U;
    }
  }
  inline int pix_cv_type(ofPixels pix){
    return CV_MAKETYPE(pix_depth(pix),pix.getNumChannels());
  }
  inline cv::Mat pix2mat(ofPixels pix){
    return cv::Mat(pix.getHeight(), pix.getWidth(), pix_cv_type(pix), pix.getData(), 0);
  }
  inline ofPixels mat2pix(cv::Mat mat){
    ofPixels pix;
    pix.setFromExternalPixels(mat.ptr(),mat.cols,mat.rows,mat.channels());
    return pix;
  }
}
