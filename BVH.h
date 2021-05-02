#pragma once

#include <iostream>
#include <vector>

#include "Shape.h"
#include "Shader.h"
#include "Light.h"
#include "BoundingBox.h"

class BVH: public Shape{
 public:

  BVH();
  
  BVH(std::vector<Shape*> allShapes, int height);

  BVH(Shape *s, int height);
  
  bool intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h);

  Vector3D provideShader(Shader *pshader);
  
  Shape * leftMost;
  Shape * rightMost;
  
 private:


};
