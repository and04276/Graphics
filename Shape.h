#pragma once
#include <iostream>

#include "hitStruct.h"
#include "BoundingBox.h"

class Shader;

/** \Generic Shape Class*/
class Shape{
 public:
  virtual bool intersect(const Ray &r, float &tmin, float &tmax, hitStruct &h) = 0;

  virtual Vector3D provideShader(Shader *shader) = 0;

  Vector3D color; //Holds shape color (used in ray tracer)

  Shader *shader;
  
  hitStruct shapeHit;

  BoundingBox * bbox;

};
