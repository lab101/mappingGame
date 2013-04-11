
varying vec2 uv_var;
uniform sampler2D texture;
void main()
{

        gl_FragColor = texture2D(texture, uv_var.xy);
        // gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}





