#pragma once

#include <iostream>
#include "Light.h"
#include "../src/Vector3D.cpp"
#include "CoordinateSystem.h"

/** \Area Light Class                                                                                                                 
 */
class AreaLight : public Light{
 public:
  AreaLight();
  AreaLight(Vector3D p, Vector3D i, Vector3D normal, float width, float length);  
  float w, l;
  Vector3D n;
  Vector3D getPointOnLight(hitStruct &h, Ray &ray);
};
