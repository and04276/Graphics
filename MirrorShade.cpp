#include "MirrorShade.h"

/**default constructor - if depth not specified, set to 2*/
MirrorShade::MirrorShade(){
  depth = 2;
}

/**constructor that specifies depth*/
MirrorShade::MirrorShade(float d){
  depth = d;
}

/**Mirror shader
 * creates a reflection vector that is calculated by -v + 2(v dot n)*n
 * sends the reflect vector into the scene to return scene color
 *
 * @params normal vector (hitStruct), point of intersection, vector of lights (not used for mirrors, 
 * but contained in parent class method, Ray (not used, but contained in parent class method), hitStruct
 * to track shapes hit and hit information
 */
Vector3D MirrorShade::shade(Vector3D n, Vector3D intersect, const std::vector<Light*>& lights,
                                 Ray &ray, SceneContainer *s, hitStruct &h){
  Vector3D color(0, 0, 0);
  Ray reflect;

  depth = depth - 1;
  n.normalize();
  Vector3D v = ray.direction * -1.0;
  reflect.origin = intersect;
  reflect.direction = (-1.0*v) + 2*(v.dot(n)) * n;

  /**gets scene's color from reflect ray*/
  color = s->getSceneColor(reflect, .0001, 9999, s, h);
  return color;
}


/** \Sets name of Mirror Shader*/
void MirrorShade::setName(string newName){
  name = newName;
}
