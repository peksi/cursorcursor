//
//  Eyetracker.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 10/02/2019.
//

#ifndef Eyetracker_hpp
#define Eyetracker_hpp

#include "ofMain.h"

// ofxAddon includes
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxPS3EyeGrabber.h"

class Eyetracker {
public:
    Eyetracker();
    void setup();
    void updateImage(ofImage _cameraImage);
    void detectEyes();
    void drawHelpers();
    void updateDetectedEyes();
    
    ofxCvColorImage cameraImage;
    ofxCvGrayscaleImage grayscaleFrame;
    ofxCv::ObjectFinder eyeFinder;
    
    
    
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;
private:
    ofVec2f irisPoint, irisBoxOffset;
    int irisRadius;
};

#endif /* Eyetracker_hpp */
