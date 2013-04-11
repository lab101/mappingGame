attribute vec4 position;
attribute vec4 normal;
attribute vec4 tangent;
attribute vec2 uv ;

uniform mat4 perspectiveMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 objectMatrix ;

uniform vec3 lightPos;
varying vec3 lightPos_var;
varying vec2 uv_var;
varying vec4 normal_var;
void main()
{
	
	vec4 objectPos  = objectMatrix*position;
	vec4 worldPos = worldMatrix *objectPos;
	gl_Position= perspectiveMatrix*worldPos;
    normal_var =tangent;
    normal_var =normal;

    uv_var=uv.xy;
	lightPos_var = lightPos;
}