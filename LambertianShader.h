#pragma once

#include <iostream>

#include "SceneContainer.h"
#include "Shader.h"

/** \Lambertain Shader class*/
class LambertianShader: public Shader{
 public:
  LambertianShader();

  LambertianShader(ShaderCoefficient originalColor);

  LambertianShader(const Vector3D &orignalColor, float lambVal);

  float lVal;
  Vector3D Lamb; //holds the cooresponding Vector3D that is shaded and will be used to color
  string name;
  
  Vector3D shade(Vector3D surfaceNormal, Vector3D intersect, const std::vector<Light*>& lights, Ray &ray,
		 SceneContainer *s, hitStruct &h);
  
  void setName(string newName);

};
