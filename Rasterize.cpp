#include "Rasterize.h"
#include "Matrix.h"

void Rasterize::image(string fileName){

  float r = w/2;

  Matrix4x4 Mp, Mperspective, Mmodel, Mvp, Mlocal;

  Matrix4x4 Mcam, M;
  Vector3D v, vcam, vs;
  Triangle t;
  
  Matrix4x4 Mortho(
  for(int i = 0; i < shapePtr.size()){
    //for all triangles
    
    M = Mvp * Mortho * Mp;
    //Mmodel(); initialize model matrix
    
    //for(triangle vertices v)

    //camera space shading
    vcam = Mcam * Mlocal * v;
    for(int j = 0; j < lightPtr.size()){
      lightPtr[j].position = Mcam * lightPtr[j].position;
    }

    //pervertex shading
    //v.attribute.vertexShadeColor = Lambertian.apply();

    //screen space
    vs = M * vcam;
    
    vs[0] = v[0]/w; //perspective divide;
    vs[1] = v[1]/w;
    vs[2] = v[2]/w;

    float alpha, beta, gamma;
    for (int x = t.min[0]; x <= t.max[0]; x++){
      for (int y = t.min[1]; y <= t.max[1]; y++){

	  //alpha = f12(x,y) / f12(x0,y0) 
	  //beta = f20(x,y) / f20(x1,y1) 
	  //gamma =  f01(x,y) / f01(x2,y2) 
	  if (alpha > 0 && beta > 0 && gamma > 0){
	    // barycentric interpolation of color
	    Vector3D c = sTri[0].c*alpha + sTri[1].c*beta + sTri[2].c*gamma;
	    //fb.setPixel(x, y, c);
	    if (x > 0 && y > 0) && (x < nx && y < ny){
		// barycentric interpolation of depth at the fragment
		//float depth = sTri[0].p[2]*alpha + sTri[1].p[2]*beta + sTri[2].p[2]*gamma;
		//if (depth < depthBuffer(x, y)) {
		//        colorBuffer(x,y) = c;
		//        depthBuffer(x,y) = depth;
		//}
	      }
	  }
      }
    }
  
  }

};

