//
//  Eyetracker.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 10/02/2019.
//

#include "Eyetracker.hpp"

using namespace cv;
using namespace ofxCv;

Eyetracker::Eyetracker() {
    cameraImage.allocate(1280, 720);
    grayscaleFrame.allocate(1280,720);
    
    if (!faceCascade.load("bin/data/haarcascades/haarcascade_frontalface_default.xml")) {
        cout << "Could not load faceCascade" << endl;
    }
    if (eyeCascade.load("bin/data/haarcascades/haarcascade_eye.xml")) {
        cout << "Could not load eyeCascade" << endl;
    }
}
void Eyetracker::setup() {
    
}
void Eyetracker::updateImage(ofImage _cameraImage) {
    cameraImage = _cameraImage;
    
    detectEyes(cameraImage,faceCascade,eyeCascade);
}
void Eyetracker::detectEyes(ofxCvColorImage _frame, cv::CascadeClassifier _faceCascade, cv::CascadeClassifier _eyeCascade) {
    
    grayscaleFrame.setFromColorImage(_frame);
    
    /*
    std::vector<cv::Rect> eyes;
    eyeCascade.detectMultiScale(grayscaleFrame, eyes);
    
    for (int i = 0; i < eyes.size(); i++) {
        Point<int> topLeft = eyes[i].tl();
        Point<int> bottomRight = eyes[i].br();
        ofDrawRectangle(topLeft.x,topLeft.y,bottomRight.x,bottomRight.y);
    }
     */
}
