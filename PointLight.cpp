#include <iostream>

#include "PointLight.h"

PointLight::PointLight(){
  position = Vector3D(0, 0, 0);
  intensity = Vector3D(0, 0, 0);
}

/** \Light Construtor                                                                                                                   
 * @ params Vector3D position of light, Vector3D intensity/energy of light                                                              
 */
PointLight::PointLight(Vector3D p, Vector3D i){
  position = p;
  intensity = i;
}

Vector3D PointLight::getPointOnLight(hitStruct &h, Ray &ray){
  return position;
}
