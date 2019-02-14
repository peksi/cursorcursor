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
    grayscaleFrame.setFromColorImage(cameraImage);
}
void Eyetracker::detectEyes() {
    eyeFinder.update(cameraImage);
    
    
    // only for drawing
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

    if(eyeFinder.size() > 0){
        ofRectangle object = eyeFinder.getObjectSmoothed(0);
        
        cout << eyeFinder.getObjectSmoothed(0).x << endl;
        
        grayscaleFrame.setROI(object);
        
        std::vector<cv::Vec3f> circles;
        cv::Mat imageMat = toCv(grayscaleFrame);
        cout << "here" << endl;
        // next line messes up
//        cv::HoughCircles(imageMat, circles, CV_HOUGH_GRADIENT, 1, 2); // dunno about the last values but let's use something for now
        
        for (int i = 0; i < circles.size(); i++) {
            cout << circles[i].all << endl;
        }
    }
    

}

