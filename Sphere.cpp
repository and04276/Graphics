#include <iostream>
#include <cmath>

#include "Sphere.h"

/** \Default Sphere Constructor*/
Sphere::Sphere(){
  center = Vector3D(0, 0, 0);
}

/** \Sphere Constructor
 *
 * @params Vector3D center of sphere, Vector3D radius of sphere
 */
Sphere::Sphere(Vector3D sCenter, float sRadius){
  center = sCenter;
  radius = sRadius;

  max[0] = sCenter[0] + sRadius;
  max[1] = sCenter[1] + sRadius;
  max[2] = sCenter[2] + sRadius;

  min[0] = sCenter[0] - sRadius;
  min[1] = sCenter[1] - sRadius;
  min[2] = sCenter[2] - sRadius;
  
  bbox = new BoundingBox(max, min);
}

/** \Sphere intersection method 
 *  computes intersection truth value
 *  p(t): (x - centerx)^2+(y - centery)^2+(z-centerz)^2 - radius^2 = 0 
 *  using the quadratic equation
 *  if point on ray intersects with the computed value of equation
 *  set tmax value to current tvalue; you are at the max
 *  send back true after computing various hitStruct information to be used for shading
 *
 * @params Ray r, tmin, tmac and hitStruct h*/
bool Sphere::intersect(const Ray &r, float &tmin, float &tmax, hitStruct &h){  
  float A = (r.direction).dot(r.direction);
  Vector3D eMinusC = r.origin - center;
  float B = 2.0*(r.direction).dot(eMinusC);
  float C = eMinusC.dot(eMinusC) - (radius*radius);
  
  float disc = ((B*B) - (4.0f)*A*C); //discriminant
  
  //No intersect
  if(disc < 0.0f){
    return false;
  }

  //intersect - two solutions
  float squaredD = sqrt(disc);
  float t0 = (-B - squaredD) / (2.0 * A);
  float t1 = (-B + squaredD) / (2.0 * A);

  float t = t1;
  if(t0 < t1){
    t = t0;
  }

  shapeHit.actualT = t;
  if(t >= tmin && t < tmax){
    tmax = t;
    shapeHit.pointOfIntersection = r.origin + t * r.direction;
    shapeHit.surfaceNormal = shapeHit.pointOfIntersection - center;
    shapeHit.surfaceNormal.normalize();
    return true;
  }

  else{
    return false;
  }
}

Vector3D Sphere::provideShader(Shader *pshader){
  shader = pshader;
}


