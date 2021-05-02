#include <nlohmann/json.hpp>

#include "SceneContainer.h"
#include "ShaderCoefficient.h"

using json = nlohmann::json;

/** \adds camera to camera vector*/
void SceneContainer::addCamera(Camera* cameras){
  allCameras.push_back(cameras);
}

/** \adds light to light  vector*/
void SceneContainer::addLight(Light* lights){
  allLights.push_back(lights);
}

/** \adds shape to shape vector*/
void SceneContainer::addShape(Shape* shapes){
  allShapes.push_back(shapes);
}

/** \adds shader to shader vector map*/
void SceneContainer::addShaders(string name, Shader* shaders){
  allShaders.insert(pair<string, Shader*>(name, shaders));
}

/** \locates current shader being used*/
Shader* SceneContainer::locateShader(const string &sname){
  std::map<std::string, Shader*>::const_iterator mIterator = allShaders.find( sname );
     if (mIterator != allShaders.end()) {
            return mIterator->second;
     }
        else
            return nullptr;
}

/** \returns the color of scene where a reflection ray hits*/
Vector3D SceneContainer::getSceneColor(Ray &r, float tmin, float tmax, SceneContainer *s, hitStruct &h){
  Vector3D sceneColor;
  for(int i = 0; i < allShapes.size(); i++){
    if(allShapes[i]->intersect(r, tmin, tmax, h)){
      allShapes[i] -> color = allShapes[i] -> shader -> shade(allShapes[i] -> shapeHit.surfaceNormal,
							       allShapes[i] -> shapeHit.pointOfIntersection,
							       allLights, r, s, allShapes[i]->shapeHit);
      sceneColor = allShapes[i] -> color;
    }
  }
  return sceneColor;                                                                                            
}

/** \Parse JSON files
 * Modified for and04276 corresponding methods
 * 
 **/
void SceneContainer::parseJSONData(const string &filename){
    cout << "Attempting to parse: " << filename <<endl;
    ifstream inputFileStream( filename );
    json j;
    inputFileStream >> j;
    Vector3D p;
    /**CAMERAS*/
    json jsonCameraStructure = j["scene"]["camera"];
    if (jsonCameraStructure.is_array()) {
        cout << "Number of cameras: " << jsonCameraStructure.size() << endl;
        for (auto i=0; i<jsonCameraStructure.size(); i++) {
            json camInfo = jsonCameraStructure[i];
            Vector3D viewDir, position;
            position = camInfo["position"];
            if (!camInfo["lookatPoint"].empty()) {
                Vector3D lookAtPoint;
                lookAtPoint = camInfo["lookatPoint"];
                viewDir = lookAtPoint - position;
            }
            else {
	      viewDir = camInfo["viewDir"];
            }
            float focalLength = camInfo["focalLength"];
            float imagePlaneWidth = camInfo["imagePlaneWidth"];
            string camType = camInfo["_type"];
            if (camType == "perspective") {
             allCameras.push_back( new PerspectiveCamera(focalLength, imagePlaneWidth, position, viewDir, 300, 300) );
            }                                                                            
	}
    }

    /**Shaders*/
    cout << "Number of shaders: " << j["scene"]["shader"].size() << std::endl;
    for (auto i=0; i<j["scene"]["shader"].size(); i++) {
        json shaderInfo = j["scene"]["shader"][i];
        string shaderType = shaderInfo["_type"];
        Shader *shaderPtr = nullptr;
        if (shaderType == "Lambertian") {
            Vector3D diffuse;
            diffuse = shaderInfo["diffuse"];
            cout << "Diffuse = " << diffuse <<endl;
            ShaderCoefficient kd(diffuse, 0);
            shaderPtr = new LambertianShader(kd);  
        }
        else if (shaderType == "BlinnPhong" || shaderType == "Phong") {
            float phongExp;
            sivelab::Vector3D diffuse, specular;
            diffuse = shaderInfo["diffuse"];
            specular = shaderInfo["specular"];
            phongExp = shaderInfo["phongExp"];
            ShaderCoefficient kd(diffuse, 0);
            ShaderCoefficient ks(specular, 0);
            if (shaderType == "BlinnPhong"){
	      shaderPtr = new BlinnPhong(kd, ks, phongExp);
	    }
            else
	      cout<<"Not supported yet";
	      //shaderPtr = new Phong(diffuse, specular, phongExp);
	}
	else if (shaderType == "Mirror") {
	  shaderPtr = new MirrorShade();
        }
        string name = shaderInfo["_name"];
        shaderPtr->setName(name);
	allShaders[name] = shaderPtr;
    }
    
    /**Shapes*/
    cout << "Number of shapes: " << j["scene"]["shape"].size() << endl;    
    for (auto i=0; i<j["scene"]["shape"].size(); i++) {
        json shapeInfo = j["scene"]["shape"][i];
        Shape *sPtr = nullptr;
        string type = shapeInfo["_type"];
        string name = shapeInfo["_name"];
        if (type == "sphere") {
	    float radius;
            Vector3D center;
            center = shapeInfo["center"];
            radius = shapeInfo["radius"];
            sPtr = new Sphere(center, radius);
        }
        else if (type == "triangle") { 
	  Vector3D v0, v1, v2;
          v0 = shapeInfo["v0"];
          v1 = shapeInfo["v1"];
          v2 = shapeInfo["v2"];
          sPtr = new Triangle(v0, v1, v2);
	}
	else if (type == "box") {
	  sivelab::Vector3D minPt, maxPt;
	  minPt = shapeInfo["minPt"];
	  maxPt = shapeInfo["maxPt"];
	  sPtr = new Box(minPt, maxPt);
	}
	sPtr->provideShader(locateShader(shapeInfo["shader"]["_ref"]));
        allShapes.push_back( sPtr );
	
    }

    // Walk over all lights
    cout << "Number of lights: " << j["scene"]["light"].size() << endl;
    for (auto i=0; i<j["scene"]["light"].size(); i++) {
      string type = j["scene"]["light"][i]["_type"];
      Vector3D position, radiantEnergy;
      position = j["scene"]["light"][i]["position"];
      radiantEnergy = j["scene"]["light"][i]["intensity"];
      if ( type == "point" ){
	allLights.push_back(new PointLight(position, radiantEnergy));
      }
      else if(type == "area"){
	  Vector3D normal;
	  normal = j["scene"]["light"][i]["normal"];
	  float width = 1.0, length = 1.0;
          width = j["scene"]["light"][i]["width"];
          length = j["scene"]["light"][i]["length"];
	  allLights.push_back(new AreaLight(position, radiantEnergy, normal, width, length) );
	}
    }

}


bool SceneContainer::visibilityQuery (Ray &r, float tmin, float tmax, hitStruct &hit){
  for(int i = 0; i < allShapes.size(); i++){
    if(allShapes[i]->intersect(r, tmin, tmax, hit)){
      return true;
      }
  }
  return false;
}
