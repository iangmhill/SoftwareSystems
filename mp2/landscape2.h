#ifndef LANDSCAPE_H_
#define LANDSCAPE_H_

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <cstdlib>

class Landscape {
  int rows;
  int columns;
  double highest;                         // the highest point in the mesh
  std::vector< std::vector<double>  > d;  // the grid of elevations
  int solidId;                            // display list id for solid mesh
  int wireFrameId;                        // display list id for wire mesh
  static double unused;
  double scale(double x) {return x * (((double)rand()/RAND_MAX) - 0.5);}
public:
  Landscape(int rows, int columns);
  void create(double rug);
  void draw() {glCallList(solidId);}
  void drawWireFrame() {}
};

#endif