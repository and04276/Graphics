#include "SceneContainer.h"

/**Rasterizer*/
class Rasterizer{
 public:

  Rasterize(const float &imgHeight,
                     const float &imgWidth,
                       const SceneContainer &scene, const int &r);

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
  void image(string fileName); //Image output to png -> the ray tracing function                                                        
};
