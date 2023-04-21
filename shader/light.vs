#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;


//-----------custom_variables
varying vec4 fragPosition;
varying vec3 normal;

void main(){
	fragTexCoord = vertexTexCoord;
	fragColor = vertexColor;
	normal = vertexNormal;
	
	
	vec4 pos = mvp * vec4(vertexPosition, 1.0);
	pos.y += (pos.z*pos.z)*0.003;
	gl_Position = pos;

	fragPosition = gl_Position;
}
