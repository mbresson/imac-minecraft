#version 330


in vec3 vPosition_view;
in vec3 vNormal_view;
out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


vec3 blinnPhong(){

	vec3 w0 = normalize(-vPosition_view);
	vec3 wi = normalize (uLightDir_vs);
	vec3 halfVector = normalize ((w0 + wi) / 2);

	vec3 color = vec3 (uLightIntensity * (uKd*(dot (wi, vNormal_view))) + uKs * pow (dot (halfVector, vNormal_view) , uShininess) );
	return color;
};

void main() {
	fFragColor = blinnPhong();
};