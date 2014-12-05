#version 120

varying vec4 outcolor;
varying vec2 outtexcoord;
attribute vec3 color;

uniform int hasTex;
uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, outtexcoord);
	
}
