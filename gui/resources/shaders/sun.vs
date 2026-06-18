#version 330

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;

void main() {
    mat4 mvp = matProjection * matView * matModel;
    vec4 worldPos = matModel * vec4(vertexPosition, 1.0);
    fragPos = worldPos.xyz; 
    fragNormal = normalize(mat3(matModel) * vertexNormal);
    fragTexCoord = vertexTexCoord;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
};