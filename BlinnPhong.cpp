#include "BlinnPhong.h"
#include "hitStruct.h"
#include "SceneContainer.h"

BlinnPhong:: BlinnPhong(){
}

BlinnPhong::BlinnPhong(ShaderCoefficient originalColorkd, ShaderCoefficient originalColorks, float phongEx){
  ks = originalColorks.diffuse;
  kd = originalColorkd.diffuse;
  p = phongEx;
}

BlinnPhong::BlinnPhong(const Vector3D &orignalColor, float lambVal){
}
                                                                                                                                         
Vector3D BlinnPhong::shade(Vector3D surfaceNormal, Vector3D intersect, const std::vector<Light*>& lights, Ray &ray, SceneContainer *s, hitStruct &h){

  Vector3D color(0, 0, 0);
  Ray shadow;
  shadow = ray;
  
  for(int i = 0; i < lights.size(); i++){
    shadow.origin = intersect;
    shadow.direction = lights[i]->getPointOnLight(h, shadow) - shadow.origin;

    if(!(s->visibilityQuery(shadow, .0000001f, 9999999, h))){

      surfaceNormal.normalize();       
      Vector3D l = lights[i]->getPointOnLight(h, shadow) - intersect;
      Vector3D v = ray.direction * -1.0;
      v.normalize();
      l.normalize();

      Vector3D halfVector = l + v;
      halfVector.normalize();

      Vector3D kdComp =  kd*lights[i]->intensity*max(0.0, surfaceNormal.dot(l));
      float maxVal = max(0.0, surfaceNormal.dot(halfVector));
      color +=  kdComp + ks*lights[i]->intensity*pow(maxVal, p);
    }
  }
      color.clamp(0, 1);
      
    
  
  return color;
}

void BlinnPhong::setName(string newName){
  name = newName;
}
