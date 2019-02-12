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
    ofSpherePrimitive userHead;
    
    
    void setup();
    void displayUser();
    void updateUser(ofVec3f position, ofVec3f rotation);
private:
    ofVec3f position;
    ofVec3f rotation;
};

#endif /* user_hpp */
