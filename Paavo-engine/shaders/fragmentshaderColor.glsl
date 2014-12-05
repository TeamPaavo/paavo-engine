#version 120

varying vec4 outcolor;

void main()
{
	gl_FragColor = vec4(outcolor);
}
