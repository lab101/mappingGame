#version 120
attribute vec4 position;
attribute vec3 uv;

uniform mat4 worldMatrix;
varying vec3 uvVarying;



void main()
{
    gl_Position = worldMatrix * position;
    uvVarying = uv;
   // uvVarying.y=1.0-uv.y;

}