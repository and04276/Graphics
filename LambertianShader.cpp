#include "LambertianShader.h"
#include "hitStruct.h"
#include "SceneContainer.h"

/** \Constructor 
 * @params the kd value, lambVal
 */
LambertianShader::LambertianShader(const Vector3D &originalColor, float lambVal){
  kd = originalColor;
  lVal = lambVal;
}


/** \One argument constructor 
 * @params kd value
 */
LambertianShader::LambertianShader(ShaderCoefficient originalColor){
  kd = originalColor.diffuse;
}

/** \Apply Shader Method
 *   Function that applies the Lambertian Shader - normalizes n, and sets vector l
 *   by subtracting the intersection point - the position of the light
 *   normalizes the computed l
 *   calculates the max value of n.dot(l) to avoid dark values
 *   normalizes kd (original color value)
 *   calculates the Vector3D color value to be returned with Cooresponding Light Intensity
 *    * kd value * maxValue
 *
 *@params Vector3D n - the surface normal to the shape (taken from hitStruct of Shape)
 *        Vector3D intersect - the intersection point of ray (taken from hitStruct of Shape)
 *        const std::vector<Light*>& lights - a vector of Lights
 */
Vector3D LambertianShader::shade(Vector3D n, Vector3D intersect, const std::vector<Light*>& lights,
				 Ray &ray, SceneContainer *s, hitStruct &h){
  Vector3D color(0, 0, 0);
  Ray shadow;
  shadow = ray;
  
  for(int i = 0; i < lights.size(); i++){
    shadow.origin = h.pointOfIntersection;
    shadow.direction = lights[i]->getPointOnLight(h, shadow) - shadow.origin;
   
    if(!(s->visibilityQuery(shadow, .000001f, 999999, h))){
      n.normalize();
      Vector3D l = lights[i]->position - intersect;;
      l.normalize();
      float maxVal = max(0.0f, (float)n.dot(l));
      color += (lights[i]->intensity) * kd * maxVal;
    }
  }
  color.clamp(0, 1);
  return color;
}


/** \Sets name of Lambertain Shader*/
void LambertianShader::setName(string newName){
  name = newName;
}
