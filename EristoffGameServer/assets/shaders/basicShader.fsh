varying vec3 normal_var;
varying vec2 uv_var;

varying vec3 lightPos_var;
varying vec4 shadowPos_var;
varying vec4 projPos_var;
uniform sampler2D textureShadow;
uniform sampler2D textureMain;
void main()
{
        vec3 lightDir =normalize(lightPos_var);
        float lambert =  dot(normal_var.xyz,lightDir)*0.5+0.5  ;

	vec3 shadowDepthLokal = (shadowPos_var.xyz/shadowPos_var.w) ;
    vec4 shadowDepth = texture2D(textureShadow, shadowDepthLokal.xy*0.5 +0.5)*2.0 -1.0;
    gl_FragColor = texture2D(textureMain, uv_var);
    if (shadowDepthLokal.z >shadowDepth.x)
    {
      gl_FragColor.xyz *=0.0 ;
    
    }
        // gl_FragColor = texture2D(texture, uv_var);
       gl_FragColor.xyz *= lambert ;
  // gl_FragColor.xyz = normal_var.xyz;
    // gl_FragColor.xyz *= lambert ;
}





