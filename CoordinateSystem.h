#pragma once

#include <iostream>
#include "../src/Vector3D.cpp"

using namespace sivelab;

class CoordinateSystem{
 public:

  /**Default Constructor*/
  CoordinateSystem();
  
  CoordinateSystem(const Vector3D &viewDir);

  CoordinateSystem(const Vector3D &viewDir, Vector3D &tempUp);

  Vector3D uVec;

  Vector3D vVec;

  Vector3D wVec;
  


};
