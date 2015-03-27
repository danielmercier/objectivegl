/*****************************************************************************
File: dice-model-VS.glsl

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

layout(location = 0) in vec3 vp;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main () {
  gl_Position = projection * view * model * vec4 (vp, 1.0);
};
