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
    void detectEyes(ofxCvColorImage _frame, cv::CascadeClassifier _faceCascade, cv::CascadeClassifier _eyeCascade);
    
    ofxCvColorImage cameraImage;
    ofxCvGrayscaleImage grayscaleFrame;
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;
private:
};

#endif /* Eyetracker_hpp */
