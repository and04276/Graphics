#pragma once
#include <iostream>

#include "../src/Vector3D.cpp"

class Ray{
 public:

  Vector3D origin;

  Vector3D direction;

  int N;

  Vector3D color;

  float j, k;
};
