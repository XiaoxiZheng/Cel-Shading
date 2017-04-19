#version 120

varying vec3 eyePos;
attribute  vec3 VertexPosition;
varying vec3 lightDir, normal, cameraDir;
varying vec4 mainColor;

void main(){
	lightDir = normalize(vec3(1.0,1.0,0.0));
	normal = gl_NormalMatrix * gl_Normal;


	eyePos = vec3(0.0,0.0,1.0);
	cameraDir = normalize ( eyePos - VertexPosition);

	mainColor = vec4(1.0, 0.5, 0.5, 1.0);

	gl_Position = ftransform();
}
