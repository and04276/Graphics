#include "SceneContainer.h"

/**Ray Tracer Class*/
class RayTracer{
 public:

  RayTracer(const float &imgHeight,
                     const float &imgWidth,
	    const SceneContainer &scene);

  RayTracer(const float &imgHeight,
                     const float &imgWidth,
		       const SceneContainer &scene, const int &r);
  
  RayTracer(const float &imgHeight,
            const float &imgWidth,  const std::vector<Shape*>& shape,
	    const std::vector<Camera*>& camera, const std::vector<Light*>& lights, const SceneContainer &scene);
  
  RayTracer(const float &imgHeight,
	    const float &imgWidth,
	    const std::vector<Shape*>& shape, const std::vector<Camera*>& camera, const std::vector<Light*>& lights);

  png::image< png::rgb_pixel > imData; //png image data
  float w; //image width for png
  float h; //image height for png

  hitStruct hit; //hit struct to send into shape intersect NOT SHAPE HITSTRUCT
  
  std::vector<Shape*> shapePtr; //Shape object pointer
  std::vector<Camera*> cameraPtr; //Camera pointer
  std::map<std::string, Shader*> shader; //Shader map pointer
  std::vector<Light*> lightPtr; //Lights pointer
  SceneContainer sc;
  
  Framebuffer fb; //Framebuffer
  float rpp;
  void image(string fileName); //Image output to png -> the ray tracing function

};
