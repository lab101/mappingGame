

attribute vec4 position;
attribute float psize;
attribute float alpha;
attribute float texOffset;

varying lowp float  alpha_frag;
varying lowp float texOffset_frag;

uniform mat4 worldMatrix;


void main()
{
    
    gl_Position = worldMatrix * position;
    gl_PointSize = psize;
    
    texOffset_frag = texOffset;
    alpha_frag = alpha;
 
}
