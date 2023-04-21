#version 330

varying vec3 normal;
varying vec4 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;


void main(){
	float doo = dot(normal, vec3(0.0, 0.5, -0.5));
	
	doo = 1.0 - (floor(doo*8.0)/8.0);

	vec3 color = colDiffuse.xyz;
	float depth = (1.0 - (fragPosition.z/150.0));
	finalColor = vec4( color * doo, 1.0);
}
