#pragma once

#include <iostream>
#include <vector>

#include "Light.h"
#include "Ray.h"
#include "ShaderCoefficient.h"

/** \Generic Shader class - will use as a 
 * parent class to other shaders
 * Has virtual methods shade and setName
*/

class SceneContainer;
class hitStruct;

class Shader{
 public:

  virtual Vector3D shade(Vector3D n, Vector3D l, const std::vector<Light*>& lights, Ray &ray, SceneContainer *sc, hitStruct &h) = 0;

  virtual void setName(const string name) = 0;

  Vector3D kd;
};

