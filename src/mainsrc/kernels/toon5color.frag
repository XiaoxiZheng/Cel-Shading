#version 120

varying vec3 lightDir, normal, cameraDir;
varying vec4 mainColor;

void main() {
	float intensity;
	vec4 color;

	vec3 l = normalize(lightDir);

	vec3 n = normalize(normal);

	intensity = dot(l,n);

	if (intensity > 0.7)
		color = vec4(1.0, 1.0, 1.0, 1.0) * mainColor;
	else if (intensity > 0.4)
		color = vec4(0.8, 0.8, 0.8, 1.0) * mainColor;
	else if (intensity > 0.20)
		color = vec4(0.6, 0.6, 0.6, 1.0) * mainColor;
	else if (intensity > 0.10)
		color = vec4(0.5, 0.5, 0.5, 1.0) * mainColor;
	else
		color = vec4(0.4,0.4,0.4,1.0) * mainColor;

	float hold = dot(n,cameraDir);

	float angle = acos(hold);
	angle = angle * (180/3.1415);

	if (angle > 65){
		color = vec4(0.0,0.0,0.0,1.0);
	
	}

	gl_FragColor = color;

}
