#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

//custom stuff here!!!
uniform sampler2D tex;

void main(){
	vec4 texelColor = texture(texture0, fragTexCoord);
	vec4 texelColor_two = texture(tex, fragTexCoord);
	
	float edge = abs(texelColor_two.x - (texelColor.x));
	vec3 color = vec3(0.0, 0.0, 0.0);
	if(edge > 0.001){
		color = vec3(1.0, 1.0, 1.0);
	}
	
	if(fragTexCoord.x > 0.5){
		//color = texelColor.xyz;
	}
	else{
		//color = texelColor_two.xyz;
	}

	finalColor = vec4(color, 1.0);
}
