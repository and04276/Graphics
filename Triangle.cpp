#pragma once
#include <iostream>

#include "Triangle.h"

/** \Constructor
 *
 *  @params 3 Vector3D that correspond with the vectors that are intersecting at 3 points*/
Triangle::Triangle(Vector3D v1, Vector3D v2, Vector3D v3){
  vec1 = v1;
  vec2 = v2;
  vec3 = v3;

  for(int i = 0;  i<3; i++){
    if(vec1[i] > vec2[i] && vec1[i] > vec3[i]){
      max[i] = vec1[i];
    }
    else if(vec2[i] > vec1[i] && vec2[i] > vec3[i]){
      max[i] = vec2[i];
    }
    else{
      max[i] = vec3[i];
    }

    if(vec1[i] < vec2[i] && vec1[i] < vec3[i]){
      min[i] = vec1[i];
    }
    else if(vec2[i] < vec1[i] && vec2[i] < vec3[i]){
      min[i] = vec2[i];
    }
    else{
      min[i] = vec3[i];
    }
  }
  
  bbox = new BoundingBox(max, min);

}


/** \Triangle intersect
 *
 *  Create a whole bunch of values to represent
 *  the computation of vec1 - vec2, vec1 - rayOrigin, and vec1 - vec3
 *  create the matrix M
 *  compute the tvalue with matrix M and corresponding values
 *  if t is not in range, then false
 *  if beta or beta + gamma > 1 or < 0 then false
 *
 *  otherwise, calculate hit information using the edges computed
 */
bool Triangle::intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &hitter){
  float a, b, c, d, e, f, g, h, i, j, k, l;

  a = vec1[0] - vec2[0];
  b = vec1[1] -	vec2[1];
  c = vec1[2] -	vec2[2];
  
  d = vec1[0] - vec3[0];
  e = vec1[1] -	vec3[1];
  f = vec1[2] - vec3[2];
  
  g = ray.direction[0];
  h = ray.direction[1];
  i = ray.direction[2];
  
  j = vec1[0] - ray.origin[0];
  k = vec1[1] - ray.origin[1];
  l = vec1[2] -	ray.origin[2];

  float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
  float t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;

  if((t < tmin) || (t > tmax)){
    return false;
  } 

  float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / M;
  if(gamma < 0.0 || gamma > 1.0){
    return false;
  }

  float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
  if(beta < 0.0 || beta > (1.0 - gamma)){
    return false;
  }

  tmax = t;
  shapeHit.pointOfIntersection = vec1 + beta * (vec2 - vec1) + gamma * (vec3 - vec1);
  intersectionPoint = shapeHit.pointOfIntersection; //used for boxes

  Vector3D edgeU, edgeV;
  edgeU = vec2 - vec1;
  edgeV = vec3 - vec1;

  shapeHit.surfaceNormal = edgeU.cross(edgeV);
  shapeHit.surfaceNormal.normalize();
  shapeHit.actualT = t;
  
  return true;
}


Vector3D Triangle::provideShader(Shader *shade){
   shader = shade;
}
