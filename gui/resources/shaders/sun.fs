#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragPos;
in vec3 fragNormal;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 sunDirection;
uniform vec3 sunColor;
uniform vec3 cameraPos;

void main()
{
    vec4 tex = texture(texture0, fragTexCoord);
    vec4 albedo = tex * colDiffuse * fragColor;

    vec3 normal = normalize(fragNormal);
    vec3 direction = normalize(-sunDirection);

    float NdotL = max(dot(normal, direction), 0.0);
    vec3 ambient = 0.35 * sunColor;
    vec3 diffuse = NdotL * sunColor;

    vec3 camPosDelta = normalize(cameraPos - fragPos);
    vec3 reflectionVector = reflect(-direction, normal);
    float spec = pow(max(dot(camPosDelta, reflectionVector), 0.0), 32.0);
    vec3 specular = 0.35 * spec * sunColor;

    vec3 lit = ambient + diffuse + specular;
    finalColor = vec4(albedo.rgb * lit, albedo.a);
}