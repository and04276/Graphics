#pragma once

#include <iostream>

#include "Shape.h"
#include "BoundingBox.h"

/**Triangle Class - derived from Shape*/
class Triangle: public Shape{
 public:
  bool intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h);

  Vector3D provideShader(Shader *shade);
  
  Triangle(Vector3D v1, Vector3D v2, Vector3D v3);

  Vector3D vec1, vec2, vec3;

  Vector3D intersectionPoint;

  Vector3D max, min;
};
