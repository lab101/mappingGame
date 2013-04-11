//
//  Created by Kris Meeusen 
//  Copyright 2012 Lab101. All rights reserved.
//

precision mediump float;

varying lowp vec3 uvVarying;

uniform sampler2D texture; 

void main()
{
    
    
    gl_FragColor =texture2D(texture, uvVarying.xy);
    
    vec3 alphaSamplePos = vec3(uvVarying.x + 0.5,uvVarying.y ,0);
    vec4 alphaColor =texture2D(texture, alphaSamplePos.xy);
    
    gl_FragColor.a   *= alphaColor.x;
    gl_FragColor.a   *= uvVarying.z;
    gl_FragColor.xyz /= gl_FragColor.a;
        
}