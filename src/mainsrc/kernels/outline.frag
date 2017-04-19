#version 120


varying vec3 lightDir, normal, cameraDir;
varying vec4 mainColor;


void main() {

	vec4 color;
	color = vec4(1.0, 0.5, 0.5, 1.0);
	float hold = dot(normal,cameraDir);

	float angle = acos(hold);
	angle = angle * (180/3.1415);

	if (angle > 60){
		color = vec4(0.0,0.0,0.0,1.0);
		gl_FragColor = color;
	}
	
color = vec4(0.0,0.0,0.0,1.0);
		gl_FragColor = color;
}
