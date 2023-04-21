#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

//custom stuff here!!!
uniform float size=0.0;
uniform vec2 screen_size = vec2(0.0,0.0);

void main(){

	float pi = 6.28318530718;

	float direction = 8.0;
	float quality = 8.0;

	vec2 radius = size/screen_size;

	vec2 uv = fragTexCoord;
	vec4 color = texture(texture0, uv);

	for(float d=0.0; d<pi; d+= pi/direction){
		for(float i=1.0/quality; i<=1.0; i+=1.0/quality){
			color += texture(texture0, uv + vec2(cos(d) , sin(d)) * radius * i);
		}
	}
	
	color /= quality * direction - 15.0;
	vec4 texelColor = texture(texture0, fragTexCoord);
	finalColor = color * colDiffuse;
}
