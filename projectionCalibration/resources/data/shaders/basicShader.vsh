attribute vec4 position;
attribute vec4 normal;
attribute vec2 uv ;

uniform mat4 perspectiveMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 objectMatrix ;

varying vec4 normal_var;
void main()
{
	
	vec4 objectPos  = objectMatrix*position;
	vec4 worldPos = worldMatrix *objectPos;
	gl_Position= perspectiveMatrix*worldPos;
	normal_var =vec3(uv,0);
	
}