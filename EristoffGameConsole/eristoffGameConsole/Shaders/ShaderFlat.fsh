//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


varying mediump vec3 uvVarying;
uniform sampler2D texture; 

void main()
{
    
    gl_FragColor =texture2D(texture, uvVarying.xy);    
   // gl_FragColor.xyz /=gl_FragColor.a ;
////    
//    
//    mediump vec3 yuv;
//    lowp vec3 rgb;
//    
//    yuv.x = texture2D(texture,uvVarying.xy).r;
//    yuv.yz = texture2D(texture,uvVarying.xy).rg - vec2(0.5, 0.5);
//    
//    // BT.601, which is the standard for SDTV is provided as a reference
//    /*
//     rgb = mat3(    1,       1,     1,
//     0, -.34413, 1.772,
//     1.402, -.71414,     0) * yuv;
//     */
//    
//    // Using BT.709 which is the standard for HDTV
//    rgb = mat3(      1,       1,      1,
//               0, -.18732, 1.8556,
//               1.57481, -.46813,      0) * yuv;
//    
//    gl_FragColor = vec4(rgb, 1);

     
}