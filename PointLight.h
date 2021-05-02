#pragma once

#include <iostream>
#include "../src/Vector3D.cpp"
#include "Ray.h"
#include "Light.h"

/** \Generic Light Class                                                                                                                
 */
class PointLight : public Light{
 public:
  PointLight();
  PointLight(Vector3D p, Vector3D i);
  Vector3D getPointOnLight(hitStruct &h, Ray &ray);
};
