#pragma once

#include <iostream>
#include <string>

#include "Camera.h"

class PerspectiveCamera: public Camera{
 public:
  
  /**default*/
  PerspectiveCamera();

  PerspectiveCamera(const float d, const float imgW, const Vector3D pos, const Vector3D viewDir, float x, float y);
  void generateRay(const float i, const float j, Ray &r) ;
 
};

