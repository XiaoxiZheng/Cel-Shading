#version 120


varying vec3 lightDir, normal;

void main(){
	lightDir = normalize(vec3(1.0,1.0,0.0));
	normal = gl_NormalMatrix * gl_Normal;

	gl_Position = ftransform();
}
