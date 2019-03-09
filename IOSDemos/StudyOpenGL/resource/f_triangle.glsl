#version 150

uniform sampler2D tex;
out vec4 finalColor;
in vec2 fragTexCoord;

void main() {

    finalColor = texture(tex,fragTexCoord);

}
