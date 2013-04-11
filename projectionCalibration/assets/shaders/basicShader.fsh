varying vec4 normal_var;
varying vec2 uv_var;

varying vec3 lightPos_var;

uniform sampler2D texture;
void main()
{
        vec3 lightDir =normalize(lightPos_var);
        float lambert =  dot(normal_var.xyz,-lightDir)*0.5+0.5  ;

	
        gl_FragColor = texture2D(texture, uv_var.xy);
        gl_FragColor.xyz *= lambert ;
           //gl_FragColor.xyz = normal_var.xyz;
}





