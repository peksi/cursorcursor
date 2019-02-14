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
    eyeFinder.setPreset(ObjectFinder::Fast);
    eyeFinder.getTracker().setSmoothingRate(0.3);
    
}
void Eyetracker::setup() {
    
}
void Eyetracker::updateImage(ofImage _cameraImage) {
    cameraImage = _cameraImage;
}
void Eyetracker::detectEyes() {
    eyeFinder.update(cameraImage);
    
    for (int i = 0; i < eyeFinder.size(); i++) {
        ofRectangle object = eyeFinder.getObjectSmoothed(i);
    }
}
void Eyetracker::drawDetectedEyes() {
    for (int i = 0; i < eyeFinder.size(); i++) {
        ofRectangle object = eyeFinder.getObjectSmoothed(i);
        
        ofPath eyeBox;
        eyeBox.setColor(ofColor(0,255,0));
        eyeBox.setStrokeWidth(5);
        eyeBox.setFilled(false);
        eyeBox.rectangle(object.x, object.y, object.width, object.height);
        eyeBox.draw();
    }
}
