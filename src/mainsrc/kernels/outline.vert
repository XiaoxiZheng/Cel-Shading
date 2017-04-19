#version 120


varying vec3 eyePos;
attribute  vec3 VertexPosition;
varying vec3 lightDir, normal, cameraDir;


void main(){

	
	eyePos = vec3(0.0,0.0,1.0);
	cameraDir = normalize ( eyePos - VertexPosition);

	gl_Position = ftransform();
}
