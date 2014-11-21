#version 120


attribute vec2 position;
attribute vec3 color;
attribute vec2 texcoord;

varying vec3 outcolor;
varying vec2 outtexcoord;

uniform mat4 projection;
uniform mat4 world;
uniform mat4 view;
uniform vec2 offset;

void main()
{
	outcolor = color;
	outtexcoord = texcoord;
	gl_Position = projection * view * world * vec4(position+offset, 0.0, 1.0);
}