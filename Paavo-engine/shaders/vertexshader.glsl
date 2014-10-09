#version 120


attribute vec2 position;
attribute vec3 color;
attribute vec2 texcoord;

varying vec3 outcolor;
varying vec2 outtexcoord;

void main()
{
	outcolor = color;
	outtexcoord = texcoord;
	gl_Position = vec4(position, 0.0, 1.0);
}