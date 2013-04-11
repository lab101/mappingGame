attribute vec4 position;
attribute vec3 normal;

attribute vec2 uv ;

uniform mat4 perspectiveMatrix ;
uniform mat4 worldMatrix ;

uniform mat4 perspectiveMatrixShadow;
uniform mat4 worldMatrixShadow ;



uniform mat4 objectMatrix ;
uniform mat3 normalMatrix ;
uniform vec3 lightPos;
varying vec3 lightPos_var;
varying vec4 shadowPos_var;
varying vec4 projPos_var;

varying vec2 uv_var;
varying vec3 normal_var;
void main()
{
	
	vec4 objectPos  = objectMatrix*position;
	vec4 worldPos = worldMatrix *objectPos;
	gl_Position= perspectiveMatrix*worldPos;
    projPos_var = gl_Position;
    
   
	vec4 worldPosShadow = worldMatrixShadow *objectPos;
	shadowPos_var= perspectiveMatrixShadow* worldPosShadow ;
    
    
        normal_var =normalMatrix*normal;

    uv_var=uv.xy;
	lightPos_var = lightPos;
}