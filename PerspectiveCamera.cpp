#include <iostream>
#include <cstdlib>
#include <cmath>

#include "PerspectiveCamera.h"

using namespace sivelab;   
                                                                                                                      
/**default*/
PerspectiveCamera::PerspectiveCamera(){
  name = "Perspective Camera";
  position = Vector3D(0, 0, 0);                                                                                                   
  focalLength = 1.0;
  
  width = 10;
  height = 10;

  nx = 10;
  ny = 10;
}

/** \Constructor                                                                                                                
 *                                                                                                                                      
 * initializes name to Perspective Camera 
 * pixel dimensions to x and y float values
 * coordinate system with viewDirection and tempUp vector
 * camera position
 * width to image plane width
 * height to the aspect ratio calculation (width/height = nx/ny)
 *
 * @params d (focalLength), imgW (imagePlaneWidth), pos (camera position), viewDir (view direction), x (pixels), y (pixels)              */
PerspectiveCamera::PerspectiveCamera(const float d, const float imgW, const Vector3D pos, const Vector3D viewDir, float x, float y){
  name = "Perspective Camera";
  Vector3D tempup = Vector3D(0, 1, 0);               

  nx = x;
  ny = y;

  coord = CoordinateSystem(viewDir, tempup);
  position = pos; //camera position
  
  focalLength = d;

  width = imgW; //imagePlane
  height = (width * ny) / nx; //imagePlane

}


/** \generateRay                                                                                                                        
 *                                                                                                                                      
 *                                                                 
 * initialize l(left half width) = -width/2                                                                                             
 * initialize r(right half width) = width/2                                                                               
 * initialize b(bottom half length) = -height(calculated above)/2                                                                       
 * initialize t(upper half length) = height/2                                                                                           
 *                                                                                                
 * u = l(left half width) + (width)*(get to half the pixel) / nxpixels                                                                   * v = b(bottom half length) + (height)*(get to hald the pixel) / nypixels
 *
 * set ray origin to position
 *
 * ray direction = (wVector(from coordinate system) * -focalLength) + (uVector * u) + (vVector * v) 
 *                          
 * @params i (x image size), j (y image size), Ray (virtual class Ray.h)             
 */
void PerspectiveCamera::generateRay(const float i, const float j, Ray &ray ){
  float l = -width/2.0;
  float r = width/2.0;
  float b = -height/2.0;
  float t = height/2.0;
  ray.origin = position;
  
  float u = (l) + (r-l) * (i) / nx;
  float v = (b) + (t-b) * (j) / ny;
 
  ray.direction = (coord.wVec * -focalLength) + (coord.uVec * u) + (coord.vVec * v);    
}
