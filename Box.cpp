#include "Box.h"
#include "Triangle.cpp"

Box::Box(){

}

Box::Box(Vector3D minPt, Vector3D maxPt){
  max = maxPt;
  min = minPt;

  bbox = new BoundingBox(max, min);
}

bool Box::intersect(const Ray &ray, float& tmin, float &tmax, hitStruct &h){
  /**Vertices*/
  Vector3D a(max[0], min[1], max[2]);
  Vector3D b(min[0], min[1], max[2]);
  Vector3D c(max[0], min[1], min[2]);
  Vector3D d(max[0], max[1], min[2]);
  Vector3D e(min[0], max[1], min[2]);
  Vector3D f(min[0], max[1], max[2]);

  /**Face 1*/
  Triangle tri1(max, e, d);
  Triangle tri2(max, f, e);

  /**Face 2*/
  Triangle tri3(a, b, f);
  Triangle tri4(a, f, max);

  /**Face 3*/
  Triangle tri5(a, b, c);
  Triangle tri6(b, c, min);

  /**Face 4*/
  Triangle tri7(c, min, e);
  Triangle tri8(c, e, d);

  /**Face 5*/
  Triangle tri9(b, f, e);
  Triangle tri10(b, e, min);

  /**Face 6*/
  Triangle tri11(a, c, d);
  Triangle tri12(a, max, d);

  Vector3D edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12, edge13, edge14, edge15,
    edge16, edge17, edge18, edge19, edge20, edge21, edge22, edge23, edge24;

  /**Face 1 - front*/
  if(tri1.intersect(ray, tmin, tmax, h)){
    edge1 = e - max;
    edge2 = d - max;
    shapeHit.pointOfIntersection = tri1.intersectionPoint;
    shapeHit.surfaceNormal = edge2.cross(edge1);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  if(tri2.intersect(ray, tmin, tmax, h)){
    edge3 = f - max;
    edge4 = e - max;
    shapeHit.pointOfIntersection = tri2.intersectionPoint;
    shapeHit.surfaceNormal = edge4.cross(edge3);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
	

  /**Face 2 - top*/
  if(tri3.intersect(ray, tmin, tmax, h)){
    edge5 = b - a;
    edge6 = f - a;
    shapeHit.pointOfIntersection = tri3.intersectionPoint;
    shapeHit.surfaceNormal = edge6.cross(edge5);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  if(tri4.intersect(ray, tmin, tmax, h)){
    edge7 = f - a;
    edge8 = max - a;
    shapeHit.pointOfIntersection = tri4.intersectionPoint;
    shapeHit.surfaceNormal = edge8.cross(edge7);
    shapeHit.surfaceNormal.normalize();
    return true;
  }

  /**Face 3 - back*/
  if(tri5.intersect(ray, tmin, tmax, h)){
    edge9 = b - a;
    edge10 = c - a;
    shapeHit.pointOfIntersection = tri5.intersectionPoint;
    shapeHit.surfaceNormal = edge10.cross(edge9);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  
  else if(tri6.intersect(ray, tmin, tmax, h)){
    edge11 = c - b;
    edge12 = min - b;
    shapeHit.pointOfIntersection = tri6.intersectionPoint;
    shapeHit.surfaceNormal = edge12.cross(edge11);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  
  /**Face 4 - bottom*/
  if(tri7.intersect(ray, tmin, tmax, h)){
    edge13 = min - c;
    edge14 = e - c;
    shapeHit.pointOfIntersection = tri7.intersectionPoint;
    shapeHit.surfaceNormal = edge14.cross(edge13);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  if(tri8.intersect(ray, tmin, tmax, h)){
    edge15 = e - c;
    edge16 = d - c;
    shapeHit.pointOfIntersection = tri8.intersectionPoint;
    shapeHit.surfaceNormal = edge15.cross(edge16);
    shapeHit.surfaceNormal.normalize();
    return true;    
  }
  
  /**Face 5 - right*/
  if(tri9.intersect(ray, tmin, tmax, h)){
    edge17 = f - b;
    edge18 = e - b;
    shapeHit.pointOfIntersection = tri9.intersectionPoint;
    shapeHit.surfaceNormal = edge18.cross(edge17);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  if(tri10.intersect(ray, tmin, tmax, h)){
    edge19 = e - b;
    edge20 = min - b;
    shapeHit.pointOfIntersection = tri10.intersectionPoint;
    shapeHit.surfaceNormal = edge20.cross(edge19);
    shapeHit.surfaceNormal.normalize();
    return true;

  }
  
  /**Face 6 - left*/
  if(tri11.intersect(ray, tmin, tmax, h)){
    edge21 = c - a;
    edge22 = d - a;
    shapeHit.pointOfIntersection = tri11.intersectionPoint;
    shapeHit.surfaceNormal = edge22.cross(edge21);
    shapeHit.surfaceNormal.normalize();
    return true;
  }

  if(tri12.intersect(ray, tmin, tmax, h)){
    edge23 = max - a;
    edge24 = d - a;
    shapeHit.pointOfIntersection = tri12.intersectionPoint;
    shapeHit.surfaceNormal = edge24.cross(edge23);
    shapeHit.surfaceNormal.normalize();
    return true;
  }
  
 
  return false;
}
Vector3D Box::provideShader(Shader *shade){
  shader = shade;
}

