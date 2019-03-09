#version 150

uniform mat4 model;
uniform sampler2D tex;

uniform struct Light
{
	vec3 position;
	vec3 intensities;
}light;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    
    vec3 fragPosition = vec3(model * vec4(fragVert,1));

    vec3 surfaceToLight = light.position - fragPosition;

    float brightness = dot(normal,surfaceToLight) / (length(normal) * length(surfaceToLight));
    brightness = clamp(brightness, 0, 1);
    
    vec4 surfaceColor = texture(tex,fragTexCoord);
    
    finalColor = vec4(brightness * light.intensities * surfaceColor.rgb, surfaceColor.a);
}
