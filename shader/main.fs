#version 330

varying vec4 fragPosition;
varying vec3 fragNormal;

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

//custom_variables!!
float far = 130.0;


void main(){	
	float f = distance(fragPosition.xyz, vec3(0.0, -2.0, -8.0) )/far;
	float dot_normal = dot(fragPosition.xyz, vec3(0.0, 0.0, 0.0));

	float normal_avg = (fragNormal.x + fragNormal.y + fragNormal.z) / 3.0;
	//finalColor = vec4( vec3(1.5 - f) * normal_avg, 1.0);
	finalColor = vec4(fragNormal * colDiffuse.xyz, 1.0);
}
