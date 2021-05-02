#pragma once
#include <iostream>

#include "../src/Vector3D.cpp"
#include "Shader.h"

class Shape;

/**HitStruct Class*/
/**Holds all hit information*/
class hitStruct{
 public:
  Vector3D pointOfIntersection;
  Vector3D surfaceNormal;
  float actualT;

  Shape * shape;
  bool hit = false;
};
