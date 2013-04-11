varying vec4 normal_var;

void main()
{
	gl_FragColor= vec4(1.0,0.0,0.0,1.0);
	gl_FragColor.xyz =  normal_var.xyz ;
}





