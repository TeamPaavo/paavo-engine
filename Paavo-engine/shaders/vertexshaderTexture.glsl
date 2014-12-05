#version 120


attribute vec2 position;
attribute vec2 texcoord;

varying vec2 outtexcoord;

uniform mat4 projection;
uniform vec2 offset;

void main()
{

	outcolor = vec4(color+unifcolor,unifalpha);
	outtexcoord = texcoord;
	gl_Position = projection * vec4(position+offset, 0.0, 1.0);
}
