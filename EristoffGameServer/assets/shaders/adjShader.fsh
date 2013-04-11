
uniform sampler2D textureMain;
varying vec2 uv_var;
uniform float saturation;
uniform float contrast;
uniform float brightness;
void main()
{
       

	   vec4 color = texture2D(textureMain,uv_var);
    
    
    
    
    
    
    float pivot=(min(min(color.x, color.y), color.z)+max(max(color.x, color.y), color.z))/2.0;
   color.xyz -= vec3( pivot );
    color.xyz *= saturation;
    color.xyz += vec3( pivot );
    
    
   color.xyz= ((color.xyz - 0.5) * max(contrast, 0.0)) + 0.5;
    
 
   color.xyz += brightness;
    
    
    
    
   
    gl_FragColor =color;
   
 
}





