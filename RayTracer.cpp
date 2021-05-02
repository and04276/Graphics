#include "RayTracer.h"

/**image height, image width and single scene constructor*/ 
RayTracer::RayTracer(const float &imgHeight,
                     const float &imgWidth,
                     const SceneContainer &scene){
  w = imgWidth;
  h = imgHeight;
  fb = Framebuffer((float)imgWidth, (float)imgHeight);
  shapePtr = scene.allShapes;
  cameraPtr = scene.allCameras;
  lightPtr = scene.allLights;
  imData = png::image< png::rgb_pixel >((float)imgWidth, (float)imgHeight);
  sc = scene;
  rpp = 1;
}

RayTracer::RayTracer(const float &imgHeight,
                     const float &imgWidth,
                     const SceneContainer &scene, const int &r){
  w = imgWidth;
  h = imgHeight;
  fb = Framebuffer((float)imgWidth, (float)imgHeight);
  shapePtr = scene.allShapes;
  cameraPtr = scene.allCameras;
  lightPtr = scene.allLights;
  imData = png::image< png::rgb_pixel >((float)imgWidth, (float)imgHeight);
  sc = scene;
  rpp = r;
}

RayTracer::RayTracer(const float &imgHeight,
		     const float &imgWidth,  const std::vector<Shape*>& shape,
                     const std::vector<Camera*>& camera, const std::vector<Light*>& lights,
		     const SceneContainer &scene){
  w = imgWidth;
  h = imgHeight;
  fb = Framebuffer((float)imgWidth, (float)imgHeight);
  shapePtr = shape;
  cameraPtr = camera;
  lightPtr = lights;
  imData = png::image< png::rgb_pixel >((float)imgWidth, (float)imgHeight);
  sc = scene;
  rpp = 1;
}


/** \Constructor 
 * sets image width and height for png
 * sets shape, camera and light pointers
 * sets imageData infomation to be used for pngs
 */
RayTracer::RayTracer(const float &imgHeight,
		     const float &imgWidth,
		     const std::vector<Shape*>& shape,
		     const std::vector<Camera*>& camera, const std::vector<Light*>& lights){
  w = imgWidth;
  h = imgHeight;  
  fb = Framebuffer((float)imgWidth, (float)imgHeight);
  shapePtr = shape;
  cameraPtr = camera;
  lightPtr = lights;
  imData = png::image< png::rgb_pixel >((float)imgWidth, (float)imgHeight);
}

/** \Image trace - Ray Trace Method 
 * for height and width of image
 * generate ray based on camera (only set up for one camera)
 * sets an original tmax and tmix
 * sets a background color
 *
 *  for all objects 
 *  if object intersects with it's own intersect function
 *  call upon the shapes color variable and set it to the shader that is held within the shape
 *  currently and call that shader's shade function with hitStruct info computed by the shape
 *  as well as the vector of lights
 *  That method will compute the color, and set pixel x, y on the framebuffer to that color
 *
 *  Write that image to a png with the framebuffer
 **/
void RayTracer::image(string fileName){
  Shape * hitShape;
  Vector3D shapeColor(0.0, 0.0, 0.0);
 
  BVH * bvh = new BVH(shapePtr, 0);

  /**For all pixels**/
  for (unsigned int y = 0; y < imData.get_height(); y++){
    for(int x = 0; x < imData.get_width(); x++){
     
      Ray r;
      r.N = sqrt(rpp);
      r.color = Vector3D(0.0, 0.0, 0.0);

      float tmin = 0.0;
      float tmax = 99999.0;

      bool imageHit = false;
      
      /**subpixels*/
      for(int p = 0; p < r.N; p++){
	for(int q = 0; q < r.N; q++){

	  /*offset*/
	  r.k = (p + drand48()) / r.N; //y
          r.j = (q + drand48()) / r.N; //x
	  
	  /**compute subpixel ray*/
	  float xPoint = x + r.j;
	  float yPoint = y + r.k;
          cameraPtr[0]->generateRay(xPoint, yPoint, r);
  
	  if(bvh -> intersect(r, tmin, tmax, hit)){
	    hit.shape-> intersect(r, tmin, tmax, hit);
	    hitShape = hit.shape;
	    imageHit = true;	 
	  }
	  
	  else{
	    Vector3D back(0.25, 0.25, 0.25);                                                                                           
            shapeColor = back;
	  }
	  
	  if(imageHit){
	    shapeColor = hit.shape -> shader -> shade(hit.shape -> shapeHit.surfaceNormal,
						      hit.shape -> shapeHit.pointOfIntersection, lightPtr, r, &sc,
						      hit.shape -> shapeHit);
	  }	  
	
	  r.color += shapeColor;
        
	}
      }
    
     
      /**end of subpixels*/
      Vector3D cij = r.color / (rpp);
      fb.setPixel(x, y, cij);       
      
    }
  }
  
  fb.writeToPNG(fileName);
}

