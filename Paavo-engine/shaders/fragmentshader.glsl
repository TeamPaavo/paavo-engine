#version 120

uniform sampler2D tex;

varying vec3 outcolor;
varying vec2 outtexcoord;

void main()
{
	vec4 color = texture2D(tex, outtexcoord);
	gl_FragColor = color;
}