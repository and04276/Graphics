#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "PerspectiveCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "LambertianShader.h"
#include "BlinnPhong.h"
#include "ShaderCoefficient.h"
#include "Box.h"
#include "hitStruct.h"
#include "../myFramebuffer/Framebuffer.cpp"                                                                                             
#include "Ray.h"
#include "ShaderCoefficient.h"
#include "MirrorShade.h"
#include "AreaLight.h"
#include "PointLight.h"
#include "BVH.h"

/**Scene Container Class*/

class SceneContainer{
 public:
  void parseJSONData(const std::string &filename);
  
  void addCamera(Camera* cameras);

  void addLight(Light* lights);

  void addShape(Shape* shapes);

  void addShaders(std::string, Shader* shaders);

  Shader *locateShader( const std::string &sname );

  bool visibilityQuery (Ray &r, float tmin, float tmax, hitStruct &hit);

  Vector3D getSceneColor(Ray &r, float tmin, float tmax, SceneContainer *s,  hitStruct &h);

  std::vector<Camera*> allCameras;

  std::vector<Light*> allLights;

  std::vector<Shape*> allShapes; 

  std::map<std::string, Shader*> allShaders;
};

