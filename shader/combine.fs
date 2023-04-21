#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

//custom stuff here!!!
uniform sampler2D blur_tex;

void main(){
	vec4 texelColor = texture(texture0, fragTexCoord);
	vec4 blur_color = texture(blur_tex, fragTexCoord);
	finalColor = texelColor * blur_color * colDiffuse;
}
