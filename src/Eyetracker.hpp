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
#include "ofxPS3EyeGrabber.h"

class Eyetracker {
public:
    Eyetracker();
    void setup();
    void updateImage(ofImage _cameraImage);
    
    ofxCvColorImage cameraImage;
private:
};

#endif /* Eyetracker_hpp */
