#version 120


attribute vec2 position;
attribute vec3 color;

varying vec4 outcolor;

uniform mat4 projection;
uniform vec2 offset;
uniform vec3 unifcolor;
uniform float unifalpha;

void main()
{
	outcolor = vec4(color+unifcolor,unifalpha);
	gl_Position = projection * vec4(position+offset, 0.0, 1.0);
}
