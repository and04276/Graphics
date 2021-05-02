#pragma once

#include <iostream>

#include "Ray.h"
#include "hitStruct.h"
#include "../src/Vector3D.cpp"

class Shape;

class BoundingBox{

 public:
  
  BoundingBox(const Vector3D& boxmax, const Vector3D& boxmin);

  Vector3D min, max;

  bool intersect(const Ray& r, float& tmin, float &tmax, hitStruct &h);

  BoundingBox * combine(BoundingBox* a, BoundingBox *b);
  
  float txmin, txmax, tymin, tymax, tzmax, tzmin;

};
