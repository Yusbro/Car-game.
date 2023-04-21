#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

uniform vec4 colDiffuse;

out vec4 finalColor;

vec2 res = vec2(800.0, 600.0);

void main(){
	float h = 3.0;
	
	vec4 o = texture(texture0, fragTexCoord + (vec2(0.0, 0.0)/res));
	vec4 n =texture(texture0, fragTexCoord + (vec2(0.0, h)/res));
	vec4 e =texture(texture0, fragTexCoord + (vec2(h, 0.0)/res));
	vec4 s =texture(texture0, fragTexCoord + (vec2(0.0, -h)/res));
	vec4 w =texture(texture0, fragTexCoord + (vec2(-h, 0.0)/res));

	vec4 dy = (n - s) * 0.5;
	vec4 dx = (e - w) * 0.5;
	
	vec4 edge = sqrt(dx * dx + dy* dy) * 5.0;
	vec4 angle = atan(dy, dx);
	
	float intensity = edge.x + edge.y +edge.z;
	vec3 color = vec3(1.0, 1.0, 1.0);
	if(intensity > 0.4){
		color = vec3(0.0, 0.0, 0.0);
	}

	finalColor = vec4( color ,1.0);
}
