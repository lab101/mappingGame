attribute vec4 position;


uniform mat4 perspectiveMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 objectMatrix ;


void main()
{
	
	vec4 objectPos  = objectMatrix*position;
	vec4 worldPos = worldMatrix *objectPos;
	gl_Position= perspectiveMatrix*worldPos;
	
	
}