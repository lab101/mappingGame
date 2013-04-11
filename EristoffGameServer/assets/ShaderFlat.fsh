uniform sampler2D texture;
varying vec3 uvVarying;

void main()
{
    gl_FragColor = texture2D(texture, uvVarying.xy);  
    gl_FragColor.a   *= uvVarying.z;
    gl_FragColor.xyz /= gl_FragColor.a; 
}