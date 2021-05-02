#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Ray.h"
#include "CoordinateSystem.cpp"

class Camera{
 public:
  virtual void generateRay(const float i, const float j, Ray &r ) = 0;

  Vector3D position; //center position    
 protected:
  string name;
  CoordinateSystem coord;
  float width, height; //imagePlane
  float nx, ny; //pixel dimnesions

  float focalLength;
};

