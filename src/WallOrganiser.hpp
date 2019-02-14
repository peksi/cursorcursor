//
//  WallOrganiser.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#ifndef WallOrganiser_hpp
#define WallOrganiser_hpp

#include "ofMain.h"

// ofxAddon includes
#include "ofxXmlSettings.h"

// Personal includes
#include "Wall.hpp"

class WallOrganiser {
public:
    WallOrganiser();
    void setup(ofxXmlSettings _XMLconfig, ofVec3f* _position, ofVec3f* _ray);
    void addWall(vector<ofVec2f> _wallCoords, int _wallId);
    void addProjection(vector<ofVec2f> _projectionCoords, int _projectionId);
    void displayWalls();
    void displayGroundplane();
    void displayProjections();
    void displayFbo();
    
    vector<Wall> wallVector;

    ofPath groundPlane;
    vector<ofPath> wallPathVector;
    
    float wallHeight;
    
    ofVec3f* userRayOrigin;
    ofVec3f* userRay;

private:
};

#endif /* WallOrganiser_hpp */
