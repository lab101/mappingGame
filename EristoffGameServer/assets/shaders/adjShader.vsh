attribute vec4 position;


attribute vec2 uv ;



varying vec2 uv_var;

void main()
{

	gl_Position= position;
    uv_var =uv;
}