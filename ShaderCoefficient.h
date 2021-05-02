#pragma once
#include <iostream>
/** \Stores the shader coefficient data l and diffuse to be used for kd and ks */
class ShaderCoefficient{
 public:
  ShaderCoefficient(Vector3D d, float l);

  float l;

  Vector3D diffuse;
};
