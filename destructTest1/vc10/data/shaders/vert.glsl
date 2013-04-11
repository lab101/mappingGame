
attribute vec4 position;
uniform mat4 perspectiveMatrix ;
uniform mat4 worldMatrix ;
void main()
{
	

	vec4 worldPos = worldMatrix *position;
	gl_Position		= perspectiveMatrix*worldPos;
	
	
}