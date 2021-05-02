#include <iostream>

#include "handleGraphicsArgs.h"
#include "RayTracer.cpp"
#include "SceneContainer.cpp"
#include "PerspectiveCamera.cpp"
#include "Sphere.cpp"
#include "LambertianShader.cpp"
#include "BlinnPhong.cpp"
#include "Triangle.cpp"
#include "Box.cpp"
#include "ShaderCoefficient.cpp"
#include "PointLight.cpp"
#include "MirrorShade.cpp"
#include "AreaLight.cpp"
#include "BVH.cpp"
#include "BoundingBox.cpp"

int main(int argc, char *argv[]){
  /**SceneContainer s;
  s.parseJSONData("../Renderer/oneTriangle.json");
  RayTracer trace = RayTracer(300, 300, s.allShapes, s.allCameras);                                                                     
  trace.image("trial.png");*/

  GraphicsArgs args;
  args.process(argc, argv);
  float rpp = args.rpp;
  int h = args.height, w = args.width;

  SceneContainer th;
  th.parseJSONData("../Renderer/manySpheres.json");                                                                                
  RayTracer sp = RayTracer(300, 300, th, rpp);                                                                                    
  sp.image("manySpheres.png");
  
  
  SceneContainer m;                                                                                                               
  m.parseJSONData("../Renderer/soft.json");                                                                                           
  RayTracer mi = RayTracer(300, 300, m, rpp);                                                                                           
  mi.image("soft.png");
  
  
  SceneContainer s2;
  s2.parseJSONData("../Renderer/threeTriangles.json");
  RayTracer trace2 = RayTracer(300, 300, s2, rpp);
  trace2.image("triangles.png");
  
  /** SceneContainer s3;
  s3.parseJSONData("../Renderer/spheresAndTriangles.json");
  RayTracer trace3 = RayTracer(300, 300, s3.allShapes, s3.allCameras);
  trace3.image("trial3.png");*/

  /**SceneContainer s4;
  s4.parseJSONData("../Renderer/1Ksphere.json");
  RayTracer trace4 = RayTracer(300, 300, s4.allShapes, s4.allCameras, s4.allLights);
  trace4.image("spheres.png");*/
  
  /**SceneContainer BP;
  BP.parseJSONData("../Renderer/BP.json");
  RayTracer tracebp = RayTracer(300, 300, BP.allShapes, BP.allCameras, BP.allLights);
  tracebp.image("bp.png");*/

  /**SceneContainer c;
  c.parseJSONData("../Renderer/box.json");
  RayTracer box = RayTracer(300, 300, c.allShapes, c.allCameras, c.allLights, c);                                                    
  box.image("box.png");
  */
  /**SceneContainer s;
  s.parseJSONData("../Renderer/floor.json");
  RayTracer r = RayTracer(300, 300, s, rpp);
  r.image("shadow.png");
  */
  
  /**SceneContainer re;
  re.parseJSONData("../Renderer/mirror.json");
  RayTracer me = RayTracer(500, 500, re, rpp);
  me.image("mirror.png");*/
}
