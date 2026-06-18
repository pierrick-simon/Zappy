#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 finalColor;

uniform vec3 sunDirection;
uniform vec4 sunColor;
uniform vec3 cameraPos; 
uniform sampler2D texture0;

void main() {

	vec4 textureColor;
	vec4 color;
	vec3 lightDir;
	float lightIntensity;


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = texture(texture0, fragTexCoord);

	// Set the default output color to the ambient light value for all pixels.
	color = vec4(0.1);

	// Invert the light direction for calculations.
	lightDir = -sunDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = clamp(dot(fragNormal, lightDir), 0.0f, 1.0f);

	if(lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color += (sunColor * lightIntensity);
	}

	// Clamp the final light color.
	color = clamp(color, 0.0f, 1.0f);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	finalColor = color * textureColor;
}
