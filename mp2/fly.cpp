#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "airplane.h"
#include "landscape.h"
#include <iostream>

// A landscape to fly around, with some parameters that are manipuated by the
// program.
Landscape landscape(200, 143);

// Wireframe view or solid view?
static bool wireframe = false;

void newLandscape() {
  static double rug = ((double)rand()) / RAND_MAX;
  landscape.create(rug);
}

// A ship and some functions to control it: Later, we need to add a ship
// controller class so even the navigation controls are pluggable.
static Airplane theAirplane(Point(60, 40, 220));

void keyboard(unsigned char key, int, int) {
  const double deltaSpeed = 0.01;
  const double angle = 0.02;
  switch(key) {
    case '2': theAirplane.setSpeed(theAirplane.getSpeed() + deltaSpeed); break;
    case '3': theAirplane.setSpeed(theAirplane.getSpeed() - deltaSpeed); break;
    case 'f': wireframe = !wireframe; break;
    case 'r': newLandscape();
    case 'q': theAirplane.roll(angle); break;
    case 'e': theAirplane.roll(-angle); break;
    case 'a': theAirplane.yaw(angle); break;
    case 'd': theAirplane.yaw(-angle); break;
    case 's': theAirplane.pitch(-angle); break;
    case 'w': theAirplane.pitch(angle);  break;
  }
}

// Display and Animation: To draw we just clear the window and draw the scene.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible.  Animation is achieved by successively moving
// the ship and drawing.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  wireframe ? landscape.drawWireFrame() : landscape.draw();
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

// Move the ship one step, recompute the view, and ask to redisplay.
void timer(int v) {
  theAirplane.fly();
  Point eye(theAirplane.getPosition());
  Point at(theAirplane.getPosition() + theAirplane.getDirection());
  Vector up(theAirplane.getVertical());
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.i, up.j, up.k);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

// Reshape callback: Make the viewport take up the whole window, recompute the
// camera settings to match the new window shape, and go back to modelview
// matrix mode.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.05, 300.0);
  glMatrixMode(GL_MODELVIEW);
}

// init(): Initialize GLUT and enter the GLUT event loop.
void init() {
  srand(9903);
  glEnable(GL_DEPTH_TEST);
  newLandscape();
  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat dark[] = { 0.2, 0.15, 0.2, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 0.2, 1.0, 0.5, 0.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);

  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
}

// Writes some trivial help text to the console.
void writeHelpToConsole() {
  std::cout << "q/e = roll left / right\n";
  std::cout << "s/w - pitch down / up\n";
  std::cout << "a/d - yaw left / right\n";
  std::cout << "2/3 - speed up / slow down\n";
  std::cout << "f - toggle wireframe mode\n";
  std::cout << "r - generate a new landscape\n";
}

// main(): Initialize GLUT and enter the GLUT event loop.
int main(int argc, char** argv) {
  writeHelpToConsole();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(780, 500);
  glutCreateWindow("Simple Flight");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
}
