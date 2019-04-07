#version 430

layout (location = 0) in vec3 position; 

out vec4 vertexColour;

uniform vec2 location;
uniform vec4 colour;

void main(void) {
	gl_Position = vec4(position + vec3(location, 0.0), 1.0);
	vertexColour = colour;
}