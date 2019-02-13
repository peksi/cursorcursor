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
}
void Eyetracker::setup() {
    
}
void Eyetracker::updateImage(ofImage _cameraImage) {
    cameraImage = _cameraImage;
}
