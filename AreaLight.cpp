#include <iostream>

#include "AreaLight.h"
#include "Light.h"

AreaLight::AreaLight(){
}

/** \Light Construtor                                                                                                                   
 * @ params Vector3D position of light, Vector3D intensity/energy of light                                                              
 */
AreaLight::AreaLight(Vector3D p, Vector3D i, Vector3D normal, float width, float length){
  position = p;
  intensity = i;
  l = length;
  w = width;
  n = normal;
}

Vector3D AreaLight::getPointOnLight(hitStruct &h, Ray &ray){;
  CoordinateSystem coord(n);

  Vector3D point;

  Vector3D a = position - coord.uVec * l/2 - coord.vVec * l/2;
  Vector3D b = position - coord.vVec * w/2 - coord.vVec * w/2;

  point = (a) + coord.uVec * (l * ray.k) + coord.vVec * (w * ray.j);
  
  return point;
};
