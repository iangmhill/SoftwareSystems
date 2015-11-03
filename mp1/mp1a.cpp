// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

// Set this to true to animate.
static bool spinning = true;

// This is the number of frames per second to render.
static const int FPS = 60;

// State of the system
static GLfloat currentAngleOfRotation = 0.0;

static GLfloat color = 0.0;

static float scale = 2.0;

// Clears the current window and draws a triangle.
void display() {

  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0);

  // Drawing is done by specifying a sequence of vertices.  The way these
  // vertices are connected (or not connected) depends on the argument to
  // glBegin.  GL_POLYGON constructs a filled polygon.
  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-.6,1.);
    glVertex2f(.6,1.);
    glVertex2f(-.2,.6);
    glVertex2f(.2,.6);
    glVertex2f(-.2,-.6);
    glVertex2f(.2,-.6);
    glVertex2f(-.6,-1.);
    glVertex2f(.6,-1.);
  glEnd();

  glBegin(GL_TRIANGLES);
    glColor3f(0, 0, color);
    glVertex2f(-.6,1.);
    glVertex2f(-.6,.6);
    glVertex2f(-.2,.6);
    glVertex2f(-.2,-.6);
    glVertex2f(-.6,-.6);
    glVertex2f(-.6,-1.);
    glVertex2f(.6,-1.);
    glVertex2f(.6,-.6);
    glVertex2f(.2,-.6);
    glVertex2f(.2,.6);
    glVertex2f(.6,.6);
    glVertex2f(.6,1.);
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
  glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  GLfloat aspect = (GLfloat)w / (GLfloat)h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h) {
    // width is smaller, go from -50 .. 50 in width
    glOrtho(-scale, scale, -scale/aspect, scale/aspect, -1.0, 1.0);
  } else {
    // height is smaller, go from -50 .. 50 in height
    glOrtho(-scale*aspect, scale*aspect, -scale, scale, -1.0, 1.0);
  }
}

void timer(int v) {
  if (spinning) {
    currentAngleOfRotation += 1.0;
    if (currentAngleOfRotation > 360.0) {
      currentAngleOfRotation -= 360.0;
    }
    color = 0.5*sin(currentAngleOfRotation*(3.1415/180)) + 0.5;
    glutPostRedisplay();
  }
  glutTimerFunc(1000/FPS, timer, v);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {

  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Spinning I");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glutDisplayFunc(display);

  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.
  glutMainLoop();
}