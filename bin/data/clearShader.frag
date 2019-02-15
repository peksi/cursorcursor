//
//  projectionShader.frag
//  cursorcursor
//
//  Created by Robbert Groenendijk on 14/02/2019.
//

#version 150

uniform vec2 u_resolution;
uniform vec2 u_mousePosition;
uniform vec2 u_contactPoint;
uniform float u_time;

out vec4 outputColor;

void main() {
    vec2 uN_resolution = gl_FragCoord.xy/u_resolution.xy;
    vec2 uN_mousePosition = u_mousePosition.xy/u_resolution.xy;
    vec2 uN_contactPoint = u_contactPoint.xy/u_resolution.xy;
    
    vec4 color = vec4(0.0);
    float r,g,b,a;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    a = 0.0;
    
    color = vec4(r,g,b,a);
    outputColor = color;
}
