/*****************************************************************************
File: dice-model_FS.glsl

Informatique Graphique
Master d'informatique
Christian Jacquemin, Universite Paris-Sud & LIMSI-CNRS

Copyright (C) 2014 University Paris-Sud 
This file is provided without support, instruction, or implied
warranty of any kind.  University Paris 11 makes no guarantee of its
fitness for a particular purpose and is not liable under any
circumstances for any damages or loss whatsoever arising from the use
or inability to use this file or items derived from it.
******************************************************************************/
#version 420

in vec2 texCoordOut;
in vec3 normal;
in vec3 light;
in vec3 vertex;

layout (location = 0) out vec4 frag_colour;

uniform vec3 eye;

void main () {
	vec3 n = normalize(normal);
	vec3 l = normalize(light);
	vec3 v = normalize(vertex);
	vec3 e = normalize(eye);
	l = normalize(l-v);
	vec3 r = normalize(2 * dot(n,l) - l);
	float diffuse = max(0.2, dot(n,l));
	float specular = pow(max(0, dot(r,v)), 40);

	frag_colour = vec4(1,0,0.0,1.0);
	frag_colour.rgb *= (diffuse + specular);
};
