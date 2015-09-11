#version 430

in vec4 _color;
in vec3 _normal;

out vec4 finalColor;

void main()
{
	float factor = dot(_normal, normalize(vec3(1.0, 1.0, 0.0)));	
	finalColor = _color;
}