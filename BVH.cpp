#include <iostream>
#include <vector>
#include <algorithm>

#include "BVH.h"

BVH::BVH(std::vector<Shape*> allShapes, int height = 0){
  height++;
  float k = allShapes.size()/2;
  float size = allShapes.size();

  if(size == 1){
    leftMost = allShapes[0];
    rightMost = nullptr;
    bbox = new BoundingBox(allShapes[0]->bbox->max, allShapes[0]->bbox->min);
  }

  else if(size == 2){
    leftMost = allShapes[0];
    rightMost = allShapes[1];
    bbox = bbox -> combine(leftMost->bbox, rightMost->bbox);
  }

  else if(size > 2){
    std::vector<Shape*> lefts, rights;
    /**first half of shapes*/
    for(int j = 0; j < k; j++){
      lefts.push_back(allShapes[j]);
    }
    /**second half of shapes*/
    for(int m = k; m < size; m++){
      rights.push_back(allShapes[m]);
    }
    
    leftMost = new BVH(lefts, height%3);
    rightMost = new BVH(rights, height%3);
    bbox = bbox->combine(leftMost->bbox, rightMost->bbox);
  }
  
}

BVH::BVH(Shape* oneShape, int height = 0){
  leftMost = oneShape;
  rightMost = nullptr;
  bbox = new BoundingBox(oneShape->bbox->max, oneShape->bbox->min);
}


bool BVH::intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h){
  bool rightHit = false;
  bool leftHit = false;
  /**if ray hits root box*/
  if(bbox != nullptr){
 
    if(bbox->intersect(ray, tmin, tmax, h)){
      /**if ray hits left subtree box*/
      if(leftMost != nullptr){
	  if(leftMost -> intersect(ray, tmin, tmax, h)){  
	    leftHit = true;
	  }
	}
	/**if ray hits right subtree box*/
      if(rightMost != nullptr){
	  if(rightMost -> intersect(ray, tmin, tmax, h)){
	    rightHit = true;
	  }
	}
    }
  }

  /**if ray hits BOTH of them*/
  if(rightHit == true && leftHit == true){
    /**Return closest*/
    if(leftMost -> shapeHit.actualT < rightMost -> shapeHit.actualT){
      leftHit = false;
      }
  }

  /**just left hit*/
    if(leftHit == true){
      /**store the shape it hit in the hit struct*/
      h.shape = leftMost;
      return true;
    }
    
    /**just right hit*/
    else if(rightHit == true){
      /**store the shape it hit in the hit struct*/
      h.shape = rightMost;
      return true;
    }

  else{
    return false;
  }
}


Vector3D BVH::provideShader(Shader *pshader){
  shader = pshader;
}
