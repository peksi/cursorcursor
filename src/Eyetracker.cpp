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
    
    eyeFinder.setup("haarcascade_eye.xml");
    
}
void Eyetracker::setup() {
    
}
void Eyetracker::updateImage(ofImage _cameraImage) {
    cameraImage = _cameraImage;
    
    detectEyes();
}
void Eyetracker::detectEyes() {

    grayscaleFrame.setFromColorImage(cameraImage);
    
    std::vector<cv::Rect> eyes;
    
    eyeFinder.findHaarObjects(grayscaleFrame); // an ofxCvGrayscaleImage
    for(int i = 0; i < eyeFinder.blobs.size(); i++) {
        ofxCvBlob cur = eyeFinder.blobs[i];
        cout << cur.boundingRect << endl;
    }
}
