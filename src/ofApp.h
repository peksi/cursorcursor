#pragma once

#include <string>
#include <string.h>
#include "ofMain.h"

// ofxAddon includes
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxPS3EyeGrabber.h"

// Personal includes
#include "WallOrganiser.hpp"
#include "Eyetracker.hpp"
#include "user.hpp"

#define PORT 12001
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
        void setupGui();
		void update();
		void draw();
        void exit();
        void drawAxis();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Gui
    ofxPanel viewGui;
    ofxPanel fboGui;
    ofParameterGroup viewParameterGroup;
    ofParameterGroup fboParameterGroup;
    ofParameter<bool> showCamera, show3D, showLog, showAxis;
    
    // Personal class instances
    WallOrganiser wallOrganiser;
    Eyetracker eyeTracker;
    User user;
    
    // XML
    ofxXmlSettings XMLconfig;
    
    // OSC
    ofxOscReceiver receiver;
    int currentMsgString;
    string msgStrings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    // Eyetracker camera
    ofVideoGrabber camera;
    
    // Virtual camera
    ofEasyCam virtualCamera;
    float xOrigin,yOrigin,zOrigin;
};
