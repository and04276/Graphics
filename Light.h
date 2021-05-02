#pragma once

#include <iostream>
#include "../src/Vector3D.cpp"
#include "Ray.h"
//#include "hitStruct.h"

class hitStruct;
/** \Generic Light Class
 */

class Light{  
 public:
  Vector3D intensity;
  Vector3D position;
  
  virtual Vector3D getPointOnLight(hitStruct &h, Ray &ray) = 0;
};
