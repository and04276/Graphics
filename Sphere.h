#pragma once

#include <iostream>

#include "Shape.h"
#include "Shader.h"
#include "Light.h"
#include "BoundingBox.h"

class Sphere: public Shape{
 public:  
  bool intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h);

  Vector3D provideShader(Shader *pshader);

  Vector3D center;
  
  float radius;

  Vector3D min, max;
  
  Sphere();
  
  Sphere(Vector3D sCenter, float sRadius);
  
 private:


};

