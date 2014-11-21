#version 120

uniform sampler2D tex;

varying vec3 outcolor;
varying vec2 outtexcoord;
uniform float unifalpha;

void main()
{
//	if(outtexcoord != 0)
//	gl_FragColor = texture2D(tex, outtexcoord);
	
//	else
	gl_FragColor = vec4(outcolor,unifalpha);
}