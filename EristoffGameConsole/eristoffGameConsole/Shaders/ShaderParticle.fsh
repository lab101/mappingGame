//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//



uniform sampler2D texture; 
varying lowp float alpha_frag;
varying lowp float texOffset_frag;


void main()
{
    //gl_PointCoord.y /= 2.0;
    mediump vec2 realTexCoord = gl_PointCoord;
    realTexCoord.y = (gl_PointCoord.y / 2.0) + (texOffset_frag * 0.5);
    gl_FragColor = texture2D(texture, realTexCoord);
    gl_FragColor.a *= alpha_frag;
    gl_FragColor.xyz /= gl_FragColor.a;
   
    
}