#version 120

varying vec3 lightDir, normal;
varying vec4 mainColor;

void main() {
	float intensity;
	vec4 color;

	vec3 l = normalize(lightDir);

	vec3 n = normalize(normal);

	intensity = dot(l,n);

	if (intensity > 0.05)
		color = vec4(1.0, 1.0, 1.0, 1.0) * mainColor;
	else
		color = vec4(0.1, 0.1, 0.1, 0.1) * mainColor;

	gl_FragColor = color;

}
