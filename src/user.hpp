//
//  user.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 08/02/2019.
//

#ifndef user_hpp
#define user_hpp

#include "ofMain.h"

class User {
public:
    User();
    
    void setup();
    void updateUser(vector<string> _incomingOSCmessage);
    void smoothPosition();
    void displayUser();
    void calculateRay();
    void smoothRay();
    void displayRay();
    
    ofSpherePrimitive userHead;
    
    ofParameter<float> rotationOffsetH,rotationOffsetV;
    ofParameter<float> xOffset,yOffset,zOffset;
    ofParameter<bool> flipX,flipY,flipZ;
    
    ofVec3f position;
    ofVec3f incomingPosition;
    ofVec3f rotation;
    
    ofVec3f normalRay;
    ofVec3f scaledRay;
    ofVec3f smoothedRay;
    ofVec3f normalSmoothedRay;
    
private:
    
};

#endif /* user_hpp */
