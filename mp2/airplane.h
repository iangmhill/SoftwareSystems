#ifndef AIRPLANE_H_
#define AIRPLANE_H_

#include "geometry.h"

class Airplane {
  Point position;
  Vector forward, up, right;
  double speed;
public:
  Airplane(Point initialPosition = Point(0, 0, 0));
  Point getPosition() {return position;}
  void fly() {position += speed * forward;}
  void teleport(Point newPosition) {position = newPosition;}
  Vector getDirection() {return forward;}
  Vector getVertical() {return up;}
  void pitch(double angle);
  void roll(double angle);
  void yaw(double angle);
  double getSpeed() {return speed;}
  void setSpeed(double newSpeed) {speed = newSpeed;}
};

inline Airplane::Airplane(Point initialPosition):
  position(initialPosition),
  forward(0, 0, -1),
  up(0, 1, 0),
  right(1, 0, 0),
  speed(0.01)
{
}

inline void Airplane::pitch(double angle) {
  forward = unit(forward * cos(angle) + up * sin(angle));
  up = right.cross(forward);
}

inline void Airplane::roll(double angle) {
  right = unit(right * cos(angle) + up * sin(angle));
  up = right.cross(forward);
}

inline void Airplane::yaw(double angle) {
  right = unit(right * cos(angle) + forward * sin(angle));
  forward = up.cross(right);
}

#endif