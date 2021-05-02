#pragma once

#include <iostream>

#include "Shader.h"
#include "SceneContainer.h"
#include "ShaderCoefficient.h"

/** \BlinnPhong Shader class*/
class BlinnPhong: public Shader{
 public:
  BlinnPhong();

  BlinnPhong(ShaderCoefficient originalColorkd, ShaderCoefficient originalColorks, float phongEx);

  BlinnPhong(const Vector3D &orignalColor, float lambVal);

  float lVal;
  float p; //phong exponent
  Vector3D ks, kd;
  Vector3D BP; //holds the cooresponding Vector3D that is shaded and will be used to color                                             
  string name;
  
  Vector3D shade(Vector3D surfaceNormal, Vector3D intersect, const std::vector<Light*>& lights, Ray &ray, SceneContainer *s, hitStruct &h);

  void setName(string newName);

};

