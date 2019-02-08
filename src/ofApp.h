#pragma once

#include <string>
#include <string.h>
#include "ofMain.h"

// ofxAddon includes
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

// Personal includes
#include "WallOrganiser.hpp"
#include "user.hpp"

#define PORT 12001
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
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
		
    WallOrganiser wallOrganiser;
    User user;
    
    
    ofxXmlSettings XMLconfig;
    
    ofEasyCam virtualCamera;
    float xOrigin,yOrigin,zOrigin;
    
    ofxOscReceiver receiver;
    
    int currentMsgString;
    string msgStrings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
};
