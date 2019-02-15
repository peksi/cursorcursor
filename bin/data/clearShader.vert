//
//  projectionShader.vert
//  cursorcursor
//
//  Created by Robbert Groenendijk on 14/02/2019.
//

#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;

void main() {
    
    gl_Position = modelViewProjectionMatrix * position;
}
