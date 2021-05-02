#include <iostream>
#include <algorithm> 

#include "BoundingBox.h"



BoundingBox::BoundingBox(const Vector3D& boxmax, const Vector3D& boxmin){
  max = boxmax;
  min = boxmin;
}

bool BoundingBox::intersect(const Ray& ray, float& tmin, float &tmax, hitStruct &h){
  float ax = 1/ray.direction[0];
  float ay = 1/ray.direction[1];
  float az = 1/ray.direction[2];

  /**x max's and min's*/
  if(ax >= 0.0){
    txmin = ax * (min[0] - ray.origin[0]);
    txmax = ax * (max[0] - ray.origin[0]);
  }
  else{
    txmax = ax * (min[0] - ray.origin[0]);
    txmin = ax * (max[0] - ray.origin[0]);
  }
  
  /**y min's and max's*/
  if(ay >= 0.0){
    tymax = ay * (max[1] - ray.origin[1]);
    tymin = ay * (min[1] - ray.origin[1]);
  }

  else{
    tymin = ay * (max[1] - ray.origin[1]);
    tymax = ay * (min[1] - ray.origin[1]);
  }

  /**z max's and min's*/	
  if(az >= 0.0){
    tzmin = az * (min[2] - ray.origin[2]);
    tzmax = az * (max[2] - ray.origin[2]);
  }
  else{
    tzmax = az * (min[2] - ray.origin[2]);
    tzmin = az * (max[2] - ray.origin[2]);
  }

 
  if(txmin > tymax || tymin > txmax || txmin > tzmax || tzmin > txmax || tymin > tzmax || tzmin > tymax) return false;
  else{
    return true;
  }
}

BoundingBox * BoundingBox::combine(BoundingBox* a, BoundingBox* b){
  Vector3D nmax, nmin;

  /**x max points*/
  if(a->max[0] > b->max[0]){
    nmax[0] = a->max[0];
  }
  
  else{
    nmax[0] = b->max[0];
  }

  /**x min points*/
  if(b->min[0] > a->min[0]){
    nmin[0] = a->min[0];
  }
  else{
    nmin[0] = b->min[0];
  }

  /**y max points*/
  if(a->max[1] > b->max[1]){
    nmax[1] = a->max[1];
  }
  else{
    nmax[1] = b->max[1];
  }

  /**y min points*/
  if(b->min[1] > a->min[1]){
    nmin[1] = a->min[1];
  }
  else{
    nmin[1] = b->min[1];
  }

  /**z max points*/
  if(a->max[2] > b->max[2]){
    nmax[2] = a->max[2];
  }
  else{
    nmax[2] = b->max[2];
  }

  /**z min points*/
  if(b->min[2] > a->min[2]){
    nmin[2] = a->min[2];
  }
  else{
    nmin[2] = b->min[2];
  }
  
  return new BoundingBox(nmax, nmin);

}
