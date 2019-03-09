#version 150

in vec3 vert;
uniform mat4 modelViewMatrix;

void main(){

	gl_Position = modelViewMatrix * vec4(vert,1);

}