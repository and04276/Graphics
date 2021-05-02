#pragma once

#include <iostream>

#include "Shader.h"
#include "ShaderCoefficient.h"

/** \Mirror Shader class*/
class MirrorShade: public Shader{
 public:
  MirrorShade();

  MirrorShade(float d);

  float depth;
  string name;
  Vector3D shade(Vector3D n, Vector3D intersect, const std::vector<Light*>& lights,
                                 Ray &ray, SceneContainer *s, hitStruct &h);
  void setName(string newName);

};
