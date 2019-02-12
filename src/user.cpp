//
//  user.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 08/02/2019.
//

#include "user.hpp"

User::User() {
}
void User::setup() {
    
}

void User::updateUser(ofVec3f _position, ofVec3f _rotation) {
    position = _position;
    rotation = _rotation;
}

void User::displayUser() {
    
    userHead.set(30, 10);
    userHead.setPosition(position.x, position.y, position.z);
    userHead.draw();
    
}
