#include "CoordinateSystem.h"


/**Default Constructor*/
CoordinateSystem::CoordinateSystem(){
  uVec = Vector3D(1, 0, 0);
  vVec = Vector3D(0, 1, 0);
  wVec = Vector3D(0, 0, 1);
}

CoordinateSystem::CoordinateSystem(const Vector3D &viewDir){
  wVec = viewDir * -1.0;
  wVec.normalize();

  Vector3D t = wVec;
  if(fabs(t.dot(wVec)) < 1.001 && fabs(t.dot(wVec)) > 0.9999){
    int lowest = 0;
    for(int i = 0; i < 3; i++){
      t[i] = fabs(t[i]);
      if(t[i] <= t[lowest]){
	lowest = i;
      }
    }
    t[lowest] = 1;
  }
  
  uVec = t.cross(wVec);
  uVec.normalize();
  
  vVec = wVec.cross(uVec);
  vVec.normalize();
}

/** \Constructor                                                                                                                        
 *                                                                                                                                      
 * wVector = -viewDirection (look the correct way)                                                                                       * normalize that wVector                                                                              
 *                                                                                                                      
 * check to see if it is colinear (dot product = 1)                                                                                      * if it is, chose another random tempUp                    
 *                                                                         
 * uVector = tempUp crossed with wVector (left hand rule)                                                                                * normalize it
 * vVector = wVector crossed with uVector                                   
 * normalize it
 *
 * @params viewDirection Vector3D, temporaryUp Vector3D
 */
CoordinateSystem::CoordinateSystem(const Vector3D &viewDir, Vector3D &tempUp){
  wVec = viewDir* -1.0;
  wVec.normalize();

  Vector3D newTemp = Vector3D(1, 0, 0);
  if(fabs(tempUp.dot(wVec)) < 1.001 && fabs(tempUp.dot(wVec)) > 0.9999){
    tempUp = newTemp;
     }
  
  uVec = tempUp.cross(wVec);
  uVec.normalize();
  
  vVec = wVec.cross(uVec);
  vVec.normalize();
}
