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

void User::updateUser(ofVec3f position, ofVec3f rotation) {
    _position = position;
    _rotation = rotation;
}

void User::displayUser() {
    
    userHead.set(30, 10);
    userHead.setPosition(_position.x, _position.y, _position.z);
    userHead.draw();
    
}
