#version 400
in vec3 vp;
uniform vec3 offset;

void main(){
	vec3 totalOffset = offset + vp;
	gl_Position = vec4(totalOffset, 1.0);
}