//
//  Created by Kris Meeusen 
//  Copyright 2012 Lab101. All rights reserved.
//


attribute vec4 position;
attribute vec3 uv;

uniform mat4 worldMatrix;

varying vec3 uvVarying;



void main()
{
    
    gl_Position =worldMatrix*position;
    uvVarying =uv;
}
