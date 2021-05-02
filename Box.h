#pragma once
#include <iostream>

#include "Shape.h"
#include "Shader.h"
#include "Light.h"

class Box: public Shape{
 public:
  Box();
  
  bool intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h);

  Vector3D provideShader(Shader *shade);

  Vector3D max, min;  
 
  Box(Vector3D minPt, Vector3D maxPt);

};
